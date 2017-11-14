/**
 * @file iface.c
 * @brief receive function from network interface
 */
/*** include ***/
#include <stdio.h>
#include "pthread.h"
#include "ttr/com.h"
#include "ttr/network.h"

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
    int idx  = 0;
    int ret  = 0;
    int sock = 0;
    
    if ((NULL == ifnm) || (NULL == buf)) {
        printf("invalid parameter\n");
        return TTR_NG;
    }
    
    /* initialize value */
    memset(&iface,   0x00, sizeof(iface));
    memset(&sa,      0x00, sizeof(sa));
    memset(&rcv_cmp, 0x00, sizeof(ttr_nw_rcvinf_t));
    
    /* set ifname */
    if (strlen( ifnm ) >= sizeof(iface.ifr_name)) {
        printf("too long ifname\n");
        return TTR_NG;
    }
    strncpy(
        iface.ifr_name,
        ifnm,
        sizeof(iface.ifr_name)
    );
    
    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("socket");
        printf("socket error\n");
        return TTR_NG;
    }
    
    if ((ret = ioctl(sock, SIOCGIFINDEX, &iface)) < 0) {
        perror("siocgifindex");
        printf("failed ioctl\n");
        close(sock);
        return TTR_NG;
    }
    
    memset(&sa, 0x00, sizeof(sa));
    sa.sll_family   = AF_PACKET;
    sa.sll_ifindex  = iface.ifr_ifindex;
    
    /* set promiscuous mode */
    memset(&mreq, 0x00, sizeof(mreq));
    mreq.mr_type    = PACKET_MR_PROMISC;
    mreq.mr_ifindex = iface.ifr_ifindex;
    if(setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP,
            (void *)&mreq, sizeof(mreq)) < 0){
        printf("setsockopt error\n");
        close(sock);
        return TTR_NG;
    }
    
    if ((ret = bind(sock, (const struct sockaddr *)&sa, sizeof(sa))) < 0) {
        printf("bind error\n");
        close(sock);
        return TTR_NG;
    }
    
    for (idx=0; idx < TTR_NW_IFNCT ;idx++) {
        if (0 == memcmp(&g_rcv[idx], &rcv_cmp, sizeof(ttr_nw_rcvinf_t))) {
            g_rcv[idx].sock = sock;
            g_rcv[idx].buf  = buf;
            g_rcv[idx].size = size;
            break;
        }
    }
    if (TTR_NW_IFNCT == idx) {
        printf("rcv_info is full\n");
        return TTR_NG;
    }
    
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
    int loop    = 0;
    int sck_idx = TTR_NG;
    
    if (NULL == cb) {
        return TTR_NG;
    }
    
    /* get socket index */
    for (loop=0; loop < TTR_NW_IFNCT ;loop++) {
        if (g_rcv[loop].sock == sck) {
            sck_idx = loop;
            break;
        }
    }
    if (TTR_NG == sck_idx) {
        return TTR_NG;
    }
    
    
    while(1) {
        memset(&(g_rcv[sck_idx].buf[0]), 0x00, g_rcv[sck_idx].size);
        len = recv(g_rcv[sck_idx].sock, g_rcv[sck_idx].buf, g_rcv[sck_idx].size, 0);
        if (-1 == len) {
            printf("recv error\n");
            return TTR_NG;
        }
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
    int loop    = 0;
    int sck_idx = 0;
    
    if (NULL == thd) {
        return TTR_NG;
    }
    
    /* get socket index */
    for (loop=0; loop < TTR_NW_IFNCT ;loop++) {
        if (g_rcv[loop].sock == sck) {
            sck_idx = loop;
            break;
        }
    }
    if (TTR_NG == sck_idx) {
        return TTR_NG;
    }
    
    g_rcv[sck_idx].callback = cb; 
    
    pthread_create(thd, NULL, &ttr_nw_thdwrp, &(g_rcv[sck_idx]));
    return TTR_OK;
}
/* end of file */
