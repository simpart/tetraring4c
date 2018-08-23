/**
 * @file memory.h
 * @brief defined memory function
 * @author simpart
 */
#ifndef __TTR_MEMORY_H__
#define __TTR_MEMORY_H__

/*** include ***/
#include "ttr/check.h"

/*** define ***/

/*** struct ***/

/*** prototype ***/
void * ttrmem_malloc(size_t);
void   ttrmem_free(void **);

/*** macro ***/
#define TTRMEM_STRINIT(s)  memset(s, 0x00, sizeof(s))
#define TTRMEM_NINIT(t, n) memset(t, 0x00, n)
#define TTRMEM_INIT(t)     TTRMEM_NINIT(t, sizeof(t))

#define TTRMEM_MALLOC(t, v, s)          \
    t v = (t) ttrmem_malloc(s);         \
    TTRCHK_NULLVAL(v, "failed malloc")

#define TTRMEM_STRMLOC(nm, src) \
    TTRCHK_STRLEN(strnlen(src), 32) \
    TTRMEM_MALLOC(char *, nm, strnlen(src, 32)+1 )
    
#define TTRMEM_FREE(f) ttrmem_free((void **) &f)

#endif
/* end of file */
