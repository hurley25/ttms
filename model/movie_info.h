/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * movie_info.h -- for movie info
 *
 * Version: 1.0  05/13/2015 11:22:51 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef MODEL_MOVIE_INFO_H
#define MODEL_MOVIE_INFO_H

#include <time.h>

#define MAX_MOVIE_NAME  (50)
#define MAX_MOVIE_DESC  (200)
#define MAX_TIME_INFO   (40)
#define MAX_LANGUAGE    (20)
#define MAX_COUNTRY     (30)
#define MAX_DIRECTOR    (30)

// 剧目信息
typedef
struct movie_info {
    int id;                             // 剧目编号
    char name[MAX_MOVIE_NAME];          // 片名
    int duration;                       // 时长(min)
    char director[MAX_DIRECTOR];        // 导演
    char language[MAX_LANGUAGE];        // 语言
    char country[MAX_COUNTRY];          // 国家
    char release_time[MAX_TIME_INFO];   // 上映时间
    char info[MAX_MOVIE_DESC];          // 描述
} movie_info;

#define SEAT_COUNT      (100)           // 默认座位数都为 100

// 放映厅信息
typedef
struct playhouse {
    int id;             // 剧场编号
    int seat_count;     // 座位数
} playhouse;

#define MAX_TIME        (50)

// 演出场次信息
typedef 
struct action_cutting {
     int movie_id;                  // 播放的电影 id
     int playhouse_id;              // 放映厅 id
     double fare;                   // 票价
     char start_time[MAX_TIME];     // 开始时间
} action_cutting;

#endif  // MODEL_MOVIE_INFO_H

