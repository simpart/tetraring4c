/**
 * @file console.h
 * @brief defined console function
 * @author simpart
 */
#ifndef __TTR_CONSOLE_H__
#define __TTR_CONSOLE_H__

/*** include ***/
#include <stdio.h>

/*** include ***/

/*** define ***/
#define TTRCON_ARROW_NMCH  0x100
#define TTRCON_ARROW_UP    0x101
#define TTRCON_ARROW_DOWN  0x102
#define TTRCON_ARROW_RIGHT 0x103
#define TTRCON_ARROW_LEFT  0x104

#define TTRCON_ARWSTR_UP    "\x1b[1A"
#define TTRCON_ARWSTR_DOWN  "\x1b[1B"
#define TTRCON_ARWSTR_RIGHT "\x1b[1C"
#define TTRCON_ARWSTR_LEFT  "\x1b[1D"

/*** struct ***/

/*** prototype ***/
int ttrcon_isarrow_chr   (char);
int ttrcon_isup_chr      (char);
int ttrcon_isdown_chr    (char);
int ttrcon_isleft_chr    (char);
int ttrcon_isright_chr   (char);
int ttrcon_arrowtype_chr (char);
int ttrcon_arrowtype (char *);
int ttrcon_isup      (char *);
int ttrcon_isdown    (char *);
int ttrcon_isleft    (char *);
int ttrcon_isright   (char *);

/*** macro ***/

#endif
/* end of file */
