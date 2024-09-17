#include "binary_indexed_tree.h"
#include "gtest/gtest.h"

using namespace BINARY_INDEXED_TREE;

TEST(binary_indexed_tree, binary_indexed_tree_test)
{
    binary_indexed_tree<int> bt;
    vector<int> s_arr = {1, 2, 3, 4, 5, 6 ,7, 8, 9, 0};
    bt.binary_indexed_tree_init(s_arr);

    FOR_EACH(i, 0, s_arr.size())
    {
        ASSERT_EQ(true, bt.query_interval(i, i) == s_arr[i]);
    }
    int value = 10;

    FOR_EACH(i, 0, s_arr.size())
    {
        s_arr[i] += value;
        bt.add(i, value);
        ASSERT_EQ(true, bt.query_interval(i, i) == s_arr[i]);
    }
    auto temp_sum_func= [&s_arr] (int l, int r) ->int {
        int sum = 0;
        FOR_EACH(i, l, r + 1)
        {
            sum += s_arr[i];
        }
        return sum;
    };
    FOR_EACH(i, 0, s_arr.size())
    {
        FOR_EACH(j, i, s_arr.size())
        {
            ASSERT_EQ(true, bt.query_interval(j - i, j) == temp_sum_func(j - i, j));
        }
        ASSERT_EQ(true, bt.query(i) == temp_sum_func(0, i));
    }
    value = 33;
    FOR_EACH(i, 0, s_arr.size())
    {
            s_arr[i] = value;
        bt.update(i, value);
        ASSERT_EQ(true, bt.query_interval(i, i) == temp_sum_func(i, i));
        ASSERT_EQ(true, bt.query_interval(0, s_arr.size() - 1) == temp_sum_func(0, s_arr.size() - 1));
        ASSERT_EQ(true, bt.query(i) == temp_sum_func(0, i));
    }
}
