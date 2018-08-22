/**
 * @file string.h
 * @brief defined string function
 * @author simpart
 */
#ifndef __TTR_STRING_H__
#define __TTR_STRING_H__

/*** include ***/

/*** define ***/
#define TTRSTR_SPMAX_LEN 256

#define TTRSTR_RET_NOSPCHR 100
#define TTRSTR_RET_MAXIDX  101
/*** struct ***/

/*** prototype ***/
int ttrstr_split (const char *, char, unsigned int, char *);

#endif
/* end of file */
