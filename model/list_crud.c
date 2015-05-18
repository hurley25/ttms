/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * list_crud.c -- info list crud
 *
 * Version: 1.0  05/13/2015 01:53:20 PM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#include <stdlib.h>
#include <string.h>

#include "model/list_crud.h"

// 用户信息链表
struct list_head user_list_head = LIST_HEAD_INIT(user_list_head);

// 放映厅信息链表
struct list_head playhouse_list_head = LIST_HEAD_INIT(playhouse_list_head);

// 剧目信息链表
struct list_head movie_list_head = LIST_HEAD_INIT(movie_list_head);

// 场次信息链表
struct list_head action_cutting_list_head = LIST_HEAD_INIT(action_cutting_list_head);

// 添加用户
void add_user_info(user_type type, const char *username, const char *password)
{
    user_info *ui_node = NULL;
    ui_node = (user_info *)malloc(sizeof(user_info));
    bzero(ui_node, sizeof(user_info));
    
    ui_node->type = type;
    strncpy(ui_node->username, username, MAX_USERNAME);
    strncpy(ui_node->password, password, MAX_PASSWORD);

    list_add_tail(&(ui_node->list), &user_list_head);
}

void add_user_info_node(user_info *ui_node)
{
    list_add_tail(&(ui_node->list), &user_list_head);
}

// 添加放映厅
void add_playhouse(int id, int seat_count)
{
    playhouse *ph_node = NULL;
    ph_node = (playhouse *)malloc(sizeof(playhouse));
    bzero(ph_node, sizeof(playhouse));
    
    ph_node->id = id;
    ph_node->seat_count = seat_count;

    list_add_tail(&(ph_node->list), &playhouse_list_head);
}

void add_playhouse_node(playhouse *ph_node)
{
    list_add_tail(&(ph_node->list), &playhouse_list_head);
}

// 添加剧目
void add_movie_info(int id, const char *name, int duration,
                    const char *director, const char *language,
                    const char *country, const char *release_time,
                    const char *desc)
{
    movie_info *mi_node = NULL;
    mi_node = (movie_info *)malloc(sizeof(movie_info));
    bzero(mi_node, sizeof(movie_info));

    mi_node->id = id;
    strncpy(mi_node->name, name, MAX_MOVIE_NAME);
    mi_node->duration = duration;
    strncpy(mi_node->director, director, MAX_DIRECTOR);
    strncpy(mi_node->language, language, MAX_LANGUAGE);
    strncpy(mi_node->country, country, MAX_COUNTRY);
    strncpy(mi_node->release_time, release_time, MAX_TIME);
    strncpy(mi_node->desc, desc, MAX_MOVIE_DESC);

    list_add_tail(&(mi_node->list), &movie_list_head);
}

void add_movie_info_node(movie_info *mi_node)
{
    list_add_tail(&(mi_node->list), &movie_list_head);
}

// 添加场次
void add_action_cutting(int id, int movie_id, int playhouse_id, double fare,
                            int seat_count, int remaining_seat, const char *start_time)
{
    action_cutting *ac_node = NULL;
    ac_node = (action_cutting *)malloc(sizeof(action_cutting));
    bzero(ac_node, sizeof(action_cutting));

    ac_node->id = id;
    ac_node->movie_id = movie_id;
    ac_node->playhouse_id = playhouse_id;
    ac_node->fare = fare;
    ac_node->seat_count = seat_count;
    ac_node->remaining_seat = remaining_seat;
    strncpy(ac_node->start_time, start_time, MAX_TIME);

    list_add_tail(&(ac_node->list), &action_cutting_list_head);
}

void add_action_cutting_node(action_cutting *ac_node)
{
    list_add_tail(&(ac_node->list), &action_cutting_list_head);
}

// 删除用户
void del_user_info_by_name(const char *username)
{ 
    user_info *ui_node = NULL;
    user_info *ui_node_next = NULL;
    list_for_each_entry_safe(ui_node, ui_node_next, &user_list_head, list) {
        if (strcmp(ui_node->username, username) == 0) {
            list_del(&(ui_node->list));
            free(ui_node);
        }
    }
}

// 删除放映厅
void del_playhouse_by_id(int id)
{
    playhouse *ph_node = NULL;
    playhouse *ph_node_next = NULL;
    list_for_each_entry_safe(ph_node, ph_node_next, &playhouse_list_head, list) {
        if (ph_node->id == id) {
            list_del(&(ph_node->list));
            free(ph_node);
        }
    }
}

// 删除剧目
void del_movie_info_by_id(int id)
{
    movie_info *mi_node = NULL;
    movie_info *mi_node_next = NULL;
    list_for_each_entry_safe(mi_node, mi_node_next, &movie_list_head, list) {
        if (mi_node->id == id) {
            list_del(&(mi_node->list));
            free(mi_node);
        }
    }
}

// 删除场次
void del_action_cutting_by_id(int id)
{
    action_cutting *ac_node = NULL;
    action_cutting *ac_node_next = NULL;
    list_for_each_entry_safe(ac_node, ac_node_next, &action_cutting_list_head, list) {
        if (ac_node->id == id) {
            list_del(&(ac_node->list));
            free(ac_node);
        }
    }
}

// 遍历用户信息(对每个元素调用参数给出的回调函数，回调函数可删除该元素)
void for_range_user_info(void (*func)(user_info *))
{
    user_info *ui_node = NULL;
    user_info *ui_node_next = NULL;
    list_for_each_entry_safe(ui_node, ui_node_next, &user_list_head, list) {
        func(ui_node);
    }
}

// 遍历放映厅信息
void for_range_playhouse(void (*func)(playhouse *))
{
    playhouse *ph_node = NULL;
    playhouse *ph_node_next = NULL;
    list_for_each_entry_safe(ph_node, ph_node_next, &playhouse_list_head, list) {
        func(ph_node);
    }
}

// 遍历剧目信息
void for_range_movie_info(void (*func)(movie_info *))
{
    movie_info *mi_node = NULL;
    movie_info *mi_node_next = NULL;
    list_for_each_entry_safe(mi_node, mi_node_next, &movie_list_head, list) {
        func(mi_node);
    }
}

// 遍历场次信息
void for_range_action_cutting(void (*func)(action_cutting *))
{
    action_cutting *ac_node = NULL;
    action_cutting *ac_node_next = NULL;
    list_for_each_entry_safe(ac_node, ac_node_next, &action_cutting_list_head, list) {
        func(ac_node);
    }
}

// 初始化原始数据(生成测试数据)
void create_origin_data(void)
{
    // 添加用户
    add_user_info(UT_ADMIN, "admin", "111");
    add_user_info(UT_MANAGER, "manager", "222");
    add_user_info(UT_CLERK, "clerk", "333");

    // 添加放映厅
    add_playhouse(1, 100);
    add_playhouse(2, 100);
    add_playhouse(3, 100);
    add_playhouse(4, 100);

    // 添加剧目
    add_movie_info(1, "复仇者联盟2(奥创纪元)", 150, "乔斯 韦登", "英语", "美国", "2015年",
            "身经百战的超级英雄们产生了职业倦怠，已经卸下钢铁战甲的托尼斯塔克因此发明了奥创...");
    add_movie_info(2, "速度与激情7", 137, "詹姆斯 温", "英语", "美国", "2015年",
            "《速度与激情7》（Furious 7）是环球影业出品的一部赛车题材动作片，是《速度与激情》系列的第7部...");
    add_movie_info(3, "超能陆战队", 101, "唐 霍尔", "英语", "美国", "2015年",
            "故事设定在一个融合东西方文化（旧金山+东京）的虚构大都市旧京山（San Fransokyo）中，一名精通机器人的...");
    add_movie_info(4, "狼图腾", 116, "让 雅克 阿诺", "中文", "中国/法国", "2015年",
            "1967年，北京知青陈阵和杨克响应国家上山下乡的号召，从北京来到了内蒙古额仑大草原插队...");

    // 添加场次
    add_action_cutting(1, 1, 1, 50, 100, 100, "09:10 AM");
    add_action_cutting(2, 2, 2, 60, 100, 100, "11:00 AM");
    add_action_cutting(3, 3, 3, 70, 100, 100, "03:00 PM");
    add_action_cutting(4, 4, 4, 80, 100, 100, "05:30 PM");
}

// 检查用户密码
user_type check_user_password(const char *username, const char *password)
{
    user_info *ui_node = NULL;
    user_info *ui_node_next = NULL;
    list_for_each_entry_safe(ui_node, ui_node_next, &user_list_head, list) {
        if (strcmp(ui_node->username, username) == 0 && strcmp(ui_node->password, password) == 0) {
            return ui_node->type;
        }
    }

    return UT_ERROR;
}

// 售票
int sale_action_cutting_by_id_count(int id, int count)
{
    action_cutting *ac_node = NULL;
    action_cutting *ac_node_next = NULL;
    list_for_each_entry_safe(ac_node, ac_node_next, &action_cutting_list_head, list) {
        if (ac_node->id == id && ac_node->remaining_seat >= count) {
            ac_node->remaining_seat -= count;
            return 0;
        }
    }

    return -1;
}

// 返回目前的销售额
int get_sales_volume(void)
{
    int sales_volume = 0;

    action_cutting *ac_node = NULL;
    action_cutting *ac_node_next = NULL;
    list_for_each_entry_safe(ac_node, ac_node_next, &action_cutting_list_head, list) {
        sales_volume += (ac_node->seat_count - ac_node->remaining_seat) * ac_node->fare;
    }

    return sales_volume;
}

