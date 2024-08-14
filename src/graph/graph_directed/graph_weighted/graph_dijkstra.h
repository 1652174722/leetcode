#ifndef _GRAPH_DIJKSTRA_H
#define _GRAPH_DIJKSTRA_H

#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <array>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "template.h"
using namespace std;

namespace GRAPH_DIJKSTRA {

/**
 * @brief Dijkstra算法
 * 背景：迪杰斯特拉算法(Dijkstra)是由荷兰计算机科学家狄杰斯特拉于1959 年提出的，因此又叫狄克斯特拉算法
 *      求解：指定点到其他所有节点的最短路径（权重之和最小）下的权重和
 * @param 
 * @param
 * @return 
 */
template<class T>
class graph_dijkstra
{
private:
    vector<vector<int>> edges;
    vector<vector<T>> weight;
    vector<vector<int>> adjcency_table;  // 存放所有出边的节点
public:

    /**
     * @brief 有权重的有向shi图初始化
     *        约束：权重值 T 只能为正,可以为整数,小数

     * 
     * @param edges edegs[i][j]为0 表示节点i到节点j没有边; 1表示节点i到j之间存在一条边
     * @param weight weight[i][j]，边i->j的权重，大于等于0,即 T1+T2 >= T1或T2
     * @return
     */
    void graph_dijkstra_init(vector<vector<int>> &edges, vector<vector<T>> &weight)
    {
        this->edges = edges;
        this->weight = weight;

        FOR_EACH(i, 0, edges.size())
        {
            this->adjcency_table.push_back(vector<int>(0));
            FOR_EACH(j, 0, edges[i].size())
            {
                if (edges[i][j] != 0 && j != i)
                {
                    this->adjcency_table[i].push_back(j);
                }
            }
        }
    }

    /**
     * @brief 获取指定节点k到其他节点的权重
     * @return res，res[k]固定为0，res[i](i != k)表示k到i的最短路径
     */
    vector<T> get_shortest_path_weight_between_nodo_with_others(int k)
    {
        if (k < 0 || k >= this->edges.size())
        {
            return vector<T>(0);
        }
        vector<int> visited(this->edges.size(), 0);
        vector<T> res = vector<T>(this->edges.size(), (T)INT32_MAX);
        res[k] = (T)0;
        
        auto weight_comp = [](const pair<T, int> &a, const pair<T, int> &b) -> bool
        {
            return a.first > b.first;
        };
 
        std::priority_queue<pair<T, int>, vector<pair<T, int>>, decltype(weight_comp)> filter(weight_comp);

        FOR_EACH(i, 0, res.size())
        {
            filter.push(make_pair(res[i], i));
        }

        while (!filter.empty())
        {
            pair<T, int> p = filter.top();

            for(auto &node : this->adjcency_table[p.second])
            {
                if (visited[node] == 0)
                {
                    T sum = res[p.second] + this->weight[p.second][node];
                    if (sum < res[node])
                    {
                        res[node] = sum;
                    }   
                }   
            }

            res[p.second] = p.first;
            visited[p.second] = 1;
            filter.pop();
        }
        
        return res;
    }

};

}
#endif