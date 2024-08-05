#include "segment_tree.h"
#include "gtest/gtest.h"

using namespace SEGMENT_TREE;

TEST(segment_tree, segment_tree_test)
{
    {
            // 测试区间查询能力
        vector<int> s_arr = {0, 1, 2, 3, 4, 5};
        segment_tree<int> st = segment_tree<int>();
            st.segment_tree_init(s_arr);
            auto temp_sum_func= [&s_arr] (int l, int r) ->int {
            int sum = 0;
            FOR_EACH(i, l, r + 1)
            {
                sum += s_arr[i];
            }
            return sum;
        };
            ASSERT_EQ(true, st.query_interval(0, 5) == temp_sum_func(0, 5));
    }
    
    {
        // 测试 单点更新
        vector<int> s_arr = {0, 1, 2, 3, 4, 5};
        segment_tree<int> st = segment_tree<int>();
        st.segment_tree_init(s_arr);

        auto temp_sum_func= [&s_arr] (int l, int r) ->int {
            int sum = 0;
            FOR_EACH(i, l, r + 1)
            {
                sum += s_arr[i];
            }
            return sum;
        };

        int value = 10;
        FOR_EACH(i, 0, s_arr.size())
        {
            s_arr[i] += value;
            st.add(i, value);

            ASSERT_EQ(true, st.query_interval(i, i) == temp_sum_func(i, i));
            ASSERT_EQ(true, st.query_interval(0, 5) == temp_sum_func(0, 5));
        }
    }


    {
        // 测试 区间更新
        vector<int> s_arr = {0, 1, 2, 3, 4, 5};
        segment_tree<int> st = segment_tree<int>();
        st.segment_tree_init(s_arr);

        auto add_func_interval= [&s_arr] (int l, int r, int k) {
            FOR_EACH(i, l, r + 1)
            {
                s_arr[i] += k;
            }
        };

        auto temp_sum_func= [&s_arr] (int l, int r) ->int {
            int sum = 0;
            FOR_EACH(i, l, r + 1)
            {
                sum += s_arr[i];
            }
            return sum;
        };

        int value = 10;
        FOR_EACH(i, 0, s_arr.size())
        {
            add_func_interval(0, i, value);
            st.add_interval(0, i, value);

            ASSERT_EQ(true, st.query_interval(0, i) == temp_sum_func(0, i));
            ASSERT_EQ(true, st.query_interval(0, 5) == temp_sum_func(0, 5));
        }
    }

    {
        // 测试 区间更新
        vector<int> s_arr = {0, 1, 2, 3, 4, 5};
        segment_tree<int> st = segment_tree<int>();
        st.segment_tree_init(s_arr);

        auto add_func_interval= [&s_arr] (int l, int r, int k) {
            FOR_EACH(i, l, r + 1)
            {
                s_arr[i] += k;
            }
        };

        auto temp_sum_func= [&s_arr] (int l, int r) ->int {
            int sum = 0;
            FOR_EACH(i, l, r + 1)
            {
                sum += s_arr[i];
            }
            return sum;
        };

        int value = 10;
        FOR_EACH(i, 0, s_arr.size())
        {
            add_func_interval(i, s_arr.size() - 1, value);
            st.add_interval(i, s_arr.size() - 1, value);

            ASSERT_EQ(true, st.query_interval(i, s_arr.size() - 1) == temp_sum_func(i, s_arr.size() - 1));
            ASSERT_EQ(true, st.query_interval(0, 5) == temp_sum_func(0, 5));
        }

    }

    {
        // 测试 单点更新
        vector<int> s_arr = {0, 1, 2, 3, 4, 5};
        segment_tree<int> st = segment_tree<int>();
        st.segment_tree_init(s_arr);

        auto update_func_interval= [&s_arr] (int pos, int value) {
            s_arr[pos] = value;
        };

        auto temp_sum_func= [&s_arr] (int l, int r) ->int {
            int sum = 0;
            FOR_EACH(i, l, r + 1)
            {
                sum += s_arr[i];
            }
            return sum;
        };

        int value = 10;
        FOR_EACH(i, 0, s_arr.size())
        {
            update_func_interval(i, value);
            st.update(i, value);
            ASSERT_EQ(true, st.query_interval(i, i) == temp_sum_func(i, i));
            ASSERT_EQ(true, st.query_interval(0, 5) == temp_sum_func(0, 5));
        }

    }
}

