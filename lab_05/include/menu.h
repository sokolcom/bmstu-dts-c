#ifndef _MENU_H_
#define _MENU_H_

void welcome();
void print_menu();
void clear_stream();

int limits_input(int *const _Number, int *const _MIN_lim_in, int *const _MAX_lim_in,
                 int *const _MIN_lim_out, int *const _MAX_lim_out,
                 int *const _Repeats);

#endif