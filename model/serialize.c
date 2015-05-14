/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * serialize.h -- for Serialization
 *
 * Version: 1.0  05/13/2015 01:30:43 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

/**
 * 头文件包含顺序：
 * 本代码文件的头文件、C库函数头文件、系统头文件、本项目其他模块头文件
 */
#include "model/serialize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "model/management_info.h"
#include "model/info_list.h"
#include "util/logger.h"

/**
 * 不需要其他模块知道的宏定义不要暴露在头文件里
 * 此处具体载入和输出的数据文件名只在本模块使用
 */
// 用户信息文件
#define USER_DATA_FILE = "user_data.dat";

// 放映厅信息文件
#define PLAYHOUSE_FILE = "playhouse_data.dat"

// 剧目信息文件
#define MOVIE_DATA_FILE = "movie_data.dat"

// 场次信息文件
#define ACTION_CUTTING_DATA_FILE = "action_cutting_data.dat"

/**
 * 仅在本文件使用的函数使用 static 限制函数作用域
 */

// 读取文件
static char *read_file(const char *filename);

// 写入文件
static int write_file(const char *filename, const char *data, size_t length);

// 从文件载入所有信息
int load_all_info(void)
{
    if (load_user_info() == -1) {
        return -1;
    }
    if (load_movie_info() == -1) {
        return -1;
    }
    if (load_playhouse_info() == -1) {
        return -1;
    }
    if (load_action_cutting_info() == -1) {
        return -1;
    }

    return 0;
}

// 序列化所有信息到文件
int dump_all_info(void)
{
    if (dump_user_info() == -1) {
        return -1;
    }
    if (dump_movie_info() == -1) {
        return -1;
    }
    if (dump_playhouse_info() == -1) {
        return -1;
    }
    if (dump_action_cutting_info() == -1) {
        return -1;
    }

    return 0;
}

// 从文件载入用户信息
int load_user_info(void)
{
    
    return 0;
}

// 从文件载入剧目信息
int load_movie_info(void)
{

    return 0;
}

// 从文件载入演出厅信息
int load_playhouse_info(void)
{

    return 0;
}

// 从文件载入演出安排信息
int load_action_cutting_info(void)
{

    return 0;
}

// 序列化用户信息到文件
int dump_user_info(void)
{

    return 0;
}

// 序列化剧目信息到文件
int dump_movie_info(void)
{

    return 0;
}

// 序列化演出厅信息到文件
int dump_playhouse_info(void)
{

    return 0;
}

// 序列化演出安排信息到文件
int dump_action_cutting_info(void)
{

    return 0;
}

// 读取文件
static char *read_file(const char *filename)
{
    FILE *file;
    size_t file_len;
    char *data;
	
	file = fopen(filename, "r");
    if (file == NULL) {
        log_error("Open File %s Error: %s", filename, strerror(errno));
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

	data = (char *)malloc(file_len + 1); // file_len + '\0'
    if (data == NULL) {
        log_error("Malloc(%d) Error: %s", file_len + 1, strerror(errno));
        fclose(file);
        return NULL;
    }
    if (fread(data, 1, file_len, file) != file_len) {
        log_error("Read File %s Error: %s", filename, strerror(errno));
        free(data);
        fclose(file);
        return NULL;
    }
    fclose(file);

    return data;
}

// 写入文件
static int write_file(const char *filename, const char *data, size_t length)
{
    FILE *file;
	
	file = fopen(filename, "w");
    if (file == NULL) {
        log_error("Open File %s Error: %s", filename, strerror(errno));
        return -1;
    }
    if (fwrite(data, 1, length, file) != length) {
        log_error("Write File %s Error: %s", filename, strerror(errno));
        fclose(file);
        return -1;
    }
    fclose(file);

    return 0;
}
