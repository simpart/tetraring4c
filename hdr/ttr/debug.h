/**
 * @file debug.h
 * @author simpart
 */
#ifndef __TTR_ERROR_H__
#define __TTR_ERROR_H__

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
#define TTRDBG_EMER(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_EMER, s)
#define TTRDBG_ALRT(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_ALRT, s)
#define TTRDBG_CRIT(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_CRIT, s)
#define TTRDBG_ERR(s)  ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_ERR , s)
#define TTRDBG_WARN(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_WARN, s)
#define TTRDBG_NOTI(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_NOTI, s)
#define TTRDBG_INFO(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_INFO, s)
#define TTRDBG_DEBG(s) ttrdbg_set (__LINE__, __FILE__, TTRDBG_LV_DEBG, s)

#endif
/* end of file */
