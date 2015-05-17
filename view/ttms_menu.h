/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * ttms_menu.h -- for menu
 *
 * Version: 1.0  05/17/2015 07:17:24 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef VIEW_TTMS_MENU_H
#define VIEW_TTMS_MENU_H

#include "model/mngmnt_info.h"

// 显示登陆菜单
void show_login_menu(void);

// 显示用户总菜单
void show_user_menu(user_type type);

// 显示用户管理菜单
void show_user_mng_menu(void);

// 显示放映厅管理菜单
void show_playhouse_mng_menu(void);

// 显示影片管理菜单
void show_movie_mng_menu(void);

// 显示剧目管理菜单
void show_action_cutting_mng_menu(void);

// 显示售票管理菜单
void show_sale_mng_menu(void);

#endif  // VIEW_TTMS_MENU_H
