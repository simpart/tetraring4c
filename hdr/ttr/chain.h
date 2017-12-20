/**
 * @file   chain.h
 * @brief  chain function header
 * @author simpart
 */
#ifndef __TTR_CHAIN_H__
#define __TTR_CHAIN_H__

/*** define ***/
#define DCNH_MNGID -100

/*** struct ***/
typedef struct ttrchn {
    int   idx;
    void *next;
    void *prev;
    void *conts;
} ttrchn_t;

//typedef struct ttrchn_mng {
//    int id;
//    ttrchn_t *head;
//} ttrchn_mng_t;

/*** prototype ***/
/* manage */
int ttrchn_init (void);
int ttrchn_create (void);
ttrchn_t * ttrchn_gethead (int);
void ttrchn_free (int);
void ttrchn_close (void);
/* ctrl */
int ttrchn_add (int, void *);
int ttrchn_remove (int, int);
/* getter */
void * ttrchn_get (int, int);
void ** ttrchn_find (int, void *, size_t);
void ** ttrchn_head (void);
void ** ttrchn_last (int);
ttrchn_t * ttrchn_lastchn (int);
#endif
/* end of file */
