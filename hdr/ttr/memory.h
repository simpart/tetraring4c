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
#define __ttrmem_strinit(s)  memset(s, 0x00, sizeof(s))
#define __ttrmem_ninit(t, n) memset(t, 0x00, n)
#define __ttrmem_init(t)     __ttrmem_ninit(t, sizeof(t))

#define __ttrmem_malloc(t, v, s)        \
    t v = (t) ttrmem_malloc(s);         \
    __ttrchk_nullval(v, "failed malloc")

#define __ttrmem_strmloc(nm, src)     \
    __ttrchk_strlen(strnlen(src), 32) \
    __ttrmem_malloc(char *, nm, strnlen(src, 32)+1 )
    
#define __ttrmem_free(f) ttrmem_free((void **) &f)

#endif
/* end of file */
