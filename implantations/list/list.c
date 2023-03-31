#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *list_new()
{
    List *res = (List *)(malloc(sizeof(List)));
    res->_sentinel = (struct ListNode *)malloc(sizeof(struct ListNode));
    res->_size = 0;
    res->_sentinel->_next = res->_sentinel;
    res->_sentinel->_previous = res->_sentinel;
    res->_visited = res->_sentinel->_next;
    res->_at_visit = 0;
    ;
    return res;
}

void *list_front(List *list)
{
    if (!list->_size)
    {
        fputs("ERROR: on front() of empty List.", stderr);
        exit(-1);
    }
    return list->_sentinel->_next->__data;
}

void *list_back(List *list)
{
    if (!list->_size)
    {
        fputs("ERROR: on back() of empty List.", stderr);
        exit(-1);
    }
    return list->_sentinel->_previous->__data;
}

ulli list_size(List *list)
{
    return list->_size;
}

bool list_empty(List *list)
{
    return (list->_size == 0);
}

void list_push_back(List *to, void *with)
{
    struct ListNode *p = (struct ListNode *)malloc(sizeof(struct ListNode));
    p->_previous = to->_sentinel->_previous;
    p->_next = to->_sentinel;
    p->__data = with;
    to->_sentinel->_previous->_next = p;
    to->_sentinel->_previous = p;
    if (to->_at_visit || !to->_size)
    {
        to->_visited = to->_sentinel->_next;
        to->_at_visit = 0;
        ;
    }
    ++to->_size;
    return;
}

void list_push_front(List *to, void *with)
{
    struct ListNode *p = (struct ListNode *)malloc(sizeof(struct ListNode));
    p->_previous = to->_sentinel;
    p->_next = to->_sentinel->_next;
    p->__data = with;
    to->_sentinel->_next->_previous = p;
    to->_sentinel->_next = p;
    if (to->_at_visit || !to->_size)
    {
        to->_visited = to->_sentinel->_next;
        to->_at_visit = 0;
        ;
    }
    ++to->_size;
    return;
}

void *list_at(List *list, ulli index)
{
    if (!list->_size)
    {
        fputs("ERROR: on at() of empty List.", stderr);
        exit(-1);
    }
    if (index >= list->_size)
    {
        fputs("ERROR: on at() with invaild index.\n", stderr);
        exit(-1);
    }
    struct ListNode *needle = list->_visited;
    struct ListNode *stop = list->_sentinel;
    ulli at = list->_at_visit;
    ulli half = (list->_size) >> 1;
    if (((at > index) ? (at - index) : (index - at)) > half)
    {
        if (at > half)
        {
            needle = stop->_next;
            at = 0;
        }
        else
        {
            needle = stop->_previous;
            at = list->_size - 1;
        }
    }
    while (at < index)
    {
        needle = needle->_next;
        ++at;
    }
    while (at > index)
    {
        needle = needle->_previous;
        --at;
    }
    list->_at_visit = at;
    list->_visited = needle;
    return needle->__data;
}

void *list_remove(List *list, ulli index)
{
    if (!list->_size)
    {
        fputs("ERROR: on remove() of empty List.", stderr);
        exit(-1);
    }
    struct ListNode *needle = list->_visited;
    struct ListNode *stop = list->_sentinel;
    ulli at = list->_at_visit;
    void *ret;
    while (at < index)
    {
        if (needle == stop)
        {
            fputs("ERROR: on remove() with up-outbounded index.\n", stderr);
            exit(-1);
        }
        needle = needle->_next;
        ++at;
    }
    while (at > index)
    {
        if (needle == stop)
        {
            fputs("ERROR: on remove() with down-outbounded index.\n", stderr);
            exit(-1);
        }
        needle = needle->_previous;
        --at;
    }
    if (needle->_previous != stop)
    {
        list->_visited = needle->_previous;
        list->_at_visit = at - 1;
    }
    else if (needle->_next != stop)
    {
        list->_visited = needle->_next;
        list->_at_visit = at + 1;
    }
    else
    {
        list->_visited = list->_sentinel->_next;
        list->_at_visit = 0;
        ;
    }
    needle->_previous->_next = needle->_next;
    needle->_next->_previous = needle->_previous;
    ret = needle->__data;
    free(needle);
    --list->_size;
    return ret;
}

void *list_pop_back(List *list)
{
    void *ret;
    if (!list->_size)
    {
        fputs("ERROR: on pop() of empty List.", stderr);
        exit(-1);
    }
    struct ListNode *res = list->_sentinel->_previous;
    res->_previous->_next = list->_sentinel;
    list->_sentinel->_previous = res->_previous;
    --list->_size;
    ret = res->__data;
    free(res);
    if (list->_at_visit)
    {
        list->_visited = list->_sentinel->_next;
        list->_at_visit = 0;
        ;
    }
    return ret;
}

void *list_pop_front(List *list)
{
    void *ret;
    if (!list->_size)
    {
        fputs("ERROR: on pop() of empty List.", stderr);
        exit(-1);
    }
    struct ListNode *res = list->_sentinel->_next;
    res->_next->_previous = list->_sentinel;
    list->_sentinel->_next = res->_next;
    --list->_size;
    ret = res->__data;
    free(res);
    if (list->_at_visit)
    {
        list->_visited = list->_sentinel->_next;
        list->_at_visit = 0;
        ;
    }
    return ret;
}

void list_clear(List *list, void (*deleter)(void *))
{
    if (!list->_size)
    {
        fputs("ERROR: on clear() of empty List.", stderr);
        exit(-1);
    }
    struct ListNode *needle = list->_sentinel->_next;
    struct ListNode *stop = list->_sentinel;
    if (!deleter)
        deleter = free;
    while (needle != stop)
    {
        struct ListNode *tmp = needle;
        needle = needle->_next;
        deleter(tmp->__data);
        free(tmp);
    }
    list->_size = 0;
    list->_visited = list->_sentinel->_next = list->_sentinel->_previous = list->_sentinel;
    list->_at_visit = 0;
    ;
}

void list_delete(List *list, void (*deleter)(void *))
{
    if (list->_size)
    {
        struct ListNode *needle = list->_sentinel->_next;
        struct ListNode *stop = list->_sentinel;
        if (!deleter)
            deleter = free;
        while (needle != stop)
        {
            struct ListNode *tmp = needle;
            needle = needle->_next;
            deleter(tmp->__data);
            free(tmp);
        }
    }
    free(list->_sentinel);
    free(list);
}