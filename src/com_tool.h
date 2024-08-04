#ifndef LEETCODE_ALGORITHM_LIB_H
#define LEETCODE_ALGORITHM_LIB_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;
/*
***********************************************
输  入:map[in]:数组下标为节点的值,map[i]表示节点i的所有邻接点;
      begin:开始点
      end:结束点
输  出:
返回值:返回路径最小时的所有可行的路径
说  明:先从开始点通过bfs安层进行遍历，得到逆向的图，再通过dfs遍历逆向的图，即可得到所有可行的路径,

1，给定图，求给定两点之间的最小路径
********************************************
*/

vector<vector<int>> minimal_path_with_special_two_vertex(vector<vector<int>> &map, int begin, int end);

/*
***********************************************
功  能:求a,b两个正整数的最大公约数Greatest Common Divisor
输  入:a[in];b[in]
输  出:
返回值:返回，a,b的最大公约数
说  明:a, b都大于0
********************************************
*/
long long gcd(long long a, long long b);


/*
分割字符串
*/
vector<string> str_split(string strs, string split_str);

/*
分割字符串
*/
vector<string> str_split(string strs, char split_chr);

// set 转换为 vector
template <class T>
vector<T> set_to_vector(set<T> &set1)
{
      vector<T> v1;
      for (auto v : set1 )
      {
            v1.push_back(v);
      }
      return v1;
}


#endif 