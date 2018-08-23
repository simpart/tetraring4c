/**
 * @file split.c
 * @brief split string function
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/check.h"
#include "ttr/memory.h"
#include "ttr/string.h"

/*** function ***/
int ttrstr_split (const char *str, char sp, uint idx, char *out) {
    
    __ttrchk_nullprm2(str, out);
    
    /* get string length */
    int len = strnlen(str, TTRSTR_SPMAX_LEN);
    __ttrchk_strlen(len, TTRSTR_SPMAX_LEN);
    
    /* split string */
    uint sp_cnt   = 0;
    int  sp_idx   = 0;
    char *ret_buf = (char *) ttrmem_malloc(len);
    __ttrchk_nullval(ret_buf, "faild malloc");
    
    __ttr_loop_i(len) {
        
        /* buffering return value */
        *(ret_buf + sp_idx) = *(str+i);
        
        /* check split char */
        if (sp == *(str+i)) {
            if (idx == sp_cnt) {
                *(ret_buf + sp_idx) = '\0';
                strncpy(out, ret_buf, len);
                __ttrmem_free(ret_buf);
                return TTR_OK;
            } else {
                memset(ret_buf, 0x00, len);
                sp_idx = -1;
            }
            sp_cnt++;
        }
        sp_idx++;
    }

    if (idx == sp_cnt) {
        *(ret_buf + sp_idx) = '\0';
        strncpy(out, ret_buf, len);
        __ttrmem_free(ret_buf);
        return TTR_OK;
    } else {
        *out = '\0';
        __ttrchk_free(ret_buf);
        return (0 == sp_cnt) ? TTRSTR_RET_NOSPCHR : TTRSTR_RET_MAXIDX;
    }
}

/* end of file */
