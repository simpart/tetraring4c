/**
 * @file info.c
 * @brief getter about network interface
 * @author simpart
 */
/*** include ***/
#include <stdio.h>

#include <string.h> /* for strncpy */
#include <unistd.h> /* for close */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "ttr/com.h"
#include "ttr/check.h"
#include "ttr/network.h"

/*** function ***/
int ttrnw_getaddr (char *ifnm, ttrnw_ipv4_t *v4) {
    
    /* check parameter */
    __ttrchk_nullprm2(ifnm, v4);
    
    struct ifreq ifr;
    __ttr_initval(ifr);
    
    /* set iface conf */
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, ifnm, IFNAMSIZ-1);
    
    /* get */
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    
    struct sockaddr_in *addr = (struct sockaddr_in *) &(ifr.ifr_addr);
    __ttrchk_equal(addr->sin_addr.s_addr, 0, "failed getaddr");
    /* set address */
    v4->addr[0] = 0xFF & addr->sin_addr.s_addr;
    v4->addr[1] = (0xFF00 & addr->sin_addr.s_addr) >> 8;
    v4->addr[2] = (0xFF0000 & addr->sin_addr.s_addr) >> 16;
    v4->addr[3] = (0xFF000000 & addr->sin_addr.s_addr) >> 24;
    
    return TTR_OK;
}
/* end of file */
