/**
 * @file iface.c
 * @brief receive function from network interface
 */
/*** include ***/
#include <stdio.h>
#include "pthread.h"
#include "ttr/com.h"
#include "ttr/network.h"
#include "ttr/check.h"

/*** global ***/
ttr_nw_rcvinf_t g_rcv[TTR_NW_IFNCT];

/*** function ***/
/**
 * initialize network interface
 * 
 * @param[in] ifnm : interface name
 * @param[in] buf : receive buffer
 * @param[in] size : size of receive buffer
 * @return TTR_OK : succeed init
 * @return TTR_NG : failed init
 * @note configure L2 level receive
 */
int ttr_nw_init(char *ifnm, uint8_t *buf, size_t size) {
    struct sockaddr_ll sa;
    struct packet_mreq mreq;
    struct ifreq       iface;
    ttr_nw_rcvinf_t rcv_cmp;
    int ret  = 0;
    int sock = 0;
    
    TTRCHK_NULLPRM2(ifnm, buf);
    
    /* initialize value */
    TTR_INIT3(iface, sa, rcv_cmp);
    
    /* set ifname */
    if (strlen( ifnm ) >= sizeof(iface.ifr_name)) {
        printf("too long ifname\n");
        return TTR_NG;
    }
    strncpy(iface.ifr_name, ifnm, sizeof(iface.ifr_name));
    
    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    TTRCHK_ISLESS(sock, 0, "failed get socket");
    
    ret = ioctl(sock, SIOCGIFINDEX, &iface);
    TTRCHK_ISLESS_GOTO(ret, 0, "failed ioctl", CLOSE_SOCK);
    
    memset(&sa, 0x00, sizeof(sa));
    sa.sll_family  = AF_PACKET;
    sa.sll_ifindex = iface.ifr_ifindex;
    
    /* set promiscuous mode */
    memset(&mreq, 0x00, sizeof(mreq));
    mreq.mr_type    = PACKET_MR_PROMISC;
    mreq.mr_ifindex = iface.ifr_ifindex;

    ret = setsockopt(
              sock,
              SOL_PACKET,
              PACKET_ADD_MEMBERSHIP,
              (void *)&mreq,
              sizeof(mreq)
          );
    TTRCHK_ISLESS_GOTO(ret, 0, "failed setsockopt", CLOSE_SOCK);
    
    ret = bind(
              sock,
              (const struct sockaddr *)&sa,
              sizeof(sa)
          );
    TTRCHK_ISLESS_GOTO(ret, 0, "failed bind", CLOSE_SOCK);
    
    TTR_LOOP(idx, TTR_NW_IFNCT) {
        if (0 == memcmp(&g_rcv[idx], &rcv_cmp, sizeof(ttr_nw_rcvinf_t))) {
            g_rcv[idx].sock = sock;
            g_rcv[idx].buf  = buf;
            g_rcv[idx].size = size;
            break;
        }
    }
    
    TTRCHK_ISEQUAL_GOTO(idx, TTR_NW_IFNCT, "could not find receive info", CLOSE_SOCK);
    
CLOSE_SOCK:
    close(sock);
    return TTR_NG;

    return sock;
}

/**
 * start frame receive loop
 * 
 * @param[in] sck : target socket
 * @param[in] cb : receive callback function
 * @return TTR_OK : finish receive
 * @return TTR_NG : failed receive
 */
int ttr_nw_rcvloop (int sck, void (*cb)(uint8_t *, size_t)) {
    int len     = 0;
    int sck_idx = TTR_NG;
    
    TTRCHK_NULLPRM(cb);
    
    /* get socket index */
    TTR_LOOP(loop, TTR_NW_IFNCT) {
        if (g_rcv[loop].sock == sck) {
            sck_idx = loop;
            break;
        }
    }
    
    TTRCHK_ISEQUAL(sck_idx, TTR_NG, "could not find socket index");
    
    
    while(TTR_TRUE) {
        memset(&(g_rcv[sck_idx].buf[0]), 0x00, g_rcv[sck_idx].size);
        len = recv(g_rcv[sck_idx].sock, g_rcv[sck_idx].buf, g_rcv[sck_idx].size, 0);
        
        TTRCHK_ISEQUAL(len, -1, "receive error");
        
        /* execute callback */
        cb(g_rcv[sck_idx].buf, len);
    }

    close(g_rcv[sck_idx].sock);
    return TTR_OK;
}

void * ttr_nw_thdwrp (void *prm) {
    ttr_nw_rcvinf_t *rcv_inf = NULL;
    
    if (NULL == prm) {
        return NULL;
    }
    rcv_inf = (ttr_nw_rcvinf_t *) prm;
    
    if(TTR_OK != ttr_nw_rcvloop(rcv_inf->sock, rcv_inf->callback)) {
        return NULL;
    }
    
    return NULL;
}

int ttr_nw_rcvloop_thd (int sck, void (*cb)(uint8_t *, size_t), pthread_t * thd) {
    int sck_idx = TTR_NG;
    
    if (NULL == thd) {
        return TTR_NG;
    }
    
    /* get socket index */
    TTR_LOOP(loop, TTR_NW_IFNCT) {
        if (g_rcv[loop].sock == sck) {
            sck_idx = loop;
            break;
        }
    }
    TTRCHK_ISEQUAL(sck_idx, TTR_NG, "could not find socket index");
    
    g_rcv[sck_idx].callback = cb; 
    
    pthread_create(thd, NULL, &ttr_nw_thdwrp, &(g_rcv[sck_idx]));
    return TTR_OK;
}
/* end of file */
