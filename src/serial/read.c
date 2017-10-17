#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "ttr.h"


void start_read (int fd, void (*cb)(unsigned char *)) {
    unsigned char buf[255] = {0};
    int len  = 0;
    
    while(1) {
        memset(&buf[0], 0x00, sizeof(buf));
        len = read(fd, buf, sizeof(buf));
        if (0 < len) {
            cb(buf);
        }
    }
}

int open_serial (char *sport, int brate) {
    int    fd          = 0;
    struct termios tio = {0};      // for communicate config
    
    if (NULL == sport) {
        return -1;
    }
    /* open device */
    fd = open(sport, O_RDWR);
    if (0 > fd) {
        printf("open error\n");
        return -1;
    }
    
    /* set io config */
    tio.c_cflag += CREAD;   // enable recive
    tio.c_cflag += CLOCAL;  // local line
    tio.c_cflag += CS8;     // data   bit -> 8bit
    tio.c_cflag += 0;       // stop   bit -> 1bit
    tio.c_cflag += 0;       // parity bit -> 1bit
    cfsetispeed(&tio, brate);
    cfsetospeed(&tio, brate);
    cfmakeraw(&tio);               // ser RAW mode
    tcsetattr(fd, TCSANOW, &tio);
    ioctl(fd, TCSETS, &tio);
    
    return fd;
}
/* end of file */
