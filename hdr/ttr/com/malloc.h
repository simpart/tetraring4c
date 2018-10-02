/**
 * @file malloc.h
 * @brief defined malloc function
 * @author simpart
 */
#ifndef __TTR_MALLOC_H__
#define __TTR_MALLOC_H__

/*** include ***/
#include "ttr/com/util.h"

/*** define ***/

/*** struct ***/

/*** prototype ***/
void * ttr_malloc(size_t);
char * ttr_strmalloc(char *, size_t);
void   ttr_free(void **);

/*** macro ***/
#define __ttr_ninit(t, n) memset(t, 0x00, n)
#define __ttr_init(t)     __ttr_ninit(t, sizeof(t))

#define __ttr_malloc(t, v, s)        \
    t v = (t) ttr_malloc(s);         \
    __ttrchk_nullval(v, "failed malloc")

#define __ttr_free(f) ttr_free((void **) &f)
#define __ttr_free2(f1, f2) __ttr_free(f1); __ttr_free(f2)
#define __ttr_free3(f1, f2, f3) __ttr_free(f1); __ttr_free(f2); __ttr_free(f3)

#endif
/* end of file */
