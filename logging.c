#include "logging.h"
#include "uart.h"

void logging_init() {
#ifdef DEBUG
    uart1_init();
#endif
}

void logging_log(unsigned char *message) {
#ifdef DEBUG
    uart1_puts(message);
#endif
}