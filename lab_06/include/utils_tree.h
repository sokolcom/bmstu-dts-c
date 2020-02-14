#ifndef _UTILS_TREE_H_
#define _UTILS_TREE_H_

void get_size(treeNode_t *_Root, int *const _Size);
treeNode_t *add_node(const int _Key, treeNode_t *_Root, int *const _Code);
int bst_remove(treeNode_t **node, const int value, int *comp_num);

treeNode_t *upload_tree(const char *const _Filename, int *const _Code);
void print_tree(FILE *const _Stream, treeNode_t *const _Root, int _Depth);
treeNode_t *balance_tree(treeNode_t *_Root);
void traversal(FILE *const _Stream, avlNode_t *_Root);
void free_tree(treeNode_t *_Root);
void free_avl_tree(avlNode_t *root);

void print_tree_visualized(FILE *const _Stream, treeNode_t *const _Root, int _Depth);
void init_gv(FILE *_Stream);
void end_gv(FILE *_Stream);


void make_avl(treeNode_t *_BST, avlNode_t **_AVL, int *_Sum);
void print_avl(FILE *const output_stream, avlNode_t *const root, int depth);
void print_avl_visualized(FILE *const output_stream, avlNode_t *const root, int depth);
int avl_remove(avlNode_t **root, int value, int *temp_cmp);

#endif
