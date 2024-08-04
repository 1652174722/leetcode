#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
using namespace std;


namespace TOPO_SORT{
    
/**
 * @brief topological sort
 *
 * @param edges directed edge eg:pair.::irst->pair::second
 * @param split_chr split char
 * @return success:return sorted vector<int>;error: return null (vector<int>())
 */
vector<int> topological_sort(vector<pair<int, int>> edges);

}