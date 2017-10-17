/**
 * @file ttr.h
 * @author simpart
 */
#ifndef __SERIAL_H__
#define __SERIAL_H__

int  open_serial (char *, int);
void start_read (int, void (*)(unsigned char *, int));

#endif
/* end of file */
