#ifndef _BINARY_INDEXED_TREE
#define _BINARY_INDEXED_TREE

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


namespace BINARY_INDEXED_TREE {

/**
 * @brief binary indexed tree 树状数组也称二叉索引树
 * 用于单点修改与区间查询和都频繁的场景
 */
template<class T>
class binary_indexed_tree
{
private:
    vector<T> s_arr;
    vector<T> c_arr;

    int get_lowbit(int x)
    {
        return x & (-x);
    }

public:
    void binary_indexed_tree_init(vector<T> arr)
    {
        if (arr.size() == 0) return;

        this->s_arr = arr;

        // 根据原始数组生成对应的树状数组 c_arr[i] = SUM[s_arr[i],..., (i + 1) - lowbit(i + 1))
        this->c_arr.resize(this->s_arr.size(), 0);
        FOR_EACH(i, 0, this->s_arr.size())
        {
            FOR_EACH(j, (i + 1 - this->get_lowbit(i + 1)), i + 1)
            {
                this->c_arr[i] += this->s_arr[j];
            }
        }
    }

    /**
     * @brief 在对应位置上加上k
     * 
     */
    void add(int pos, T k)
    {
        if (pos < 0 || pos >= this->s_arr.size())
        {
            return;
        }

        // 根据 pos 向上追溯，更新所有的父节点 找到其最顶层 // i_parent = lowbit(i + 1) + 1 + 1 - 1;
        this->s_arr[pos] += k;
        this->c_arr[pos] += k;
        int parent = this->get_lowbit(pos + 1) + pos;
        while (parent < this->s_arr.size())
        {
            pos = parent;
            this->c_arr[pos] += k;
            parent = this->get_lowbit(pos + 1) + pos;
        }
    }

    /**
     * @brief 返回数组位置为pos以及前面所有元素的值
     * 
     */
    T query(int pos)
    {
        T res = T();
        if (pos < 0 || pos >= this->s_arr.size())
        {
            return res;
        }

        res = this->c_arr[pos];
        pos = pos - this->get_lowbit(pos + 1);
        while (pos >= 0)
        {
            res += this->c_arr[pos];
            pos = pos - this->get_lowbit(pos + 1);
        }
        return res;
    }

    /**
     * @brief 区间查询
     *
     * @param 
     * @param 
     * @return 返回区间[l, r]内的元素和
     */
    T query_interval(int l, int r)
    {
        T res = T();
        if (l < 0 || r >= this->s_arr.size() || l > r) return res;
        if (l == r)
        {
            return this->s_arr[l];
        }
        if (l == 0)
        {
            return this->query(r);
        }
        
        return this->query(r) - this->query(l - 1);
    }

    /**
     * @brief 单点更新
     *
     * @param 
     * @param 
     * @return
     */
    void update(int pos, T n)
    {
        if (pos < 0 || pos >= this->s_arr.size())
        {
            return;
        }
        T k = n - this->query_interval(pos, pos);
        this->add(pos, k);
    }

};

}
#endif