/**
 * @file trycatch.h
 * @brief defined try-catch function
 * @author simpart
 */

#ifndef __TTR_TRYCATCH_H__
#define __TTR_TRYCATCH_H__

/*** include ***/

/*** define ***/
#define __ttr_try
#define __ttr_catch TTR_CATCH:
#define __ttr_throwcheck if (TTR_TRUE == ttr_isthrew()) goto TTR_CATCH;

/*** struct ***/

/*** prototype ***/
int  ttr_isthrew         (void);
void ttr_throw_exception (char *);

/*** macro ***/

#endif
/* end of file */
