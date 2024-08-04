#include "topological_sort.h"

namespace TOPO_SORT {

struct topological_sort_node
{  
public:
    int id;
    set<int> in_negihbors;
    set<int> out_negihbors;    
};

/**
 * @brief topological sort 拓扑排序
 *
 * @param edges directed edge eg:pair::first->pair::second
 * @param split_chr split char
 * @return success:return sorted vector<int>;error: return null (vector<int>())
 */
vector<int> topological_sort(vector<pair<int, int>> edges)
{
    vector<int> res;
    // establish directed graph
    map<int, topological_sort_node> graph;

    // establish directed graph
    for (auto &edge : edges)
    {
        if (graph.count(edge.first) ==  0)
        {
            graph[edge.first] = topological_sort_node();
            graph[edge.first].id = edge.first;
        }
        if (graph.count(edge.second) ==  0)
        {
            graph[edge.second] = topological_sort_node();
            graph[edge.second].id = edge.second;
        }
        graph[edge.first].out_negihbors.insert(edge.second);
        graph[edge.second].in_negihbors.insert(edge.first);
    }

    // topo sort

    queue<int> qu;
    for (auto &p1 : graph)
    {
        if (p1.second.in_negihbors.size() == 0)
        {
            qu.push(p1.first);
        }
    }

    // push id into stack when indegree is 0
    while (!qu.empty())
    {
        int id = qu.front();
        res.push_back(id);
        qu.pop();
        for (auto &tmp_id : graph[id].out_negihbors)
        {
            graph[tmp_id].in_negihbors.erase(id);
            if (graph[tmp_id].in_negihbors.size() == 0)
            {
                qu.push(tmp_id);
            }
        }
    }

    if (res.size() != graph.size())
    {
        return vector<int>(0);
    }
    return res;
}

}