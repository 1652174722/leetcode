#ifndef _SEGMENT_TREE
#define _SEGMENT_TREE

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

namespace SEGMENT_TREE {

/**
 * @brief segment tree 线段树
 * 支持区间修改与区间查询
 * T 只能为 整数或者小数
 */
template<class T>
class segment_tree
{
private:
    class segment_tree_node
    {
    public:
        int l, r;
        T sum;
        int lazy;
        int k;
        segment_tree_node()
        {
            this->r = this->l = 0;
            this->sum = T();
            this->lazy = 0;
            this->k = 0;
        }
        segment_tree_node(int L, int R) : l(L), r(R){ 
            this->sum = T();
            this->lazy = 0;
            
        }
    };
    vector<segment_tree_node> st_arr;
    vector<T> s_arr;
    int segment_tree_layers;

    vector<segment_tree_node> generate_segment_tree_array(vector<T> arr, int &segment_tree_layers)
    {
        vector<segment_tree_node> res;
        // 根据数据大小，确认二叉树的层数
        
        int length_len = 1;
        int sum_length = length_len;
        segment_tree_layers = 1;
        while (length_len < arr.size())
        {
            segment_tree_layers++;
            length_len *= 2; 
            sum_length += length_len;
        }
        
        // 倒数第二层叶子节点的个数
        int last_second_layer = length_len - arr.size();
        // 最后一层叶子节点的个数
        int last_layer = arr.size() - last_second_layer;

        // 求出所需要二叉树数组的长度
        sum_length -= (length_len - last_layer);

        res = vector<segment_tree_node>(sum_length);

        R_FOR_EACH(i, res.size(), res.size() - last_layer)
        {
            int pos = i - res.size() + last_layer - 1;
            res[i - 1].r = res[i - 1].l = pos;
            res[i - 1].sum = arr[pos];
        }

        R_FOR_EACH(i, res.size() - last_layer, res.size() - arr.size())
        {
            int pos = i - (res.size() - last_layer) + arr.size() - 1;
            res[i - 1].r = res[i - 1].l = pos;
            res[i - 1].sum = arr[pos];
        }

        // 对数组res从后往前遍历
        R_FOR_EACH(i, res.size(), 1)
        {
            int pos = (i - 2) / 2;
            if ((i - 1) % 2 == 0)
            {
                res[pos].r = res[i - 1].r;
                res[pos].sum = res[i - 1].sum;
            }
            else
            {
                res[pos].l = res[i - 1].l;
                res[pos].sum += res[i - 1].sum;
            }
        }
        return res;
    }

    int get_pow(int x, int n)
    {
        if (n == 0) return 1;
        int res = 1;
        while (n > 0)
        {
            res *= x;
            n--;
        }
        return res;
    }

    /**
     * @brief 根据数组位置找到对应
     *
     * @param 
     * @param 
     * @return
     */
    int get_segment_tree_pos(int pos)
    {
        // 倒数第二层叶子节点的个数
        int last_second_layer = this->get_pow(2, this->segment_tree_layers - 1) - this->s_arr.size();
        // 最后一层叶子节点的个数
        int last_layer = this->s_arr.size() - last_second_layer;
        if ((pos + 1) <= last_layer)
        {
            return this->st_arr.size() - last_layer + (pos + 1) - 1;
        }
        else
        {
            return this->st_arr.size() - this->s_arr.size() + (pos + 1 - last_layer) - 1; 
        }
    }

    void touch_lazy_flag(vector<segment_tree_node> &st_arr, int next_pos, T k)
    {
        if (this->st_arr[next_pos].lazy != 0)
        {
            this->st_arr[next_pos].k += k;
        }
        else
        {
            this->st_arr[next_pos].lazy = 1;
            this->st_arr[next_pos].k = k;
        }         
    }

    /**
     * @brief 区间查询
     *
     * @param 
     * @param 
     * @return
     */
    T query_dfs(int curr_pos, int l, int r)
    {
        if (this->st_arr[curr_pos].l >= l &&  this->st_arr[curr_pos].r <= r)
        {
            return this->st_arr[curr_pos].sum + this->st_arr[curr_pos].lazy * (this->st_arr[curr_pos].r - this->st_arr[curr_pos].l + 1) * 
                this->st_arr[curr_pos].k;
        }

        int child_l = curr_pos * 2 + 1;
        int child_r = curr_pos * 2 + 2;
        int mid = this->st_arr[child_l].r;
        
        // 将懒标记下发
        if (this->st_arr[curr_pos].lazy != 0)
        {
            this->touch_lazy_flag(this->st_arr, child_l, this->st_arr[curr_pos].k);

            this->touch_lazy_flag(this->st_arr, child_r, this->st_arr[curr_pos].k);

            this->st_arr[curr_pos].sum += (this->st_arr[curr_pos].r - this->st_arr[curr_pos].l + 1) * this->st_arr[curr_pos].k;
            this->st_arr[curr_pos].k = T();
            this->st_arr[curr_pos].lazy = 0;
        }

        if (r <= mid)
        {
            return this->query_dfs(child_l, l, r);
        }
        else if (l > mid)
        {
            return this->query_dfs(child_r, l, r);
        }
        return this->query_dfs(child_l, l, mid) + this->query_dfs(child_r, mid + 1, r);
    }

    /**
     * @brief 区间更新，利用懒标记lazy实现
     *
     * @param 
     * @param 
     * @return
     */
    T add_dfs(int curr_pos, int l, int r, T k)
    {
        if (l <= this->st_arr[curr_pos].l && r >= this->st_arr[curr_pos].r)
        {
            if (l == r)
            {
                this->st_arr[curr_pos].sum += k;
                return k;
            }
            
            // 这里直接懒标记，不在往下遍历
            this->touch_lazy_flag(this->st_arr, curr_pos, k);
            return k * (r - l + 1);
        }
        else
        {
            int child_l = curr_pos * 2 + 1;
            int child_r = curr_pos * 2 + 2;
            int mid = this->st_arr[child_l].r;

            // 将懒标记下发
            if (this->st_arr[curr_pos].lazy != 0)
            {
                this->touch_lazy_flag(this->st_arr, child_l, this->st_arr[curr_pos].k);

                this->touch_lazy_flag(this->st_arr, child_r, this->st_arr[curr_pos].k);

                this->st_arr[curr_pos].lazy = 0;
                this->st_arr[curr_pos].sum += this->st_arr[curr_pos].k * 
                    (this->st_arr[curr_pos].r - this->st_arr[curr_pos].l + 1);
            }
            int temp_sum;
            if (mid >= r)
            {
                temp_sum = this->add_dfs(child_l, l, r, k);
            } else if (mid < l)
            {
                temp_sum = this->add_dfs(child_r, l, r, k);
            }
            else
            {
                temp_sum = this->add_dfs(child_l, l, mid, k) + this->add_dfs(child_r, mid + 1, r, k);
            }
            this->st_arr[curr_pos].sum += temp_sum;
            return temp_sum;
        }
    }

public:
    /**
     * @brief 初始化
     *
     * @param 
     * @param 
     * @return
     */
    void segment_tree_init(vector<T> &arr)
    {
        if (arr.size() == 0) return;

        this->s_arr = arr;
        this->st_arr = this->generate_segment_tree_array(arr, this->segment_tree_layers);
    }

    /**
     * @brief 单点增加
     *
     * @param 
     * @param 
     * @return
     */
    void add(int pos, T k)
    {
        if (pos < 0 || pos >= this->s_arr.size()) return;
        
        // 根据数组位置找到对应
        int st_arr_pos = this->get_segment_tree_pos(pos);

        while (st_arr_pos > 0)
        {
            this->st_arr[st_arr_pos].sum += k;
            st_arr_pos = (st_arr_pos - 1) / 2;
        }
        this->st_arr[st_arr_pos].sum += k;
    }

    /**
     * @brief 区间增加，利用懒标记lazy
     *
     * @param 
     * @param 
     * @return
     */
    void add_interval(int l, int r, T k)
    {
        if (l < 0 || r >= this->s_arr.size() || l > r)
        {
            return;
        }

        this->add_dfs(0, l, r, k);
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
        if (l < 0 || r >= this->s_arr.size() || l > r)
        {
            return res;
        }
        return this->query_dfs(0, l, r);
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
        if (pos >= this->s_arr.size()) return;
        
        T k = n - this->query_interval(pos, pos);
        this->add(pos, k);
    }
};

}

#endif