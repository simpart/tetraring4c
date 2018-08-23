/**
 * @file   ctrl.c
 * @brief  chain management
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/chain.h"
#include "ttr/memory.h"
#include "ttr/check.h"

/*** global ***/
int g_ttrchn_init      = TTR_FALSE;
int g_ttrchn_idcnt     = 0;
ttrchn_t *g_ttrchn_mng = NULL;

/*** function ***/
/**
 * create management chain
 *
 * @return (TTR_OK) successful init
 * @return (TTR_NG) failed init
 */
int ttrchn_init (void) {
    /* check init */
    if (TTR_TRUE == g_ttrchn_init) {
        return TTR_OK;
    }
    /* init global */
    g_ttrchn_idcnt = 1;
    
    g_ttrchn_mng = (ttrchn_t *) ttrmem_malloc(sizeof(ttrchn_t));
    __ttrchk_nullval(g_ttrchn_mng, "failed malloc");
    
    g_ttrchn_init = TTR_TRUE;
    
    return TTR_OK;
}

/**
 * release chian
 *
 * @param[in] (int) chain id
 */
void ttrchn_free (int cid) {
    ttrchn_t *head = NULL;
    ttrchn_t *next = NULL;
    ttrchn_t *tmp  = NULL;
    
    head = ttrchn_gethead(cid);
    if (NULL == head) {
        return;
    }
    next = head->next;
    
    while (NULL != next) {
        if (NULL != next->conts) {
            free(next->conts);
        }
        tmp  = next;
        next = (ttrchn_t *) next->next;
        __ttrmem_free(tmp);
    }
    __ttrmem_free(head);
}

/**
 * release all chain
 */
void ttrchn_close (void) {
    ttrchn_t *tmp  = g_ttrchn_mng;
    ttrchn_t *next = tmp->next;
    
    if (NULL == tmp) {
        /* there is no chain. nothing to do. */
        return;
    }
    
    while (NULL != next) {
        next = (ttrchn_t *) tmp->next;
        ttrchn_free(tmp->idx);
        
        __ttrmem_free(tmp);
        tmp = next;
    }
    __ttrmem_free(g_ttrchn_mng);
    
    return;
}

/**
 * get head of management chain
 *
 * @param[in] (int) chain id
 * @return (ttrchn_t *) chain pointer
 * @return (NULL) failed get head
 */
ttrchn_t * ttrchn_gethead (int cid) {
    ttrchn_t *mng_chn  = g_ttrchn_mng;
    
    if (0 >= cid) {
        /* this function is not supported management chain */
        return NULL;
    }
    
    /* find chain */
    while (NULL != mng_chn) {
        if (cid == mng_chn->idx) {
            /* hit chian */
            return mng_chn->conts;
        }
        mng_chn = mng_chn->next;
    }
    /* not hitted chain id */
    return NULL;
}

ttrchn_t * ttrchn_getlast (int cid) {
    ttrchn_t *tgt = NULL;

    if (TTRCHN_ID_MNG == cid) {
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
