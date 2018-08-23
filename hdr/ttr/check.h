/**
 * @file   check.h
 * @brief  defined check function
 * @author simpart
 */
#ifndef __TTR_CHECK_H__
#define __TTR_CHECK_H__

/*** include ***/
#include "ttr/debug.h"

/*** define ***/
#define TTRCHN_ID_INIT -1
#define TTRCHN_ID_MNG  -100

/*** struct ***/

/*** prototype ***/

/*** macro ***/
#define __ttrchk_nullval(p, msg) \
    if (NULL == p) {             \
        __ttrdbg_err(msg);       \
        return TTR_NG;           \
    }

#define __ttrchk_nullprm(p)               \
    if (NULL == p) {                      \
       __ttrdbg_err("invalid parameter"); \
       return TTR_NG;                     \
    }

#define __ttrchk_nullprm2(p1, p2)          \
    if ((NULL == p1) || (NULL == p2)) {    \
        __ttrdbg_err("invalid parameter"); \
        return TTR_NG;                     \
    }

#define __ttrchk_signprm(p)                \
    if (0 > p) {                           \
        __ttrdbg_err("invalid parameter"); \
        return TTR_NG;                     \
    }

#define __ttrchk_strlen(l, m)                  \
    if ((0 == l) || (m == l)) {                \
        __ttrdbg_err("invalid string length"); \
        return TTR_NG;                         \
    }

#define __ttrchk_strnlen(str, len) ttrchk_strlen(strnlen(str,len),len)

#define __ttrchk_less(v, l, msg) \
    if (l > v) {                 \
        __ttrdbg_err(msg);       \
        return TTR_NG;           \
    }

#define __ttrchk_less_goto(v, l, msg, lbl) \
    if (l > v) {                           \
        __ttrdbg_err(msg);                 \
        goto lbl;                          \
    }

#define __ttrchk_equal(r, ng, msg)  \
    if (r == ng) {                  \
        __ttrdbg_err(msg);          \
        return TTR_NG;              \
    }

#define __ttrchk_equal_goto(r, ng, msg, lbl) \
    if (r == ng) {                           \
        __ttrdbg_err(msg);                   \
        goto lbl;                            \
    }

#define __ttrchk_not(ret, cmp, msg)  \
    if (ret != cmp) {                \
        __ttrdbg_err(msg);           \
        return TTR_NG;               \
    }

#define __ttrchk_not_goto(ret, cmp, msg, lbl) \
    if (ret != cmp) {                         \
    __ttrdbg_err(msg);                        \
    goto lbl;                                 \
}

#define __ttrchk_retng(ret) __ttrchk_equal(ret, TTR_NG, "error return value")

#define __ttrchk_retng_goto(ret, lbl) __ttrchk_equal_goto(ret, TTR_NG, "error return value", lbl)

#define __ttrchk_notok(ret) __ttrchk_not(ret, TTR_OK, "error return value")

#define __ttrchk_notok_goto(ret, lbl) __ttrchk_not_goto(ret, TTR_OK, "error return value", lbl)

#define __ttrchk_lange(tgt, st, end)        \
    if ( !((st <= tgt) && (end >= tgt)) ) { \
        __ttrdbg_err("invalid lange");      \
        return TTR_NG;                      \
    }

#endif
/* end of file */
