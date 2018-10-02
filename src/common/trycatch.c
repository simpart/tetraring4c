/**
 * @file trycatch.c
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "ttr/com.h"
//#include "ttr/com/errmsg.h"

ttr_trychctl_st gttr_tchctl;

void ttr_tchinit (void) {
    memset(&gttr_tchctl, 0x00, sizeof(ttr_trychctl_st));
}

void ttr_setcatsts(ttr_catsts_en sts) {
    gttr_tchctl.sts = sts;
}
//int ttr_iserr (void) {
//    
//    //if (TTR_TRUE == gttr_throwflg) {
//    //    ttr_dbgset(file, line, TTR_DBGLV_ERR, "detect threw error"); 
//    //}
//    return gttr_throwflg;
//}

void ttr_throwerr(const char *file, int line, char *msg) {
    
    __ttr_nullskip2(file, msg);
    line = line;
    
    strncpy(&gttr_tchctl.errmsg[0], msg, TTR_TCHMSG_LEN-1);
    
    //if (TTREN_CATSTS_INCAT == gttr_tchctl.sts) {
    //    gttr_tchctl.sts = TTREN_CATSTS_INCATERR;
    //}
    //ttr_dbgset(file, line, TTR_DBGLV_ERR, msg);
}
/* end of file */
