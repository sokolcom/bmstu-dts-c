#ifndef _QUEUE_ARRAY_H_
#define _QUEUE_ARRAY_H_

int is_overflow_qarray(qArray_t *const _Queue);
int is_empty_qarray(qArray_t *const _Queue);

qArray_t *create_qarray(const int _Capacity);
void add_qarray(qArray_t *const _Queue, const task_t _Task);
task_t out_qarray(qArray_t *const _Queue);
void free_qarray(qArray_t *_Queue);

#endif