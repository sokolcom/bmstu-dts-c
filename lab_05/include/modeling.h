#ifndef _MODELING_H_
#define _MODELING_H_

void model_list(qList_t *const _Queue, array_t *const Memory,
                const int _MIN_lim_in, const int _MAX_lim_in,
                const int _MIN_lim_out, const int _MAX_lim_out,
                const int _Repeats);

void model_array(qArray_t *const _Queue,
                 const int _MIN_lim_in, const int _MAX_lim_in,
                 const int _MIN_lim_out, const int _MAX_lim_out,
                 const int _Repeats);
#endif