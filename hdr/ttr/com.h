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
#define TTR_LOOP(i, c) int i=0; for (;i < c;i++)
#define TTR_LOOP_i(c) TTR_LOOP(i, c)
#define TTR_LOOP_j(c) TTR_LOOP(j, c)
#define TTR_LOOP_k(c) TTR_LOOP(k, c)


#define TTR_INIT(i) memset(&i, 0x00, sizeof(i))
#define TTR_INIT2(i1, i2) TTR_INIT(i1); TTR_INIT(i2)
#define TTR_INIT3(i1, i2, i3) TTR_INIT(i1); TTR_INIT(i2); TTR_INIT(i3)

#define TTR_STRINIT(s) memset(&s[0], 0x00, sizeof(s))
#define TTR_STRINIT2(s1, s2) TTR_STRINIT(s1); TTR_STRINIT(s2)
#define TTR_STRINIT3(s1, s2, s3) TTR_STRINIT(s1); TTR_STRINIT(s2); TTR_STRINIT(s3)

#endif
/* end of file */
