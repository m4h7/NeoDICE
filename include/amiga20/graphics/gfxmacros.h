#ifndef	GRAPHICS_GFXMACROS_H
#define	GRAPHICS_GFXMACROS_H
/*
**	$Filename: graphics/gfxmacros.h $
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

#ifndef  GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif

#define ON_DISPLAY	custom.dmacon = BITSET|DMAF_RASTER;
#define OFF_DISPLAY	custom.dmacon = BITCLR|DMAF_RASTER;
#define ON_SPRITE	custom.dmacon = BITSET|DMAF_SPRITE;
#define OFF_SPRITE	custom.dmacon = BITCLR|DMAF_SPRITE;

#define ON_VBLANK	custom.intena = BITSET|INTF_VERTB;
#define OFF_VBLANK	custom.intena = BITCLR|INTF_VERTB;

#define SetOPen(w,c)	{(w)->AOlPen = c;(w)->Flags |= AREAOUTLINE;}
#define SetDrPt(w,p)	{(w)->LinePtrn = p;(w)->Flags |= FRST_DOT;(w)->linpatcnt=15;}
#define SetWrMsk(w,m)	{(w)->Mask = m;}
#define SetAfPt(w,p,n)	{(w)->AreaPtrn = p;(w)->AreaPtSz = n;}

#define BNDRYOFF(w)	{(w)->Flags &= ~AREAOUTLINE;}

#define CINIT(c,n)	  UCopperListInit(c,n);
#define CMOVE(c,a,b)	{ CMove(c,&a,b);CBump(c); }
#define CWAIT(c,a,b)	{ CWait(c,a,b);CBump(c); }
#define CEND(c)	{ CWAIT(c,10000,255); }

#define DrawCircle(rp,cx,cy,r)	DrawEllipse(rp,cx,cy,r,r);
#define AreaCircle(rp,cx,cy,r)	AreaEllipse(rp,cx,cy,r,r);

#endif	/* GRAPHICS_GFXMACROS_H */
