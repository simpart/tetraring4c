/**
 * @file   ctrl.c
 * @brief  chain main controller
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/chain.h"

/*** global ***/
extern ttrchn_t *g_ttrchn_mng;

/*** function ***/
int ttrchn_add (int cid, void *elm) {
    ttrchn_t *add_chn  = NULL;
    ttrchn_t *last = NULL;
    
    /* check parameter */
    if (NULL == elm) {
        return TTR_NG;
    }
    
    /* get management last chain when cid is manamegent id */
    /* get main last chain when cid chain id               */
    last = ttrchn_lastchn(cid);
    if (NULL == last) {
        return TTR_NG;
    }

    /* create additional chain */
    add_chn = (ttrchn_t *) malloc(sizeof(ttrchn_t));
    if (NULL == add_chn) {
        return TTR_NG;
    }
    memset(add_chn, 0x00, sizeof(ttrchn_t));
    add_chn->idx   = (last->idx) + 1;
    add_chn->conts = elm;
    
    /* make chain */
    last->next    = add_chn;
    add_chn->prev = last;
    
    return TTR_OK;
}

int ttrchn_remove (int cid, int idx) {
    int      idx_cnt  = 0;
    void     *val     = NULL;
    ttrchn_t *tmp     = NULL;
    ttrchn_t *rep_chn = NULL;
    
    /* release contents */
    val = ttrchn_get(cid, idx);
    if (NULL == val) {
        return TTR_NG;
    }
    free(val);
    
    /* get taregt chain */
    tmp = ttrchn_gethead(cid);
    if (NULL == tmp) {
        return TTR_NG;
    }
    while (NULL != tmp) {
        if (tmp->idx == (idx+1)) {
            if (NULL != tmp->next) {
                /* replace chain */
                rep_chn = (ttrchn_t *) tmp->prev;
                rep_chn->next = tmp->next;
                rep_chn = tmp->next;
                rep_chn->prev = tmp->prev;
            } else {
                /* this chain is last */
                rep_chn = (ttrchn_t *) tmp->prev;
                rep_chn->next = NULL;
            }
            break;
        }
        tmp = (ttrchn_t *) tmp->next;
    }
    /* release target chain */
    if (NULL == tmp) {
        return TTR_NG;
    }
    free(tmp);
    
    /* re-index chain */
    tmp = ttrchn_gethead(cid);
    if (NULL == tmp) {
        return TTR_NG;
    }
    if (NULL == tmp->next) {
        /* this chain is no element */
        return TTR_OK;
    }
    
    while (NULL != tmp) {
        tmp->idx = idx_cnt;
        tmp = (ttrchn_t *) tmp->next;
        idx_cnt++;
    }
    
    return TTR_OK;
}
/* end of file */
