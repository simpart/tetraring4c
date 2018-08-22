/**
 * @file calloc.c
 * @brief safaty calloc function
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include <stdlib.h>
#include "ttr/com.h"
#include "ttr/debug.h"

/*** function ***/
void * ttrmem_malloc(size_t siz) {
    void * ret = malloc(siz);
    if (NULL == ret) {
        TTRDBG_EMER("failed malloc");
        ttrdbg_print();
        return NULL;
    }
    memset(ret, 0x00, siz);
    return ret;
}

void ttrmem_free(void ** tgt) {
    if ((NULL == tgt) || (NULL == *tgt)) {
        return;
    }
    free(*tgt);
    *tgt = NULL;
}
/* end of file */
