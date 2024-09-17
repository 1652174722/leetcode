#include "difference_array.h"
#include "gtest/gtest.h"

using namespace DIFFERENCE_ARRAY;

TEST(difference_array, difference_array_test_001)
{
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
    {
        int K = 10;
        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, v.size() - 1, K);

            FOR_EACH(i, 0, v.size())
            {
                ASSERT_EQ(true, (v[i] + K) == da.query(i));
            }
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, 0, K);

            ASSERT_EQ(true, (v[0] + K) == da.query(0));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, 1, K);

            ASSERT_EQ(true, (v[0] + K) == da.query(0));

            ASSERT_EQ(true, (v[1] + K) == da.query(1));

            ASSERT_EQ(true, v[2] == da.query(2));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(v.size() - 2, v.size() - 1, K);

            ASSERT_EQ(true, v[v.size() - 3] == da.query(v.size() - 3));

            ASSERT_EQ(true, (v[v.size() - 2] + K) == da.query(v.size() - 2));

            ASSERT_EQ(true, (v[v.size() - 1] + K) == da.query(v.size() - 1));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(v.size() - 1, v.size() - 1, K);

            ASSERT_EQ(true, v[v.size() - 2] == da.query(v.size() - 2));
            ASSERT_EQ(true, (v[v.size() - 1] + K) == da.query(v.size() - 1));
        }
    }

    {
        int K = -10;
        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, v.size() - 1, K);

            FOR_EACH(i, 0, v.size())
            {
                ASSERT_EQ(true, (v[i] + K) == da.query(i));
            }
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, 0, K);

            ASSERT_EQ(true, (v[0] + K) == da.query(0));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(0, 1, K);

            ASSERT_EQ(true, (v[0] + K) == da.query(0));

            ASSERT_EQ(true, (v[1] + K) == da.query(1));

            ASSERT_EQ(true, v[2] == da.query(2));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(v.size() - 2, v.size() - 1, K);

            ASSERT_EQ(true, v[v.size() - 3] == da.query(v.size() - 3));

            ASSERT_EQ(true, (v[v.size() - 2] + K) == da.query(v.size() - 2));

            ASSERT_EQ(true, (v[v.size() - 1] + K) == da.query(v.size() - 1));
        }

        {
            vector<int> v = {1, 3, 5, 7, 9};
            difference_array<int> da(v);

            da.add_given_range(v.size() - 1, v.size() - 1, K);

            ASSERT_EQ(true, v[v.size() - 2] == da.query(v.size() - 2));
            ASSERT_EQ(true, (v[v.size() - 1] + K) == da.query(v.size() - 1));
        }
    }
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
}