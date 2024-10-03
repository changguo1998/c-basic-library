#include <stdio.h>
#include <unistd.h>
#include "CBL_Log.h"

int main() {
    LOG_terminal_output = true;
    LOG_file_output     = true;
    sprintf(LOG_file_name, "log.txt");
    LOG_init();
    sleep(1);
    printf("===== Default state ======================\n");
    LOG_print_state();
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    sleep(1);
    printf("===== set level to 0 ======================\n");
    LOG_output_level = LOG_LEVEL_NONE;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    sleep(1);
    printf("===== set level to debug level ======================\n");
    LOG_output_level = LOG_LEVEL_DEBUG;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    sleep(1);
    printf("===== turn on all output format ======================\n");
    LOG_prefix_format |= LOG_PREFIX_LEVEL_TAG;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");
    LOG_print_message("level debug + 10", LOG_LEVEL_DEBUG + 10);

    sleep(1);
    printf("===== set level to all ======================\n");
    LOG_prefix_format |= LOG_PREFIX_DATE | LOG_PREFIX_CLOCK_HMS;
    LOG_prefix_format &= ~LOG_PREFIX_CLOCK_SEC;
    LOG_output_level = LOG_LEVEL_ALL;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");
    LOG_print_message("level debug + 10", LOG_LEVEL_TRACE + 10);
    sleep(1);
    LOG_final();
    printf("end =======================\n");
    return 0;
}
