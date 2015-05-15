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

// 保存所有信息到文件
int save_all_info(void);

#endif  // MODEL_SERIALIZATION_H

