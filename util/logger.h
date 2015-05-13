/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * logger.h -- for logger
 *
 * Version: 1.0  05/13/2015 10:26:59 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <stdio.h>
#include <time.h>

#define __LOG_LINE_MAX  (1024)

extern FILE *__logger_fp;

static inline void __logger_arg(FILE *fp, const char *string, ...)
{
    char __logger_buf[__LOG_LINE_MAX];
    va_list __logger_ap;
    va_start(__logger_ap, string);
    vsnprintf(__logger_buf, __LOG_LINE_MAX, string, __logger_ap);
    va_end(__logger_ap);
    fprintf(fp, "%s", __logger_buf);
}

#define __logger(type, fp, string ...)   \
    ({fprintf(fp, "%s - <%s:%d:%s> => ", type, __FILE__, __LINE__, __FUNCTION__); \
     __logger_arg(fp, string); fprintf(fp, "\n"); fflush(fp);})

/**
 * log_init - init logger
 * @logger: std output (stdout & stderr), or logger file name.
 */
#define log_init(logger)        \
    ({FILE *_logger = (FILE *) logger; \
    if (_logger != stdout && _logger != stderr) \
        __logger_fp = fopen((const char *) logger, "a"); \
    else __logger_fp = _logger;})

/**
 * log_free - free logger
 */
#define log_free()              \
    ({fflush(__logger_fp); \
    if (__logger_fp != stdout && __logger_fp != stderr) \
        fclose(__logger_fp);})

/**
 * log_debug - output log for program debug message
 * @log ...:   log format and args.
 */
#ifdef DEBUG
#define log_debug(log ...)      \
    __logger("DEBUG", __logger_fp, log)
#else
#define log_debug(log ...) ({})
#endif

/**
 * log_info - output log for normal info message
 * @log ...:  log format and args.
 */
#define log_info(log ...)       \
    __logger("INFO ", __logger_fp, log)

/**
 * log_warn - output log for warning message
 * @log ...:  log format and args.
 */
#define log_warn(log ...)       \
    __logger("WARN ", __logger_fp, log)

/**
 * log_error - output log for error message
 * @log ...:   log format and args.
 */
#define log_error(log ...)      \
    __logger("ERROR", __logger_fp, log)

/**
 * log_fatal - output log for failure message
 * @log ...:   log format and args.
 */
#define log_fatal(log ...)      \
    __logger("FATAL", __logger_fp, log)

#endif  // UTIL_LOGGER_H

