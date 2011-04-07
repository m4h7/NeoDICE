/*
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

/*
 *  DAS     Minimal assembler and peephole optimizer for DCC
 *
 *	    -doesn't understand include or IF constructions
 *	    -only understands decimal and $ hex
 *	    -only understands +, -, and negate
 *
 *  DAS infile [-o outfile] -O[optlevel]
 */

/*
**      $Filename: main.c $
**      $Author: dice $
**      $Revision: 30.326 $
**      $Date: 1995/12/24 06:12:49 $
**      $Log: main.c,v $
 * Revision 30.326  1995/12/24  06:12:49  dice
 * .
 *
 * Revision 30.5  1994/06/13  18:41:10  dice
 * .
 *
 * Revision 30.0  1994/06/10  18:07:44  dice
 * .
 *
 * Revision 1.2  1993/09/19  20:55:01  jtoebes
 * Fixed BUG06033 - DAS does not report original C source line numbers.
 * Changed format of error message to take into account a C file present.
 * Also respect the error formatting codes so that it is parsed by the editor.
 *
 * Revision 1.1  1993/09/19  19:56:59  jtoebes
 * Initial revision
 *
**/

#include "defs.h"
#include "DAS_rev.h"

static char *DCopyright =
"Copyright (c) 1992,1993,1994 Obvious Implementations Corp., Redistribution & Use under DICE-LICENSE.TXT." VERSTAG;


Prototype char	  *AsBuf;
Prototype long	  AsLen;
Prototype long	  MLines;
Prototype long	  LineNo;
Prototype short   AddSym;
Prototype short   DDebug;
Prototype short   Optimize;
Prototype short   NoUnitName;
Prototype short   Verbose;
Prototype short   ErrorOpt;
Prototype FILE	  *ErrorFi;
Prototype MachCtx **MBase;
Prototype FILE	  *Fo;
Prototype char	  *FoName;
Prototype long	  ExitCode;
Prototype char	  *SrcFileName;
Prototype char	  *AsmFileName;

Prototype int	main(int, char **);
Prototype void	DebugPass(char);
Prototype void	*zalloc(long);
Prototype void	help(void);
Prototype short CToSize(char);
Prototype void	Filter(void);

#ifndef DEBUG
#define DebugPass(x)
#endif

char	*AsBuf;
long	AsLen;
long	MLines;
long	LineNo;
short   AddSym;
short	DDebug;
short	NoUnitName;
short	Optimize;
short	Verbose;
short	ErrorOpt;
FILE	*ErrorFi;
MachCtx **MBase;
FILE	*Fo;	    /*	used on error exit to close file  */
char	*FoName;    /*	used on error exit to delete file */
char	*AsmFileName;
char	*SrcFileName;
long	ExitCode;

int
main(int ac, char **av)
{
    char *inFile = NULL;
    char *outFile = NULL;
    short i;

    if (ac == 1)
	help();

    for (i = 1; i < ac; ++i) {
	char *ptr = av[i];
	if (*ptr != '-') {
	    inFile = ptr;
	    AsmFileName = ptr;
	    if (SrcFileName == NULL)
		SrcFileName = ptr;
	    continue;
	}
	ptr += 2;
	switch(ptr[-1]) {
	case 'n':
	    switch(*ptr) {
	    case 'u':
		NoUnitName = 1;
		break;
	    }
	    break;
	case 'v':
	    Verbose = 1;
	    break;
	case 'd':
	    DDebug = 1;
	    break;
	case 's':
	    AddSym = 1;
	    break;
	case 'O':
	    Optimize = atoi((*ptr) ? ptr : av[++i]);
	    break;
	case 'E':
	    ErrorOpt = 1;
	    if (*ptr == 'E')
		ErrorOpt = 2;
	    else if ((*ptr >= '0') && (*ptr <= '9'))
 		ErrorOpt = *ptr - '0';

	    ptr = av[++i];
	    ErrorFi = fopen(ptr, "a");
	    break;
	case 'N':
	    if (*ptr == 0)
		ptr = av[++i];
	    SrcFileName = ptr;
	    break;
	case 'o':
	    outFile = (*ptr) ? ptr : av[++i];
	    break;
	default:
	    help();
	}
    }
    if (inFile == NULL) {
	cerror(EERROR_NO_INPUT_FILE);
	help();
    }
    if (outFile == NULL) {
	i = strlen(inFile);
	outFile = malloc(i + 5);
	strcpy(outFile, inFile);
	for (--i; i >= 0 && outFile[i] != '.'; --i);
	if (outFile[i] == '.')
	    strcpy(outFile + i + 1, "o");
	else
	    strcat(outFile, ".o");
    }
    {
	FILE *fi = fopen(inFile, "r");
	if (fi == NULL)
	    cerror(EFATAL_CANT_OPEN_FILE, inFile);
	fseek(fi, 0L, 2);
	AsLen = ftell(fi);
	if (AsLen <= 0)
	    cerror(EFATAL_CANT_SEEK_INPUT);
	AsBuf = malloc(AsLen + 2);
	if (AsBuf == NULL)
	    NoMemory();
	fseek(fi, 0L, 0);
	if (fread(AsBuf, 1, AsLen, fi) != AsLen)
	    cerror(EFATAL_READ_ERROR);
	AsBuf[AsLen++] = '\n';  /*  make sure it ends in a newline  */
	AsBuf[AsLen] = 0;
	fclose(fi);
    }
    /*
     *	Allocate a machine context structure for each line
     */
    {
	long i;
	long lines = 0;
	for (i = 0; AsBuf[i]; ++i) {
	    if (AsBuf[i] == '\n')
		++lines;
	}
	MBase = malloc((lines + 3) * sizeof(MachCtx *));
	if (MBase == NULL)
	    NoMemory();
    }

    InitAlNumAry();
    InitOps();
    InitSect();

    Filter();

    DebugPass('a');
    PassA();	    /*	Loads MachCtx & resolves directives	*/
    DebugPass('b');
    PassB();	    /*	resolves addressing modes (expressions) */
    DebugPass('x');
    ResetSectAddrs();
    DebugPass('c');
    PassC();	    /*	optimize!   */
    ResetSectAddrs();
    DebugPass('g');
    PassG();	   /*  generate code		       */
    DebugPass('s');
    {
	FILE *fo = fopen(outFile, "w");
	if (fo == NULL)
	    cerror(EFATAL_CANT_CREATE_FILE, outFile);
	Fo = fo;
	FoName = outFile;
	SectCreateObject(fo, inFile);
	fclose(fo);
	Fo = NULL;
    }
    if (ExitCode > 5 && FoName)
	remove(FoName);
    return(ExitCode);
}

#ifdef DEBUG

void
DebugPass(c)
char c;
{
    dbprintf(0, ("PASS %c\n", c));
}

#endif

void *
zalloc(bytes)
long bytes;
{
    static char *Buf;
    static long Bytes;

    if (bytes <= Bytes) {
	void *ptr;

	ptr = (void *)Buf;
	Buf += bytes;
	Bytes -= bytes;
	return(ptr);
    }
    if (bytes > 128) {
	void *ptr;

	ptr = malloc(bytes);
	if (ptr == NULL) {
	    NoMemory();
	}
	setmem(ptr, bytes, 0);
	return(ptr);
    }
    Buf = malloc(ZALLOCSIZ);
    if (Buf == NULL) {
        NoMemory();
    }
    Bytes = ZALLOCSIZ;

    setmem(Buf, Bytes, 0);

    Buf += bytes;
    Bytes -= bytes;
    return(Buf - bytes);
}

void
help()
{
    printf("%s\n%s\n", VSTRING, DCopyright);
    cerror(EVERB_INTRO1);
    cerror(EVERB_INTRO2);
    exit(5);
}

short
CToSize(char c)
{
    switch(c|0x20) {
    case 'b':
    case 's':
	return(1);
    case 'w':
	return(2);
    case 'l':
	return(4);
    }
    cerror(EERROR_ILLEGAL_SIZE, c);
    return(0);
}

void
Filter()
{
    char *ptr = AsBuf;

    while (*ptr) {
	if (*ptr == '\"') {
	    for (++ptr; *ptr != '\n' && *ptr != '\"'; ++ptr);
	    ++ptr;
	} else if (*ptr == '\'') {
	    for (++ptr; *ptr != '\n' && *ptr != '\''; ++ptr);
	    ++ptr;
	} else if (*ptr == ';') {
	    while (*ptr != '\n')
		*ptr++ = ' ';
	    ++ptr;
	} else {
	    ++ptr;
	}
    }
}

