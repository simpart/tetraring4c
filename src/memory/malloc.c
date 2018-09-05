/**
 * @file calloc.c
 * @brief safaty calloc function
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ttr/com.h"
#include "ttr/string.h"
#include "ttr/debug.h"
#include "ttr/check.h"

/*** function ***/
void * ttrmem_malloc(size_t siz) {
    void * ret = malloc(siz);
    if (NULL == ret) {
        __ttrdbg_emer("failed malloc");
        ttrdbg_print();
        return NULL;
    }
    memset(ret, 0x00, siz);
    return ret;
}

char * ttrmem_strmloc(char *str, size_t max) {
    /* param check */
    if (NULL == str) {
        __ttrdbg_err("invalid parameter");
        return NULL;
    }
    
    /* get string length */
    size_t str_len = strnlen(str, max);
    if (max == str_len) {
        __ttrdbg_err("over max string length");
        return NULL;
    } else if (0 == str_len) {
        __ttrdbg_err("null string");
        return NULL;
    }
    
    char * ret = (char *) ttrmem_malloc(str_len+1);
    strncpy(ret, str, str_len);

    return ret;
}

void ttrmem_free(void ** tgt) {
    if ((NULL == tgt) || (NULL == *tgt)) {
        __ttrdbg_err("invalid parameter");
        return;
    }
    free(*tgt);
    *tgt = NULL;
}
/* end of file */
