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
#define TTRCHK_NULLVAL(p, msg)  if (NULL == p) { TTRDBG_ERR(msg); return TTR_NG;}
#define TTRCHK_NULLPRM(p)  if (NULL == p) { TTRDBG_ERR("invalid parameter"); return TTR_NG;}
#define TTRCHK_NULLPRM2(p1, p2)  if ((NULL == p1) || (NULL == p2)) { TTRDBG_ERR("invalid parameter"); return TTR_NG; }

#define TTRCHK_STRLEN(l, m)   if ((0 == l) || (m == l)) { TTRDBG_ERR("invalid string length"); return TTR_NG; }

#define TTRCHK_STRNLEN(str, len) TTRCHK_STRLEN(strnlen(str,len),len)

#define TTRCHK_ISLESS(v, l, msg)   if (l > v) { TTRDBG_ERR(msg); return TTR_NG; }
#define TTRCHK_ISLESS_GOTO(v, l, msg, lbl)   if (l > v) { TTRDBG_ERR(msg); goto lbl; }
#define TTRCHK_ISEQUAL(r, ng, msg) if (r == ng) { TTRDBG_ERR(msg); return TTR_NG; }
#define TTRCHK_ISEQUAL_GOTO(r, ng, msg, lbl) if (r == ng) { TTRDBG_ERR(msg); goto lbl; }

#define TTRCHK_LANGE(tgt, st, end) if ( !((st <= tgt) && (end >= tgt)) ) { TTRDBG_ERR("invalid lange"); return TTR_NG; }

#endif
/* end of file */
