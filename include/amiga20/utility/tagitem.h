#ifndef UTILITY_TAGITEM_H
#define UTILITY_TAGITEM_H TRUE
/*
**	$Filename: utility/tagitem.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 36.1 $
**	$Date: 90/07/12 $
**
**	extended specification mechanism
**
**	(C) Copyright 1989-1991 Commodore-Amiga Inc.
**		All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* ======================================================================= */
/* ====	TagItem	========================================================== */
/* ======================================================================= */
/* This data type may propagate through the system for more general use.
 * In the meantime, it is used as a general mechanism of extensible data
 * arrays for parameter specification and property inquiry (coming soon
 * to a display controller near you).
 *
 * In practice, an array (or chain of arrays) of TagItems is used.
 */

typedef ULONG	Tag;

struct TagItem	{
    Tag		ti_Tag;
    ULONG	ti_Data;
};

/* ----	system tag values -----------------------------	*/
#define TAG_DONE   (0L)	/* terminates array of TagItems. ti_Data unused	*/
#define TAG_END	TAG_DONE
#define	TAG_IGNORE (1L)	/* ignore this item, not end of array		*/
#define	TAG_MORE   (2L)	/* ti_Data is pointer to another array of TagItems
			 * note that this tag terminates the current array
			 */
#define	TAG_SKIP   (3L)	/* skip this and the next ti_Data items		*/

/* ----	user tag identification -----------------------	*/
#define TAG_USER  (1L<<31)    /* differentiates user tags from system tags*/

/* until further notice, tag bits 16-30 are RESERVED and should be zero.
 * Also, the value (TAG_USER | 0) should never be used as a tag value.
 */

/* ---- Tag filter logic specifiers ---- */
#define TAGFILTER_AND	0	/* exclude everything but filter hits	*/
#define TAGFILTER_NOT	1	/* exclude only filter hits		*/

#endif
