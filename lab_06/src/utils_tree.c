#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/define.h"
#include "../include/structs.h"
#include "../include/utils_tree.h"



treeNode_t *add_node(const int key, treeNode_t *root, int *const code)
{
    if (root == NULL)
    {   
        root = (treeNode_t *)calloc(1, sizeof(treeNode_t));
        if (!root)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
        else
        {
            root->value = key;
            root->left = NULL;
            root->right = NULL;
        }
    }
    else if (root->value < key)
    {
        root->right = add_node(key, root->right, code);
        if (!root->right)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
    }     
    else if (root->value > key)
    {
        root->left = add_node(key, root->left, code);
        if (!root->left)
        {
            *code = MEMORY_ERROR;
            return NULL;
        }
    }

    return root;
}


treeNode_t *upload_tree(const char *const filename, int *const code)
{
    FILE *src = fopen(filename, "r");
    if (!src)
    {
        *code = FILE_NFOUND_ERROR;
        return NULL;
    }
    rewind(src);

    *code = SUCCESS;
    int number;
    treeNode_t *root = NULL;
    while (fscanf(src, "%d", &number) == 1)
    {
        root = add_node(number, root, code);
    }
    
    fclose(src);

    return root;
}


void bst_delete_node(treeNode_t **node)
{
    if ((*node)->left == NULL)
    {
        treeNode_t *right = (*node)->right;
        free(*node);
        *node = right;
    }
    else if ((*node)->right == NULL)
    {
        treeNode_t *left = (*node)->left;
        free(*node);
        *node = left;
    }
    else
    {
        treeNode_t *min_parent = *node;
        treeNode_t *min_node = (*node)->right;

        while(min_node->left != NULL)
        {
            min_parent = min_node;
            min_node = min_node->left;
        }

        (*node)->value = min_node->value;

        if (min_parent->left == min_node)
            min_parent->left = min_node->right;
        else
            min_parent->right = min_node->right;

        free(min_node);
    }
}

int bst_remove(treeNode_t **node, const int value, int *comp_num)
{
    {
        *comp_num += 1;
        if (node == NULL)
        {
            // printf("\nTree is empty!\n");
            return 0;
        }

        if ((*node)->value == value)
        {
            bst_delete_node(node);
            return 1;
        }

        if ((*node)->value > value)
        {
            if ((*node)->left == NULL)
            {
                // printf("\nDont have this key in tree!\n");
                return 0;
            }
            bst_remove(&(*node)->left, value, comp_num);
            return 1;
        }

        if ((*node)->value < value)
        {
            if ((*node)->right == NULL)
            {
                // printf("\nDont have this key in tree!\n");
                return 0;
            }
            bst_remove(&(*node)->right, value, comp_num);
            return 1;
        }
    }
    return 0;
}


// Recursive print tree into console
void print_tree(FILE *const output_stream, treeNode_t *const root, int depth)
{
    if (root)
    {
        print_tree(output_stream, root->left, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            fprintf(output_stream, "    ");
        }
        fprintf(output_stream, "%3d\n", root->value);

        print_tree(output_stream, root->right, depth + 1);
    }    
}


void init_gv(FILE *output_stream)
{
    fprintf(output_stream, "graph G\n{\n");
}


void end_gv(FILE *output_stream)
{
    fprintf(output_stream, "}\n");
}


void print_tree_visualized(FILE *const output_stream, treeNode_t *const root, int depth)
{
    if (root)
    {
        if (root->left != NULL) 
        {
            fprintf(output_stream, "%d -- %d;\n", root->value, root->left->value);
        }
        
        if (root->right != NULL)
        {
            fprintf(output_stream, "%d -- %d;\n", root->value, root->right->value);
        }

        print_tree_visualized(output_stream, root->left, depth + 1);
        print_tree_visualized(output_stream, root->right, depth + 1);
    }
}





void compress(treeNode_t *root, int amount)
{
    treeNode_t *scan = root;

    for (int i = 1; i < amount; i++)
    {
        treeNode_t *child = scan->right;

        scan->right = child->right;
        scan = scan->right;
        child->right = scan->left;
        scan->left = child; 
    }
}


static void to_vine(treeNode_t *root)
{
    treeNode_t *tail = root;
    treeNode_t *rest = tail->right;

    while (rest)
    {
        if (rest->left != NULL)
        {   
            treeNode_t *temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        }
        else
        {
            tail = rest;
            rest = rest->right;
        }
    }
}


static void to_tree(treeNode_t *root, int size)
{
    int leaves_amount = (size + 1) - (int)pow(2, log2(size + 1));

    compress(root, leaves_amount);
    size -= leaves_amount;

    while (size > 1)
    {
        compress(root, size / 2);
        size /= 2;
    }
}


void get_size(treeNode_t *root, int *const size)
{
    if (root)
    {
        get_size(root->left, size);
        (*size)++;
        get_size(root->right, size);
    }
}


treeNode_t *balance_tree(treeNode_t *root)
{
    int size = 1;
    get_size(root, &size);

    treeNode_t *pseudo = (treeNode_t *)calloc(1, sizeof(treeNode_t));

    pseudo->right = root;

    to_vine(pseudo);
    to_tree(pseudo, size);

    treeNode_t *temp = pseudo->right;
    free(pseudo);

    return temp;
}


// Travesal
void pre_order(FILE *const output_stream, avlNode_t *root)
{
    if (root)
    {
        fprintf(output_stream, "%d ", root->value);
        pre_order(output_stream, root->left);
        pre_order(output_stream, root->right);
    }
}


void in_order(FILE *const output_stream, avlNode_t *root)
{
    if (root)
    {
        in_order(output_stream, root->left);
        fprintf(output_stream, "%d ", root->value);
        in_order(output_stream, root->right);
    }
}


void post_order(FILE *const output_stream, avlNode_t *root)
{
    if (root)
    {
        post_order(output_stream, root->left);
        post_order(output_stream, root->right);
        fprintf(output_stream, "%d ", root->value);
    }
}

void traversal(FILE *const output_stream, avlNode_t *root)
{
    fprintf(output_stream, "PRE-order\n");
    pre_order(output_stream, root);
    fprintf(output_stream, "\n#####################\n");

    fprintf(output_stream, "IN-order:\n");
    in_order(output_stream, root);
    fprintf(output_stream, "\n#####################\n");

    fprintf(output_stream, "POST-order\n");
    post_order(output_stream, root);
    fprintf(output_stream, "\n#####################\n");
}



// Recursive free tree
void free_tree(treeNode_t *root)
{   
    if (root)   
    {
        free_tree(root->left);
        free_tree(root->right);

        free(root);
    }
}


void free_avl_tree(avlNode_t *root)
{   
    if (root)   
    {
        free_avl_tree(root->left);
        free_avl_tree(root->right);

        free(root);
    }
}


///////////////////////////////////////////////////////////////////////////////
/////////////////// AVL functions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

avlNode_t* right_rotate(avlNode_t* node)
{
    static const int array[6][4] = {
                    {-1,-1,+1,+1},
                    {-1,+0,+1,+0},
                    {-1,+1,+2,+0},
                    {-2,-1,+0,+0},
                    {-2,-2,+0,+1},
                    {-2,+0,+1,-1} 
                                    };

    avlNode_t* n_left_ptr = node->left;
    avlNode_t* n_left_right_ptr = n_left_ptr->right;

    n_left_ptr->right = node;
    node->left = n_left_right_ptr;

    for (int n = 0; n < 6; n++)
    {
        if(array[n][0] == node->balance && array[n][1] == n_left_ptr->balance)
        {
            n_left_ptr->balance = array[n][2];
            node->balance = array[n][3];
            break;
        }
    }

    return n_left_ptr;
}

avlNode_t* left_rotate(avlNode_t* node)
{
    static const int array[6][4] = { 
                    {+1,-1,-2,+0}, 
                    {+1,+0,-1,+0}, 
                    {+1,+1,-1,-1}, 
                    {+2,+0,-1,+1}, 
                    {+2,+1,+0,+0}, 
                    {+2,+2,+0,-1}
                                    }; 

    avlNode_t* n_right_ptr = node->right;
    if (node->right == NULL)
        return n_right_ptr;

    avlNode_t* n_right_left_ptr = n_right_ptr->left;
    n_right_ptr->left = node;
    node->right = n_right_left_ptr;

    for(int n = 0; n < 6; n++)
    {
        if(array[n][0] == node->balance && array[n][1] == n_right_ptr->balance)
        {
            n_right_ptr->balance = array[n][2];
            node->balance = array[n][3];
            break;
        }
    }

    return n_right_ptr;
}


int balance_insert(avlNode_t **root)
{
    avlNode_t* node = *root;
    if (node->balance > 1)
    {
        if (node->right->balance < 0)
        {
            node->right = right_rotate(node->right);
        }

        *root = left_rotate(node);
        return 1;
    }

    if (node->balance < -1)
    {
        if (node->left->balance > 0)
        {
            node ->left = left_rotate(node->left);
        }

        *root = right_rotate(node);
        return 1;
    }
    return 0;
}


avlNode_t* create_avl(int value)
{
    avlNode_t* new = NULL;

    new = (avlNode_t *)calloc(1, sizeof(avlNode_t));
    if (!new)
    {
        return NULL;
    }

    new->left = NULL;
    new->right = NULL;
    new->value = value;
    new->balance = 0;

    return new;
}

int avl_insert(avlNode_t** root, int value, int *temp_cmp)
{
    *temp_cmp += 1;
    int res = 0;

    avlNode_t* node = *root;
    if (!node)
    {
        *root = create_avl(value);
        return 1;
    }
    if (value == node->value)
        return 0;

    if (value < node->value)
        res = avl_insert(&node->left,  value, temp_cmp) && --(node->balance);
    else
        res = avl_insert(&node->right, value, temp_cmp) && ++(node->balance);

    if (balance_insert(root))
        res = 0;
        
    return res;
}

void make_avl(treeNode_t* node_bst, avlNode_t** root_avl, int *sum)
{
    int temp_cmp = 0;
    if (node_bst == NULL)
        return;

    avl_insert(root_avl, node_bst->value, &temp_cmp);
    *sum += temp_cmp;

    make_avl(node_bst->left, root_avl, sum);
    make_avl(node_bst->right, root_avl, sum);
}


// Recursive print tree into console
void print_avl(FILE *const output_stream, avlNode_t *const root, int depth)
{
    if (root)
    {
        print_avl(output_stream, root->left, depth + 1);

        for (int i = 0; i < depth; i++)
        {
            fprintf(output_stream, "    ");
        }
        fprintf(output_stream, "%3d\n", root->value);

        print_avl(output_stream, root->right, depth + 1);
    }    
}


void print_avl_visualized(FILE *const output_stream, avlNode_t *const root, int depth)
{
    if (root)
    {
        if (root->left != NULL) 
        {
            fprintf(output_stream, "%d -- %d;\n", root->value, root->left->value);
        }
        
        if (root->right != NULL)
        {
            fprintf(output_stream, "%d -- %d;\n", root->value, root->right->value);
        }

        print_avl_visualized(output_stream, root->left, depth + 1);
        print_avl_visualized(output_stream, root->right, depth + 1);
    }
}


int balance_remove(avlNode_t **root, int res)
{
    avlNode_t *node = *root;
    if (node->balance > 1)
    {
        res = !!node->right->balance;

        if (node->right != NULL && node->right->balance < 0)
            node->right = right_rotate(node->right);

        *root = left_rotate(node);
    }

    if (node->balance < -1)
    {
        res = node->left->balance;
        if (node->left->balance > 0)
            node -> left = left_rotate(node->left);

        *root = right_rotate(node);
    }
    return res;
}


int get_min(avlNode_t **root, avlNode_t **res)
{
    avlNode_t *node = *root;
    if (node->left)
    {
        if (get_min(&node->left, res) && !++node->balance)
            return 1;

        return balance_remove(root, 0);
    }

    *res = node;
    *root = node->right;
    return 1;
}


int avl_remove(avlNode_t **root, int value, int *temp_cmp)
{
    *temp_cmp += 1;
    int rc = 0;

    avlNode_t *node = *root;
    if (!node)
    {
        // printf("\nTree is empty!");
        return rc;
    }

    if (node->value < value)
    {
        if (avl_remove(&node->right, value, temp_cmp) && !--node->balance)
        {
            rc = 1;
        }
    }
    else if (node->value > value)
    {
        if (avl_remove(&node->left, value, temp_cmp) && !++node->balance)
        {
            rc = 1;
        }
    }
    else
    {
        if (!node->right)
        {
            *root = node->left;
            free(node);
            return 1;
        }
        rc = get_min(&node->right, root);
        if (*root != NULL)
        {
            (*root)->balance = node->balance;
            (*root)->left = node->left;
            (*root)->right = node->right;
        }
        free(node);
        if (rc)
        {
            rc = !--(*root)->balance;
        }
    }

    return balance_remove(root, rc);
}
