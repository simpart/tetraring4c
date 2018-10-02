/**
 * @file debug.h
 * @author simpart
 */
#ifndef __TTR_DEBUG_H__
#define __TTR_DEBUG_H__

/*** include ***/
#include <time.h>
#include "ttr/chain.h"

/*** define ***/
#define TTR_DBGSTR_SIZ  128     //! filename buffer size
#define TTR_DBGLV_ALL   0x100   //! all
#define TTR_DBGLV_EMER  0x101   //! emergency
#define TTR_DBGLV_ALRT  0x102   //! alert
#define TTR_DBGLV_CRIT  0x103   //! critical
#define TTR_DBGLV_ERR   0x104   //! error
#define TTR_DBGLV_WARN  0x105   //! warining
#define TTR_DBGLV_NOTI  0x106   //! notice
#define TTR_DBGLV_INFO  0x107   //! information
#define TTR_DBGLV_DEBG  0x108   //! debug

/*** struct ***/
typedef struct ttr_dbgconts {
    int    lv;
    char   str[TTR_DBGSTR_SIZ];
} ttr_dbgconts_t;

/*** prototype ***/
void       ttr_dbgset     (const char *, int, int, const char *);
ttrchn_t * ttr_dbgget     (void);
void       ttr_dbglvprint (int);
void       ttr_dbgprint   (void);
void       ttr_dbgfree    (void);

/*** macro ***/
#define __ttr_dbgemer(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_EMER, msg)
#define __ttr_dbgalrt(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_ALRT, msg)
#define __ttr_dbgcrit(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_CRIT, msg)
#define __ttr_dbgerr(msg)  ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_ERR , msg)
#define __ttr_dbgwarn(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_WARN, msg)
#define __ttr_dbgnoti(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_NOTI, msg)
#define __ttr_dbginfo(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_INFO, msg)
#define __ttr_dbgdebg(msg) ttr_dbgset (__FILE__, __LINE__, TTR_DBGLV_DEBG, msg)

#endif
/* end of file */
