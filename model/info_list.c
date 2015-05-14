/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * info_list.c -- info list
 *
 * Version: 1.0  05/13/2015 01:53:20 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include "model/info_list.h"

// 用户信息链表
struct list_head user_list = LIST_HEAD_INIT(user_list);

// 放映厅信息链表
struct list_head playhouse_list = LIST_HEAD_INIT(playhouse_list);

// 剧目信息链表
struct list_head movie_list = LIST_HEAD_INIT(movie_list);

// 场次信息链表
struct list_head action_cutting_list = LIST_HEAD_INIT(action_cutting_list);

