/**
 * @file ttr/serial.h
 * @author simpart
 */
#ifndef __TTR_SERIAL_H__
#define __TTR_SERIAL_H__

/*** include ***/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <arpa/inet.h>


/*** define ***/
#define TTR_SRI_BUFSIZE 256

/*** struct ***/
typedef struct ttr_sri_rcvinf {
    int     fd;
    uint8_t buf[TTR_SRI_BUFSIZE];
} ttr_sri_rcvinf_t;

/*** prototype ***/
int ttr_sri_init (char *, int);
int ttr_sri_start (void (*)(unsigned char *, int));
#endif
/* end of file */
