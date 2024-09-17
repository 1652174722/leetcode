#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "graph_du_topological_sort.h"
#include "gtest/gtest.h"

TEST(graph_du_topological_sort, graph_du_topological_sort_test)
{
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
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

    vector<int> res = GRAPH_DU_TOPO_SORT::graph_du_topological_sort(edges);
    EXPECT_EQ(res.size(), (const long unsigned int)8);

    for (auto &id : res)
    {
        cout << id << " ";
    }
    cout << endl;
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
}

