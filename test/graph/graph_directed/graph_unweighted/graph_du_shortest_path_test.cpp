#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include "graph_du_shortest_path.h"
#include "gtest/gtest.h"

TEST(graph_du_shortest_path, get_shortest_path_length_between_two_nodes_test)
{
    pair<int, int> edge_list[] = {
        {0, 1},
        {0, 2},
        {0, 5},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {2, 5},
        {2, 7}
    };
    vector<vector<int>> edges = vector<vector<int>>(8, vector<int>(8, 0));

    for (auto &edge : edge_list)
    {
        edges[edge.first][edge.second] = 1;
        edges[edge.second][edge.first] = 1;
    }
    GRAPH_DU_SHORTEST_PATH::graph_du_shortest_path uw_graph;
    uw_graph.undirected_graph_init(edges);

    int min_depth = uw_graph.get_shortest_path_length_between_two_nodes(0, 5);
    EXPECT_TRUE(1 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(0, 1);
    EXPECT_TRUE(1 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(0, 3);
    EXPECT_TRUE(2 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(6, 4);
    EXPECT_TRUE(INT32_MAX == min_depth);
    
    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(6, 6);
    EXPECT_TRUE(0 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(3, 3);
    EXPECT_TRUE(0 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(7, 1);
    EXPECT_TRUE(2 == min_depth);

    min_depth = uw_graph.get_shortest_path_length_between_two_nodes(1, 7);
    EXPECT_TRUE(2 == min_depth);
}


TEST(graph_du_shortest_path, get_shorts_paths_between_two_nodes_test)
{
    pair<int, int> edge_list[] = {
        {0, 1},
        {0, 2},
        {0, 5},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 7},
        {2, 5},
        {2, 7},
        {5, 7}
    };
    vector<vector<int>> edges = vector<vector<int>>(8, vector<int>(8, 0));

    for (auto &edge : edge_list)
    {
        edges[edge.first][edge.second] = 1;
        edges[edge.second][edge.first] = 1;
    }
    GRAPH_DU_SHORTEST_PATH::graph_du_shortest_path uw_graph;
    uw_graph.undirected_graph_init(edges);

    auto is_equal_func = [](vector<vector<int>> &a, vector<vector<int>> &b) -> bool {
        if(a.size() != b.size()) return false;

        FOR_EACH(i, 0, a.size())
        {
            if (a[i].size() != b[i].size()) return false;
            FOR_EACH(j, 0, a[i].size())
            {
                if (a[i][j] != b[i][j]) return false;   
            }
        }
        return true;
    };

    {
        vector<vector<int>> real_res = {
            {0, 1, 7},
            {0, 2, 7},
            {0, 5, 7}
        };

        vector<vector<int>> res = uw_graph.get_all_shortest_paths_between_two_nodes(0, 7);
        EXPECT_TRUE(3 == res.size());
        EXPECT_TRUE(true == is_equal_func(res, real_res));
    }

    {
        vector<vector<int>> res = uw_graph.get_all_shortest_paths_between_two_nodes(0, 0);
        EXPECT_TRUE(0 == res.size());
    }

    {
        vector<vector<int>> res = uw_graph.get_all_shortest_paths_between_two_nodes(0, 6);
        EXPECT_TRUE(0 == res.size());
    }


    {
        vector<vector<int>> real_res = {
            {0, 5}
        };
        vector<vector<int>> res = uw_graph.get_all_shortest_paths_between_two_nodes(0, 5);
        EXPECT_TRUE(1 == res.size());
        EXPECT_TRUE(true == is_equal_func(res, real_res));
    }
}

