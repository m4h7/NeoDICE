#ifndef DOS_EXALL_H
#define DOS_EXALL_H
/*
**
**	$Filename: dos/exall.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 36.5 $
**	$Date: 90/07/12 $
**
**	include file for ExAll() data structures
**
**	(C) Copyright 1989-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
**
*/

#ifndef EXEC_TYPES_H
#include "exec/types.h"
#endif

#ifndef UTILITY_HOOKS_H
#include "utility/hooks.h"
#endif

/* values that can be passed for what data you want from ExAll() */
/* each higher value includes those below it (numerically)	 */
/* you MUST chose one of these values */
#define	ED_NAME		1
#define	ED_TYPE		2
#define ED_SIZE		3
#define ED_PROTECTION	4
#define ED_DATE		5
#define ED_COMMENT	6

/*
 *   Structure in which exall results are returned in.	Note that only the
 *   fields asked for will exist!
 */

struct ExAllData {
	struct ExAllData *ed_Next;
	UBYTE  *ed_Name;
	LONG	ed_Type;
	ULONG	ed_Size;
	ULONG	ed_Prot;
	ULONG	ed_Days;
	ULONG	ed_Mins;
	ULONG	ed_Ticks;
	UBYTE  *ed_Comment;	/* strings will be after last used field */
};

/*
 *   Control structure passed to ExAll.  Unused fields MUST be initialized to
 *   0, expecially eac_LastKey.
 *
 *   eac_MatchFunc is a hook (see utility.library documentation for usage)
 *   It should return true if the entry is to returned, false if it is to be
 *   ignored.
 *
 *   This structure MUST be allocated by AllocDosObject()!
 */

struct ExAllControl {
	ULONG	eac_Entries;	 /* number of entries returned in buffer      */
	ULONG	eac_LastKey;	 /* Don't touch inbetween linked ExAll calls! */
	UBYTE  *eac_MatchString; /* wildcard string for pattern match or NULL */
	struct Hook *eac_MatchFunc; /* optional private wildcard function     */
};

#endif /* DOS_EXALL_H */
