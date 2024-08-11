#include "graph_du_shortest_path.h"

namespace GRAPH_DU_SHORTEST_PATH {

    int graph_du_shortest_path::get_shortest_path_length_between_two_nodes_bfs(vector<vector<int>> &adjcency_table, int curr_node, int target_node)
    {
        vector<int> visited(adjcency_table.size(), 0);
        queue<pair<int, int>> qs;  // pair<int, int>：node_id, curr_depths
        qs.push(make_pair(curr_node, 0));
        visited[curr_node] = 1;
        int min_depth = INT32_MAX;

        // 先通过bfs得到 最短路径长度
        while (!qs.empty())
        {
            pair<int, int> p = qs.front();

            if (p.first == target_node && p.second <= min_depth)
            {
                min_depth = p.second;
                break;
            }
            else
            {
                for(auto &node_id : adjcency_table[p.first])
                {
                    if (visited[node_id] == 0)
                    {
                        qs.push(make_pair(node_id, p.second + 1));
                        visited[node_id] = 1;      
                    }
                }
            }
            qs.pop();
        }
        
        return min_depth;
    }

    void graph_du_shortest_path::get_all_shortest_paths_between_two_nodes_dfs(vector<vector<int>> &adjcency_table, vector<int> &visited, vector<int> &path,
        int curr_depth, int min_depth, int curr_node, int target_node, vector<vector<int>> &paths)
    {
        if (visited[curr_node] == 0 && curr_depth <= min_depth)
        {
            path.push_back(curr_node);
            visited[curr_node] =1;

            if (curr_node == target_node)
            {
                paths.push_back(path);
            }
            else
            {
                for(auto &node_id : adjcency_table[curr_node])
                {
                    if (visited[node_id] == 0)
                    {
                        get_all_shortest_paths_between_two_nodes_dfs(adjcency_table, visited, path, curr_depth + 1, min_depth, node_id, target_node, paths);   
                    }
                }
            }
            
            visited[curr_node] = 0;
            path.pop_back();
        }
    }

    void graph_du_shortest_path::undirected_graph_init(vector<vector<int>> edges)
    {
        // 通过 edges 生成邻接表，减少遍历次数
        this->edges = edges;
        this->adjcency_table = vector<vector<int>>(edges.size(), vector<int>(0));
        FOR_EACH(i, 0, edges.size())
        {
            FOR_EACH(j, 0, edges[i].size())
            {
                if (edges[i][j] != 0 && j != i)
                {
                    adjcency_table[i].push_back(j);
                }
            }
        }
    }

    int graph_du_shortest_path::get_shortest_path_length_between_two_nodes(int a, int b)
    {
        return get_shortest_path_length_between_two_nodes_bfs(this->adjcency_table, a, b);
    }

    vector<vector<int>> graph_du_shortest_path::get_all_shortest_paths_between_two_nodes(int a, int b)
    {
        vector<vector<int>> res(0);
        int min_depth = get_shortest_path_length_between_two_nodes_bfs(this->adjcency_table, a, b);

        if (min_depth == 0 || min_depth == INT32_MAX)
        {
            return res;
        }

        vector<int> visited(this->adjcency_table.size(), 0);
        vector<int> path;
        get_all_shortest_paths_between_two_nodes_dfs(this->adjcency_table, visited, path, 0, min_depth, a, b, res);
        return res;
    }
}