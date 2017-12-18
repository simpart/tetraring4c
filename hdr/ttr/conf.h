/**
 * @file   conf.h
 * @brief  config function header
 * @author simpart
 */
#ifndef __TTR_CONF_H__
#define __TTR_CONF_H__

/*** define ***/
#define TTRCNF_KEYCNT  64
#define TTRCNF_VALCNT  64
#define TTRCNF_CNFCNT  TTRCNF_KEYCNT + TTRCNF_VALCNT

/*** struct ***/
typedef struct ttr_conf {
    char key[TTRCNF_KEYCNT];
    char val[TTRCNF_VALCNT];
    void *next;
} ttr_conf_t;

/*** prototype ***/
ttr_conf_t * ttrcnf_load (char *);
ttr_conf_t * ttrcnf_find (ttr_conf_t *, char *);
int ttrcnf_remsp (char *, char *, size_t);
int ttrcnf_free (ttr_conf_t *);

#endif
/* end of file */
