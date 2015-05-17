/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * password.h -- password input
 *
 * Version: 1.0  2015年05月17日 20时32分26秒
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef UTIL_PASSWORD_H
#define UTIL_PASSWORD_H

// 密码输入函数，参数 passwd 为密码缓冲区，buff_len 为缓冲区长度
char *passwd_input(char *passwd, int buff_len);

#endif  // UTIL_PASSWORD_H
