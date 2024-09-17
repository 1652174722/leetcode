#ifndef _GRAPH_DU_SHORTEST_PATH_H
#define _GRAPH_DU_SHORTEST_PATH_H

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


namespace GRAPH_DU_SHORTEST_PATH {

/**
 * @brief GRAPH_DU_SHORTEST_PATH:graph directed unweight shortest path
 * 有向图且无权重的常用属性求解
 * 两点之间的最短路径长度
 * 两点之间的所有最短路径
 * 使用场景
 *       可用于有向图与有向图，对于有向图：可理解两节点之间存在两条相互的边
 */

class  graph_du_shortest_path{
private:
    vector<vector<int>> edges;
    vector<vector<int>> adjcency_table;  // 存放所有出边的节点

    /**
     * @brief 获取有向图中两图中两节点(a,b)之间最短的路径的长度
     *        
     * @param 
     * @return 返回值范围[0, INT32_MAX],0表示两节点为同一节点；INT32_MAX表示两节点之间无法连接；其他值表示最短路径长度
     */   
    int get_shortest_path_length_between_two_nodes_bfs(vector<vector<int>> &adjcency_table, int curr_node, int target_node);

    /**
     * @brief 获取有向图中两图中两节点(a,b)之间最短的路径的长度
     *        
     * @param adjcency_table 节点邻接表
     * @param visited 是否访问标记，防止循环递归
     * @param visited 是否访问标记，防止循环递归
     * @param curr_depth 当前遍历的深度
     * @param min_depth 深度遍历的最大深度
     * @param curr_node 当前遍历的节点id
     * @param target_node 目标id
     * @param path 返回所有最短路径 path[i]为一个路径
     * @return 返回值范围[0, INT32_MAX],0表示两节点为同一节点；INT32_MAX表示两节点之间无法连接；其他值表示最短路径长度
     */
    void get_all_shortest_paths_between_two_nodes_dfs(vector<vector<int>> &adjcency_table,
        vector<int> &visited, vector<int> &path, size_t curr_depth, size_t min_depth, size_t curr_node, size_t target_node, 
        vector<vector<int>> &paths);

public:
    
    /**
     * @brief 无权重的有向图初始化
     *
     * @param edges edegs[i][j]为0 表示节点i到节点j没有边; 1表示节点i到j之间存在一条边
     * @return
     */
    void undirected_graph_init(vector<vector<int>> edges);

    /**
     * @brief 获取有向图中两图中两节点(a,b)之间最短的路径的长度
     *        
     * @param 
     * @return 返回值范围[0, INT32_MAX],0表示两节点为同一节点；INT32_MAX表示两节点之间无法连接；其他值表示最短路径长度
     */
    int get_shortest_path_length_between_two_nodes(int a, int b);

    /**
     * @brief 获取有向图中两图中两节点之间所有最短的路径
     *
     * @param
     * @return 所有最短连线的路径, 长度为0，表示两节点之间没有连接
     */
    vector<vector<int>> get_all_shortest_paths_between_two_nodes(int a, int b);
};

}

#endif