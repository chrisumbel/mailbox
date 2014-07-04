#include "logging.h"
#include "uart.h"

void logging_init() {
    uart1_init();
}

void logging_log(unsigned char *message) {
    uart1_puts(message);
}