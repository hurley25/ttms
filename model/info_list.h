/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * info_list.h -- info list
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

// 用户信息链表
extern struct list_head user_list;

// 放映厅信息链表
extern struct list_head playhouse_list;

// 剧目信息链表
extern struct list_head movie_list;

// 场次信息链表
extern struct list_head action_cutting_list;

#endif  // MODEL_INFO_LIST_H

