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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Module_Log.h"
#include "Type_DateTime.h"
#include "Type_String.h"

Int   LOG_output_level = LOG_LEVEL_INFO;
Bool  LOG_terminal_output = true;
Bool  LOG_file_output = false;
Char  LOG_file_name[LOG_MAX_FILE_NAME_LENGTH];
UInt8 LOG_prefix_format = LOG_PREFIX_BRACKET | LOG_PREFIX_TIME |
    LOG_PREFIX_CLOCK_SEC;
FILE*   LOG_fp = NULL;
clock_t LOG_start_clock;

void LOG_init(const char* file_name) {
    strcpy(LOG_file_name, file_name);
    LOG_start_clock = clock();
    if(LOG_file_output) LOG_open_log_file();
}

void LOG_flush() { if(LOG_file_output) fflush(LOG_fp); }

void LOG_final() { if(LOG_file_output) LOG_close_log_file(); }

void LOG_open_log_file() {
    if(LOG_fp != NULL) {
        printf("Log file already opened, will be closed");
        fclose(LOG_fp);
    }
    if(LOG_file_output) {
        LOG_fp = fopen(LOG_file_name, "w");
        if(LOG_fp == NULL) printf("Error opening log file %s\n", LOG_file_name);
        else printf("\n\nLog file '%s' opened successfully\n\n", LOG_file_name);
    }
}

void LOG_close_log_file() {
    if(LOG_fp != NULL) fclose(LOG_fp);
    printf("\n\nLog file '%s' closed\n\n", LOG_file_name);
}

void LOG_prefix(Int level, struct String* prefix) {
    clock_t current_clock;
    Int     i;
    Float   rc;
    Char    buf1[64];

    struct String info_vector[LOG_PREFIX_PART];
    for(i = 0; i < LOG_PREFIX_PART; i++) String_new_(&info_vector[i]);
    CBL_DECLARE_VARS(String, 1, delimiter);
    CBL_DECLARE_VARS(Time, 1, t);
    CBL_DECLARE_VARS(DateTime, 1, dt);

    if((LOG_prefix_format & LOG_PREFIX_BRACKET) > 0) {
        CBL_CALL(info_vector[0], set_, "[");
        CBL_CALL(info_vector[5], set_, "]");
    }
    if((LOG_prefix_format & LOG_PREFIX_LEVEL_TAG) > 0) {
        if(level >= LOG_LEVEL_TRACE)
            CBL_CALL(info_vector[1], set_, "  TRACE");
        else if(level >= LOG_LEVEL_DEBUG)
            CBL_CALL(info_vector[1], set_, "  DEBUG");
        else if(level >= LOG_LEVEL_INFO)
            CBL_CALL(info_vector[1], set_, "   INFO");
        else if(level >= LOG_LEVEL_WARNING)
            CBL_CALL(info_vector[1], set_, "WARNING");
        else if(level >= LOG_LEVEL_ERROR)
            CBL_CALL(info_vector[1], set_, "  ERROR");
    }
    CBL_CALL(dt, now_, 1);
    if(LOG_prefix_format & LOG_PREFIX_DATE)
        CBL_CALL(dt.date, string, &info_vector[2]);
    if(LOG_prefix_format & LOG_PREFIX_TIME)
        CBL_CALL(dt.time, string, &info_vector[3]);

    if(LOG_prefix_format & (LOG_PREFIX_CLOCK_HMS | LOG_PREFIX_CLOCK_SEC)) {
        current_clock = clock();
        CBL_CALL(t, zero_);
        rc = (current_clock - LOG_start_clock) / ((Float)CLOCKS_PER_SEC);
        if(LOG_prefix_format & LOG_PREFIX_CLOCK_SEC) {
            sprintf(buf1, "%.3fs", rc);
            CBL_CALL(info_vector[4], set_, buf1);
        }
        else if(LOG_prefix_format & LOG_PREFIX_CLOCK_HMS) {
            CBL_CALL(t, add_second_, rc);
            CBL_CALL(t, string, &info_vector[4]);
        }
    }
    CBL_CALL(*prefix, free_);
    CBL_CALL(delimiter, set_, " ");
    CBL_CALL(*prefix, join_, info_vector, 6, delimiter);
    CBL_FREE_VARS(String, 1, delimiter);
    for(i = 0; i < LOG_PREFIX_PART; i++) String_free_(&info_vector[i]);
}

void LOG_print_message(const char* message, Int level) {
    struct String* lines = NULL;
    CBL_DECLARE_VARS(String, 3, s_message, prefix, LF);
    Int   n_lines,      i;
    Char *buf1 = NULL, *buf2 = NULL;

    if(level > LOG_output_level) return;

    CBL_CALL(s_message, set_, message);
    LOG_prefix(level, &prefix);
    CBL_CALL(LF, set_, "\n");
    i = CBL_CALL(s_message, nextmatch, LF, 0);
    if(i < 0) {
        if(buf1) {
            free(buf1);
            buf1 = NULL;
        }
        CBL_CALL(prefix, cstr_, &buf1);
        if(LOG_terminal_output) printf("%s %s\n", buf1, message);

        if(LOG_file_output) {
            if(LOG_fp == NULL) LOG_open_log_file();
            fprintf(LOG_fp, "%s %s\n", buf1, message);
        }
        if(buf1) {
            free(buf1);
            buf1 = NULL;
        }
        return;
    }
    CBL_CALL(s_message, split, LF, &lines, &n_lines);
    for(i = 0; i < n_lines; i++) {
        if(buf1) {
            free(buf1);
            buf1 = NULL;
        }
        if(buf2) {
            free(buf2);
            buf2 = NULL;
        }
        CBL_CALL(prefix, cstr_, &buf1);
        CBL_CALL(lines[i], cstr_, &buf2);
        if(LOG_terminal_output)printf("%s %s\n", buf1, buf2);
        if(LOG_file_output) {
            if(LOG_fp == NULL) LOG_open_log_file();
            fprintf(LOG_fp, "%s %s\n", buf1, buf2);
        }
        CBL_CALL(lines[i], free_);
    }
    if(buf1) {
        free(buf1);
        buf1 = NULL;
    }
    if(buf2) {
        free(buf2);
        buf2 = NULL;
    }
    free(lines);
    CBL_FREE_VARS(String, 3, s_message, prefix, LF);
}

void LOG_print_state() {
    Char* buf = NULL;
    CBL_DECLARE_VARS(String, 1, prefix);
    printf("Logging state:\n");
    printf("Logging level: %d\n", LOG_output_level);
    printf("Terminal output: %s\n", LOG_terminal_output ? "on" : "off");
    printf("Write to log file: %s\n", LOG_file_output ? "on" : "off");
    if(LOG_file_output) {
        printf("Log file name: %s\n", LOG_file_name);
        printf("Log file is %s\n", LOG_fp ? "open" : "closed");
    }
    LOG_prefix(LOG_LEVEL_DEBUG, &prefix);
    CBL_CALL(prefix, cstr_, &buf);
    printf("prefix format: %s\n", buf);
    free(buf);
}
