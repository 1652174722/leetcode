#include <sys/time.h>
#include <vector>

#include "avl_tree.h"
#include "gtest/gtest.h"

using namespace AVL_TREE;

TEST(avl_tree, avl_tree_test)
{
    auto cmp_func = [] (const int &a, const int &b) -> int {
        if (a == b) return 0;
        else if (a > b) return 1;
        else return -1;
    };

    auto size_func = [] (vector<size_t> &v) -> size_t {
        size_t sum = 0;
        FOR_EACH(i, 0, v.size())
        {
            sum += v[i];
        }
        return sum;
    };

    auto insert_func = [] (vector<size_t> &v, size_t i) -> size_t {
        if (i < 0 || i >= v.size()) return -1;
        v[i]++;
        return v[i];
    };

    auto erase_func = [] (vector<size_t> &v, size_t i) -> size_t {
        if (i < 0 || i >= v.size()) return 0;

        size_t real_count = v[i];
        v[i] = 0;
        return real_count;
    };

    auto erase_once_func = [] (vector<size_t> &v, size_t i) -> size_t {
        if (i < 0 || i >= v.size()) return -1;

        size_t real_count = v[i];
        if (real_count == 0) return 0;
        v[i]--;
        return real_count;
    };

    auto find_func = [] (vector<size_t> &v, size_t i) -> size_t {
        if (i < 0 || i >= v.size()) return 0;

        return v[i];
    };

    auto clear_func = [] (vector<size_t> &v) {
        FOR_EACH(i, 0, v.size())
        {
            v[i] = 0;
        }
    };

    auto traverse_func = [] (vector<size_t>&v, int(*process_func)(size_t count, const int &value, void *in_out), void *in_out) -> int {
        FOR_EACH(i, 0, v.size())
        {
            int ret = 0;
            if (v[i] > 0)
            {
                ret = process_func(v[i], i, in_out);
                if (ret)
                {
                    return -1;
                } 
            }     
        }
        return 0;
    };

    auto get_kth_func = [] (vector<size_t> &v, size_t t) -> int {
        size_t sum = 0;
        FOR_EACH(i, 0, v.size())
        {
            sum += v[i];
            if (t < sum)
            {
                return i;
            }
        }

        throw string("out of avl size range");
    };

    auto get_position_func = [] (vector<size_t> &v, const int &value) -> pair<size_t, size_t> {
        if (value < 0 || value >= (int)v.size())
        {
            throw string("no such value in avl");
        }
        size_t start_pos = 0;
        FOR_EACH(i, 0, v.size())
        {

            if (value == (int)i)
            {
                return make_pair(start_pos, start_pos + v[i]);
            }
            start_pos += v[i];
        }
        return make_pair(0, 0);
    };

    auto first_lt_func = [] (vector<size_t> &v, const int &value) -> int {
        if (value <= 0)
        {
            throw string("no such value in avl");
        }
        if (value > (int)(v.size() - 1)) return v.size() - 1;
        return value - 1;
    };

    auto first_gt_func = [] (vector<size_t> &v, const int &value) -> int {
        if (value >= (int)(v.size() - 1))
        {
            throw string("no such value in avl");
        }
        if (value < 0) return 0;
        return value + 1;
    }; 


    // 单重复值测试
    {
        int count = 10;
        vector<size_t> v1 = vector<size_t>(count, 0);
        avl_tree<int> t1(cmp_func);

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.insert(llll) == insert_func(v1, llll));
        }
        
        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.kth(llll) == get_kth_func(v1, llll));
            auto p1 = t1.position(llll);
            auto p2 = get_position_func(v1, llll);
            ASSERT_EQ(true, p1.first == p2.first && p2.second == p2.second);
        }

        EXPECT_ANY_THROW(t1.kth(-1));
        EXPECT_ANY_THROW(t1.kth(t1.size()));

        EXPECT_ANY_THROW(t1.position(-1));
        EXPECT_ANY_THROW(t1.position(t1.size()));


        EXPECT_ANY_THROW(t1.first_lt(0));
        FOR_EACH(i, 1, v1.size() + 1)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.first_lt(llll) == first_lt_func(v1, llll));
        }

        ASSERT_EQ(true, t1.first_gt(-1)== first_gt_func(v1, -1));
        FOR_EACH(i, 0, v1.size() - 1)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.first_gt(llll) == first_gt_func(v1, llll));
        }
        EXPECT_ANY_THROW(t1.first_gt(t1.size() - 1));

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase_once(llll) == erase_once_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
        }

        ASSERT_EQ(true, t1.size() == size_func(v1));

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.insert(llll) == insert_func(v1, llll));
            ASSERT_EQ(true, t1.size() == size_func(v1));
        }

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase(llll) == erase_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
        }

        FOR_EACH(i, v1.size(), v1.size() * 2)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase(llll) == erase_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
        }

        t1.clear();
        clear_func(v1);
        ASSERT_EQ(true, t1.size() == size_func(v1));
    }

    // 多重复值测试
    {
        int count = 10;
        int loop_count = 10;
        vector<size_t> v1 = vector<size_t>(count, 0);
        avl_tree<int> t1(cmp_func);
        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            FOR_EACH(j, 0, loop_count)
            {
                ASSERT_EQ(true, t1.insert(llll) == insert_func(v1, llll));
                ASSERT_EQ(true, t1.size() == size_func(v1));
            }
        }

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.kth(llll) == get_kth_func(v1, llll));
            auto p1 = t1.position(llll);
            auto p2 = get_position_func(v1, llll);
            ASSERT_EQ(true, p1.first == p2.first && p2.second == p2.second);
        }

        EXPECT_ANY_THROW(t1.kth(-1));
        EXPECT_ANY_THROW(t1.kth(t1.size()));

        EXPECT_ANY_THROW(t1.position(-1));
        EXPECT_ANY_THROW(t1.position(t1.size()));


        EXPECT_ANY_THROW(t1.first_lt(0));
        FOR_EACH(i, 1, v1.size() + 1)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.first_lt(llll) == first_lt_func(v1, llll));
        }

        ASSERT_EQ(true, t1.first_gt(-1)== first_gt_func(v1, -1));
        FOR_EACH(i, 0, v1.size() - 1)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.first_gt(llll) == first_gt_func(v1, llll));
        }
        EXPECT_ANY_THROW(t1.first_gt(t1.size() - 1));

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase_once(llll) == erase_once_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.size() == size_func(v1));
        }

        FOR_EACH(i, v1.size(), v1.size() * 2)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase(llll) == erase_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
        }

        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.erase(llll) == erase_func(v1, llll));
            ASSERT_EQ(true, t1.find(llll) == find_func(v1, llll));
            ASSERT_EQ(true, t1.size() == size_func(v1));
        }

        t1.clear();
        clear_func(v1);
        ASSERT_EQ(true, t1.size() == size_func(v1));
    }

    // 遍历能力测试
    {
        int count = 10;
        int loop_count = 10;
        vector<size_t> v1 = vector<size_t>(count, 0);
        avl_tree<int> t1(cmp_func);
        FOR_EACH(i, 0, v1.size())
        {
            int llll = (int)i;
            FOR_EACH(j, 0, loop_count)
            {
                ASSERT_EQ(true, t1.insert(llll) == insert_func(v1, llll));
                ASSERT_EQ(true, t1.size() == size_func(v1));
            }
        }

        auto traverse_func_test = [](size_t count, const int &value, void *in_out) -> int {
            vector<pair<int, int>> *v1 = (vector<pair<int, int>> *)in_out;

            v1->push_back(make_pair(count, value));
            return 0;
        };

        vector<pair<int, int>> res1;
        vector<pair<int, int>> res2;
        t1.traverse(traverse_func_test, &res1);
        traverse_func(v1, traverse_func_test, &res2);

        ASSERT_EQ(true, res1.size() == res2.size());
        FOR_EACH(i, 0, res1.size())
        {
            ASSERT_EQ(true, res1[i].first == res2[i].first && res1[i].second == res2[i].second);
        }
    }

    // 性能测试
    {
        double time_consume;
        struct timeval start;
        struct timeval end;
        
        int count = 1024 * 1024 * 10;
        avl_tree<int> t1(cmp_func);

        gettimeofday(&start, NULL);
        FOR_EACH(i, 0, count)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.insert(llll) == 1);
        }
        gettimeofday(&end, NULL);
        time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        cout << "avl_tree insert count(" << count << ")" << " duration:" << time_consume << "s" << endl;

        gettimeofday(&start, NULL);
        FOR_EACH(i, 0, count)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.find(llll) == 1);
        }
        gettimeofday(&end, NULL);
        time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        cout << "avl_tree find count(" << count << ")" << " duration:" << time_consume << "s" << endl;

        gettimeofday(&start, NULL);
        FOR_EACH(i, 0, count)
        {
            int llll = (int)i;
            ASSERT_EQ(true, t1.erase(llll) == 1);
        }
        gettimeofday(&end, NULL);
        time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        cout << "avl_tree erase count(" << count << ")" << " duration:" << time_consume << "s" << endl;

        // set<int> s1;
        // gettimeofday(&start, NULL);
        // FOR_EACH(i, 0, count)
        // {
        //     int llll = (int)i;
        //     s1.insert(llll);
        // }
        // gettimeofday(&end, NULL);
        // time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        // cout << "set insert count(" << count << ")" << " duration:" << time_consume << "s" << endl;

        // gettimeofday(&start, NULL);
        // FOR_EACH(i, 0, count)
        // {
        //     int llll = (int)i;
        //     s1.find(llll);
        // }
        // gettimeofday(&end, NULL);
        // time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        // cout << "set find count(" << count << ")" << " duration:" << time_consume << "s" << endl;

        // gettimeofday(&start, NULL);
        // FOR_EACH(i, 0, count)
        // {
        //     int llll = (int)i;
        //     s1.erase(llll);
        // }
        // gettimeofday(&end, NULL);
        // time_consume = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        // cout << "set erase count(" << count << ")" << " duration:" << time_consume << "s" << endl;
        

    }
}