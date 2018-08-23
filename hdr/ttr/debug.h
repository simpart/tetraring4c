/**
 * @file debug.h
 * @author simpart
 */
#ifndef __TTR_DEBUG_H__
#define __TTR_DEBUG_H__

/*** include ***/
#include <time.h>
#include "chain.h"

/*** define ***/
#define TTRDBG_STRSIZ   128     //! filename buffer size
#define TTRDBG_LV_ALL   0x100   //! all
#define TTRDBG_LV_EMER  0x101   //! emergency
#define TTRDBG_LV_ALRT  0x102   //! alert
#define TTRDBG_LV_CRIT  0x103   //! critical
#define TTRDBG_LV_ERR   0x104   //! error
#define TTRDBG_LV_WARN  0x105   //! warining
#define TTRDBG_LV_NOTI  0x106   //! notice
#define TTRDBG_LV_INFO  0x107   //! information
#define TTRDBG_LV_DEBG  0x108   //! debug

/*** struct ***/
typedef struct ttrdbg_conts {
    int    lv;
    char   str[TTRDBG_STRSIZ];
} ttrdbg_conts_t;

/*** prototype ***/
void       ttrdbg_set     (int,const char *, int, const char *);
ttrchn_t * ttrdbg_get     (void);
void       ttrdbg_lvprint (int);
void       ttrdbg_print   (void);
void       ttrdbg_free    (void);

/*** macro ***/
#define __ttrdbg_emer(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_EMER, msg)
#define __ttrdbg_alrt(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_ALRT, msg)
#define __ttrdbg_crit(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_CRIT, msg)
#define __ttrdbg_err(msg)  ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_ERR , msg)
#define __ttrdbg_warn(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_WARN, msg)
#define __ttrdbg_noti(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_NOTI, msg)
#define __ttrdbg_info(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_INFO, msg)
#define __ttrdbg_debg(msg) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_DEBG, msg)

#endif
/* end of file */
