#ifndef INTUITION_SCREENS_H
#define INTUITION_SCREENS_H TRUE
/*
**  $Filename: intuition/screens.h $
**  $Release: 2.04 Includes, V37.4 $
**  $Revision: 36.36 $
**  $Date: 91/10/07 $
**
**  The Screen and NewScreen structures and attributes
**
**  (C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#ifndef GRAPHICS_CLIP_H
#include <graphics/clip.h>
#endif

#ifndef GRAPHICS_VIEW_H
#include <graphics/view.h>
#endif

#ifndef GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif

#ifndef GRAPHICS_LAYERS_H
#include <graphics/layers.h>
#endif

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/*
 * NOTE:  intuition/iobsolete.h is included at the END of this file!
 */

/* ======================================================================== */
/* === DrawInfo ========================================================= */
/* ======================================================================== */

/* This is a packet of information for graphics rendering.  It originates
 * with a Screen, and is gotten using GetScreenDrawInfo( screen );
 */

/* If you find dri_Version >= DRI_VERSION, you know this structure
 * has at least the fields defined in this version of the include file
 */
#define RI_VERSION	(1)	/* obsolete, will be removed		*/
#define DRI_VERSION	(1)

struct DrawInfo
{
    UWORD	dri_Version;	/* will be  DRI_VERSION			*/
    UWORD	dri_NumPens;	/* guaranteed to be >= numDrIPens	*/
    UWORD	*dri_Pens;	/* pointer to pen array			*/

    struct TextFont	*dri_Font;	/* screen default font		*/
    UWORD	dri_Depth;	/* (initial) depth of screen bitmap	*/

    struct {	  /* from DisplayInfo database for initial display mode	*/
	UWORD	X;
	UWORD	Y;
    }		dri_Resolution;

    ULONG	dri_Flags;		/* defined below		*/
    ULONG	dri_Reserved[7];	/* avoid recompilation ;^)	*/
};

#define DRIF_NEWLOOK	0x00000001	/* specified SA_Pens, full treatment */

/* rendering pen number indexes into DrawInfo.dri_Pens[]	*/
#define DETAILPEN	 (0x0000)	/* compatible Intuition rendering pens	*/
#define BLOCKPEN	 (0x0001)	/* compatible Intuition rendering pens	*/
#define TEXTPEN		 (0x0002)	/* text on background			*/
#define SHINEPEN	 (0x0003)	/* bright edge on 3D objects		*/
#define SHADOWPEN	 (0x0004)	/* dark edge on 3D objects		*/
#define FILLPEN		 (0x0005)	/* active-window/selected-gadget fill	*/
#define FILLTEXTPEN	 (0x0006)	/* text over FILLPEN			*/
#define BACKGROUNDPEN	 (0x0007)	/* always color 0			*/
#define HIGHLIGHTTEXTPEN (0x0008)	/* special color text, on background	*/

#define NUMDRIPENS	 (0x0009)


/* ======================================================================== */
/* === Screen ============================================================= */
/* ======================================================================== */
struct Screen
{
    struct Screen *NextScreen;		/* linked list of screens */
    struct Window *FirstWindow;		/* linked list Screen's Windows */

    WORD LeftEdge, TopEdge;		/* parameters of the screen */
    WORD Width, Height;			/* parameters of the screen */

    WORD MouseY, MouseX;		/* position relative to upper-left */

    UWORD Flags;			/* see definitions below */

    UBYTE *Title;			/* null-terminated Title text */
    UBYTE *DefaultTitle;		/* for Windows without ScreenTitle */

    /* Bar sizes for this Screen and all Window's in this Screen */
    /* Note that BarHeight is one less than the actual menu bar
     * height.	We're going to keep this in V36 for compatibility,
     * although V36 artwork might use that extra pixel
     *
     * Also, the title bar height of a window is calculated from the
     * screen's WBorTop field, plus the font height, plus one.
     */
    BYTE BarHeight, BarVBorder, BarHBorder, MenuVBorder, MenuHBorder;
    BYTE WBorTop, WBorLeft, WBorRight, WBorBottom;

    struct TextAttr *Font;		/* this screen's default font	   */

    /* the display data structures for this Screen */
    struct ViewPort ViewPort;		/* describing the Screen's display */
    struct RastPort RastPort;		/* describing Screen rendering	   */
    struct BitMap BitMap;		/* extra copy of RastPort BitMap   */
    struct Layer_Info LayerInfo;	/* each screen gets a LayerInfo    */

    /* Only system gadgets may be attached to a screen.
     *	You get the standard system Screen Gadgets automatically
     */
    struct Gadget *FirstGadget;

    UBYTE DetailPen, BlockPen;		/* for bar/border/gadget rendering */

    /* the following variable(s) are maintained by Intuition to support the
     * DisplayBeep() color flashing technique
     */
    UWORD SaveColor0;

    /* This layer is for the Screen and Menu bars */
    struct Layer *BarLayer;

    UBYTE *ExtData;

    UBYTE *UserData;	/* general-purpose pointer to User data extension */

    /**** Data below this point are SYSTEM PRIVATE ****/
};


/* --- FLAGS SET BY INTUITION --------------------------------------------- */
/* The SCREENTYPE bits are reserved for describing various Screen types
 * available under Intuition.
 */
#define SCREENTYPE	0x000F	/* all the screens types available	*/
/* --- the definitions for the Screen Type ------------------------------- */
#define WBENCHSCREEN	0x0001	/* identifies the Workbench screen	*/
#define PUBLICSCREEN	0x0002	/* public shared (custom) screen	*/
#define CUSTOMSCREEN	0x000F	/* original custom screens		*/

#define SHOWTITLE	0x0010	/* this gets set by a call to ShowTitle() */

#define BEEPING		0x0020	/* set when Screen is beeping (private)	*/

#define CUSTOMBITMAP	0x0040	/* if you are supplying your own BitMap */

#define SCREENBEHIND	0x0080	/* if you want your screen to open behind
				 * already open screens
				 */
#define SCREENQUIET	0x0100	/* if you do not want Intuition to render
				 * into your screen (gadgets, title)
				 */
#define SCREENHIRES	0x0200	/* do not use lowres gadgets  (private)	*/

#define NS_EXTENDED	0x1000		/* ExtNewScreen.Extension is valid	*/
/* V36 applications can use OpenScreenTagList() instead of NS_EXTENDED	*/

#define AUTOSCROLL	0x4000	/* screen is to autoscoll		*/

#define STDSCREENHEIGHT -1	/* supply in NewScreen.Height		*/
#define STDSCREENWIDTH -1	/* supply in NewScreen.Width		*/

/*
 * Screen attribute tag ID's.  These are used in the ti_Tag field of
 * TagItem arrays passed to OpenScreenTagList() (or in the
 * ExtNewScreen.Extension field).
 */

/* Screen attribute tags.  Please use these versions, not those in
 * iobsolete.h.
 */

#define SA_Dummy	(TAG_USER + 32)
/*
 * these items specify items equivalent to fields in NewScreen
 */
#define SA_Left		(SA_Dummy + 0x0001)
#define SA_Top		(SA_Dummy + 0x0002)
#define SA_Width	(SA_Dummy + 0x0003)
#define SA_Height	(SA_Dummy + 0x0004)
			/* traditional screen positions	and dimensions	*/
#define SA_Depth	(SA_Dummy + 0x0005)
			/* screen bitmap depth				*/
#define SA_DetailPen	(SA_Dummy + 0x0006)
			/* serves as default for windows, too		*/
#define SA_BlockPen	(SA_Dummy + 0x0007)
#define SA_Title	(SA_Dummy + 0x0008)
			/* default screen title				*/
#define SA_Colors	(SA_Dummy + 0x0009)
			/* ti_Data is an array of struct ColorSpec,
			 * terminated by ColorIndex = -1.  Specifies
			 * initial screen palette colors.
			 */
#define SA_ErrorCode	(SA_Dummy + 0x000A)
			/* ti_Data points to LONG error code (values below)*/
#define SA_Font		(SA_Dummy + 0x000B)
			/* equiv. to NewScreen.Font			*/
#define SA_SysFont	(SA_Dummy + 0x000C)
			/* Selects one of the preferences system fonts:
			 *	0 - old DefaultFont, fixed-width
			 *	1 - WB Screen preferred font
			 */
#define SA_Type		(SA_Dummy + 0x000D)
			/* equiv. to NewScreen.Type			*/
#define SA_BitMap	(SA_Dummy + 0x000E)
			/* ti_Data is pointer to custom BitMap.  This
			 * implies type of CUSTOMBITMAP
			 */
#define SA_PubName	(SA_Dummy + 0x000F)
			/* presence of this tag means that the screen
			 * is to be a public screen.  Please specify
			 * BEFORE the two tags below
			 */
#define SA_PubSig	(SA_Dummy + 0x0010)
#define SA_PubTask	(SA_Dummy + 0x0011)
			/* Task ID and signal for being notified that
			 * the last window has closed on a public screen.
			 */
#define SA_DisplayID	(SA_Dummy + 0x0012)
			/* ti_Data is new extended display ID from
			 * <graphics/displayinfo.h>.
			 */
#define SA_DClip	(SA_Dummy + 0x0013)
			/* ti_Data points to a rectangle which defines
			 * screen display clip region
			 */
#define SA_Overscan	(SA_Dummy + 0x0014)
			/* was S_STDDCLIP.  Set to one of the OSCAN_
			 * specifiers below to get a system standard
			 * overscan region for your display clip,
			 * screen dimensions (unless otherwise specified),
			 * and automatically centered position (partial
			 * support only so far).
			 * If you use this, you shouldn't specify
			 * SA_DClip.  SA_Overscan is for "standard"
			 * overscan dimensions, SA_DClip is for
			 * your custom numeric specifications.
			 */
#define SA_Obsolete1	(SA_Dummy + 0x0015)
			/* obsolete S_MONITORNAME			*/

/** booleans **/
#define SA_ShowTitle	(SA_Dummy + 0x0016)
			/* boolean equivalent to flag SHOWTITLE		*/
#define SA_Behind	(SA_Dummy + 0x0017)
			/* boolean equivalent to flag SCREENBEHIND	*/
#define SA_Quiet	(SA_Dummy + 0x0018)
			/* boolean equivalent to flag SCREENQUIET	*/
#define SA_AutoScroll	(SA_Dummy + 0x0019)
			/* boolean equivalent to flag AUTOSCROLL	*/
#define SA_Pens		(SA_Dummy + 0x001A)
			/* pointer to ~0 terminated UWORD array, as
			 * found in struct DrawInfo
			 */
#define SA_FullPalette	(SA_Dummy + 0x001B)
			/* boolean: initialize color table to entire
			 *  preferences palette (32 for V36), rather
			 * than compatible pens 0-3, 17-19, with
			 * remaining palette as returned by GetColorMap()
			 */

/* this is an obsolete tag included only for compatibility with V35
 * interim release for the A2024 and Viking monitors
 */
#ifndef NSTAG_EXT_VPMODE
#define NSTAG_EXT_VPMODE (TAG_USER | 1)
#endif


/* OpenScreen error codes, which are returned in the (optional) LONG
 * pointed to by ti_Data for the SA_ErrorCode tag item
 */
#define OSERR_NOMONITOR	(1)	/* named monitor spec not available	*/
#define OSERR_NOCHIPS	(2)	/* you need newer custom chips		*/
#define OSERR_NOMEM	(3)	/* couldn't get normal memory		*/
#define OSERR_NOCHIPMEM	(4)	/* couldn't get chipmem			*/
#define OSERR_PUBNOTUNIQUE (5)	/* public screen name already used	*/
#define OSERR_UNKNOWNMODE (6)	/* don't recognize mode asked for	*/

/* ======================================================================== */
/* === NewScreen ========================================================== */
/* ======================================================================== */
/* note: to use the Extended field, you must use the
 * new ExtNewScreen structure, below
 */
struct NewScreen
{
    WORD LeftEdge, TopEdge, Width, Height, Depth;  /* screen dimensions */

    UBYTE DetailPen, BlockPen;	/* for bar/border/gadget rendering	*/

    UWORD ViewModes;		/* the Modes for the ViewPort (and View) */

    UWORD Type;			/* the Screen type (see defines above)	*/

    struct TextAttr *Font;	/* this Screen's default text attributes */

    UBYTE *DefaultTitle;	/* the default title for this Screen	*/

    struct Gadget *Gadgets;	/* UNUSED:  Leave this NULL		*/

    /* if you are opening a CUSTOMSCREEN and already have a BitMap
     * that you want used for your Screen, you set the flags CUSTOMBITMAP in
     * the Type field and you set this variable to point to your BitMap
     * structure.  The structure will be copied into your Screen structure,
     * after which you may discard your own BitMap if you want
     */
    struct BitMap *CustomBitMap;
};

/*
 * For compatibility reasons, we need a new structure for extending
 * NewScreen.  Use this structure is you need to use the new Extension
 * field.
 *
 * NOTE: V36-specific applications should use the
 * OpenScreenTagList( newscreen, tags ) version of OpenScreen().
 * Applications that want to be V34-compatible as well may safely use the
 * ExtNewScreen structure.  Its tags will be ignored by V34 Intuition.
 *
 */
struct ExtNewScreen
{
    WORD LeftEdge, TopEdge, Width, Height, Depth;
    UBYTE DetailPen, BlockPen;
    UWORD ViewModes;
    UWORD Type;
    struct TextAttr *Font;
    UBYTE *DefaultTitle;
    struct Gadget *Gadgets;
    struct BitMap *CustomBitMap;

    struct TagItem	*Extension;
				/* more specification data, scanned if
				 * NS_EXTENDED is set in NewScreen.Type
				 */
};

/* === Overscan Types ===	*/
#define OSCAN_TEXT	(1)	/* entirely visible	*/
#define OSCAN_STANDARD	(2)	/* just past edges	*/
#define OSCAN_MAX	(3)	/* as much as possible	*/
#define OSCAN_VIDEO	(4)	/* even more than is possible	*/


/* === Public Shared Screen Node ===	*/

/* This is the representative of a public shared screen.
 * This is an internal data structure, but some functions may
 * present a copy of it to the calling application.  In that case,
 * be aware that the screen pointer of the structure can NOT be
 * used safely, since there is no guarantee that the referenced
 * screen will remain open and a valid data structure.
 *
 * Never change one of these.
 */

struct PubScreenNode	{
    struct Node		psn_Node;	/* ln_Name is screen name */
    struct Screen	*psn_Screen;
    UWORD		psn_Flags;	/* below		*/
    WORD		psn_Size;	/* includes name buffer	*/
    WORD		psn_VisitorCount; /* how many visitor windows */
    struct Task		*psn_SigTask;	/* who to signal when visitors gone */
    UBYTE		psn_SigBit;	/* which signal	*/
};

#define PSNF_PRIVATE	(0x0001)

/* NOTE: Due to a bug in NextPubScreen(), make sure your buffer
 * actually has MAXPUBSCREENNAME+1 characters in it!
 */
#define MAXPUBSCREENNAME	(139)	/* names no longer, please	*/

/* pub screen modes	*/
#define SHANGHAI	0x0001	/* put workbench windows on pub screen */
#define POPPUBSCREEN	0x0002	/* pop pub screen to front when visitor opens */


/* Include obsolete identifiers: */
#ifndef INTUITION_IOBSOLETE_H
#include <intuition/iobsolete.h>
#endif

#endif
