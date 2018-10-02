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

/*** global ***/
int g_ttr_dbgchain = TTRCHN_ID_INIT;

/*** function  ***/
void ttr_dbgset (const char *file, int line, int lv, const char *str) {
//    ttr_dbgconts_t * conts = NULL;
//    char * lv_str[]  = {
//        "emergency",
//        "alert"    ,
//        "critical" ,
//        "error"    ,
//        "warning"  ,
//        "notice"   ,
//        "info"     ,
//        "debug"
//    };
//
//    /* parameter check */
//    if ( (NULL == file) ||
//         (NULL == str)  ||
//         (TTR_DBGLV_EMER > lv) ||
//         (TTR_DBGLV_DEBG < lv) ) {
//        return;
//    }
//    
//    /* init check */
//    if (TTRCHN_ID_INIT == g_ttr_dbgchain) {
//        /* create chain */
//        g_ttr_dbgchain = ttrchn_create();
//        if (TTR_NG == g_ttr_dbgchain) {
//            return;
//        }
//    }
//    
//    /* create contents */
//    conts = (ttr_dbgconts_t *) ttr_malloc(sizeof(ttr_dbgconts_t));
//    if (NULL == conts) {
//        return;
//    }
//    
//    /* set level */
//    conts->lv = lv;
//    /* set string */
//    snprintf(
//        &(conts->str[0]) ,
//        TTR_DBGSTR_SIZ    ,
//        "[%ld][%s] %s (%s >> %d)\n",
//        time(NULL)       ,
//        lv_str[lv-0x101] ,
//        str              ,
//        file             ,
//        line
//    );
//    
//    /* add to chain */
//    ttrchn_add(g_ttr_dbgchain, conts);
}

ttrchn_t * ttr_dbgget (void) {
//    if (TTRCHN_ID_INIT == g_ttr_dbgchain) {
//        g_ttr_dbgchain = ttrchn_create();
//        if (TTR_NG == g_ttr_dbgchain) {
            return NULL;
//        }
//    }
//    return ttrchn_gethead(g_ttr_dbgchain);
}

void ttr_dbgprint (void) {
//    ttr_dbglvprint(TTR_DBGLV_ALL);
}

void ttr_dbglvprint (int lv) {
//    int len = ttrchn_len(g_ttr_dbgchain);
//    ttr_dbgconts_t * conts = NULL;
//    
//    for (;len >= 0;len--) {
//        conts = (ttr_dbgconts_t *) ttrchn_get(g_ttr_dbgchain, len);
//        if (NULL != conts) {
//            if ( (TTR_DBGLV_ALL == lv) ||
//                 (conts->lv     == lv) ) {
//                printf("%s", conts->str);
//            }
//        }
//    }
}

void ttr_dbgfree () {
//    ttrchn_free(g_ttr_dbgchain);
}
/* end of file */
