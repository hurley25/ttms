/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * main.c -- ttms main
 *
 * Version: 1.0  05/13/2015 10:06:44 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include <stdio.h>

#include "util/logger.h"
#include "model/serialize.h"
#include "control/ttms_control.h"

int main(void)
{
    // 初始化日志输出到stderr 或 "ttms.log"
    log_init(stderr);

    // 从文件载入所有数据
    load_all_info();

    // 进入程序控制循环
    control_start();

    // 保存所有数据到文件
    save_all_info();

    // 关闭日志文件
    log_free();

    return 0;
}

