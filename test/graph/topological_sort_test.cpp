#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "topological_sort.h"
#include "gtest/gtest.h"

TEST(topological_sort, topological_sort_test)
{
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(1, 2));
    edges.push_back(make_pair(1, 4));

    edges.push_back(make_pair(2, 3));

    edges.push_back(make_pair(3, 6));
    edges.push_back(make_pair(3, 8));

    edges.push_back(make_pair(4, 2));

    edges.push_back(make_pair(5, 3));

    edges.push_back(make_pair(6, 8));

    edges.push_back(make_pair(7, 5));

    vector<int> res = TOPO_SORT::topological_sort(edges);
    EXPECT_EQ(res.size(), 8);

    for (auto &id : res)
    {
        cout << id << " ";
    }
    cout << endl;
    
}

