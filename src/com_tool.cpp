#include"com_tool.h"

/*

图中两点之间路径中 边最少问题
1，给定图，求给定两点之间路径中边的个数最少的所有路径
*/
static void minimal_path_with_special_two_vertex_dfs(vector<vector<int>> &map, int end, int curr, vector<int> &path, vector<vector<int>> &res){
        if(end == curr){
                res.push_back(path);
                res[res.size() -1].push_back(end);
                return ;
        }
        path.push_back(curr);
        for(int i = 0; i < (int)map[curr].size(); i++){
                minimal_path_with_special_two_vertex_dfs(map, end, map[curr][i], path, res);
        }
        path.pop_back();
}

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
vector<vector<int>> minimal_path_with_special_two_vertex(vector<vector<int>> &map, int begin, int end){
        vector<vector<int>> parent(map.size());    
        vector<int> steps(map.size(), -1);
        queue<int> que;
        stack<int> sta;
        vector<vector<int>> res;
        vector<int> path;
        int flag = 0;
        int step = 1;
        que.push(begin);
        steps[begin] = step++;
        while(!que.empty() && flag == 0){
                int i = 0;
                int n = que.size();
                while(i < n){
                        int curr = que.front();
                        que.pop();
                        for(int j = 0; j < (int)map[curr].size(); j++){
                                if(map[curr][j] == end) flag = 1;
                                if(steps[map[curr][j]] == -1){
                                        steps[map[curr][j]] = step;
                                        que.push(map[curr][j]);
                                }
                                if(steps[map[curr][j]] == step){
                                        parent[map[curr][j]].push_back(curr);
                                } 
                        }
                        i++;
                }
                step++;
        }

        /* 这里采用栈的方式，进行bfs遍历 */
        minimal_path_with_special_two_vertex_dfs(parent, begin, end, path, res); 
        return res;
}




/*
***********************************************
功  能:求a,b两个正整数的最大公约数Greatest Common Divisor
输  入:a[in];b[in]
输  出:
返回值:返回，a,b的最大公约数
说  明:a, b都大于0
********************************************
*/
long long gcd(long long a, long long b){
        return b != 0 ? gcd(b, a % b) : a;
}


/*
***********************************************
功  能:求一个正整数二进制位中1的个数
输  入:a[in];b[in]
输  出:
返回值:返回i中二进制位中1的个数
说  明:
********************************************
*/
int bit_count1(unsigned int i){
      int n = 0;
      while(i){
        i &= (i - 1);
        n++;
      }  
      return n;
}


/*
***********************************************
功  能:求一个正整数二进制位中1的个数
输  入:a[in];b[in]
输  出:
返回值:返回i中二进制位中1的个数
说  明:二分法
********************************************
*/
int bit_count2(unsigned int i){
        i = (i &0x55555555) + ((i >>1) &0x55555555) ; //n相邻位相加 0101 0101
        i = (i &0x33333333) + ((i >>2) &0x33333333) ; //n相邻（以2为单位）相加 0011 0011
        i = (i &0x0f0f0f0f) + ((i >>4) &0x0f0f0f0f) ; //n相邻（以4为单位）相加0000 1111
        i = (i &0x00ff00ff) + ((i >>8) &0x00ff00ff) ; //n相邻（以8为单位）相加1111 1111
        i = (i &0x0000ffff) + ((i >>16) &0x0000ffff) ;//n相邻（以16为单位）相加1111 1111 1111 1111
        return 1 ;
}

/*
***********************************************
功  能:求一个正整数二进制位中1的个数
输  入:a[in];b[in]
输  出:
返回值:返回i中二进制位中1的个数
说  明:查表法
********************************************
*/
int bit_count3(unsigned int i){
        unsigned int table[256] = { 
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, };
        unsigned char *p = (unsigned char*)&i;
        return table[p[0]] + table[p[1]] + table[p[2]] + table[p[3]];
}

/*
***********************************************
功  能:求一个正整数二进制位中1的个数
输  入:a[in];b[in]
输  出:
返回值:返回i中二进制位中1的个数
说  明:8进制
        举个例子：
        十进制数6（0110）= 4 * 1 + 2 * 1 + 0，这里a = 1, b = 1, c = 0, a + b + c = 2，所以6的二进制表示中有两个1。
        现在的问题是，如何得到a + b + c呢？注意位运算中，右移一位相当于除2，就利用这个性质！
        4a + 2b + c 右移一位等于2a + b ，4a + 2b + c 右移两位等于a，
        然后做减法 4a + 2b + c –(2a + b) – a = a + b + c，这就是第一行代码所作的事，明白了吧
********************************************
*/
int bit_count4(unsigned int i)
{
    unsigned int tmp = i - ((i >>1) &033333333333) - ((i >>2) &011111111111);
    return ((tmp + (tmp >>3)) &030707070707) %63;
}


/**
 * @brief split the strs by splite_chr
 *
 * @param strs strs
 * @param split_chr split str
 * @return string list
 */
vector<string> str_split(string &strs, string split_str)
{
    vector<string> v1;
    size_t pos;
    size_t pre_pos = 0;
    while (pre_pos < strs.length() && string::npos != (pos = strs.find(split_str, pre_pos)))
    {
        if (pos != pre_pos)
        {
            v1.push_back(strs.substr(pre_pos, pos - pre_pos));
        }
        pre_pos = pos + split_str.length();
    }

    if (pre_pos < strs.length())
    {
        v1.push_back(strs.substr(pre_pos, strs.length() - pre_pos));
    }
    return v1;
}

/**
 * @brief split the strs by splite_chr
 *
 * @param strs strs
 * @param split_chr split char
 * @return string list
 */
vector<string> str_split(string &strs, char split_chr)
{
    vector<string> v1;
    size_t pos;
    size_t pre_pos = 0;
    while (pre_pos < strs.length() && string::npos != (pos = strs.find(split_chr, pre_pos)))
    {
        if (pos != pre_pos)
        {
            v1.push_back(strs.substr(pre_pos, pos - pre_pos));
        }
        pre_pos = pos + 1;
    }

    if (pre_pos < strs.length())
    {
        v1.push_back(strs.substr(pre_pos, strs.length() - pre_pos));
    }
    return v1;
}


