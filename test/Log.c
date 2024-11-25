/**********************************************************************************
 * MIT License                                                                    *
 *                                                                                *
 * Copyright (c) 2024 Chang Guo                                                   *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 **********************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "Module_Log.h"

int main() {
    LOG_terminal_output = true;
    LOG_file_output     = true;
    LOG_init("log.txt");
    usleep((useconds_t)(0.5 * 1000 * 1000));
    printf("===== Default state ======================\n");
    LOG_print_state();
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    usleep((useconds_t)(0.5 * 1000 * 1000));
    printf("===== set level to 0 ======================\n");
    LOG_output_level = LOG_LEVEL_NONE;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    usleep((useconds_t)(0.5 * 1000 * 1000));
    printf("===== set level to debug level ======================\n");
    LOG_output_level = LOG_LEVEL_DEBUG;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");

    usleep((useconds_t)(0.5 * 1000 * 1000));
    printf("===== turn on all output format ======================\n");
    LOG_prefix_format |= LOG_PREFIX_ALL;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");
    LOG_print_message("level debug + 10", LOG_LEVEL_DEBUG + 10);

    usleep((useconds_t)(0.5 * 1000 * 1000));
    printf("===== set level to all ======================\n");
    LOG_prefix_format |= LOG_PREFIX_DATE | LOG_PREFIX_CLOCK_HMS;
    LOG_prefix_format &= ~LOG_PREFIX_CLOCK_SEC;
    LOG_output_level = LOG_LEVEL_ALL;
    LOG_print_debug("debug");
    LOG_print_info("info");
    LOG_print_warning("warning");
    LOG_print_error("error");
    LOG_print_message("level trace + 10", LOG_LEVEL_TRACE + 10);
    sleep(1);
    LOG_final();
    printf("end =======================\n");
    return 0;
}
