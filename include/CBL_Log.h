#ifndef _CBL_LOG_H_
#define _CBL_LOG_H_

#include <time.h>

#include "CBL_Basic.h"
#include "CBL_DateTime.h"
#include "CBL_String.h"

extern Int LOG_output_level;
extern Bool LOG_terminal_output;
extern Bool LOG_file_output;
extern char LOG_file_name[LOG_MAX_FILE_NAME_LENGTH];
extern UInt8 LOG_prefix_format;

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 100
#define LOG_LEVEL_WARNING 200
#define LOG_LEVEL_INFO 300
#define LOG_LEVEL_DEBUG 400
#define LOG_LEVEL_TRACE 500
#define LOG_LEVEL_ALL INT_MAX

#define LOG_PREFIX_DATE      0b00000001
#define LOG_PREFIX_TIME      0b00000010
#define LOG_PREFIX_CLOCK_HMS 0b00000100
#define LOG_PREFIX_CLOCK_SEC 0b00001000
#define LOG_PREFIX_LEVEL_TAG 0b00010000
#define LOG_PREFIX_BRACE     0b10000000

#define LOG_PREFIX_PART 6

void LOG_init();

void LOG_open_log_file();

void LOG_close_log_file();

void LOG_print_message(const char* message, Int level);

void LOG_print_state();

void LOG_print_error(const char* message);

void LOG_print_warning(const char* message);

void LOG_print_info(const char* message);

void LOG_print_debug(const char* message);

void LOG_print_trace(const char* message);

#endif // _CBL_LOG_H_
