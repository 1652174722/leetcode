#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "graph_dijkstra.h"
#include "gtest/gtest.h"

TEST(graph_dijkstra, graph_dijkstra_test)
{
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
    int node_counts = 5;
    pair<pair<int, int>, int> edge_list[] = {
        {{0,  1}, 8},
        {{0,  2}, 2},
        {{1,  2}, 5},
        {{1,  3}, 1},
        {{2,  3}, 1},
        {{2,  4}, 4},
        {{3,  4}, 5},
    };
    vector<vector<int>> edges = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));
    vector<vector<int>> weights = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));

    for (auto &edge : edge_list)
    {
        edges[edge.first.first][edge.first.second] = 1;
        edges[edge.first.second][edge.first.first] = 1;

        weights[edge.first.first][edge.first.second] = edge.second;
        weights[edge.first.second][edge.first.first] = edge.second;
        
    }

    GRAPH_DIJKSTRA::graph_dijkstra<int> gd;
    gd.graph_dijkstra_init(edges, weights);

    auto is_equal_func = [](vector<int> &a, vector<int> &b) -> bool {
        if(a.size() != b.size()) return false;

        FOR_EACH(i, 0, a.size())
        {
            if (a[i] != b[i]) return false;   
        }
        return true;
    };

    vector<int> real_res = vector<int>(node_counts);
    real_res[0] = 0;
    real_res[1] = 4;
    real_res[2] = 2;
    real_res[3] = 3;
    real_res[4] = 6;

    vector<int> res = gd.get_shortest_path_weight_between_nodo_with_others(0);
    EXPECT_TRUE(true == is_equal_func(real_res, res));
}

TEST(graph_dijkstra, graph_dijkstra_test_001)
{
    int node_counts = 11;
    pair<pair<int, int>, int> edge_list[] = {
        {{0,  1}, 2},
        {{0,  2}, 8},
        {{0,  3}, 1},
        {{1,  2}, 6},
        {{1,  4}, 1},
        {{2,  3}, 7},
        {{2,  4}, 5},
        {{2,  5}, 1},
        {{2,  6}, 2},
        {{3,  6}, 9},
        {{4,  5}, 3},
        {{4,  7}, 2},
        {{4,  8}, 9},
        {{5,  6}, 4},
        {{5,  8}, 6},
        {{6,  8}, 3},
        {{6,  9}, 1},
        {{7,  8}, 7},
        {{7, 10}, 9},
        {{8,  9}, 1},
        {{8, 10}, 2},
        {{9, 10}, 4}
    };
    vector<vector<int>> edges = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));
    vector<vector<int>> weights = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));

    for (auto &edge : edge_list)
    {
        edges[edge.first.first][edge.first.second] = 1;
        edges[edge.first.second][edge.first.first] = 1;

        weights[edge.first.first][edge.first.second] = edge.second;
        weights[edge.first.second][edge.first.first] = edge.second;
        
    }

    GRAPH_DIJKSTRA::graph_dijkstra<int> gd;
    gd.graph_dijkstra_init(edges, weights);

    auto is_equal_func = [](vector<int> &a, vector<int> &b) -> bool {
        if(a.size() != b.size()) return false;

        FOR_EACH(i, 0, a.size())
        {
            if (a[i] != b[i]) return false;   
        }
        return true;
    };


    vector<int> real_res = vector<int>(node_counts);
    real_res[0] = 0;
    real_res[1] = 2;
    real_res[2] = 7;
    real_res[3] = 1;
    real_res[4] = 3;
    real_res[5] = 6;
    real_res[6] = 9;
    real_res[7] = 5;
    real_res[8] =11;
    real_res[9] = 10;
    real_res[10] = 13;

    vector<int> res = gd.get_shortest_path_weight_between_nodo_with_others(0);
    EXPECT_TRUE(true == is_equal_func(real_res, res));
}

TEST(graph_dijkstra, graph_dijkstra_test_002)
{
    int node_counts = 6;
    pair<pair<int, int>, int> edge_list[] = {
        {{0,  1}, 4},
        {{0,  2}, 2},
        {{1,  2}, 1},
        {{1,  3}, 6},
        {{2,  3}, 1}
    };
    vector<vector<int>> edges = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));
    vector<vector<int>> weights = vector<vector<int>>(node_counts, vector<int>(node_counts, 0));

    for (auto &edge : edge_list)
    {
        edges[edge.first.first][edge.first.second] = 1;
        edges[edge.first.second][edge.first.first] = 1;

        weights[edge.first.first][edge.first.second] = edge.second;
        weights[edge.first.second][edge.first.first] = edge.second;
        
    }

    GRAPH_DIJKSTRA::graph_dijkstra<int> gd;
    gd.graph_dijkstra_init(edges, weights);

    auto is_equal_func = [](vector<int> &a, vector<int> &b) -> bool {
        if(a.size() != b.size()) return false;

        FOR_EACH(i, 0, a.size())
        {
            if (a[i] != b[i]) return false;   
        }
        return true;
    };


    vector<int> real_res = vector<int>(node_counts);
    real_res[0] = 0;
    real_res[1] = 3;
    real_res[2] = 2;
    real_res[3] = 3;
    real_res[4] = (int)PATH_INFINITE;
    real_res[5] = (int)PATH_INFINITE;

    vector<int> res = gd.get_shortest_path_weight_between_nodo_with_others(0);
    EXPECT_TRUE(true == is_equal_func(real_res, res));
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
}