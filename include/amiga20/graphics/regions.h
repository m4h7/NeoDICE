#ifndef	GRAPHICS_REGIONS_H
#define	GRAPHICS_REGIONS_H
/*
**	$Filename: graphics/regions.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 37.0 $
**	$Date: 91/01/07 $
**
**
**
**	(C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

struct RegionRectangle
{
    struct RegionRectangle *Next,*Prev;
    struct Rectangle bounds;
};

struct Region
{
    struct Rectangle bounds;
    struct RegionRectangle *RegionRectangle;
};

#endif	/* GRAPHICS_REGIONS_H */
