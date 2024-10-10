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

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "CBL_Log.h"
#include "CBL_DateTime.h"
#include "CBL_String.h"

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

struct String LOG_prefix(Int level) {
    struct String info_vector[LOG_PREFIX_PART];
    clock_t       current_clock;
    DateTime      dt;

    Time  t;
    Int   i;
    Float rc;

    for(i = 0; i < LOG_PREFIX_PART; i++) String_new_(&info_vector[i]);

    if((LOG_prefix_format & LOG_PREFIX_BRACKET) > 0) {
        info_vector[0].methods->set_(&info_vector[0], "[");
        info_vector[0].methods->set_(&info_vector[5], "]");
    }
    if((LOG_prefix_format & LOG_PREFIX_LEVEL_TAG) > 0) {
        if(level >= LOG_LEVEL_TRACE)
            info_vector[1].methods->set_(&info_vector[1], "  TRACE");
        else if(level >= LOG_LEVEL_DEBUG)
            info_vector[1].methods->set_(&info_vector[1], "  DEBUG");
        else if(level >= LOG_LEVEL_INFO)
            info_vector[1].methods->set_(&info_vector[1], "   INFO");
        else if(level >= LOG_LEVEL_WARNING)
            info_vector[1].methods->set_(&info_vector[1], "WARNING");
        else if(level >= LOG_LEVEL_ERROR)
            info_vector[1].methods->set_(&info_vector[1], "  ERROR");
    }
    dt = DT_now(1);
    if((LOG_prefix_format & LOG_PREFIX_DATE) > 0) {
        DT_date_string(dt.date, info_vector[2].str);
        info_vector[2].len = (Int)strlen(info_vector[2].str);
    }
    if((LOG_prefix_format & LOG_PREFIX_TIME) > 0) {
        DT_time_string(dt.time, info_vector[3].str);
        info_vector[3].len = (Int)strlen(info_vector[3].str);
    }
    if((LOG_prefix_format & (LOG_PREFIX_CLOCK_HMS | LOG_PREFIX_CLOCK_SEC)) >
        0) {
        current_clock = clock();
        t = DT_zero_time();
        rc = (current_clock - LOG_start_clock) / ((Float)CLOCKS_PER_SEC);
        if((LOG_prefix_format & LOG_PREFIX_CLOCK_SEC) > 0)
            sprintf(
                info_vector[4].str, "%.3fs", rc);
        else if((LOG_prefix_format & LOG_PREFIX_CLOCK_HMS) > 0) {
            t = DT_time_plus_precision(t, DT_second2precision(rc));
            DT_time_string(t, info_vector[4].str);
        }
        info_vector[4].len = (Int)strlen(info_vector[4].str);
    }
    return STR_join(info_vector, 6, STR_String(" "));
}

void LOG_print_message(const char* message, Int level) {
    String s_message, *lines = NULL, prefix;
    Int    n_lines,    i;
    if(level > LOG_output_level) return;
    s_message = STR_String(message);
    prefix = LOG_prefix(level);
    i = STR_next_match(s_message, STR_String("\n"), 0);
    if(i < 0) {
        if(LOG_terminal_output) printf("%s %s\n", prefix.str, message);

        if(LOG_file_output) {
            if(LOG_fp == NULL) LOG_open_log_file();
            fprintf(LOG_fp, "%s %s", prefix.str, message);
        }
        return;
    }
    n_lines = STR_split(&lines, s_message, STR_String("\n"));
    for(i = 0; i < n_lines; i++) {
        if(LOG_terminal_output) printf("%s %s\n", prefix.str, lines[i].str);

        if(LOG_file_output) {
            if(LOG_fp == NULL) LOG_open_log_file();
            fprintf(LOG_fp, "%s %s\n", prefix.str, lines[i].str);
        }
    }
    free(lines);
}

void LOG_print_state() {
    String prefix;
    printf("Logging state:\n");
    printf("Logging level: %d\n", LOG_output_level);
    printf("Terminal output: %s\n", LOG_terminal_output ? "on" : "off");
    printf("Write to log file: %s\n", LOG_file_output ? "on" : "off");
    if(LOG_file_output) {
        printf("Log file name: %s\n", LOG_file_name);
        printf("Log file is %s\n", LOG_fp ? "open" : "closed");
    }
    prefix = LOG_prefix(LOG_LEVEL_DEBUG);
    printf("prefix format: %s\n", prefix.str);
}

void LOG_print_error(const char* message) {
    LOG_print_message(message, LOG_LEVEL_ERROR);
}

void LOG_print_warning(const char* message) {
    LOG_print_message(message, LOG_LEVEL_WARNING);
}

void LOG_print_info(const char* message) {
    LOG_print_message(message, LOG_LEVEL_INFO);
}

void LOG_print_debug(const char* message) {
    LOG_print_message(message, LOG_LEVEL_DEBUG);
}

void LOG_print_trace(const char* message) {
    LOG_print_message(message, LOG_LEVEL_TRACE);
}
