
/*
 * $VER: lib/version.h 1.0 (17.4.93)
 *
 * (c)Copyright 1992 Obvious Implementations Corp, All Rights Reserved
 */

#ifndef _LIB_VERSION_H
#define _LIB_VERSION_H

#define DICE_VERSION "3"

#ifndef __COMMODORE_DATE__
#define __COMMODORE_DATE__ __DATE__
#endif

#define DCOPYRIGHT static char *DCopyright = "Copyright (c) 1992,1993,1994 Obvious Implementations Corp., Redistribution & Use under DICE-LICENSE.TXT."


/*
 * Messages if commercial, registerd, or neither.  Also set MINIDICE flag
 * if neither.
 */

#ifdef COMMERCIAL
#define IDENT(file,subv)   static char *Ident = "$VER: " file " " DICE_VERSION subv "C (" __COMMODORE_DATE__ ")\n\r"
#define VDISTRIBUTION " Commercial"
#else
#ifdef REGISTERED
#define IDENT(file,subv)   static char *Ident = "$VER: " file " " DICE_VERSION subv "R (" __COMMODORE_DATE__ ")\n\r"
#define VDISTRIBUTION " Registered"
#else
#define IDENT(file,subv)   static char *Ident = "$VER: " file " " DICE_VERSION subv "MINIDICE  (" __COMMODORE_DATE__ ")\n\r"
#define VDISTRIBUTION " MiniDice"
#define MINIDICE
#endif
#endif

#ifdef AMIGA
#define DCC "dcc:"
#define DCC_CONFIG "dcc_config:"
#else
#include "settings.h"
#define DCC NEODICE_PREFIX
#define DCC_CONFIG DCC "config/"
#endif

#ifdef INTELBYTEORDER
extern unsigned long FromMsbOrder(unsigned long);
extern unsigned long ToMsbOrder(unsigned long);
extern unsigned long FromMsbOrderShort(unsigned long);
extern unsigned long ToMsbOrderShort(unsigned long);
#else
#define FromMsbOrder(n)		(n)
#define ToMsbOrder(n)		(n)
#define FromMsbOrderShort(n)	(n)
#define ToMsbOrderShort(n)	(n)
#endif

#endif
