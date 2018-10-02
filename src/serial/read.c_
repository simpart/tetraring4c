/**
 * @file serial/read.c
 * @brief read data from serial interface
 */
/*** include ***/
#include <unistd.h>
#include "ttr/com.h"
#include "ttr/serial.h"

/*** global ***/
ttr_sri_rcvinf_t g_rcv;

/*** function ***/
/**
 * initialize serial port
 *
 * @param[in] sport : serial port name
 * @param[in] brate : speed
 * @return TTR_OK : initialize is succeed
 * @return TTR_NG : initialize is failed
 */
int ttr_sri_init (char *sport, int brate) {
    int    fd          = 0;
    struct termios tio = {0};      // for communicate config
    
    if (NULL == sport) {
        return TTR_NG;
    }
    /* open device */
    fd = open(sport, O_RDWR);
    if (0 > fd) {
        printf("open error\n");
        return TTR_NG;
    }
    /* set io config */
    tio.c_cflag += CREAD;   // enable recive
    tio.c_cflag += CLOCAL;  // local line
    tio.c_cflag += CS8;     // data   bit -> 8bit
    tio.c_cflag += 0;       // stop   bit -> 1bit
    tio.c_cflag += 0;       // parity bit -> 1bit
    /* set speed */
    cfsetispeed(&tio, brate);
    cfsetospeed(&tio, brate);
    cfmakeraw(&tio);               // ser RAW mode
    tcsetattr(fd, TCSANOW, &tio);
    ioctl(fd, TCSETS, &tio);
    
    memset(&g_rcv, 0x00, sizeof(ttr_sri_rcvinf_t));
    g_rcv.fd = fd;
    
    return fd;
}

/**
 * start read loop
 * 
 * @param[in] cb : read callback function
 * @return TTR_OK : finished read data
 * @return TTR_NG : failed read data
 */
int ttr_sri_start (void (*cb)(unsigned char *, int)) {
    int len  = 0;
    
    if (NULL == cb) {
        return TTR_NG;
    }
    
    while(1) {
        memset(&(g_rcv.buf[0]), 0x00, TTR_SRI_BUFSIZE);
        len = read(g_rcv.fd,g_rcv.buf, TTR_SRI_BUFSIZE);
        if (0 < len) {
            cb(&(g_rcv.buf[0]), len);
        }
    }
    
    close(g_rcv.fd);
    return TTR_OK;
}
/* end of file */
