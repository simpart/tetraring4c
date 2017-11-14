/**
 * @file error.c
 * @brief common debug print function
 * @author simpart
 */

/*** include ***/
#include <stdio.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/error.h"

/*** global ***/
int g_ttrerr_init = TTR_FALSE;
ttrerr_dbginf_t g_ttrerr_dbg[TTRERR_BUFCNT];

/*** function  ***/
void ttrerr_setdbg (int line, const char *file, const char *conts) {
    ttrerr_dbginf_t cmp;
    int idx = 0;
    int hit = TTR_FALSE;
    
    memset(&cmp, 0x00, sizeof(ttrerr_dbginf_t));
    
    if (TTR_FALSE == g_ttrerr_init) {
        memset(&(g_ttrerr_dbg[0]), 0x00, sizeof(ttrerr_dbginf_t) * TTRERR_BUFCNT);
        g_ttrerr_init = TTR_TRUE;
    }
    
    for (idx=0; idx < TTRERR_BUFCNT ;idx++) {
        if (0 == memcmp(&(g_ttrerr_dbg[idx]), &cmp, sizeof(ttrerr_dbginf_t))) {
            g_ttrerr_dbg[idx].line = line;
            strncpy(
                &(g_ttrerr_dbg[idx].file[0]),
                file,
                TTRERR_FLNSIZ
            );
            strncpy(
                &(g_ttrerr_dbg[idx].conts[0]),
                conts,
                TTRERR_CNTSIZ
            );
            hit = TTR_TRUE;
            break;
        }
    }

#ifdef TTR_ERR_DBGMODE
    if (TTR_TRUE == hit) {
        ttrerr_elmprint(&g_ttrerr_dbg[idx]);
    }
#endif
    
}

void ttrerr_elmprint (ttrerr_dbginf_t *elm) {
    if (NULL == elm) {
        return;
    }
    printf("error : ");
    printf("%s (%s >> %u)", elm->conts, elm->file, elm->line);
    printf("\n");
}
/* end of file */
