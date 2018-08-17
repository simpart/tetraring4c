/**
 * @file debug.c
 * @brief common debug print function
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ttr/com.h"
#include "ttr/chain.h"
#include "ttr/debug.h"

/*** global ***/
int g_ttrdbg_chain = TTRCHN_ID_INIT;

/*** function  ***/
void ttrdbg_set (int line, const char *file, int lv, const char *str) {
    ttrdbg_conts_t * conts = NULL;
    char * lv_str[]  = {
        "emergency",
        "alert"    ,
        "critical" ,
        "error"    ,
        "warning"  ,
        "notice"   ,
        "info"     ,
        "debug"
    };

    /* parameter check */
    if ( (NULL == file) ||
         (NULL == str)  ||
         (TTRDBG_LV_EMER > lv) ||
         (TTRDBG_LV_DEBG < lv) ) {
        return;
    }
    
    /* init check */
    if (TTRCHN_ID_INIT == g_ttrdbg_chain) {
        /* create chain */
        g_ttrdbg_chain = ttrchn_create();
        if (TTR_NG == g_ttrdbg_chain) {
            return;
        }
    }
    
    /* create contents */
    conts = (ttrdbg_conts_t *) malloc(sizeof(ttrdbg_conts_t));
    if (NULL == conts) {
        return;
    }
    memset(conts, 0x00, sizeof(ttrdbg_conts_t));
    /* set level */
    conts->lv = lv;
    /* set string */
    snprintf(
        &(conts->str[0]) ,
        TTRDBG_STRSIZ    ,
        "[%ld][%s] %s (%s >> %d)\n",
        time(NULL)       ,
        lv_str[lv-0x100] ,
        str              ,
        file             ,
        line
    );
    
    /* add to chain */
    ttrchn_add(g_ttrdbg_chain, conts);
}

ttrchn_t * ttrdbg_get (void) {
    if (TTRCHN_ID_INIT == g_ttrdbg_chain) {
        g_ttrdbg_chain = ttrchn_create();
        if (TTR_NG == g_ttrdbg_chain) {
            return NULL;
        }
    }
    return ttrchn_gethead(g_ttrdbg_chain);
}

void ttrdbg_print (void) {
    ttrdbg_lvprint(TTRDBG_LV_ALL);
}

void ttrdbg_lvprint (int lv) {
    int len = ttrchn_len(g_ttrdbg_chain);
    ttrdbg_conts_t * conts = NULL;
    
    for (;len >= 0;len--) {
        conts = (ttrdbg_conts_t *) ttrchn_get(g_ttrdbg_chain, len);
        if (NULL != conts) {
            if ( (TTRDBG_LV_ALL == lv) ||
                 (conts->lv     == lv) ) {
                printf("%s", conts->str);
            }
        }
    }
}

void ttrdbg_free () {
    ttrchn_free (g_ttrdbg_chain);
}
/* end of file */
