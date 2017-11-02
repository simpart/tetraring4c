/**
 * @file main.c
 * @brief packet receive sample
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "tetraring.h"
/*** prototype ***/
void rcv_callback(uint8_t *, size_t);

/*** define ***/
#define IFACE_NAME "ens8"

/*** function ***/
int main (void) {
    int ret = 0;
    uint8_t buf[256] = {0};
    
    ret = ttr_nw_init(IFACE_NAME, buf, sizeof(buf));
    if (TTR_NG == ret) {
        return -1;
    }
    
    ret = ttr_nw_rcvloop(rcv_callback);
    if (TTR_NG == ret) {
        return -1;
    }
    
    return 0;
}

/**
 * receive callback function
 * 
 * @param[in] buf : head pointer to receive frame
 * @param[in] size : receive size
 */
void rcv_callback(uint8_t *buf, size_t size) {
    printf("receive frame\n");
    buf = buf;
    size = size;
}
/* end of file */
