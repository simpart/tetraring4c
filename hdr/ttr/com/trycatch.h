/**
 * @file trycatch.h
 * @brief defined try-catch function
 * @author simpart
 */
#ifndef __TTR_TRYCATCH_H__
#define __TTR_TRYCATCH_H__

/*** include ***/
#include "ttr/com/util.h"
//extern ttr_trychctl_st gttr_tchctl;

//extern char *gttr_errmsg[256];

/*** define ***/
#define try ttr_tchinit();
//#define try_errmsg        
//    char *errmsg = NULL;  
//    errmsg = errmsg;

#define catch       \
    return;         \
    goto TTR_CATCH; \
    TTR_CATCH:      \
    ttr_setcatsts(TTREN_CATSTS_INCAT);

#define catch_ret(r)  \
    return r;         \
    goto TTR_CATCH;   \
    TTR_CATCH:        \
    ttr_setcatsts(TTREN_CATSTS_INCAT);

#define catch_        \
    goto TTR_FINALLY; \
    goto TTR_CATCH;   \
    TTR_CATCH:        \
    ttr_setcatsts(TTREN_CATSTS_INCAT);

#define finally TTR_FINALLY:

#define TTR_TCHMSG_LEN 256

/*** enum ***/
typedef enum ttr_catsts {
    TTREN_CATSTS_INIT = 0,
    TTREN_CATSTS_INCAT,
    TTREN_CATSTS_INCATERR
} ttr_catsts_en;

/*** struct ***/
typedef struct ttr_trychctl {
    char          errmsg[TTR_TCHMSG_LEN];
    ttr_catsts_en sts;
} ttr_trychctl_st;

/*** prototype ***/
//int  ttr_iserr    (void);
void ttr_throwerr (const char *, int, char *);
void ttr_tchinit  (void);
void ttr_setcatsts(ttr_catsts_en);

extern ttr_trychctl_st gttr_tchctl;

/*** macro ***/
#define $ ;                                                    \
    if ( (0 != strnlen(gttr_tchctl.errmsg, TTR_TCHMSG_LEN)) && \
         (TTREN_CATSTS_INCATERR == gttr_tchctl.sts) ) {        \
        gttr_tchctl.sts = TTREN_CATSTS_INIT;                   \
        goto TTR_CATCH;                                        \
    }

#define __ttr_throwerr_com(msg, prs)             \
    ttr_throwerr(__FILE__, __LINE__, msg);       \
    if (TTREN_CATSTS_INCAT == gttr_tchctl.sts) { \
        gttr_tchctl.sts = TTREN_CATSTS_INCATERR; \
        prs;                                     \
    }                                            \
    goto TTR_CATCH;

#define __ttr_throwerr(msg)                      \
    __ttr_throwerr_com(msg, return;)

#define __ttr_throwerr_ret(msg, ret)             \
    __ttr_throwerr_com(msg, return ret;)

#endif
/* end of file */
