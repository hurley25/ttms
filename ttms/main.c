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
#include "model/info_list.h"
#include "model/serialize.h"

int main(void)
{
    log_init(stderr);

    //load_all_info();
    create_origin_data();
    dump_all_info();

    log_free();

    return 0;
}

