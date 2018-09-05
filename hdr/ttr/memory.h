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
char * ttrmem_strmloc(char *, size_t);
void   ttrmem_free(void **);

/*** macro ***/
#define __ttrmem_ninit(t, n) memset(t, 0x00, n)
#define __ttrmem_init(t)     __ttrmem_ninit(t, sizeof(t))

#define __ttrmem_malloc(t, v, s)        \
    t v = (t) ttrmem_malloc(s);         \
    __ttrchk_nullval(v, "failed malloc")

    
#define __ttrmem_free(f) ttrmem_free((void **) &f)
#define __ttrmem_free2(f1, f2) __ttrmem_free(f1); __ttrmem_free(f2)
#define __ttrmem_free3(f1, f2, f3) __ttrmem_free(f1); __ttrmem_free(f2); __ttrmem_free(f3)

#endif
/* end of file */
