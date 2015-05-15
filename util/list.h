/*
 * (C) 2007-2015 Alibaba Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * list.h -- code from linux kernel
 *
 * Version: 1.0  05/13/2015 11:00:48 AM
 *
 * Authors:
 *     Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *
 */

#ifndef UTIL_LIST_H
#define UTIL_LIST_H

// 链表类型
struct list_head {
    struct list_head *next, *prev;
};

#define list_entry(ptr,type,member) (type *)((char *)ptr - __offsetof(type,member))

#define __offsetof(TYPE, MEMBER) ((unsigned int) &((TYPE *)0)->MEMBER)

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new,
        struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void list_replace(struct list_head *old,
        struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old,
        struct list_head *new)
{
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}

static inline void list_del_init(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

static inline void list_move_tail(struct list_head *list,
        struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

static inline int list_is_last(const struct list_head *list,
        const struct list_head *head)
{
    return list->next == head;
}

static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

static inline int list_empty_careful(const struct list_head *head)
{
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
}

static inline int list_is_singular(const struct list_head *head)
{
    return !list_empty(head) && (head->next == head->prev);
}

static inline void __list_cut_position(struct list_head *list,
        struct list_head *head, struct list_head *entry)
{
    struct list_head *new_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = new_first;
    new_first->prev = head;
}

static inline void list_cut_position(struct list_head *list,
        struct list_head *head, struct list_head *entry)
{
    if (list_empty(head))
        return;
    if (list_is_singular(head) &&
            (head->next != entry && head != entry))
        return;
    if (entry == head)
        INIT_LIST_HEAD(list);
    else
        __list_cut_position(list, head, entry);
}

static inline void __list_splice(const struct list_head *list,
        struct list_head *prev, struct list_head *next)
{
    struct list_head *first = list->next;
    struct list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

static inline void list_splice(const struct list_head *list,
        struct list_head *head)
{
    if (!list_empty(list))
        __list_splice(list, head, head->next);
}

static inline void list_splice_tail(struct list_head *list,
        struct list_head *head)
{
    if (!list_empty(list))
        __list_splice(list, head->prev, head);
}

static inline void list_splice_init(struct list_head *list,
        struct list_head *head)
{
    if (!list_empty(list)) {
        __list_splice(list, head, head->next);
        INIT_LIST_HEAD(list);
    }
}

static inline void list_splice_tail_init(struct list_head *list,
        struct list_head *head)
{
    if (!list_empty(list)) {
        __list_splice(list, head->prev, head);
        INIT_LIST_HEAD(list);
    }
}

#define list_first_entry(ptr, type, member)                         \
    list_entry((ptr)->next, type, member)

#define list_for_each(pos, head)                                    \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head)                               \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_safe(pos, n, head)                            \
    for (pos = (head)->next, n = pos->next; pos != (head);          \
            pos = n, n = pos->next)

#define list_for_each_prev_safe(pos, n, head)                       \
    for (pos = (head)->prev, n = pos->prev;                         \
            pos != (head);                                          \
            pos = n, n = pos->prev)

#define list_for_each_entry(pos, head, member)                          \
    for (pos = list_entry((head)->next, typeof(*pos), member);          \
            &pos->member != (head);                                     \
            pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_reverse(pos, head, member)                  \
    for (pos = list_entry((head)->prev, typeof(*pos), member);          \
            pos->member != (head);                                      \
            pos = list_entry(pos->member.prev, typeof(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member)                  \
    for (pos = list_entry((head)->next, typeof(*pos), member),          \
            n = list_entry(pos->member.next, typeof(*pos), member);     \
            &pos->member != (head);                                     \
            pos = n, n = list_entry(n->member.next, typeof(*n), member))

#define list_for_each_entry_reverse_safe(pos, n, head, member)          \
    for (pos = list_entry((head)->prev, typeof(*pos), member),          \
            n = list_entry(pos->member.next, typeof(*pos), member);     \
            &pos->member != (head);                                     \
            pos = n, n = list_entry(n->member.prev, typeof(*n), member))

#endif  // UTIL_LIST_H
