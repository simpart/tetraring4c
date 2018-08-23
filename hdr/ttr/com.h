/**
 * @file ttr.h
 * @author simpart
 */
#ifndef __TTR_COM_H__
#define __TTR_COM_H__

/*** define ***/
#define TTR_OK  0
#define TTR_NG -1

#define TTR_TRUE  1
#define TTR_FALSE 0

/*** typedef ***/
typedef unsigned int   uint;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

/*** macro ***/
#define __ttr_loop(i, c) int i=0; for (;i < c;i++)
#define __ttr_loop_i(c) __ttr_loop(i, c)
#define __ttr_loop_j(c) __ttr_loop(j, c)
#define __ttr_loop_k(c) __ttr_loop(k, c)

#define __ttr_initval(i) memset(&i, 0x00, sizeof(i))
#define __ttr_initval2(i1, i2) __ttr_initval(i1); __ttr_initval(i2)
#define __ttr_initval3(i1, i2, i3) __ttr_initval(i1); __ttr_initval(i2); __ttr_initval(i3)

#define __ttr_strinit(s) memset(&s[0], 0x00, sizeof(s))
#define __ttr_strinit2(s1, s2) __ttr_strinit(s1); __ttr_strinit(s2)
#define __ttr_strinit3(s1, s2, s3) __ttr_strinit(s1); __ttr_strinit(s2); __ttr_strinit(s3)

#endif
/* end of file */
