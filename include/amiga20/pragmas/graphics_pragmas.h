/* "graphics.library"*/
/*------ BitMap primitives ------*/
#pragma libcall GfxBase BltBitMap 1E A76543291080B
#pragma libcall GfxBase BltTemplate 24 5432910808
/*------ Text routines ------*/
#pragma libcall GfxBase ClearEOL 2A 901
#pragma libcall GfxBase ClearScreen 30 901
#pragma libcall GfxBase TextLength 36 08903
#pragma libcall GfxBase Text 3C 08903
#pragma libcall GfxBase SetFont 42 8902
#pragma libcall GfxBase OpenFont 48 801
#pragma libcall GfxBase CloseFont 4E 901
#pragma libcall GfxBase AskSoftStyle 54 901
#pragma libcall GfxBase SetSoftStyle 5A 10903
/*------	Gels routines ------*/
#pragma libcall GfxBase AddBob 60 9802
#pragma libcall GfxBase AddVSprite 66 9802
#pragma libcall GfxBase DoCollision 6C 901
#pragma libcall GfxBase DrawGList 72 8902
#pragma libcall GfxBase InitGels 78 A9803
#pragma libcall GfxBase InitMasks 7E 801
#pragma libcall GfxBase RemIBob 84 A9803
#pragma libcall GfxBase RemVSprite 8A 801
#pragma libcall GfxBase SetCollision 90 98003
#pragma libcall GfxBase SortGList 96 901
#pragma libcall GfxBase AddAnimOb 9C A9803
#pragma libcall GfxBase Animate A2 9802
#pragma libcall GfxBase GetGBuffers A8 09803
#pragma libcall GfxBase InitGMasks AE 801
/*------	General graphics routines ------*/
#pragma libcall GfxBase DrawEllipse B4 3210905
#pragma libcall GfxBase AreaEllipse BA 3210905
#pragma libcall GfxBase LoadRGB4 C0 09803
#pragma libcall GfxBase InitRastPort C6 901
#pragma libcall GfxBase InitVPort CC 801
#pragma libcall GfxBase MrgCop D2 901
#pragma libcall GfxBase MakeVPort D8 9802
#pragma libcall GfxBase LoadView DE 901
#pragma libcall GfxBase WaitBlit E4 0
#pragma libcall GfxBase SetRast EA 0902
#pragma libcall GfxBase Move F0 10903
#pragma libcall GfxBase Draw F6 10903
#pragma libcall GfxBase AreaMove FC 10903
#pragma libcall GfxBase AreaDraw 102 10903
#pragma libcall GfxBase AreaEnd 108 901
#pragma libcall GfxBase WaitTOF 10E 0
#pragma libcall GfxBase QBlit 114 901
#pragma libcall GfxBase InitArea 11A 09803
#pragma libcall GfxBase SetRGB4 120 3210805
#pragma libcall GfxBase QBSBlit 126 901
#pragma libcall GfxBase BltClear 12C 10903
#pragma libcall GfxBase RectFill 132 3210905
#pragma libcall GfxBase BltPattern 138 432108907
#pragma libcall GfxBase ReadPixel 13E 10903
#pragma libcall GfxBase WritePixel 144 10903
#pragma libcall GfxBase Flood 14A 102904
#pragma libcall GfxBase PolyDraw 150 80903
#pragma libcall GfxBase SetAPen 156 0902
#pragma libcall GfxBase SetBPen 15C 0902
#pragma libcall GfxBase SetDrMd 162 0902
#pragma libcall GfxBase InitView 168 901
#pragma libcall GfxBase CBump 16E 901
#pragma libcall GfxBase CMove 174 10903
#pragma libcall GfxBase CWait 17A 10903
#pragma libcall GfxBase VBeamPos 180 0
#pragma libcall GfxBase InitBitMap 186 210804
#pragma libcall GfxBase ScrollRaster 18C 543210907
#pragma libcall GfxBase WaitBOVP 192 801
#pragma libcall GfxBase GetSprite 198 0802
#pragma libcall GfxBase FreeSprite 19E 001
#pragma libcall GfxBase ChangeSprite 1A4 A9803
#pragma libcall GfxBase MoveSprite 1AA 109804
#pragma libcall GfxBase LockLayerRom 1B0 D01
#pragma libcall GfxBase UnlockLayerRom 1B6 D01
#pragma libcall GfxBase SyncSBitMap 1BC 801
#pragma libcall GfxBase CopySBitMap 1C2 801
#pragma libcall GfxBase OwnBlitter 1C8 0
#pragma libcall GfxBase DisownBlitter 1CE 0
#pragma libcall GfxBase InitTmpRas 1D4 09803
#pragma libcall GfxBase AskFont 1DA 8902
#pragma libcall GfxBase AddFont 1E0 901
#pragma libcall GfxBase RemFont 1E6 901
#pragma libcall GfxBase AllocRaster 1EC 1002
#pragma libcall GfxBase FreeRaster 1F2 10803
#pragma libcall GfxBase AndRectRegion 1F8 9802
#pragma libcall GfxBase OrRectRegion 1FE 9802
#pragma libcall GfxBase NewRegion 204 0
#pragma libcall GfxBase ClearRectRegion 20A 9802
#pragma libcall GfxBase ClearRegion 210 801
#pragma libcall GfxBase DisposeRegion 216 801
#pragma libcall GfxBase FreeVPortCopLists 21C 801
#pragma libcall GfxBase FreeCopList 222 801
#pragma libcall GfxBase ClipBlit 228 65432910809
#pragma libcall GfxBase XorRectRegion 22E 9802
#pragma libcall GfxBase FreeCprList 234 801
#pragma libcall GfxBase GetColorMap 23A 001
#pragma libcall GfxBase FreeColorMap 240 801
#pragma libcall GfxBase GetRGB4 246 0802
#pragma libcall GfxBase ScrollVPort 24C 801
#pragma libcall GfxBase UCopperListInit 252 0802
#pragma libcall GfxBase FreeGBuffers 258 09803
#pragma libcall GfxBase BltBitMapRastPort 25E 65432910809
#pragma libcall GfxBase OrRegionRegion 264 9802
#pragma libcall GfxBase XorRegionRegion 26A 9802
#pragma libcall GfxBase AndRegionRegion 270 9802
#pragma libcall GfxBase SetRGB4CM 276 3210805
#pragma libcall GfxBase BltMaskBitMapRastPort 27C A6543291080A
/*--- (2 function slots reserved here) ---*/
#pragma libcall GfxBase AttemptLockLayerRom 28E D01
/*--- functions in V36 or higher (distributed as Release 2.0) ---*/
#pragma libcall GfxBase GfxNew 294 001
#pragma libcall GfxBase GfxFree 29A 801
#pragma libcall GfxBase GfxAssociate 2A0 9802
#pragma libcall GfxBase BitMapScale 2A6 801
#pragma libcall GfxBase ScalerDiv 2AC 21003
#pragma libcall GfxBase TextExtent 2B2 A08904
#pragma libcall GfxBase TextFit 2B8 321BA08908
#pragma libcall GfxBase GfxLookUp 2BE 801
#pragma libcall GfxBase VideoControl 2C4 9802
#pragma libcall GfxBase OpenMonitor 2CA 0902
#pragma libcall GfxBase CloseMonitor 2D0 801
#pragma libcall GfxBase FindDisplayInfo 2D6 001
#pragma libcall GfxBase NextDisplayInfo 2DC 001
/*pragma libcall GfxBase graphicsPrivate1 2E2 0*/
/*pragma libcall GfxBase graphicsPrivate2 2E8 0*/
/*pragma libcall GfxBase graphicsPrivate3 2EE 0*/
#pragma libcall GfxBase GetDisplayInfoData 2F4 2109805
#pragma libcall GfxBase FontExtent 2FA 9802
#pragma libcall GfxBase ReadPixelLine8 300 9A210806
#pragma libcall GfxBase WritePixelLine8 306 9A210806
#pragma libcall GfxBase ReadPixelArray8 30C 9A3210807
#pragma libcall GfxBase WritePixelArray8 312 9A3210807
#pragma libcall GfxBase GetVPModeID 318 801
#pragma libcall GfxBase ModeNotAvailable 31E 001
#pragma libcall GfxBase WeighTAMatch 324 A9803
#pragma libcall GfxBase EraseRect 32A 3210905
#pragma libcall GfxBase ExtendFont 330 9802
#pragma libcall GfxBase StripFont 336 801
