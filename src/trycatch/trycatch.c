/**
 * @file trycatch.c
 * @author simpart
 */
/*** include ***/
#include "ttr/com.h"
#include "ttr/trycatch.h"
#include "ttr/check.h"

int gttr_throwflg = TTR_FALSE;

int ttr_isthrew (void) {
    return gttr_throwflg;
}

void ttr_throw_exception(char *msg) {
    gttr_throwflg = TTR_TRUE;
    
    __ttrchk_nullskip(msg);
    
    __ttrdbg_err(msg);
}
/* end of file */
