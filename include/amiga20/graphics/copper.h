#ifndef GRAPHICS_COPPER_H
#define GRAPHICS_COPPER_H
/*
**	$Filename: graphics/copper.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 37.0 $
**	$Date: 91/01/07 $
**
**	graphics copper list intstruction definintions
**
**	(C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define COPPER_MOVE 0	    /* pseude opcode for move #XXXX,dir */
#define COPPER_WAIT 1	    /* pseudo opcode for wait y,x */
#define CPRNXTBUF   2	    /* continue processing with next buffer */
#define CPR_NT_LOF  0x8000  /* copper instruction only for short frames */
#define CPR_NT_SHT  0x4000  /* copper instruction only for long frames */
#define CPR_NT_SYS  0x2000  /* copper user instruction only */

struct CopIns
{
    WORD   OpCode; /* 0 = move, 1 = wait */
    union
    {
    struct CopList *nxtlist;
    struct
    {
   union
   {
   WORD   VWaitPos;	   /* vertical beam wait */
   WORD   DestAddr;	   /* destination address of copper move */
   } u1;
   union
   {
   WORD   HWaitPos;	   /* horizontal beam wait position */
   WORD   DestData;	   /* destination immediate data to send */
   } u2;
    } u4;
    } u3;
};
/* shorthand for above */
#define NXTLIST     u3.nxtlist
#define VWAITPOS    u3.u4.u1.VWaitPos
#define DESTADDR    u3.u4.u1.DestAddr
#define HWAITPOS    u3.u4.u2.HWaitPos
#define DESTDATA    u3.u4.u2.DestData


/* structure of cprlist that points to list that hardware actually executes */
struct cprlist
{
    struct cprlist *Next;
    UWORD   *start;	    /* start of copper list */
    WORD   MaxCount;	   /* number of long instructions */
};

struct CopList
{
    struct  CopList *Next;  /* next block for this copper list */
    struct  CopList *_CopList;	/* system use */
    struct  ViewPort *_ViewPort;    /* system use */
    struct  CopIns *CopIns; /* start of this block */
    struct  CopIns *CopPtr; /* intermediate ptr */
    UWORD   *CopLStart;     /* mrgcop fills this in for Long Frame*/
    UWORD   *CopSStart;     /* mrgcop fills this in for Short Frame*/
    WORD   Count;	   /* intermediate counter */
    WORD   MaxCount;	   /* max # of copins for this block */
    WORD   DyOffset;	   /* offset this copper list vertical waits */
#ifdef V1_3
    UWORD   *Cop2Start;
    UWORD   *Cop3Start;
    UWORD   *Cop4Start;
    UWORD   *Cop5Start;
#endif
};

struct UCopList
{
    struct UCopList *Next;
    struct CopList  *FirstCopList; /* head node of this copper list */
    struct CopList  *CopList;	   /* node in use */
};

/* private graphics data structure */

struct copinit
{
    UWORD vsync_hblank[2];
    UWORD diwstart[4];
    UWORD diagstrt[4];	    /* copper list for first bitplane */
    UWORD sprstrtup[(2*8*2)];
    UWORD wait14[2];
    UWORD norm_hblank[2];
    UWORD genloc[4];
    UWORD jump[(2*2)];
    UWORD wait_forever[2];
    UWORD   sprstop[4];
};

#endif	/* GRAPHICS_COPPER_H */
