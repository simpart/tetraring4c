/**
 * @file network.h
 * @author simpart
 */
#ifndef __NETWORK_H__
#define __NETWORK_H__

/*** include ***/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>

/*** define ***/
#define TTR_NW_IFNCT 10

/*** struct ***/
typedef struct ttr_nw_rcvinf {
    int     sock;
    uint8_t *buf;
    size_t  size;
    void    *callback;
} ttr_nw_rcvinf_t;

/*** prototype ***/
int ttr_nw_init(char *, uint8_t *, size_t);
int ttr_nw_rcvloop (int, void (*)(uint8_t *, size_t));
void * ttr_nw_thdwrp (void *);
int ttr_nw_rcvloop_thd (int, void (*)(uint8_t *, size_t), pthread_t *);
#endif
/* end of file */
