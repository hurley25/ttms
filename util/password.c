/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * password.c -- password input
 *
 * Version: 1.0  2015年05月17日 20时30分14秒
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include "util/password.h"
#include "util/logger.h"

#ifndef _WIN32 // 如果不是WIN32环境，则要自定义getch()函数
#include <termio.h>
 
static int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
 
     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }
 
     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }
 
     ch = fgetc(stdin);
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
          return -1;
     }
    
     return ch;
}
#else
#include <conio.h>
#endif // _WIN32
 
// 密码输入函数，参数 passwd 为密码缓冲区，buff_len 为缓冲区长度
char *passwd_input(char *passwd, int buff_len)
{
     char str;
     int i = 0;
     int enter_num = 13;
     int backspace_num;
 
     #ifndef _WIN32
     backspace_num = 127;
     #else
     backspace_num = 8;
     #endif

     if (passwd == NULL || buff_len <= 0) {
          return passwd;
     }

     while (1)
     {
          // 如果没有按下退格键 
          if ((str = getch()) != (char)backspace_num) {
               if (i < buff_len - 1) {
                    passwd[i++] = str;
                    printf("*");
               } 
          } else {
               if (i != 0) {
                    i--;
                    printf("\b \b");
               }
          }
          // 如果按下了回车键
          if (str == (char)enter_num) {
               passwd[--i] = '\0';
 
               if (i != buff_len - 1) {
                   printf("\b \b");
               }
               break;
          } else if (str == -1) {
               log_error("Error to set termio noecho.n");
          }
     }
     return passwd;
}

