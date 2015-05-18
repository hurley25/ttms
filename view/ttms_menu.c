/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * ttms_menu.c -- for menu
 *
 * Version: 1.0  05/17/2015 07:17:35 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include "view/ttms_menu.h"

#include <stdio.h>
#include <stdlib.h>

#define SHOW_MENU_TOP  { printf("----------------------------------------------------\n"    \
                                "----------------   剧场票务管理系统   --------------\n"    \
                                "----------------------------------------------------\n\n"); }

// 清屏
static void __console_clear(void)
{
#ifdef _WIN32
    // windows
    system("cls");
#else
    // linux
    system("clear");
#endif
}

// 显示登陆菜单
void show_login_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("请登陆后使用本系统～\n\n");
}

// 显示用户菜单
void show_user_menu(user_type type)
{
    __console_clear();
    SHOW_MENU_TOP

    switch (type) {
        case UT_ADMIN:
            printf("\t2. 用户管理\n");
            printf("\t3. 放映厅管理\n\n");
            break;
        case UT_MANAGER:
            printf("\t2. 影片管理\n");
            printf("\t3. 剧目管理\n");
            printf("\t4. 售票管理\n");
            printf("\t5. 销售额查看\n\n");
            break;
        case UT_CLERK:
            printf("\t2. 售票管理\n\n");
            break;
        case UT_ERROR:
        default:
            break;
    }
    printf("\t1. 注销登陆\n");
    printf("\t0. 退出系统\n\n");
}

// 显示用户管理菜单
void show_user_mng_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("\t1. 查看用户列表\n");
    printf("\t2. 增加用户\n");
    printf("\t3. 删除用户\n\n");
    printf("\t0. 返回上级菜单\n\n");
}

// 显示放映厅管理菜单
void show_playhouse_mng_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("\t1. 查看放映厅列表\n");
    printf("\t2. 增加放映厅\n");
    printf("\t3. 删除放映厅\n\n");
    printf("\t0. 返回上级菜单\n\n");
}

// 显示影片管理菜单
void show_movie_mng_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("\t1. 查看影片列表\n");
    printf("\t2. 增加影片\n");
    printf("\t3. 删除影片\n\n");
    printf("\t0. 返回上级菜单\n\n");
}

// 显示剧目管理菜单
void show_action_cutting_mng_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("\t1. 查看放映剧目列表\n");
    printf("\t2. 增加放映场次影片\n");
    printf("\t3. 删除放映场次\n\n");
    printf("\t0. 返回上级菜单\n\n");
}

// 显示售票管理菜单
void show_sale_mng_menu(void)
{
    __console_clear();
    SHOW_MENU_TOP

    printf("\t1. 售票\n\n");
    printf("\t0. 返回上级菜单\n\n");
}

