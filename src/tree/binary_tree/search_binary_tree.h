#ifndef CLASS_NAME_H
#define CLASS_NAME_H

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

using namespace std;

namespace SEARCH_BINARY_TREE {

/*
    实现了对搜索二叉树的查找函数
    1 查找比给定元素小的第一个元素
    2 查找比给定元素大的第一个元素
    3 查找是否存在等于给元素的元素
*/

template<class T>
struct TreeNode {
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


/**
 * @brief return closed node who is greater than then value
 *
 * @param root node of search binary tree
 * @param value value
 * @return return closed node who is greater than then value，if not exist return nullptr
 */
template<class T>
TreeNode<T>* get_closed_gt(TreeNode<T> *root, T value)
{
    TreeNode<T> *curr = root;
    TreeNode<T> *closed_gt = nullptr;
    while (curr)
    {
        if (value >= curr->val)
        {
            if (curr->right == nullptr)
            {
                return closed_gt != nullptr ? closed_gt : nullptr;
            }
            curr = curr->right;
        }
        else
        {
            if (curr->left == nullptr)
            {
                return curr;
            }
            closed_gt = curr;
            curr = curr->left;
        }
    }
    return nullptr;
}

/**
 * @brief return closed node who is less than then value
 *
 * @param root node of search binary tree
 * @param value value
 * @return return closed node who is less than then value，if not exist return nullptr
 */
template<class T>
TreeNode<T>* get_closed_lt(TreeNode<T> *root, T value)
{
    TreeNode<T> *curr = root;
    TreeNode<T> *closed_lt = nullptr;
    while (curr)
    {
        if (value <= curr->val)
        {
            if (curr->left == nullptr)
            {
                return closed_lt != nullptr ? closed_lt : nullptr;
            }
            curr = curr->left;
        }
        else
        {
            if (curr->right == nullptr)
            {
                return curr;
            }
            closed_lt = curr;
            curr = curr->right;
        }
    }
    return nullptr;
}

/**
 * @brief return node which's val is equal with value
 *
 * @param root root node of search binary tree
 * @param value value
 * @return return node who's val is euqal with value，if not exist return nullptr
 */
template<class T>
TreeNode<T>* get_eq(TreeNode<T> *root, T value)
{
    TreeNode<T> *curr = root;
    while (curr)
    {
        if (value == curr->val)
        {
            return curr;
        }
        else if (value < curr->val)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return nullptr;
}

}

#endif