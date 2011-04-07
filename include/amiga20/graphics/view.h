#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H
/*
**	$Filename: graphics/view.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 37.0 $
**	$Date: 91/01/07 $
**
**	graphics view/viewport definintions
**
**	(C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#define ECS_SPECIFIC

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#ifndef GRAPHICS_COPPER_H
#include <graphics/copper.h>
#endif

#ifndef GRAPHICS_GFXNODES_H
#include <graphics/gfxnodes.h>
#endif

#ifndef GRAPHICS_MONITOR_H
#include <graphics/monitor.h>
#endif

#ifndef HARDWARE_CUSTOM_H
#include <hardware/custom.h>
#endif

struct ViewPort
{
   struct   ViewPort *Next;
   struct   ColorMap  *ColorMap;    /* table of colors for this viewport */
		  /* if this is nil, MakeVPort assumes default values */
   struct   CopList  *DspIns;	    /* user by MakeView() */
   struct   CopList  *SprIns;	    /* used by sprite stuff */
   struct   CopList  *ClrIns;	    /* used by sprite stuff */
   struct   UCopList *UCopIns;	    /* User copper list */
   WORD    DWidth,DHeight;
   WORD    DxOffset,DyOffset;
   UWORD    Modes;
   UBYTE	SpritePriorities;		/* used by makevp */
   UBYTE	ExtendedModes;
   struct   RasInfo *RasInfo;
};

struct View
{
   struct ViewPort *ViewPort;
   struct cprlist *LOFCprList;	 /* used for interlaced and noninterlaced */
   struct cprlist *SHFCprList;	 /* only used during interlace */
   WORD DyOffset,DxOffset;   /* for complete View positioning */
			      /* offsets are +- adjustments to standard #s */
   UWORD   Modes;	      /* such as INTERLACE, GENLOC */
};

/* these structures are obtained via GfxNew */
/* and disposed by GfxFree */
struct ViewExtra
{
	struct ExtendedNode n;
	struct View *View;	 /* backwards link */
	struct MonitorSpec *Monitor; /* monitors for this view */
};

/* this structure is obtained via GfxNew */
/* and disposed by GfxFree */
struct ViewPortExtra
{
	struct ExtendedNode n;
	struct ViewPort *ViewPort;	/* backwards link */
	struct Rectangle DisplayClip;  /* makevp display clipping information */
};

#define EXTEND_VSTRUCT	0x1000	/* unused bit in Modes field of View */

/* defines used for Modes in IVPargs */

#define GENLOCK_VIDEO	0x0002
#define LACE		0x0004
#define SUPERHIRES	0x0020
#define PFBA		0x0040
#define EXTRA_HALFBRITE 0x0080
#define GENLOCK_AUDIO	0x0100
#define DUALPF		0x0400
#define HAM		0x0800
#define EXTENDED_MODE	0x1000
#define VP_HIDE	0x2000
#define SPRITES	0x4000
#define HIRES		0x8000

#define VPF_A2024		0x40
#define VPF_AGNUS		0x20
#define VPF_TENHZ		0x20

struct RasInfo	/* used by callers to and InitDspC() */
{
   struct   RasInfo *Next;	    /* used for dualpf */
   struct   BitMap *BitMap;
   WORD    RxOffset,RyOffset;	   /* scroll offsets in this BitMap */
};

struct ColorMap
{
	UBYTE	Flags;
	UBYTE	Type;
	UWORD	Count;
	APTR	ColorTable;
	struct	ViewPortExtra *cm_vpe;
	UWORD	*TransparencyBits;
	UBYTE	TransparencyPlane;
	UBYTE	reserved1;
	UWORD	reserved2;
	struct	ViewPort *cm_vp;
	APTR	NormalDisplayInfo;
	APTR	CoerceDisplayInfo;
	struct	TagItem *cm_batch_items;
	ULONG	VPModeID;
};

/* if Type == 0 then ColorMap is V1.2/V1.3 compatible */
/* if Type != 0 then ColorMap is V36	   compatible */

#define COLORMAP_TYPE_V1_2	0x00
#define COLORMAP_TYPE_V1_4	0x01
#define COLORMAP_TYPE_V36 COLORMAP_TYPE_V1_4	/* use this definition */

/* Flags variable */
#define COLORMAP_TRANSPARENCY	0x01
#define COLORPLANE_TRANSPARENCY	0x02
#define BORDER_BLANKING		0x04
#define BORDER_NOTRANSPARENCY	0x08
#define VIDEOCONTROL_BATCH	0x10
#define USER_COPPER_CLIP	0x20

#endif	/* GRAPHICS_VIEW_H */
