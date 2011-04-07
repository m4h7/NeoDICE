#ifndef	EXEC_MEMORY_H
#define	EXEC_MEMORY_H
/*
**	$Filename: exec/memory.h $
**	$Release: 2.04 Includes, V37.4 $
**	$Revision: 36.12 $
**	$Date: 91/03/15 $
**
**	Definitions and structures used by the memory allocation system
**
**	(C) Copyright 1985-1991 Commodore-Amiga, Inc.
**	    All Rights Reserved
*/

#ifndef EXEC_NODES_H
#include "exec/nodes.h"
#endif /* EXEC_NODES_H */


/****** MemChunk ****************************************************/

struct	MemChunk {
    struct  MemChunk *mc_Next;	/* pointer to next chunk */
    ULONG   mc_Bytes;		/* chunk byte size	*/
};


/****** MemHeader ***************************************************/

struct	MemHeader {
    struct  Node mh_Node;
    UWORD   mh_Attributes;	/* characteristics of this region */
    struct  MemChunk *mh_First; /* first free region		*/
    APTR    mh_Lower;		/* lower memory bound		*/
    APTR    mh_Upper;		/* upper memory bound+1	*/
    ULONG   mh_Free;		/* total number of free bytes	*/
};


/****** MemEntry ****************************************************/

struct	MemEntry {
union {
    ULONG   meu_Reqs;		/* the AllocMem requirements */
    APTR    meu_Addr;		/* the address of this memory region */
    } me_Un;
    ULONG   me_Length;		/* the length of this memory region */
};

#define me_un	    me_Un	/* compatibility - do not use*/
#define me_Reqs     me_Un.meu_Reqs
#define me_Addr     me_Un.meu_Addr


/****** MemList *****************************************************/

/* Note: sizeof(struct MemList) includes the size of the first MemEntry! */
struct	MemList {
    struct  Node ml_Node;
    UWORD   ml_NumEntries;	/* number of entries in this struct */
    struct  MemEntry ml_ME[1];	/* the first entry	*/
};

#define ml_me	ml_ME		/* compatability - do not use */


/*----- Memory Requirement Types ---------------------------*/
/*----- See the AllocMem() documentation for details--------*/

#define MEMF_ANY    (0L)	/* Any type of memory will do */
#define MEMF_PUBLIC (1L<<0)
#define MEMF_CHIP   (1L<<1)
#define MEMF_FAST   (1L<<2)
#define MEMF_LOCAL  (1L<<8)	/* Memory that does not go away at RESET */
#define MEMF_24BITDMA (1L<<9)	/* DMAable memory within 24 bits of address */

#define MEMF_CLEAR   (1L<<16)	/* AllocMem: NULL out area before return */
#define MEMF_LARGEST (1L<<17)	/* AvailMem: return the largest chunk size */
#define MEMF_REVERSE (1L<<18)	/* AllocMem: allocate from the top down */
#define MEMF_TOTAL   (1L<<19)	/* AvailMem: return total size of memory */

/*----- Current alignment rules for memory blocks (may increase) -----*/
#define MEM_BLOCKSIZE	8L
#define MEM_BLOCKMASK	(MEM_BLOCKSIZE-1)

#endif	/* EXEC_MEMORY_H */
