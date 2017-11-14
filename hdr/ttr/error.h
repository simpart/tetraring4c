/**
 * @file error.h
 * @author simpart
 */
#ifndef __TTR_ERROR_H__
#define __TTR_ERROR_H__

/*** include ***/

/*** define ***/
#define TTR_ERR_DBGMODE
#define TTRERR_BUFCNT 1   //! error buffer count
#define TTRERR_FLNSIZ 32  //! filename buffer size
#define TTRERR_CNTSIZ 64  //! contents buffer size

/*** struct ***/
typedef struct ttrerr_dbginf {
    int  line;
    char file[TTRERR_FLNSIZ];
    char conts[TTRERR_CNTSIZ];
} ttrerr_dbginf_t;

/*** prototype ***/
void ttrerr_setdbg (int, const char *, const char *);
void ttrerr_elmprint (ttrerr_dbginf_t *);

/*** macro ***/
#define TTR_ERROR(d) ttrerr_setdbg (__LINE__, __FILE__, d)

#endif
/* end of file */
