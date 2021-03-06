/**
 * @file string.h
 * @brief defined string function
 * @author simpart
 */
#ifndef __TTR_STRING_H__
#define __TTR_STRING_H__

/*** include ***/
#include <string.h>

/*** define ***/
#define TTRSTR_SPMAX_LEN 256
#define TTRSTR_KEYLEN 64

#define TTRSTR_RET_NOSPCHR 100
#define TTRSTR_RET_MAXIDX  101
/*** struct ***/

/*** prototype ***/
int ttrstr_split   (const char *, char, unsigned int, char *);
int ttrstr_filquot (const char *, char *, size_t);

/*** macro ***/
#define __ttrstr_atoi(num, str)            \
    num = atoi(str);                       \
    if ( (0 == num) && ('0' != str[0]) ) { \
        __ttrdbg_err("failed atoi");       \
        return TTR_NG;                     \
    }

#define __ttrstr_iskey(key, chk) if (0 == strncmp(key, chk, TTRSTR_KEYLEN))
#define __ttrstr_init(s)  memset(s, 0x00, sizeof(s))

#define __ttrstr_len(str, len)                  \
    __ttr_chkerr_value(strnlen(str, len), 0);   \
    __ttr_chkerr_value(strnlen(str, len), len); \
    strnlen(str, len)

#endif
/* end of file */
