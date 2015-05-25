/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * ttms_control.c -- for ttms control
 *
 * Version: 1.0  05/17/2015 07:20:35 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include "control/ttms_control.h"

#include <stdio.h>
#include <stdlib.h>

#include "view/ttms_menu.h"
#include "model/mngmnt_info.h"
#include "model/list_crud.h"
#include "util/password.h"

/**
 * 注意scanf 并不会清除缓冲区里遗留的 \n
 * 如果紧接着 scanf 再调用 getchar，缓冲区里的 \n 会被 getchar 获取到
 * 所以在调用 getchar 之前需要清除缓冲区，否则无法实现按回车键继续
 * 另外，使用 fflush(stdin) 的做法也可以的，不过个别老版本的C函数库会有问题，这里的清理缓冲区可以通用。
 */
static void __clear_input_buffer(void)
{
    while (getchar() != '\n')
        ;
}

static void __ttms_pause(void)
{
    __clear_input_buffer();
    getchar();
}

// 程序状态
typedef
enum ttms_state {
    TS_SHOW_LOGIN_MENU,
    TS_SHOW_USER_MENU,
    TS_EXIT
} ttms_state;

// 用户登录
static int user_login(void);

// 用户总菜单控制
static int user_menu_control(void);

// 系统管理员菜单控制
static int admin_menu_control(void);

// 经理菜单控制
static int manager_menu_control(void);

// 售票员菜单控制
static int clerk_menu_control(void);

// 用户管理菜单控制
static void user_mng_menu_control(void);

// 放映厅管理菜单控制
static void playhouse_mng_menu_control(void);

// 影片管理菜单控制
static void movie_mng_menu_control(void);

// 剧目管理菜单控制
static void action_cutting_mng_menu_control(void);

// 售票管理菜单控制
static void sale_mng_menu_control(void);

// 销售额查看
static void show_sales_volume(void);

// 程序状态控制(有限状态机)
void control_start(void)
{
    static ttms_state state = TS_SHOW_LOGIN_MENU;

    while (state != TS_EXIT) {
        switch (state) {
            case TS_SHOW_LOGIN_MENU:
                if (user_login() != -1) {
                    state = TS_SHOW_USER_MENU;
                }
                break;
            case TS_SHOW_USER_MENU:
                if (user_menu_control() == -1) {
                    state = TS_SHOW_LOGIN_MENU;
                } else {
                    state = TS_EXIT;
                }
                break;
            default:
                break;
        }
    }
}

// 当前登陆用户级别
static user_type __current_user_type = UT_ERROR;

// 用户登录
static int user_login(void)
{
    static int error_count = 0;
    char username[MAX_USERNAME+1];
    char password[MAX_PASSWORD+1];

    show_login_menu();

    // 时间关系，不对输入的长度做控制了，实际的系统肯定要控制长度的
    // 要假设用户永远是 "恶意的"
    printf("请输入用户名: ");
    scanf("%s", username);

    __clear_input_buffer();
    printf("请输入密码: " );
    passwd_input(password, MAX_PASSWORD);

    user_type type = check_user_password(username, password);
    if (type != UT_ERROR) {
        __current_user_type = type;
        printf("\n\n登陆成功! 您的身份是 [%s]。请按 回车键 继续～", user_type_name[type]);
        getchar();
        return 0;
    }

    if (++error_count >= 3) {
        printf("\n\n用户名/密码 错误次数太多，系统退出～\n");
        exit(0);
    }
    printf("\n\n用户名/密码 错误，按 回车键 继续～");
    getchar();

    return -1;
}

// 显示用户菜单
static int user_menu_control(void)
{
    switch (__current_user_type) {
        case UT_ADMIN:
            return admin_menu_control();
        case UT_MANAGER:
            return manager_menu_control();
        case UT_CLERK:
            return clerk_menu_control();
        default:
            break;
    }

    return 0;
}

// 系统管理员菜单控制
static int admin_menu_control(void)
{
    int choose = -1;

    while (choose != 0 && choose != 1) {
        show_user_menu(__current_user_type);
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
            // 注销
            case 1:
                break;
            // 用户管理
            case 2:
                user_mng_menu_control();
                break;
            // 放映厅管理
            case 3:
                playhouse_mng_menu_control();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
    if (choose == 0) {
        return -2;
    }

    return -1;
}

// 经理菜单控制
static int manager_menu_control(void)
{
    int choose = -1;

    while (choose != 0 && choose != 1) {
        show_user_menu(__current_user_type);
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
            // 注销
            case 1:
                break;
            // 影片管理
            case 2:
                movie_mng_menu_control();
                break;
            // 剧目管理
            case 3:
                action_cutting_mng_menu_control();
                break;
            // 售票管理
            case 4:
                sale_mng_menu_control();
                break;
            // 销售额查看
            case 5:
                show_sales_volume();
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
    if (choose == 0) {
        return -2;
    }

    return -1;
}

// 售票员菜单控制
static int clerk_menu_control(void)
{
    int choose = -1;

    while (choose != 0 && choose != 1) {
        show_user_menu(__current_user_type);
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
            // 注销
            case 1:
                break;
            // 售票管理
            case 2:
                sale_mng_menu_control();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
    if (choose == 0) {
        return -2;
    }

    return -1;
}

// 输出用户信息结构
static void print_user_info(user_info *ui_node)
{
    printf("用户名: %-10s  类型: %-10s\n", ui_node->username, user_type_name[ui_node->type]);
}

// 用户管理菜单控制
static void user_mng_menu_control(void)
{
    int choose = -1;
    user_type type;
    char username[MAX_USERNAME+1];
    char password[MAX_PASSWORD+1];

    while (choose != 0) {
        show_user_mng_menu();
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
                break;
            // 查看用户列表
            case 1:
                for_range_user_info(print_user_info);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 增加用户
            case 2:
                // 时间关系，不对输入做过多检测了，假定输入是可信的
                printf("请依次输入用户类型、用户名、密码(空格分隔)~\n");
                printf("用户类型为数字，含义为:\n1 系统管理员\n2 经理\n3 售票员\n\n");
                scanf("%d%s%s", &type, username, password);
                add_user_info(type, username, password);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 删除用户
            case 3:
                printf("请输入要删除用户的用户名: ");
                scanf("%s", username);
                del_user_info_by_name(username);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
}

// 输出放映厅信息结构
static void print_playhouse(playhouse *ph_node)
{
    printf("ID: %d  座位数: %d\n", ph_node->id, ph_node->seat_count);
}

// 放映厅管理菜单控制
static void playhouse_mng_menu_control(void)
{
    int choose = -1;
    int id = 0;
    int seat_count = 0;

    while (choose != 0) {
        show_playhouse_mng_menu();
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
                break;
            // 查看放映厅列表
            case 1:
                for_range_playhouse(print_playhouse);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 增加放映厅
            case 2:
                // 时间关系，代码不检测 ID 是否存在
                printf("请依次输入放映厅 ID 和 座位数(空格分隔，注意 ID 别重复了)\n");
                scanf("%d%d", &id, &seat_count);
                add_playhouse(id, seat_count);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 删除放映厅
            case 3:
                printf("请输入要删除的放映厅的 ID，该 ID 的放映厅会被全部删除～\n");
                scanf("%d", &id);
                del_playhouse_by_id(id);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
}

// 输出影片信息结构
static void print_movie_info(movie_info *mi_node)
{
    // 中文在终端上因字体的不同，这里的格式控制不好做...
    // 当然，windows 控制台字体一般没人改.. 有兴趣的话在 windows 下慢慢调合适吧...
    printf("ID: %-4d  片名: %-20s  时长: %-4d  导演: %-10s  语言: %-10s  国家: %-10s  上映时间: %-8s \n\t\t描述: %s\n",
            mi_node->id, mi_node->name, mi_node->duration, mi_node->director, mi_node->language,
            mi_node->country, mi_node->release_time, mi_node->desc);
}

// 影片管理菜单控制
static void movie_mng_menu_control(void)
{
    int choose = -1;
    int id;                               // 剧目编号
    char name[MAX_MOVIE_NAME+1];          // 片名
    int duration;                         // 时长(min)
    char director[MAX_DIRECTOR+1];        // 导演
    char language[MAX_LANGUAGE+1];        // 语言
    char country[MAX_COUNTRY+1];          // 国家
    char release_time[MAX_TIME+1];        // 上映时间
    char desc[MAX_MOVIE_DESC+1];          // 描述

    while (choose != 0) {
        show_movie_mng_menu();
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
                break;
            // 查看影片列表
            case 1:
                for_range_movie_info(print_movie_info);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 增加影片
            case 2:
                printf("请输入 ID: ");
                scanf("%d", &id);
                printf("请输入 片名: ");
                scanf("%s", name);
                printf("请输入 时长: ");
                scanf("%d", &duration);
                printf("请输入 导演: ");
                scanf("%s", director);
                printf("请输入 语言: ");
                scanf("%s", language);
                printf("请输入 国家: ");
                scanf("%s", country);
                printf("请输入 上映时间: ");
                scanf("%s", release_time);
                printf("请输入 描述: ");
                scanf("%s", desc);
                add_movie_info(id, name, duration, director, language, country, release_time, desc);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 删除影片
            case 3:
                printf("请输入要删除的影片的 ID，该 ID 的影片会被全部删除～\n");
                scanf("%d", &id);
                del_movie_info_by_id(id);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
}

// 输出场次信息结构
static void print_action_cutting(action_cutting *ac_node)
{
    printf("场次ID: %d  电影: %d  放映厅ID %d  票价: %d  总出售票数: %d  剩余数量: %d  开始时间: %s\n",
            ac_node->id, ac_node->movie_id, ac_node->playhouse_id, ac_node->fare, ac_node->seat_count,
            ac_node->remaining_seat, ac_node->start_time);
}

// 剧目管理菜单控制
static void action_cutting_mng_menu_control(void)
{
    int choose = -1;
    int id;                          // 场次 id
    int movie_id;                    // 播放的电影 id
    int playhouse_id;                // 放映厅 id
    int fare;                        // 票价
    int seat_count;                  // 总出售票数
    int remaining_seat;              // 剩余数量
    char start_time[MAX_TIME+1];     // 开始时间

    while (choose != 0) {
        show_action_cutting_mng_menu();
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
                break;
            // 查看放映剧目列表
            case 1:
                for_range_action_cutting(print_action_cutting);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 增加放映场次影片
            case 2:
                printf("\n目前可放映:\n\n");
                for_range_movie_info(print_movie_info);
                printf("\n已有场次:\n\n");
                for_range_action_cutting(print_action_cutting);
                printf("\n请依次输入以下场次信息\n");
                printf("请输入 ID: ");
                scanf("%d", &id);
                printf("请输入电影 ID: ");
                scanf("%d", &movie_id);
                printf("请输入放映厅 ID: ");
                scanf("%d", &playhouse_id);
                printf("请输入票价: ");
                scanf("%d", &fare);
                printf("请输入座位数: ");
                scanf("%d", &seat_count);
                remaining_seat = seat_count;
                printf("请输入起始时间: ");
                scanf("%s", start_time);
                add_action_cutting(id, movie_id, playhouse_id, fare, seat_count, remaining_seat, start_time);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            // 删除放映场次
            case 3:
                printf("请输入要删除的放映场次的 ID，该 ID 的放映场次会被全部删除～\n");
                scanf("%d", &id);
                del_action_cutting_by_id(id);
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
}

// 售票管理菜单控制
static void sale_mng_menu_control(void)
{
    int choose = -1;
    int id;
    int count;

    while (choose != 0) {
        show_sale_mng_menu();
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            // 退出
            case 0:
                break;
            // 售票
            case 1:
                printf("\n目前场次:\n\n");
                for_range_action_cutting(print_action_cutting);
                printf("\n请输入要售票的场次ID: ");
                scanf("%d", &id);
                printf("请输入要售票的场次数量: ");
                scanf("%d", &count);
                if (sale_action_cutting_by_id_count(id, count) != 0) {
                    printf("售票失败，请核对场次 ID 和 剩余票数～");
                } else {
                    printf("售票成功～");
                }
                printf("\n按回车键继续~\n\n");
                __ttms_pause();
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __ttms_pause();
        }
    }
}

// 销售额查看
static void show_sales_volume(void)
{
    printf("\n目前的销售额为: %d 元～\n", get_sales_volume());
}

