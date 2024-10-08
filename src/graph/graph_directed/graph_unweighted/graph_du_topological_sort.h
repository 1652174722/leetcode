#ifndef _GRAPH_DU_TOPOLOGICAL_SORT_H
#define _GRAPH_DU_TOPOLOGICAL_SORT_H


#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
using namespace std;


namespace GRAPH_DU_TOPO_SORT {
    
/**
 * @brief topological sort
 *
 * @param edges directed edge eg:pair::first->pair::second
 * @param split_chr split char
 * @return success:return sorted vector<int>;error: return null (vector<int>())
 */
vector<int> graph_du_topological_sort(vector<pair<int, int>> edges);

}


#endif