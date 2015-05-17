/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * mngmnt_info.h -- for management info
 *
 * Version: 1.0  05/13/2015 11:22:51 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef MODEL_MANAGEMENT_INFO_H
#define MODEL_MANAGEMENT_INFO_H

#include "util/list.h"

// 用户类型(控制用户权限)
typedef
enum user_type {
    UT_ERROR = 0,      // 错误类型
    UT_ADMIN = 1,      // 系统管理员
    UT_MANAGER = 2,    // 经理
    UT_CLERK = 3       // 售票员
} user_type;

// 懒得在 .c 文件里写了，这里用 static 让链接器用各文件局部的算了
static char *user_type_name[] = {
        "ERROR USER",      // 0
        "系统管理员",      // 1
        "经理",            // 2
        "售票员"           // 3
};

#define MAX_USERNAME  (16)  // 最长用户名
#define MAX_PASSWORD  (16)  // 最长密码

// 用户信息
typedef
struct user_info {
    user_type type;                   // 用户类型
    char username[MAX_USERNAME+1];    // 用户名
    char password[MAX_PASSWORD+1];    // 密码
    struct list_head list;            // 链表结构
} user_info;

#define MAX_MOVIE_NAME  (50)
#define MAX_MOVIE_DESC  (200)
#define MAX_TIME        (50)
#define MAX_LANGUAGE    (20)
#define MAX_COUNTRY     (30)
#define MAX_DIRECTOR    (500)

// 剧目信息
typedef
struct movie_info {
    int id;                               // 剧目编号
    char name[MAX_MOVIE_NAME+1];          // 片名
    int duration;                         // 时长(min)
    char director[MAX_DIRECTOR+1];        // 导演
    char language[MAX_LANGUAGE+1];        // 语言
    char country[MAX_COUNTRY+1];          // 国家
    char release_time[MAX_TIME+1];        // 上映时间
    char desc[MAX_MOVIE_DESC+1];          // 描述
    struct list_head list;                // 链表结构
} movie_info;

// 放映厅信息
typedef
struct playhouse {
    int id;                     // 剧场编号
    int seat_count;             // 座位数
    struct list_head list;      // 链表结构
} playhouse;

// 演出场次信息
typedef 
struct action_cutting {
    int id;                          // 场次 id
    int movie_id;                    // 播放的电影 id
    int playhouse_id;                // 放映厅 id
    int fare;                        // 票价
    int seat_count;                  // 总出售票数
    int remaining_seat;              // 剩余数量
    char start_time[MAX_TIME+1];     // 开始时间
    struct list_head list;           // 链表结构
} action_cutting;

#endif  // MODEL_MANAGEMENT_INFO_H

