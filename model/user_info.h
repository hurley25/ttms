/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * user_info.h -- user_info struct
 *
 * Version: 1.0  05/13/2015 11:10:36 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef MODEL_USER_INFO_H
#define MODEL_USER_INFO_H

// 用户类型(控制用户权限)
typedef
enum user_type {
    ADMIN = 0,      // 系统管理员
    MANAGER = 1,    // 经理
    CLERK = 2       // 售票员
} user_type;

#define MAX_USERNAME  (16)  // 最长用户名
#define MAX_PASSWORD  (16)  // 最长密码

// 用户信息
typedef
struct user_info {
    user_type type;                 // 用户类型
    char username[MAX_USERNAME];    // 用户名
    char password[MAX_PASSWORD];    // 密码
} user_info;

#endif  // MODEL_USER_INFO_H
