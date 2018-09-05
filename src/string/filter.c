/**
 * @file filter.c
 * @brief filter string function
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/check.h"

/*** function ***/
int ttrstr_filquot (const char *str, char *out, size_t len) {
    
    /* param check */
    __ttrchk_nullprm2(str, out);
    
    /* get string length */
    uint str_len = strnlen(str, len);
    __ttrchk_strlen(str_len, len);
    


    if ( ('\'' == str[0] || '"' == str[0]) &&
         ('\'' == str[str_len-1] || '"' == str[str_len-1]) ) {
        strncpy(out, str+1, str_len-2);
        out[str_len-1] = '\0';
    }
    
    return TTR_OK;
}


/* end of file */
