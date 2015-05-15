/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * list_crud.h -- info list crud
 *
 * Version: 1.0  05/13/2015 12:37:01 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef MODEL_INFO_LIST_H
#define MODEL_INFO_LIST_H

#include "util/list.h"
#include "model/mngmnt_info.h"

// 用户信息链表
extern struct list_head user_list_head;

// 放映厅信息链表
extern struct list_head playhouse_list_head;

// 剧目信息链表
extern struct list_head movie_list_head;

// 场次信息链表
extern struct list_head action_cutting_list_head;

// 添加用户
void add_user_info(user_type type, const char *username, const char *password);
void add_user_info_node(user_info *ui_node);

// 添加放映厅
void add_playhouse(int id, int seat_count);
void add_playhouse_node(playhouse *ph_node);

// 添加剧目
void add_movie_info(int id, const char *name, int duration,
                    const char *director, const char *language,
                    const char *country, const char *release_time,
                    const char *desc);
void add_movie_info_node(movie_info *mi_node);

// 添加场次
void add_action_cutting(int id, int movie_id, int playhouse_id, double fare,
                            int seat_count, int remaining_seat, const char *start_time);
void add_action_cutting_node(action_cutting *ac_node);

// 删除用户
int del_user_info_by_name(const char *name);

// 删除放映厅
int del_playhouse_by_id(int id);

// 删除剧目
int del_movie_info_by_id(int id);

// 删除场次
int del_action_cutting_by_id(int id);

// 初始化原始数据(生成测试数据)
void create_origin_data(void);

#endif  // MODEL_INFO_LIST_H

