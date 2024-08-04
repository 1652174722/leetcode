#ifndef DIFFERENCE_ARRAY_H
#define DIFFERENCE_ARRAY_H

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

namespace DIFFERENCE_ARRAY {

/**
 * @brief 差分数组，支持静态数组场景下 区间修改频繁，单点查询不频繁的场景
 */
template<class T>
class difference_array
{
    private:
        vector<T> s_arr;
        vector<T> diff_arr;
    public:
        difference_array(vector<T> &arr)
        {
            if (arr.size() == 0) return;

            this->s_arr = arr;
            this->diff_arr.resize(arr.size(), arr[0]);
            this->diff_arr[0] = arr[0];
            FOR_EACH(i, 1, arr.size())
            {
                this->diff_arr[i] = arr[i] - arr[i - 1];
            }
        }
        
        /**
         * @brief add k to each value with [l, r]
         *
         * @param
         * @param 
         * @return
         **/
        void add_given_range(int l, int r, T k)
        {
            if (l >= 0 && r < diff_arr.size())
            {
                diff_arr[l] += k;

                if (r != (s_arr.size() - 1))
                {
                    diff_arr[r + 1] -= k;
                }
            }
        }

        /**
         * @brief get the value of s_arr in a certain postion
         *
         * @param
         * @param 
         * @return
         **/
        T query(int pos)
        {
            if (pos >= diff_arr.size()) return diff_arr[0];
            if (pos <= 0) return diff_arr[0];
            T curr_value = diff_arr[0];
            FOR_EACH(i, 1, pos + 1)
            {
                curr_value += diff_arr[i];
            }
            return curr_value;
        }
};

}
#endif