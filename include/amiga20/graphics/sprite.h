#ifndef	GRAPHICS_SPRITE_H
#define	GRAPHICS_SPRITE_H
/*
**	$Filename: graphics/sprite.h $
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

#define SPRITE_ATTACHED 0x80

struct SimpleSprite
{
    UWORD *posctldata;
    UWORD height;
    UWORD   x,y;    /* current position */
    UWORD   num;
};

#endif	/* GRAPHICS_SPRITE_H */
