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

#ifndef _CBL_LOG_H_
#define _CBL_LOG_H_

#include <limits.h>
#include "Module_Basic.h"

/**
 * @brief output level, choose from \n
 * LOG_LEVEL_NONE \n
 * LOG_LEVEL_ERROR \n
 * LOG_LEVEL_WARNING \n
 * LOG_LEVEL_INFO \n
 * LOG_LEVEL_DEBUG \n
 * LOG_LEVEL_TRACE \n
 * LOG_LEVEL_ALL INT_MAX
 */
extern Int LOG_output_level;

/**
 * @brief switch terminal output, default is true
 */
extern Bool LOG_terminal_output;

/**
 * @brief switch log file output, default is false
 */
extern Bool LOG_file_output;

/**
 * @brief LOG_file_name
 */
extern Char LOG_file_name[LOG_MAX_FILE_NAME_LENGTH];

/**
 * @brief set prefix format for each line of log \n
 * if turn on all prefix component, it looks like:\n
 * \n
 * [LEVEL_TAG DATE TIME CLOCK]\n
 * \n
 * []: turn on using LOG_PREFIX_BRACKET\n\n
 * LEVEL_TAG: turn on using LOG_PREFIX_LEVEL_TAG\n\n
 * DATE: local date, turn on using LOG_PREFIX_DATE\n\n
 * TIME: local time, turn on using LOG_PREFIX_TIME\n\n
 * CLOCK: time since the program begined, using LOG_PREFIX_SEC to print a float in seconds,
 * using LOG_PREFIX_HMS to print as hh:mm:ss.SSS format. When both is turned on, the LOG_PREFIX_SEC
 * will work\n
 * \n
 * The flags can be used jointly, for example:\n
 * LOG_prefix_format = LOG_PREFIX_BRACKET | LOG_PREFIX_TIME | LOG_PREFIX_SEC;
 */
extern UInt8 LOG_prefix_format;

#define LOG_LEVEL_NONE    0
#define LOG_LEVEL_ERROR   100
#define LOG_LEVEL_WARNING 200
#define LOG_LEVEL_INFO    300
#define LOG_LEVEL_DEBUG   400
#define LOG_LEVEL_TRACE   500
#define LOG_LEVEL_ALL     CBL_INT_MAX

#define LOG_PREFIX_DATE      0b00000001
#define LOG_PREFIX_TIME      0b00000010
#define LOG_PREFIX_CLOCK_HMS 0b00000100
#define LOG_PREFIX_CLOCK_SEC 0b00001000
#define LOG_PREFIX_LEVEL_TAG 0b00010000
#define LOG_PREFIX_BRACKET   0b10000000
#define LOG_PREFIX_ALL (LOG_PREFIX_BRACKET | LOG_PREFIX_LEVEL_TAG | \
LOG_PREFIX_DATE | LOG_PREFIX_TIME | LOG_PREFIX_CLOCK_SEC)

#define LOG_PREFIX_PART 6

/**
 * @brief initialize global variables
 */
void LOG_init(const char* file_name);

/**
 * @brief flush file buffer of log file if opened
 */
void LOG_flush();

/**
 * @brief finalize process, including closing log file
 */
void LOG_final();

/**
 * @brief open log file if it is not opened, file name stored in global variable LOG_file_name
 */
void LOG_open_log_file();

/**
 * @brief close log file if it is opened
 */
void LOG_close_log_file();

void LOG_print_message(const char* message, Int level);

/**
 * @brief print current log global variable
 */
void LOG_print_state();

static void LOG_print_error(const char* message) { LOG_print_message(message, LOG_LEVEL_ERROR); }
static void LOG_print_warning(const char* message) { LOG_print_message(message, LOG_LEVEL_WARNING); }
static void LOG_print_info(const char* message) { LOG_print_message(message, LOG_LEVEL_INFO); }
static void LOG_print_debug(const char* message) { LOG_print_message(message, LOG_LEVEL_DEBUG); }
static void LOG_print_trace(const char* message) { LOG_print_message(message, LOG_LEVEL_TRACE); }

#endif // _CBL_LOG_H_
