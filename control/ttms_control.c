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
 * 另外，flush(stdin) 的做法按照 C 标准是未定义行为，即使可用也不能依赖
 */
static void __clear_input_buffer(void)
{
    while (getchar() != '\n')
        ;
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

// 显示用户菜单
static int user_menu_control(void);

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
    int choose = -1;

    while (choose != 0) {
        show_user_menu(__current_user_type);
        printf("请输入菜单功能编号: ");
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                break;
            default:
                printf("您的输入有误，请按回车键重新选择～");
                __clear_input_buffer();
                getchar();
        }
    }

    return -1;
}

