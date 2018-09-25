/**
 * @file arrow.c
 * @brief print arrow function
 * @author simpart
 */
#include <string.h>
#include "ttr/com.h"
#include "ttr/print.h"
#include "ttr/string.h"

/*** function ***/
int ttrpri_isarrow_chr (char key) {
    return (('\x1b' == key) ? TTR_TRUE : TTR_FALSE);
}

int ttrpri_isup_chr (char key) {
    return (('A' == key) ? TTR_TRUE : TTR_FALSE);
}

int ttrpri_isdown_chr (char key) {
    return (('B' == key)? TTR_TRUE : TTR_FALSE);
}

int ttrpri_isright_chr (char key) {
    return (('C' == key)? TTR_TRUE : TTR_FALSE);
}

int ttrpri_isleft_chr (char key) {
    return (('D' == key)? TTR_TRUE : TTR_FALSE);
}

int ttrpri_arrowtype_chr(char key) {
    switch (key) {
        case 'A':
            return TTRPRI_ARROW_UP;
        case 'B':
            return TTRPRI_ARROW_DOWN;
        case 'C':
            return TTRPRI_ARROW_RIGHT;
        case 'D':
            return TTRPRI_ARROW_LEFT;
        default:
            return TTRPRI_ARROW_NMCH;
    }
}

int ttrpri_arrowtype (char *str) {
    if (TTR_TRUE == ttrpri_isup(str)) {
        return TTRPRI_ARROW_UP;
    } else if (TTR_TRUE == ttrpri_isdown(str)) {
        return TTRPRI_ARROW_DOWN;
    } else if (TTR_TRUE == ttrpri_isright(str)) {
        return TTRPRI_ARROW_RIGHT;
    } else if (TTR_TRUE == ttrpri_isleft(str)) {
        return TTRPRI_ARROW_LEFT;
    } else {
        return TTRPRI_ARROW_NMCH;
    }
}

int ttrpri_isup (char * str) {
    __ttrstr_iskey(TTRPRI_ARWSTR_UP, str) {
        return TTR_TRUE;
    } else {
        return TTR_FALSE;
    }
}

int ttrpri_isdown (char * str) {
    __ttrstr_iskey(TTRPRI_ARWSTR_DOWN, str) {
        return TTR_TRUE;
    } else {
        return TTR_FALSE;
    }
}

int ttrpri_isright (char *str) {
    __ttrstr_iskey(TTRPRI_ARWSTR_RIGHT, str) {
        return TTR_TRUE;
    } else {
        return TTR_FALSE;
    }
}

int ttrpri_isleft (char *str) {
    __ttrstr_iskey(TTRPRI_ARWSTR_LEFT, str) {
        return TTR_TRUE;
    } else {
        return TTR_FALSE;
    }
}
/* end of file */
