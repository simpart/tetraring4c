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
#include "ttr/check.h"
#include "ttr/memory.h"

/*** function ***/
ttr_conf_t * ttrcnf_load (char *pth) {
    FILE *fp        = NULL;
    void ** nxt_cnf = NULL;
    char key[TTRCNF_KEYCNT]     = {0};
    char val[TTRCNF_VALCNT]     = {0};
    char key_tmp[TTRCNF_KEYCNT] = {0};
    char val_tmp[TTRCNF_KEYCNT] = {0};
    char line[TTRCNF_CNFCNT]    = {0};
    ttr_conf_t * ret_cnf        = NULL;
    ttr_conf_t * set_cnf        = NULL;
    
    /* check paramter */
    if (NULL == pth) {
        return NULL;
    }
    /* open config file */
    if (NULL == (fp = fopen(pth, "r"))) {
        return NULL;
    }
    /* init value */
    TTR_STRINIT3(key, val, key_tmp);
    TTR_STRINIT2(val_tmp, line);
    
    /* read config file */
    while (NULL != fgets(line, TTRCNF_CNFCNT-2, fp)) {
        sscanf(line, "%[^=]=%s", key, val);
        if ( ('#' == key[0])  ||
             (' ' == key[0])  ||
             ('\n' == key[0]) ||
             ('\r' == key[0]) ||
             ('\0' == key[0]) ) {
            continue;
        }
        
        /* remove space */
        if (TTR_NG == ttrcnf_remsp(&key_tmp[0], &key[0], TTRCNF_KEYCNT)) {
            return NULL;
        }
        if (TTR_NG == ttrcnf_remsp(&val_tmp[0], &val[0], TTRCNF_VALCNT)) {
            return NULL;
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
        memcpy(&(set_cnf->key[0]), &key_tmp[0], TTRCNF_KEYCNT);
        memcpy(&(set_cnf->val[0]), &val_tmp[0], TTRCNF_VALCNT);
        
        /* set chain */
        nxt_cnf = &(set_cnf->next);
    }
    
    return ret_cnf;
}

int ttrcnf_remsp (char *out, char *str, size_t siz) {
    int set_idx = 0;
    
    __ttrchk_nullprm2(str, out);
    
    memset(out, 0x00, siz);
    
    __ttr_loop_i( (int)siz ) {
        if ('\0' == str[i]) {
            break;
        }
        if (' ' == str[i]) {
            continue;
        }
        out[set_idx] = str[i];
        set_idx++;
    }
    
    return TTR_OK;
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
        __ttrmem_free(tmp);
        tmp = (ttr_conf_t *) next;
    } while (NULL != next);
    
    return TTR_OK;
}
/* end of file */
