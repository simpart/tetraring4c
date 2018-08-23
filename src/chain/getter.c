/**
 * @file   ctrl.c
 * @brief  chain main controller
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "ttr/com.h"
#include "ttr/chain.h"
#include "ttr/check.h"

/*** global ***/
extern ttrchn_t *g_ttrchn_mng;

/*** function ***/
void ** ttrchn_first (int cid) {
    
    if (TTRCHN_ID_MNG == cid) {
        /* this cid is management chain */
    }
    
    return NULL;
}

void * ttrchn_get (int cid, int idx) {
    ttrchn_t *tgt = NULL;
    
    tgt = ttrchn_gethead(cid);
    if (NULL == tgt) {
        return NULL;
    }
    
    while (NULL != tgt) {
        if (tgt->idx == (idx+1)) {
            return tgt->conts;
        }
        tgt = tgt->next;
    }
    
    return NULL;
}

void ** ttrchn_find (int cid, void *elm, size_t siz) {
    siz = siz;

    if (NULL == elm) {
        return NULL;
    }
    
    if (TTRCHN_ID_MNG == cid) {
        /* this cid is management chain */
        
    }
    
    return NULL;
}

//ttr_chain_t
void ** ttrchn_last (int cid) {
    ttrchn_t *tgt = NULL;
    
    /* check parameter */
    if (TTRCHN_ID_MNG == cid) {
        /* this cid is management chain */
        
    }
    
    
    
    while (NULL != tgt->next) {
        tgt = (ttrchn_t *) tgt->next;
    }
    
    return &(tgt->conts);
}


int ttrchn_len (int cid) {
    ttrchn_t *last = NULL;
    
    last = ttrchn_getlast(cid);
    __ttrchk_nullval(last, "failed get last element");
    
    return last->idx;
}
/* end of file */
