#ifndef GRAPHICS_GFXBASE_H
#define GRAPHICS_GFXBASE_H
/*
**	$Filename: graphics/gfxbase.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 37.3 $
**	$Date: 91/04/15 $
**
**	graphics base definitions
**
**	(C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif

struct GfxBase
{
    struct Library  LibNode;
    struct View *ActiView;
    struct copinit *copinit;	/* ptr to copper start up list */
    long    *cia;		/* for 8520 resource use */
    long    *blitter;		/* for future blitter resource use */
    UWORD   *LOFlist;
    UWORD   *SHFlist;
    struct bltnode *blthd,*blttl;
    struct bltnode *bsblthd,*bsblttl;
    struct Interrupt vbsrv,timsrv,bltsrv;
    struct List     TextFonts;
    struct  TextFont *DefaultFont;
    UWORD  Modes;			/* copy of current first bplcon0 */
    BYTE VBlank;
    BYTE Debug;
    WORD BeamSync;
    WORD system_bplcon0;	/* it is ored into each bplcon0 for display */
    UBYTE   SpriteReserved;
    UBYTE   bytereserved;
    UWORD   Flags;
    WORD   BlitLock;
	WORD	BlitNest;

	struct	List	BlitWaitQ;
	struct	Task	*BlitOwner;
	struct	List	TOF_WaitQ;
	UWORD	DisplayFlags;		/* NTSC PAL GENLOC etc*/
					/* flags initialized at power on */
	struct SimpleSprite **SimpleSprites;
	UWORD	MaxDisplayRow;		/* hardware stuff, do not use */
	UWORD	MaxDisplayColumn;	/* hardware stuff, do not use */
	UWORD	NormalDisplayRows;
	UWORD	NormalDisplayColumns;
	/* the following are for standard non interlace, 1/2 wb width */
	UWORD	NormalDPMX;		/* Dots per meter on display */
	UWORD	NormalDPMY;		/* Dots per meter on display */
	struct	SignalSemaphore *LastChanceMemory;
	UWORD	*LCMptr;
	UWORD	MicrosPerLine;		/* 256 time usec/line */
	UWORD	MinDisplayColumn;
	UBYTE	ChipRevBits0;
	UBYTE	crb_reserved[5];
	UWORD	monitor_id;		/* normally null */
	ULONG	hedley[8];
	ULONG	hedley_sprites[8] ;	/* sprite ptrs for intuition mouse */
	ULONG	hedley_sprites1[8] ;		/* sprite ptrs for intuition mouse */
	WORD	hedley_count;
	UWORD	hedley_flags;
	WORD	hedley_tmp;
	LONG	*hash_table;
	UWORD	current_tot_rows;
	UWORD	current_tot_cclks;
	UBYTE	hedley_hint;
	UBYTE	hedley_hint2;
	ULONG	nreserved[4];
	LONG	*a2024_sync_raster;
	WORD   control_delta_pal;
	WORD   control_delta_ntsc;
	struct	MonitorSpec *current_monitor;
	struct	List MonitorList;
	struct	MonitorSpec *default_monitor;
	struct	SignalSemaphore *MonitorListSemaphore;
	VOID	*DisplayInfoDataBase;
	WORD	lapad;			/* alignment */
	struct	SignalSemaphore *ActiViewCprSemaphore;
	ULONG	*UtilityBase;		/* for hook and tag utilities	*/
	ULONG	*ExecBase;		/* to link with rom.lib	*/
	};

#define NTSC		1
#define GENLOC		2
#define PAL		4
#define TODA_SAFE	8

#define BLITMSG_FAULT	4

/* bits defs for ChipRevBits */
#define	GFXB_BIG_BLITS	0
#define	GFXB_HR_AGNUS	0
#define GFXB_HR_DENISE	1

#define GFXF_BIG_BLITS	1
#define	GFXF_HR_AGNUS	1
#define GFXF_HR_DENISE	2

#define GRAPHICSNAME	"graphics.library"

#endif	/* GRAPHICS_GFXBASE_H */
