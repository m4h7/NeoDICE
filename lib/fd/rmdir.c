
/*
 *  RMDIR.C
 *
 *    (c)Copyright 1992-1997 Obvious Implementations Corp.  Redistribution and
 *    use is allowed under the terms of the DICE-LICENSE FILE,
 *    DICE-LICENSE.TXT.
 */

#include <stdio.h>
#include <stdlib.h>

int
rmdir(name)
char *name;
{
    return(remove(name));
}

