#ifndef _QUEUELIST_H_
#define _QUEUELIST_H_

int is_overflow_qlist(qList_t *const _Queue);
int is_empty_qlist(qList_t *const _Queue);

node_t *create_qnode(const task_t _Task);
qList_t *create_qlist(const int _Capacity);
void add_qlist(qList_t *const _Queue, const task_t _Task);
task_t out_qlist(qList_t *const _Queue, array_t *const _Memory);
void free_qlist(qList_t *_Queue, array_t *const _Memory);
int check_rear(qList_t *_Queue, array_t *_Memory);

#endif