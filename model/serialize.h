/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * serialize.h -- for Serialization
 *
 * Version: 1.0  05/13/2015 12:52:14 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef MODEL_SERIALIZATION_H
#define MODEL_SERIALIZATION_H

// 从文件载入所有信息
int load_all_info(void);

// 序列化所有信息到文件
int dump_all_info(void);

// 从文件载入用户信息
int load_user_info(void);

// 从文件载入剧目信息
int load_movie_info(void);

// 从文件载入演出厅信息
int load_playhouse_info(void);

// 从文件载入演出安排信息
int load_action_cutting_info(void);

// 序列化用户信息到文件
int dump_user_info(void);

// 序列化剧目信息到文件
int dump_movie_info(void);

// 序列化演出厅信息到文件
int dump_playhouse_info(void);

// 序列化演出安排信息到文件
int dump_action_cutting_info(void);

#endif  // MODEL_SERIALIZATION_H

