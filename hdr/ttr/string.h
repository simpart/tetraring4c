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

/*** macro ***/
#define __ttrstr_atoi(num, str)            \
    num = atoi(str);                       \
    if ( (0 == num) && ('0' != str[0]) ) { \
        __ttrdbg_err("failed atoi");       \
        return TTR_NG;                     \
    }

#endif
/* end of file */
