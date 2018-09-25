/**
 * @file print.h
 * @brief defined print function
 * @author simpart
 */
#include <stdio.h>

#ifndef __TTR_PRINT_H__
#define __TTR_PRINT_H__

/*** include ***/

/*** define ***/
#define TTRPRI_ARROW_NMCH  0x100
#define TTRPRI_ARROW_UP    0x101
#define TTRPRI_ARROW_DOWN  0x102
#define TTRPRI_ARROW_RIGHT 0x103
#define TTRPRI_ARROW_LEFT  0x104

#define TTRPRI_ARWSTR_UP    "\x1b[1A"
#define TTRPRI_ARWSTR_DOWN  "\x1b[1B"
#define TTRPRI_ARWSTR_RIGHT "\x1b[1C"
#define TTRPRI_ARWSTR_LEFT  "\x1b[1D"

/*** struct ***/

/*** prototype ***/
int ttrpri_isarrow_chr   (char);
int ttrpri_isup_chr      (char);
int ttrpri_isdown_chr    (char);
int ttrpri_isleft_chr    (char);
int ttrpri_isright_chr   (char);
int ttrpri_arrowtype_chr (char);
int ttrpri_arrowtype (char *);
int ttrpri_isup      (char *);
int ttrpri_isdown    (char *);
int ttrpri_isleft    (char *);
int ttrpri_isright   (char *);

/*** macro ***/

#endif
/* end of file */
