/**
 * @file   chain.h
 * @brief  chain function header
 * @author simpart
 */
#ifndef __TTR_CHAIN_H__
#define __TTR_CHAIN_H__

/*** include ***/
#include "ttr/com/check.h"

/*** define ***/
#define TTRCHN_ID_INIT -1
#define TTRCHN_ID_MNG  -100

/*** struct ***/
typedef struct ttrchn {
    int   idx;
    void *next;
    void *prev;
    void *conts;
} ttrchn_t;

/*** prototype ***/
/* manage */
void       ttrchn_init    (void);
ttrchn_t * ttrchn_gethead (int);
ttrchn_t * ttrchn_getlast (int);
void       ttrchn_free    (int);
void       ttrchn_close   (void);

/* ctrl */
int ttrchn_create (void);
int ttrchn_add    (int, void *);
int ttrchn_remove (int, int);

/* getter */
void *  ttrchn_get  (int, int);
void ** ttrchn_find (int, void *, size_t);
void ** ttrchn_head (void);
void ** ttrchn_last (int);
int     ttrchn_len  (int);

/*** macro ***/
#define __ttrchn_loop_chain(id)                            \
    ttrchn_t *chain = ttrchn_gethead(id);                  \
    __ttrchk_nullval(chain, "chain head is null");         \
    for (;NULL != chain; chain = (ttrchn_t *) chain->next) \
    
#endif
/* end of file */
