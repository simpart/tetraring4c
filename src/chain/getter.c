/**
 * @file   ctrl.c
 * @brief  chain main controller
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "ttr/com.h"
#include "ttr/chain.h"

/*** global ***/
extern ttrchn_t *g_ttrchn_mng;

/*** function ***/
void ** ttrchn_first (int cid) {
//    ttrchn_t *tgt = NULL;
    
    if (DCNH_MNGID == cid) {
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
    
    if (DCNH_MNGID == cid) {
        /* this cid is management chain */
        
    }
    
    return NULL;
}

//ttr_chain_t
void ** ttrchn_last (int cid) {
    ttrchn_t *tgt = NULL;
    
    /* check parameter */
    if (DCNH_MNGID == cid) {
        /* this cid is management chain */
        
    }
    
    
    
    while (NULL != tgt->next) {
        tgt = (ttrchn_t *) tgt->next;
    }
    
    return &(tgt->conts);
}

/**
 * get pointer to the chain that next is NULL
 * 
 * @atteintion head chain is empty chain. it's *conts is always NULL.
 */
ttrchn_t * ttrchn_lastchn (int cid) {
    ttrchn_t *tgt = NULL;
    
    if (DCNH_MNGID == cid) {
        /* this cid is management chain */
        tgt = g_ttrchn_mng;
    } else {
        tgt = ttrchn_gethead(cid);
    }
    
    if (NULL == tgt) {
        return NULL;
    }
    
    while (NULL != tgt->next) {
        tgt = (ttrchn_t *) tgt->next;
    }
    
    return tgt;
}

/* end of file */
