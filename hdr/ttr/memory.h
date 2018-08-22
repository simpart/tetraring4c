/**
 * @file memory.h
 * @brief defined memory function
 * @author simpart
 */
#ifndef __TTR_MEMORY_H__
#define __TTR_MEMORY_H__

/*** include ***/

/*** define ***/

/*** struct ***/

/*** prototype ***/
void * ttrmem_malloc(size_t);
void   ttrmem_free(void **);

/*** macro ***/
#define TTRMEM_FREE(f) ttrmem_free((void **) &f)

#endif
/* end of file */
