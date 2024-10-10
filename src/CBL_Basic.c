/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2024 Chang Guo                                               *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "CBL_Basic.h"

static void print_err_msg(const char* usrmsg, int en) {
    struct tm* ptime;
    time_t     ftime;
    char       timestr[64];
    time(&ftime);
    ptime = localtime(&ftime);
    strftime(timestr, 64, "%Y-%m-%d %H:%M:%S", ptime);
    printf("[ERROR %s] %s\n", timestr, usrmsg);
    fprintf(stderr, "[ERROR %s] %s\n", timestr, usrmsg);
    errno = en;
    exit(en);
}

void error_exit() { print_err_msg("", 255); }

void error_invalid_argument(const char* msg) { print_err_msg(msg, EINVAL); }

void error_index_out_of_bounds(const char* msg) { print_err_msg(msg, EINVAL); }

void error_not_initialized(const char* msg) { print_err_msg(msg, EINVAL); }

void error_out_of_memory(const char* msg) { print_err_msg(msg, ENOMEM); }

void error_unexpected_allocated_memory(const char* msg) {
    print_err_msg(msg, EINVAL);
}
