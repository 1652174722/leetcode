#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <array>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "template.h"
using namespace std;

namespace AVL_TREE
{

/**
 * @brief avl tree
 *  支持增删改查,
 *  支持重复元素插入
 *  支持删除指定元素
 *  支持删除指定元素一次
 *  支持获取第k个的元素
 *  支持查看某个元素的位置
 *  支持查询第一个小于某个元素的值
 *  支持查看第一个大于某个元素的值
 * @param
 * @param
 * @return
 */

template <class T>
struct avl_node
{
public:
    T val;

    // 0:left child; 1:right child
    struct avl_node *child[2];

    // balance factor
    int bf;

    // the height of curr node, not less than 1
    size_t height;

    // sum of node count of curr subtree ，inclue curr node
    size_t size;

    // the number of same nodes
    size_t count;

    avl_node(T value)
    {
        this->val = value;
        this->child[0] = NULL;
        this->child[1] = NULL;
        this->bf = 0;
        this->height = 1;
        this->size = 1;
        this->count = 1;
    }

    avl_node *get_left(avl_node *node)
    {
        return node->child[0];
    }

    avl_node *get_right(avl_node *node)
    {
        return node->child[1];
    } 
};

template <class T>
class avl_tree
{
private:
    // 二叉树的根节点
    avl_node<T> *root;
    int (*cmp_func)(const T &a, const T &b);
    
    void clear_by_post_order(avl_node<T> *node)
    {
        if (node)
        {
            clear_by_post_order(node->child[0]);
            clear_by_post_order(node->child[1]);
            node->child[0] = NULL;
            node->child[1] = NULL;
            free(node);
        }
    }

    int traverse_by_middle_order(avl_node<T> *node, int(*process_func)(size_t count, const T &value, void *in_out), void *in_out)
    {
        if (node)
        {
            int ret = 0;
            if (0 != traverse_by_middle_order(node->child[0], process_func, in_out))
            {
                return -1;
            }
            
            ret = process_func(node->count, node->val, in_out);
            if (ret)
            {
                return -1;
            } 

            if (0 != traverse_by_middle_order(node->child[1], process_func, in_out))
            {
                return -1;
            }
        }
        return 0;
    }

    avl_node<T>* erase_once_dfs(avl_node<T> *node, const T &value, avl_node<T> *replace_node, size_t &real_count)
    {
        if (node == NULL)
        {
            real_count = 0;
            return NULL;
        }

        avl_node<T> *sub_node;
        if (replace_node == NULL)
        {
            int ret = this->cmp_func(value, node->val);
            if (ret == 0)
            {
                real_count = node->count;
                if (node->count == 1)
                {
                    // 当前节点是否为叶子节点
                    if (node->child[0] != NULL && node->child[1] != NULL)
                    {
                        // 删除当前节点的左前驱叶子节点
                        node->child[0] = erase_once_dfs(node->child[0], value, node, real_count);
                    }
                    else if (node->child[0] != NULL)
                    {
                        // 左子树必为叶子节点。直接删除当前节点，左子树上移
                        sub_node = node->child[0];
                        free(node);
                        return sub_node;
                    }
                    else if (node->child[1] != NULL)
                    {
                        // 右子树必为叶子节点。直接删除当前节点，右子树上移
                        sub_node = node->child[1];
                        free(node);
                        return sub_node;
                    }
                    else
                    {
                        free(node);
                        return NULL;
                    }
                }
                else
                {
                    node->count--;
                    node->size--;
                    return node;
                }
            }
            else if (ret < 0)
            {
                node->child[0] = erase_once_dfs(node->child[0], value, NULL, real_count);

            }
            else
            {
                node->child[1] = erase_once_dfs(node->child[1], value, NULL, real_count);
            }
        }
        else
        {
            if (node->child[1] == NULL)
            {
                // 为要删除的节点
                replace_node->val = node->val;
                if (node->child[0] == NULL)
                {
                    sub_node = NULL;
                }
                else
                {
                    sub_node = node->child[0];
                }
                free(node);
                return sub_node;
            }
            else
            {
                node->child[1] = erase_once_dfs(node->child[1], value, replace_node, real_count);
            }
        }

        if (real_count == 0)
        {
            return node;
        }

        // update curr node's size,height,bf
        return update_node_property(node);
    }

    avl_node<T>* erase_dfs(avl_node<T> *node, const T &value, avl_node<T> *replace_node, size_t &real_count)
    {
        if (node == NULL)
        {
            real_count = 0;
            return NULL;
        }

        avl_node<T> *sub_node;
        if (replace_node == NULL)
        {
            
            int ret = this->cmp_func(value, node->val);
            if (ret == 0)
            {
                real_count = node->count;
                // 当前节点是否为叶子节点
                if (node->child[0] != NULL && node->child[1] != NULL)
                {
                    // 删除当前节点的左前驱叶子节点
                    node->child[0] = erase_dfs(node->child[0], value, node, real_count);
                }
                else if (node->child[0] != NULL)
                {
                    // 左子树必为叶子节点。直接删除当前节点，左子树上移
                    sub_node = node->child[0];
                    free(node);
                    return sub_node;
                }
                else if (node->child[1] != NULL)
                {
                    // 左子树必为叶子节点。直接删除当前节点，左子树上移
                    sub_node = node->child[1];
                    free(node);
                    return sub_node;
                }
                else
                {
                    free(node);
                    return NULL;
                }
            }
            else if (ret < 0)
            {
                node->child[0] = erase_dfs(node->child[0], value, NULL, real_count);
            }
            else
            {
                node->child[1] = erase_dfs(node->child[1], value, NULL, real_count);
            }
        }
        else
        {
            if (node->child[1] == NULL)
            {
                // 为要删除的节点
                replace_node->val = node->val;
                if (node->child[0] == NULL)
                {
                    sub_node = NULL;
                }
                else
                {
                    sub_node = node->child[0];
                }
                free(node);
                return sub_node;
            }
            else
            {
                node->child[1] = erase_dfs(node->child[1], value, replace_node, real_count);
            }
        }

        if (real_count == 0)
        {
            return node;
        }
        
        // update curr node's size,height,bf
        return update_node_property(node);
    }

    /*
     * @brief process
     *        10(n1)                          1(n2)
     *       /  \                           /   \ 
     *  (n2)1    a2    right rotate        a0   10(n1)
     *     / \        ------------>             / \
     *    a0   a1                              a1  a2
     *
     * @param ths node need to right rotate
     * @return
     *  
     */
    avl_node<T>* right_rotate(avl_node<T> *node)
    {
        avl_node<T> *n1 = node;
        avl_node<T> *n2 = node->child[0];
        avl_node<T> *a[3];
        size_t a_size[3], a_height[3];
        a[0] = n2->child[0];
        a[1] = n2->child[1];
        a[2] = n1->child[1];

        for (int i = 0; i < 3; i++)
        {
            if (a[i] != NULL)
            {
                a_size[i] = a[i]->size; a_height[i] = a[i]->height;
            }
            else
            {
                a_size[i] = 0; a_height[i] = 0;
            }
        }

        // update n1's height,size,bf;
        n1->child[0] = a[1];
        n1->child[1] = a[2];
        n1->bf = a_height[2] - a_height[1];
        n1->height = (a_height[2] > a_height[1] ? a_height[2] : a_height[1]) + 1;
        n1->size = a_size[1] + a_size[2] + n1->count;

        // update n2's height,size,bf;
        n2->child[0] = a[0];
        n2->child[1] = n1;
        n2->bf = n1->height - a_height[0];
        n2->height = (n1->height > a_height[0] ? n1->height : a_height[0]) + 1;
        n2->size = a_size[0] + n1->size + n2->count;

        return n2;
    }

    /*
     * @brief process
     *        10(n1)                            1(n2)
     *       /  \                              /  \ 
     *      a0   1(n2)    left rotat      (n1)10    a2
     *          / \     <-----------         / \
     *         a1  a2                      a0  a1
     *
     * @param ths node need to left rotate
     * @return
     *  
     */
    avl_node<T>* left_rotate(avl_node<T> *node)
    {
        avl_node<T> *n1 = node;
        avl_node<T> *n2 = node->child[1];
        avl_node<T> *a[3];
        size_t a_size[3], a_height[3];
        a[0] = n1->child[0];
        a[1] = n2->child[0];
        a[2] = n2->child[1];

        for (int i = 0; i < 3; i++)
        {
            if (a[i] != NULL)
            {
                a_size[i] = a[i]->size; a_height[i] = a[i]->height;
            }
            else
            {
                a_size[i] = 0; a_height[i] = 0;
            }
        }

        // update n1's height,size,bf;
        n1->child[0] = a[0];
        n1->child[1] = a[1];
        n1->bf = a_height[1] - a_height[0];
        n1->height = (a_height[1] > a_height[0] ? a_height[1] : a_height[0]) + 1;
        n1->size = a_size[1] + a_size[0] + n1->count;

        // update n2's height,size,bf;
        n2->child[0] = n1;
        n2->child[1] = a[2];
        n2->bf = a_height[2] - n1->height;
        n2->height = (n1->height > a_height[2] ? n1->height : a_height[2]) + 1;
        n2->size = n1->size + a_size[2] + n2->count;

        return n2;
    }

    avl_node<T>* update_node_property(avl_node<T> *node)
    {
        avl_node<T> *res_node = node;
        // update curr node's size,height,bf
        size_t l_sub_h = 0;
        size_t r_sub_h = 0;
        size_t l_sub_size = 0;
        size_t r_sub_size = 0;
        
        if (node->child[0] != NULL)
        {
            l_sub_h = node->child[0]->height;
            l_sub_size = node->child[0]->size;
        }

        if (node->child[1] != NULL)
        {
            r_sub_h = node->child[1]->height;
            r_sub_size = node->child[1]->size;
        }
        
        avl_node<T> *sub_l, *sub_r;
        size_t sub_l_h, sub_r_h;
        switch (2 + r_sub_h - l_sub_h)
        {
            case 0:
                // 平衡因子为-2，需要左右旋重新调整平衡因子
                
                sub_l = node->child[0]->child[0];
                sub_r = node->child[0]->child[1];

                // 左子树的左子树的高度
                sub_l_h = sub_l == NULL ? 0 : sub_l->height;
                // 左子树的右子树的高度
                sub_r_h = sub_r == NULL ? 0 : sub_r->height;

                if (sub_l_h >= sub_r_h)
                {
                    // 直接进行右旋
                    res_node = right_rotate(node);
                }
                else
                {
                    // 先进行左旋
                    node->child[0] = left_rotate(node->child[0]);
                    // 再进行右旋
                    res_node = right_rotate(node);
                }
                break;
            case 1:
                // update n1's height,size,bf;
                node->bf = -1;
                node->height = l_sub_h +1;
                node->size = l_sub_size + r_sub_size + node->count;
                break;
            case 2:
                // update n1's height,size,bf;
                node->bf = 0;
                node->size = l_sub_size + r_sub_size + node->count;
                break;
            case 3:
                node->bf = 1;
                node->height = r_sub_h + 1;
                node->size = l_sub_size + r_sub_size + node->count;
                break;
            case 4:
                // 平衡因子为2，需要左右旋重新调整平衡因子
                sub_l = node->child[1]->child[0];
                sub_r = node->child[1]->child[1];

                sub_l_h = sub_l == NULL ? 0 : sub_l->height; // 右子树的左子树的高度
                sub_r_h = sub_r == NULL ? 0 : sub_r->height; // 右子树的右子树的高度

                if (sub_r_h >= sub_l_h)
                {
                    // 直接进行左旋
                    res_node = left_rotate(node);
                }
                else
                {
                    // 先进行右旋
                    node->child[0] = right_rotate(node->child[0]);
                    // 再进行左旋
                    res_node = left_rotate(node);
                }
        }

        return res_node;
    }

    avl_node<T>* insert_dfs(avl_node<T> *node, const T &value, size_t &insert_count, bool &err)
    {
        if (node == NULL)
        {
            avl_node<T> *new_node = new avl_node<T>(value);
            if (new_node == NULL)
            {
                err = true;
            }
            else
            {
                insert_count = 1;
            }
            return new_node;
        }

        int ret = this->cmp_func(value, node->val);
        if (ret == 0)
        {
            node->count++;
            node->size++;
            insert_count = node->count;
            return node;
        }
        else if (ret < 0)
        {
            node->child[0] = this->insert_dfs(node->child[0], value, insert_count, err);
        }
        else
        {
            node->child[1] = this->insert_dfs(node->child[1], value, insert_count, err);
        }
        
        if (err) {
            return node;
        }

        if (insert_count != 1)
        {
            node->size++;
            return node;
        }
        // update curr node's size,height,bf
        return this->update_node_property(node);
    }
public:
    /*
     * @brief structure function
     *
     * @param cmp_func return -1 means a < b; return 0 means a = b; return 1 means a > b.
     * @return
     */
    avl_tree(int (*cmp_func)(const T &a, const T &b))
    {
        if (cmp_func == NULL)
        {
            return;
        }

        this->root = NULL;
        this->cmp_func = cmp_func;
    }

    /**
     * @brief destory function
     *
     * @param cmp_func return -1 means a < b; return 0 means a = b; return 1 means a > b.
     * @return
     */
    ~avl_tree()
    {
        this->clear();
        this->cmp_func = NULL;
    }

    /*
     * @brief object size(include the count of the value) of avl tree
     *
     * @param value value of object
     * @return size of the avl
     */
    size_t size()
    {
        if (this->root == NULL)
        {
            return 0;
        }
        return this->root->size;
    }

    /*
     * @brief insert a object
     *
     * @param value value of object
     * @return count of value after inserted ; 0 insert failed(malloc failed:out of memory)
     */
    size_t insert(const T &value)
    {
        size_t insert_count = 0;
        bool err = false;
        this->root = this->insert_dfs(this->root, value, insert_count, err);

        if (err == true)
        {
            return 0;
        }
        return insert_count;
    }

    /*
     * @brief erase all the same value
     *
     * @param value value of object
     * @return count of the value before deleted
     */
    size_t erase(const T &value)
    {
        size_t real_count = 0;
        this->root = this->erase_dfs(this->root, value, NULL, real_count);
        return real_count;
    }

    /*
     * @brief erase all the same value
     *
     * @param value value of object
     * @return  the left count of the value after the value was deleted once
     */
    size_t erase_once(const T &value)
    {
        size_t real_count = 0;
        this->root = this->erase_once_dfs(this->root, value, NULL, real_count);
        return real_count;
    }

    /*
     * @brief return the count of the same value
     *
     * @param value: in and out paremeter :be updated when find return
     * @return  the count of the same value
     */
    size_t find(T &value)
    {
        if (this->cmp_func == NULL || this->root == NULL)
        {
            return 0;
        }
        avl_node<T> *curr_node = this->root;
        int ret;
        while (curr_node)
        {
            ret = this->cmp_func(value, curr_node->val);
            if (ret < 0)
            {
                curr_node = curr_node->child[0];
            }
            else if (ret > 0)
            {
                curr_node = curr_node->child[1];
            }
            else
            {
                value = curr_node->val;
                return curr_node->count;
            }
        }
        return 0;
    }

    /*
     * @brief return the count of the same value
     *
     * @param value
     * @return  the count of the same value
     */
    size_t count(T &value)
    {
        if (this->cmp_func == NULL || this->root == NULL)
        {
            return 0;
        }
        avl_node<T> *curr_node = this->root;
        int ret;
        while (curr_node)
        {
            ret = this->cmp_func(value, curr_node->val);
            if (ret < 0)
            {
                curr_node = curr_node->child[0];
            }
            else if (ret > 0)
            {
                curr_node = curr_node->child[1];
            }
            else
            {
                return curr_node->count;
            }
        }
        return 0;
    }


    /**
     * @brief return all the number of the avl tree
     * @param
     * @return
     */
    void clear()
    {
        // 这里通过后序删除节点
        if (this->root == NULL)
        {
            return;
        }
        this->clear_by_post_order(this->root);
        this->root = NULL;
    }

    /**
     * @brief traverse avl by middle order
     *
     * @param process_func return 0, will continue traversing,;return others, will stop traversing right now, i the order number of node
     * @param process_func.parameter: i:count of same node; value:value of node; in_out:output parameter
     * @return 0 all of nodea was traversed, -1 only part of nodes was traversed because process_func return nozero
     */
    int traverse(int(*process_func)(size_t count, const T &value, void *in_out), void *in_out)
    {
        if (this->root == NULL)
        {
            return -1;
        }

        if (process_func == NULL)
        {
            return -1;
        }
        return this->traverse_by_middle_order(this->root, process_func, in_out);
    }

    /**
     * @brief return k-th value（include count）
     *
     * @param t[int] position of value(include count),start with 0
     * @param value[out] 
     * @return 0 success; others throw -1.
     */
    T kth(size_t t)
    {
        if (t >= this->size())
        {
            throw string("out of avl size range");
        }
        
        size_t left_size = t;
        avl_node<T> *curr_node = this->root;
        while (curr_node)
        {
            size_t l_size = curr_node->child[0] == NULL ? 0 : curr_node->child[0]->size;
            if (left_size < l_size)
            {
                curr_node = curr_node->child[0];
            } else if (left_size < (l_size + curr_node->count))
            {
                break;
            }
            else
            {
                left_size -= (l_size + curr_node->count);
                curr_node = curr_node->child[1];
            }
        }

        return curr_node->val;
    }

    /**
     * @brief return starting and ending position of value
     *
     * @param 
     * @return pair<start positoin, end position>,[start, end):start with 0,include start position exclude end position; others throw -1,
     */
    pair<size_t, size_t> position(const T &value)
    {
        pair<size_t, size_t> res(0, 0);
        if (this->cmp_func == NULL || this->root == NULL)
        {
            throw string("no such value in avl");
        }
        avl_node<T> *curr_node = this->root;
        size_t start_pos = 0;
        int ret;
        while (curr_node)
        {
            size_t l_size = curr_node->child[0] == NULL ? 0 : curr_node->child[0]->size;
            ret = this->cmp_func(value, curr_node->val);
            if (ret < 0)
            {
                curr_node = curr_node->child[0];
            }
            else if (ret > 0)
            {
                start_pos += l_size + curr_node->count;
                curr_node = curr_node->child[1];
            }
            else
            {
                return make_pair<size_t, size_t>(start_pos + l_size, start_pos + l_size + curr_node->count);
            }
        }

        throw string("no such value in avl");
        return res;
    }

    /**
     * @brief get first element which is less than value
     *
     * @param value
     * @return if no such element then throw exception
     */
    T first_lt(const T &value)
    {
        if (this->root == NULL || this->cmp_func == NULL)
        {
            throw string("no such element which which is less than value");
        }
        avl_node<T> *curr = root;
        avl_node<T> *first_lt = NULL;
        while (curr)
        {
            int ret = this->cmp_func(curr->val, value);

            if (ret < 0)
            {
                first_lt = curr;
                curr = curr->child[1];
            }
            else
            {
                curr = curr->child[0];
            }
        }

        if (first_lt == NULL)
        {
            throw string("no such element which which is less than value");
        }
        return first_lt->val;
    }

    /**
     * @brief get first element which is greater than value
     *
     * @param value
     * @return if no such element then throw exception
     */
    T first_gt(const T &value)
    {
        if (this->root == NULL || this->cmp_func == NULL)
        {
            throw string("no such element which which is greater than value");
        }
        avl_node<T> *curr = root;
        avl_node<T> *first_gt = NULL;
        while (curr)
        {
            int ret = this->cmp_func(curr->val, value);

            if (ret > 0)
            {
                first_gt = curr;
                curr = curr->child[0];
            }
            else
            {
                curr = curr->child[1];
            }
        }
        if (first_gt == NULL)
        {
            throw string("no such element which which is greater than value");
            
        }
        return first_gt->val;
    }
};

}

#endif