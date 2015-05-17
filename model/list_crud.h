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
void del_user_info_by_name(const char *username);

// 删除放映厅
void del_playhouse_by_id(int id);

// 删除剧目
void del_movie_info_by_id(int id);

// 删除场次
void del_action_cutting_by_id(int id);

/**
 * 以下 4 个 for_range_* 函数对链表的每个元素调用参数给出的回调函数(回调函数删除该元素是安全的)
 *
 * 这么做的原因是不希望暴露出具体的存储结构给 model 模块之外的模块，使得具体存储结构倘若
 * 发生变化，也不会影响到其他模块的代码。其它模块遍历 model 模块管理的元素的方法是提供对单个
 * 元素进行处理的函数，调用以下函数进行处理。除了当前的实现，也可以模拟出迭代器模式来实现。
 */

// 遍历用户信息(对每个元素调用参数给出的回调函数，回调函数可删除该元素)
void for_range_user_info(void (*func)(user_info *));

// 遍历放映厅信息
void for_range_playhouse(void (*func)(playhouse *));

// 遍历剧目信息
void for_range_movie_info(void (*func)(movie_info *));

// 遍历场次信息
void for_range_action_cutting(void (*func)(action_cutting *));

// 初始化原始数据(生成测试数据)
void create_origin_data(void);

// 检查用户密码
user_type check_user_password(const char *username, const char *password);

#endif  // MODEL_INFO_LIST_H

