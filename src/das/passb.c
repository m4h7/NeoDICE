/*
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

/*
 *  PASSB.C
 *
 *  Everything has been resolved into opcodes, properly placed in their
 *  section, and all EQU and REG directives have been figured out.  We
 *  can now scan the list and resolve the addressing modes.
 *
 *  XDEFd labels must be added to the appropriate section list
 */

/*
**      $Filename: passb.c $
**      $Author: dice $
**      $Revision: 30.0 $
**      $Date: 1994/06/10 18:07:45 $
**      $Log: passb.c,v $
 * Revision 30.0  1994/06/10  18:07:45  dice
 * .
 *
 * Revision 1.1  1993/09/19  19:56:46  jtoebes
 * Initial revision
 *
**/

#include "defs.h"

Prototype void	PassB(void);

void
PassB()
{
    MachCtx **pmc;
    MachCtx *mc;
    OpCod   *oc;
    char    *str;
    long i;
    long addr = 0;

    pmc = MBase;
    for (i = 0; i < MLines; ++i) {
	mc = *pmc++;
	LineNo = mc->LineNo;
	mc->m_Addr = addr;
	if (mc->Label)
	    mc->Label->l_Offset = addr;
	if ((oc = mc->OpCode) == NULL)
	    continue;
	if (oc->Id < 0) {
	    addr = ExecOpCodeB(mc, addr);
	    continue;
	}

	if (oc->Id >= LIMIT68000 && MC68020 == 0)
	    cerror(EWARN_68020);

	str = mc->m_Operands;

	if (mc->OpSize == 1) {
	    mc->Oper1.ISize |= ISF_INSTBYTE;
	    mc->Oper2.ISize |= ISF_INSTBYTE;
	}
	if (*str) {
	    str = ParseEffAddr(str, &mc->Oper1);
	}
	if (*str == ',') {
	    str = ParseEffAddr(str + 1, &mc->Oper2);
	}
	dbprintf(0, ("%s %s,%s\n", oc->OpName, EAToString(&mc->Oper1), EAToString(&mc->Oper2)));
	while (*str == ' ' || *str == 9)
	    ++str;
	if (*str)
	    cerror(EWARN_GARBAGE, str);

	/*
	 *  Find a valid op code for the addressing modes.  Remember
	 *  to check the secondary Modes.
	 *
	 *  note: ok of Mode1/2 is 0, bit 0 not used in modes bits.
	 */

	{
	    long mc10= (1 << mc->Oper1.Mode1);
	    long mc1 = mc10 | (1 << mc->Oper1.Mode2);
	    long mc20= (1 << mc->Oper2.Mode1);
	    long mc2 = mc20 | (1 << mc->Oper2.Mode2);

	    for (; oc; oc = oc->SibNext) {
		{
		    if (mc->OpSize && (oc->Sizes & (1 << mc->OpSize)) == 0)
			continue;
		}

		if (oc->SModes && oc->DModes) {
		    if ((oc->SModes & mc1) && (oc->DModes & mc2)) {
			if ((oc->SModes & mc10) == 0)    /*  secondary */
			    mc->Oper1.Mode1 = mc->Oper1.Mode2;
			if ((oc->DModes & mc20) == 0)   /*  secondary */
			    mc->Oper2.Mode1 = mc->Oper2.Mode2;
			break;
		    }
		} else if (oc->SModes) {
		    if (oc->SModes & mc1) {
			if ((oc->SModes & mc10) == 0)    /*  secondary */
			    mc->Oper1.Mode1 = mc->Oper1.Mode2;
			break;
		    }
		} else if (oc->DModes) {
		    if (oc->DModes * mc1) {
			if ((oc->DModes & mc10) == 0)   /*  secondary */
			    mc->Oper1.Mode1 = mc->Oper1.Mode2;
			mc->Oper2 = mc->Oper1;		/*  copy so matches oc */
			mc->Oper1.Mode1 = 0;		/*  turn off oper2     */
			mc->Oper1.Label1 = NULL;	/*  so passg doesn't get confused */
			break;
		    }
		} else {
		    if (mc->Oper1.Mode1)
			cerror(EERROR_TAKES_NO_OPS, oc->OpName);
		    break;
		}
	    }
	    if (oc == NULL)
		cerror(EERROR_ILLEGAL_ADDR_MODES, mc->Oper1.Mode1, mc->Oper2.Mode1, mc->OpCode->OpName);
	    mc->OpCode = oc;
	}

	/*
	 *  check for subroutine calls and references to A5 for passC.
	 *  note, register check assumes Oper*.Reg1 zero when non-register
	 *  modes are used.
	 */

        if (oc)
        {
            if (oc->Id == OpBSR || oc->Id == OpJSR)
                SetSubroutineCallFlag();

            if (oc->B_Rs >= 0 && mc->Oper1.Reg1 == RB_AREG+5 && oc->Id != OpLINK)
                SetA5UsedFlag();
            if (oc->B_Rd >= 0 && mc->Oper2.Reg1 == RB_AREG+5 && oc->Id != OpUNLK)
                SetA5UsedFlag();
	}

	addr += GetInstSize(mc);
    }
}


