/**
 * @file main.c
 * @brief packet receive sample
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "tetraring.h"
/*** define ***/
#define IFACE_NAME "ens8"
#define SRC_MAC 0x11,0x22,0x33,0x44,0x55,0x66
#define DST_MAC 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF

/*** function ***/
int main (void) {
    int     sock    = 0;
    uint8_t buf[14] = {0};
    uint8_t dmac[]  = {DST_MAC};
    uint8_t smac[]  = {SRC_MAC};
    
    /* init interface */
    sock = ttr_nw_init(IFACE_NAME, buf, sizeof(buf));
    if (TTR_NG == sock) {
        printf("initializing failed\n");
        return -1;
    }
    
    /* set mac */
    memcpy(&(buf[0]), &dmac[0], sizeof(dmac));
    memcpy(buf+sizeof(dmac), &smac[0], sizeof(smac));

    if (-1 == send(sock, &buf[0], sizeof(buf), 0) ) {
        printf("sending failed\n");
        return -1;
    }
    
    return 0;
}
/* end of file */
