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
    int ret  = 0;
    int sock = 0;
    
    //__ttrchk_nullprm2(ifnm, buf);
    if ((NULL == ifnm) || (NULL == buf)) {
	printf("invalid parameter\n");
        return TTR_NG;
    }
    
    /* initialize value */
    __ttr_initval3(iface, sa, rcv_cmp);
    
    /* set ifname */
    if (strlen(ifnm) >= sizeof(iface.ifr_name)) {
        printf("too long ifname\n");
	return TTR_NG;
    }
    strncpy(iface.ifr_name, ifnm, sizeof(iface.ifr_name)-1);
    
    sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (0 > sock) {
        printf("failed get socket\n");
	return TTR_NG;
    }
    //__ttrchk_less(sock, 0, "failed get socket");
    
    ret = ioctl(sock, SIOCGIFINDEX, &iface);
    if (0 > ret) {
	printf("failed ioctl\n");
        goto CLOSE_SOCK;
    }
    
    /* set value */
    sa.sll_family  = AF_PACKET;
    sa.sll_ifindex = iface.ifr_ifindex;
    
    /* set promiscuous mode */
    __ttr_initval(mreq);
    mreq.mr_type    = PACKET_MR_PROMISC;
    mreq.mr_ifindex = iface.ifr_ifindex;
    
    ret = setsockopt(
              sock,
              SOL_PACKET,
              PACKET_ADD_MEMBERSHIP,
              (void *)&mreq,
              sizeof(mreq)
          );
    if (0 > ret) {
        printf("failed setsockopt\n");
	goto CLOSE_SOCK;
    }
    
    ret = bind(
              sock,
              (const struct sockaddr *)&sa,
              sizeof(sa)
          );
    if (0 > ret) {
	printf("failed bind\n");
        goto CLOSE_SOCK;
    }

    __ttr_loop_i(TTR_NW_IFNCT) {
        
        if (0 == memcmp(&g_rcv[i], &rcv_cmp, sizeof(ttr_nw_rcvinf_t))) {
            g_rcv[i].sock = sock;
            g_rcv[i].buf  = buf;
            g_rcv[i].size = size;
            break;
        }
        
    }
    if (TTR_NW_IFNCT == i) {
	printf("could not find receive info\n");
        goto CLOSE_SOCK;
    }
    
    return sock;

CLOSE_SOCK:
    close(sock);
    return TTR_NG;
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
    
    if (NULL == cb) {
	printf("invalid parameter\n");
        return TTR_NG;
    }
    //__ttrchk_nullprm(cb);
    
    /* get socket index */
    __ttr_loop_i(TTR_NW_IFNCT) {
        if (g_rcv[i].sock == sck) {
            sck_idx = i;
            break;
        }
    }
    if (TTR_NG == sck_idx) {
	printf("invalid parameter\n");
        return TTR_NG;
    }
    
    
    while(TTR_TRUE) {
        memset(&(g_rcv[sck_idx].buf[0]), 0x00, g_rcv[sck_idx].size);
        len = recv(g_rcv[sck_idx].sock, g_rcv[sck_idx].buf, g_rcv[sck_idx].size, 0);
        if (TTR_NG == len) {
            printf("invalid length\n");
	    close(g_rcv[sck_idx].sock);
	    return TTR_NG;
	}
        
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
    
    __ttr_nullchk2(cb, thd, "invalid parameter\n")
    
    /* get socket index */
    __ttr_loop_i(TTR_NW_IFNCT) {
        if (g_rcv[i].sock == sck) {
            sck_idx = i;
            break;
        }
    }
    
    if (TTR_NG == sck_idx) {
        printf("could not find socket index\n");
        return TTR_NG;
    }
    
    g_rcv[sck_idx].callback = cb; 
    
    pthread_create(thd, NULL, &ttr_nw_thdwrp, &(g_rcv[sck_idx]));
    return TTR_OK;
}
/* end of file */
