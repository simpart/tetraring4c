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

/*** global ***/
int g_ttrchn_init      = TTR_FALSE;
int g_ttrchn_idcnt     = 0;
ttrchn_t *g_ttrchn_mng = NULL;

/*** function ***/
int ttrchn_init (void) {
    /* check init */
    if (TTR_TRUE == g_ttrchn_init) {
        return TTR_OK;;
    }
    /* init global */
    g_ttrchn_idcnt = 1;
    
    g_ttrchn_mng = (ttrchn_t *) malloc(sizeof(ttrchn_t));
    if (NULL == g_ttrchn_mng) {
        return TTR_NG;;
    }
    memset(g_ttrchn_mng, 0x00, sizeof(ttrchn_t));
    
    g_ttrchn_init = TTR_TRUE;
    
    return TTR_OK;
}

int ttrchn_create (void) {
    int ret_id = 0;
    ttrchn_t *head = NULL;
    
    /* init */
    ttrchn_init();
    
    /* set return chain id */
    ret_id = g_ttrchn_idcnt;
    g_ttrchn_idcnt++;
    
    /* create chain head */
    head = (ttrchn_t *) malloc(sizeof(ttrchn_t));
    if (NULL == head) {
        return TTR_NG;
    }
    memset(head, 0x00, sizeof(ttrchn_t));
    
    /* add to the management chian */
    if (TTR_OK != ttrchn_add(DCNH_MNGID, head)) {
        return TTR_NG;
    }

    return ret_id;
}

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
        free(tmp);
    }
    
    free(head);
}

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
        free(tmp);
        tmp = next;
    }
    free(g_ttrchn_mng);
    
    return;
}

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
/* end of file */
