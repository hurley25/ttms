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

#include "model/mngmnt_info.h"
#include "model/list_crud.h"
#include "util/cJSON.h"
#include "util/logger.h"

/**
 * 不需要其他模块知道的宏定义不要暴露在头文件里
 * 此处具体载入和输出的数据文件名只在本模块使用
 */
// 数据文件
#define TTMS_DATA_FILE  "ttms.dat"

/**
 * 仅在本文件使用的函数使用 static 限制函数作用域
 */
// 解析用户信息
static int __parse_user_info(cJSON *array);

// 解析演出厅信息
static int __parse_playhouse_info(cJSON *array);

// 解析剧目信息
static int __parse_movie_info(cJSON *array);

// 解析演出安排信息
static int __parse_action_cutting_info(cJSON *array);

// 序列化用户信息
static int __serialize_user_info(cJSON *root);

// 序列化演出厅信息
static int __serialize_playhouse_info(cJSON *root);

// 序列化剧目信息
static int __serialize_movie_info(cJSON *root);

// 序列化演出安排信息
static int __serialize_action_cutting_info(cJSON *root);

// 读取文件
static char *__read_file(const char *filename);

// 写入文件
static int __write_file(const char *filename, const char *data, size_t length);

// 从文件载入所有信息
int load_all_info(void)
{
    char *data = NULL;
    cJSON *root = NULL;

    data = __read_file(TTMS_DATA_FILE);
    if (data == NULL) {
        return -1;
    }
    root = cJSON_Parse(data);
    if (!root) {
        log_error("Parse Json Error! Error before: [%s]", cJSON_GetErrorPtr());
        return -1;
    }

    __parse_user_info(cJSON_GetObjectItem(root, "user"));
    __parse_playhouse_info(cJSON_GetObjectItem(root, "playhouse"));
    __parse_movie_info(cJSON_GetObjectItem(root, "movie"));
    __parse_action_cutting_info(cJSON_GetObjectItem(root, "action_cutting"));

    cJSON_Delete(root);
    free(data);

    return 0;
}

// 保存所有信息到文件
int save_all_info(void)
{
    char *tmp = NULL;
    char *data = NULL;
    int data_len;
    cJSON *root = NULL;
    
    root = cJSON_CreateObject();

    __serialize_user_info(root);
    __serialize_playhouse_info(root);
    __serialize_movie_info(root);
    __serialize_action_cutting_info(root);

    tmp = cJSON_Print(root);
    cJSON_Delete(root);
    
    data_len = strlen(tmp);
    data = (char *)malloc(data_len + 2); // data_len + '\n' + '\0'

    strncpy(data, tmp, data_len);
    data[data_len] = '\n';
    data[data_len + 1] = '\0';

    __write_file(TTMS_DATA_FILE, data, data_len + 1);
    free(tmp);
    free(data);

    return 0;
}

// 解析用户信息
static int __parse_user_info(cJSON *array)
{
    cJSON *item = NULL;
    int array_size = 0;
    int i = 0;

    array_size = cJSON_GetArraySize(array);

    for (i = 0; i < array_size; ++i) {
        item = cJSON_GetArrayItem(array, i);
        add_user_info(
                cJSON_GetObjectItem(item, "type")->valueint,
                cJSON_GetObjectItem(item, "username")->valuestring,
                cJSON_GetObjectItem(item, "password")->valuestring
        );
    }

    return 0;
}

// 解析演出厅信息
static int __parse_playhouse_info(cJSON *array)
{
    cJSON *item = NULL;
    int array_size = 0;
    int i = 0;

    array_size = cJSON_GetArraySize(array);

    for (i = 0; i < array_size; ++i) {
        item = cJSON_GetArrayItem(array, i);
        add_playhouse(
                cJSON_GetObjectItem(item, "id")->valueint,
                cJSON_GetObjectItem(item, "seat_count")->valueint
        );
    }

    return 0;
}

// 解析剧目信息
static int __parse_movie_info(cJSON *array)
{
    cJSON *item = NULL;
    int array_size = 0;
    int i = 0;

    array_size = cJSON_GetArraySize(array);

    for (i = 0; i < array_size; ++i) {
        item = cJSON_GetArrayItem(array, i);
        add_movie_info(
                cJSON_GetObjectItem(item, "id")->valueint,
                cJSON_GetObjectItem(item, "name")->valuestring,
                cJSON_GetObjectItem(item, "duration")->valueint,
                cJSON_GetObjectItem(item, "director")->valuestring,
                cJSON_GetObjectItem(item, "language")->valuestring,
                cJSON_GetObjectItem(item, "country")->valuestring,
                cJSON_GetObjectItem(item, "release_time")->valuestring,
                cJSON_GetObjectItem(item, "desc")->valuestring
        );
    }

    return 0;
}

// 解析演出安排信息
static int __parse_action_cutting_info(cJSON *array)
{
    cJSON *item = NULL;
    int array_size = 0;
    int i = 0;

    array_size = cJSON_GetArraySize(array);

    for (i = 0; i < array_size; ++i) {
        item = cJSON_GetArrayItem(array, i);
        add_action_cutting(
                cJSON_GetObjectItem(item, "id")->valueint,
                cJSON_GetObjectItem(item, "movie_id")->valueint,
                cJSON_GetObjectItem(item, "playhouse_id")->valueint,
                cJSON_GetObjectItem(item, "fare")->valueint,
                cJSON_GetObjectItem(item, "seat_count")->valueint,
                cJSON_GetObjectItem(item, "remaining_seat")->valueint,
                cJSON_GetObjectItem(item, "start_time")->valuestring
        );
    }

    return 0;
}

// 序列化用户信息
static int __serialize_user_info(cJSON *root)
{
    cJSON *array = NULL;
    cJSON *item = NULL;
    
    array = cJSON_CreateArray();

    user_info *ui_node = NULL;
    list_for_each_entry(ui_node, &user_list_head, list) {

        item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "type", ui_node->type);
        cJSON_AddStringToObject(item, "username", ui_node->username);
        cJSON_AddStringToObject(item, "password", ui_node->password);

        cJSON_AddItemToArray(array, item);
    }

    cJSON_AddItemToObject(root, "user", array);

    return 0;
}

// 序列化演出厅信息
static int __serialize_playhouse_info(cJSON *root)
{
    cJSON *array = NULL;
    cJSON *item = NULL;
    
    array = cJSON_CreateArray();

    playhouse *ph_node = NULL;
    list_for_each_entry(ph_node, &playhouse_list_head, list) {

        item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "id", ph_node->id);
        cJSON_AddNumberToObject(item, "seat_count", ph_node->seat_count);

        cJSON_AddItemToArray(array, item);
    }

    cJSON_AddItemToObject(root, "playhouse", array);

    return 0;
}

// 序列化剧目信息
static int __serialize_movie_info(cJSON *root)
{
    cJSON *array = NULL;
    cJSON *item = NULL;
    
    array = cJSON_CreateArray();

    movie_info *mi_node = NULL;
    list_for_each_entry(mi_node, &movie_list_head, list) {

        item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "id", mi_node->id);
        cJSON_AddStringToObject(item, "name", mi_node->name);
        cJSON_AddNumberToObject(item, "duration", mi_node->duration);
        cJSON_AddStringToObject(item, "director", mi_node->director);
        cJSON_AddStringToObject(item, "language", mi_node->language);
        cJSON_AddStringToObject(item, "country", mi_node->country);
        cJSON_AddStringToObject(item, "release_time", mi_node->release_time);
        cJSON_AddStringToObject(item, "desc", mi_node->desc);

        cJSON_AddItemToArray(array, item);
    }

    cJSON_AddItemToObject(root, "movie", array);

    return 0;
}

// 序列化演出安排信息
static int __serialize_action_cutting_info(cJSON *root)
{
    cJSON *array = NULL;
    cJSON *item = NULL;
    
    array = cJSON_CreateArray();

    action_cutting *ac_node = NULL;
    list_for_each_entry(ac_node, &action_cutting_list_head, list) {

        item = cJSON_CreateObject();
        cJSON_AddNumberToObject(item, "id", ac_node->id);
        cJSON_AddNumberToObject(item, "movie_id", ac_node->movie_id);
        cJSON_AddNumberToObject(item, "playhouse_id", ac_node->playhouse_id);
        cJSON_AddNumberToObject(item, "fare", ac_node->fare);
        cJSON_AddNumberToObject(item, "seat_count", ac_node->seat_count);
        cJSON_AddNumberToObject(item, "remaining_seat", ac_node->remaining_seat);
        cJSON_AddStringToObject(item, "start_time", ac_node->start_time);

        cJSON_AddItemToArray(array, item);
    }

    cJSON_AddItemToObject(root, "action_cutting", array);

    return 0;
}

// 读取文件
static char *__read_file(const char *filename)
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
static int __write_file(const char *filename, const char *data, size_t length)
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

