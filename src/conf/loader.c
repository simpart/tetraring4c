/**
 * @file   reader.c
 * @brief  config reader
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttr/com.h"
#include "ttr/conf.h"

/*** function ***/
ttr_conf_t * ttrcnf_load (char *pth) {
    FILE *fp  = NULL;
    char key[TTRCNF_KEYCNT]  = {0};
    char val[TTRCNF_VALCNT]  = {0};
    char line[TTRCNF_CNFCNT] = {0};
    ttr_conf_t * ret_cnf     = NULL;
    ttr_conf_t * set_cnf     = NULL;
    void ** nxt_cnf = NULL;
    
    /* check paramter */
    if (NULL == pth) {
        return NULL;
    }
    /* open config file */
    if (NULL == (fp = fopen(pth, "r"))) {
        return NULL;
    }
    /* init value */
    memset(&key[0],  0x00, sizeof(key));
    memset(&val[0],  0x00, sizeof(val));
    memset(&line[0], 0x00, sizeof(line));
    
    /* read config file */
    while (NULL != fgets(line, TTRCNF_CNFCNT-2, fp)) {
        sscanf(line, "%[^=]=%s", key, val);
        if (('#' == key[0]) || (' ' == key[0]) || ('\n' == key[0]) || ('\r' == key[0])) {
            continue;
        }
        /* get conf memory */
        if (NULL == ret_cnf) {
            ret_cnf = (ttr_conf_t *) malloc(sizeof(ttr_conf_t));
            set_cnf = ret_cnf;
        } else {
            *nxt_cnf = (ttr_conf_t *) malloc(sizeof(ttr_conf_t));
            set_cnf = (ttr_conf_t *) *nxt_cnf;
        }
        
        /* init conf */
        if (NULL == set_cnf) {
            return NULL;
        }
        memset(set_cnf, 0x00, sizeof(ttr_conf_t));
        
        /* set key,value */
        memcpy(&(set_cnf->key[0]), &key[0], TTRCNF_KEYCNT);
        memcpy(&(set_cnf->val[0]), &val[0], TTRCNF_VALCNT);
        
        /* set chain */
        nxt_cnf = &(set_cnf->next);
    }
    
    return ret_cnf;
}


ttr_conf_t * ttrcnf_find (ttr_conf_t *cnf, char * key) {
    void * next     = NULL;
    ttr_conf_t *tmp = cnf;
    
    if ((NULL == key) || (NULL == cnf)) {
        return NULL;
    }
    
    do {
        next = tmp->next;
        if (0 == strncmp(&(tmp->key[0]), key, TTRCNF_KEYCNT)) {
            return tmp;
        }
        tmp = (ttr_conf_t *) next;
    } while (NULL != next);
    
    return NULL;
}

int ttrcnf_free (ttr_conf_t *cnf) {
    void * next     = NULL;
    ttr_conf_t *tmp = cnf;
    
    if (NULL == cnf) {
        return TTR_NG;
    }
    do {
        next = tmp->next;
        free(tmp);
        tmp = (ttr_conf_t *) next;
    } while (NULL != next);
    
    return TTR_OK;
}
/* end of file */
