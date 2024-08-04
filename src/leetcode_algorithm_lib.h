#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<algorithm>
#include<stack>
#include<random>
#include<string.h>
#include<unordered_map>
#include<sys/time.h>
#include<limits.h>
#include"com_tool.h"
using namespace std;


// #if 1
// #define  
// #else 
// #define  
// #endif

// #if 1
// #define PRINT_ERROR(D,RET) 
// #else 
// #define PRINT_ERROR(D,RET) 
// #endif


class Solution {
public:
/*
1606. 找到处理最多请求的服务器
你有 k 个服务器，编号为 0 到 k-1 ，它们可以同时处理多个请求组。每个服务器有无穷的计算能力但是 不能同时处理超过一个请求 。请求分配到服务器的规则如下：

第 i （序号从 0 开始）个请求到达。
如果所有服务器都已被占据，那么该请求被舍弃（完全不处理）。
如果第 (i % k) 个服务器空闲，那么对应服务器会处理该请求。
否则，将请求安排给下一个空闲的服务器（服务器构成一个环，必要的话可能从第 0 个服务器开始继续找下一个空闲的服务器）。比方说，如果第 i 个服务器在忙，那么会查看第 (i+1) 个服务器，第 (i+2) 个服务器等等。
给你一个 严格递增 的正整数数组 arrival ，表示第 i 个任务的到达时间，和另一个数组 load ，其中 load[i] 表示第 i 个请求的工作量（也就是服务器完成它所需要的时间）。你的任务是找到 最繁忙的服务器 。最繁忙定义为一个服务器处理的请求数是所有服务器里最多的。

请你返回包含所有 最繁忙服务器 序号的列表，你可以以任意顺序返回这个列表。f
*/



/*方案原理*/
//定义一个set容器存放闲置的服务器序号id
//定义一个优先队列priority_queue容器作为忙于处理的服务器以pair<int,int>为元素:第二个int表示服务器的序号id,第一个int表示当前服务器会一直持续处理的时间点
//
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> server_avaliables;
        for(int i = 0; i < k; i++){
            server_avaliables.insert(i);
        }
        
        priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int>>> busy_severs;
        vector<int> busy_nums(k);
        int max_nums = 0;
        vector<int> max_servers;
        for(unsigned int i =0 ;  i < busy_nums.size(); i++){
            busy_nums[i] = 0;
        }
        set<int>::iterator temp_iter;
        //第一个int表示剩余处理的时间,第二个int表示服务器的编号
        for(unsigned int i = 0; i < arrival.size(); i++){     
            while(!busy_severs.empty()){    
                pair<int,int> temp_pair = busy_severs.top();
                //
                if(temp_pair.first <=  arrival[i]){
                    busy_severs.pop();
                    server_avaliables.insert(temp_pair.second);
                }else{
                    break;
                } 
            }
            int temp_id = i % k;
            if(server_avaliables.size()){
                if(server_avaliables.end() != (temp_iter = server_avaliables.lower_bound(temp_id))){
                }else{
                    temp_iter = server_avaliables.begin();
                }
                pair<int,int> temp_pair;
                temp_pair.first = arrival[i] + load[i];
                //
                temp_pair.second = *temp_iter;
                server_avaliables.erase(temp_iter);
                busy_severs.push(temp_pair);
                busy_nums[temp_pair.second]++;
                if(busy_nums[temp_pair.second] > max_nums){
                    max_nums = busy_nums[temp_pair.second];
                }
            }
        }
        
        //
        if(max_nums == 0){
            return max_servers;
        }
        
        //
        for(unsigned int i =0 ;  i < busy_nums.size(); i++){
            //
            if(max_nums == busy_nums[i]){
                max_servers.push_back(i);
            }
        }
        return max_servers;
    }
    
    


    int busiestServers_test_1(){
        /*[1]*/
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(5);
        vector<int> v2;
        v2.push_back(5);
        v2.push_back(2);
        v2.push_back(3);
        v2.push_back(3);
        v2.push_back(3);
        int k = 3;
        vector<int> v3;
        v3 = busiestServers(k, v1, v2);
        
        for(unsigned int i = 0; i < v3.size(); i++){
            
        }
        return 0;
    }

    int busiestServers_test_2(){
        /*[1]*/
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        vector<int> v2;
        v2.push_back(1);
        v2.push_back(2);
        v2.push_back(1);
        v2.push_back(2);
        int k = 3;
        vector<int> v3;
        v3 = busiestServers(k, v1, v2);
        
        for(unsigned int i = 0; i < v3.size(); i++){
            
        }
        return 0;
    }

    int busiestServers_test_3(){
        /*[0,1,2]*/
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        vector<int> v2;
        v2.push_back(10);
        v2.push_back(12);
        v2.push_back(11);
        int k = 3;
        vector<int> v3;
        v3 = busiestServers(k, v1, v2);
        
        for(unsigned int i = 0; i < v3.size(); i++){
            
        }
        return 0;
    }

    int busiestServers_test_4(){
        /*[0,1,2]*/
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);
        v1.push_back(8);
        v1.push_back(9);
        v1.push_back(10);
        vector<int> v2;
        v2.push_back(5);
        v2.push_back(2);
        v2.push_back(10);
        v2.push_back(3);
        v2.push_back(1);
        v2.push_back(2);
        v2.push_back(2);
        int k = 3;
        vector<int> v3;
        v3 = busiestServers(k, v1, v2);
        
        for(unsigned int i = 0; i < v3.size(); i++){
            
        }
        return 0;
    }

    int busiestServers_test_5(){
        /*[0,1,2]*/
        vector<int> v1;
        v1.push_back(1);
        vector<int> v2;
        v2.push_back(1);
        int k = 1;
        vector<int> v3;
        v3 = busiestServers(k, v1, v2);
        
        for(unsigned int i = 0; i < v3.size(); i++){
            
        }
        return 0;
    }

};





class Solution1 {
public:
    class temp_pair_sort{
    public:
        bool operator()(const pair<int,int> &a, const pair<int, int> &b){
            return a.first < b.first;
        }
    };
/*
给定一个长度为偶数的整数数组 arr，只有对 arr 进行重组后可以满足 “对于每个 0 <= i < len(arr) / 2，都有 arr[2 * i + 1] = 2 * arr[2 * i]” 时，返回 true；否则，返回 false。
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/array-of-doubled-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
    bool canReorderDoubled(vector<int>& arr) {
        //定义两个s红黑树容器set，一个用来存放无重复的arr中的元素
        //一个用来存放重复的元素及个数
        set<pair<int, int>, temp_pair_sort> set1;
        set<pair<int, int>>::iterator iter;
        pair<int, int> temp_pair;
        int zero_nums = 0;
        int positive_nums = 0;
        int nagetive_nums = 0;
        for(unsigned int i = 0; i< arr.size(); i++){
            
            if(arr[i] != 0){
                temp_pair.first = arr[i];
                temp_pair.second = 1;
                if(set1.end() != (iter = set1.find(temp_pair))){
                    if(positive_nums > 0){
                        positive_nums++;
                    }else{
                        nagetive_nums++;
                    }
                    temp_pair.second = iter->second + 1;
                    set1.erase(iter);
                    set1.insert(temp_pair);
                }else{
                    set1.insert(temp_pair);
                }
            }else{
                zero_nums = 0;
            }
            
        }
        if(zero_nums % 2 != 0) return false;
        set<pair<int, int>>::iterator iter1;
        pair<int, int> pair1;
        
        if(set1.size() % 2 != 0 || positive_nums % 2 != 0 || nagetive_nums % 2 != 0) return false;

        while(set1.size()){
            
            iter = set1.begin();
            
            pair1.first = iter->first;
            pair1.second = iter->second;
            
            
            
            while(pair1.second){
                
                if(pair1.first > 0){
                    temp_pair.first = pair1.first * 2;
                }else if(temp_pair.first % 2 == 0){
                    temp_pair.first = pair1.first / 2;
                }else return false;
                
                if(set1.end() != (iter1 = set1.find(temp_pair))){
                    
                    temp_pair.second = iter1->second - 1;
                    set1.erase(iter1);
                    if(temp_pair.second){
                        set1.insert(temp_pair);
                    }
                }else{
                    
                    return false;
                }
                pair1.second--;
            }
            
            
            set1.erase(set1.begin());
        }
        return true;
    }
    int canReorderDoubled_test_1(){
        vector<int> v1;
        v1.emplace_back(4);
        v1.emplace_back(-2);
        v1.emplace_back(2);
        v1.emplace_back(-4);
        if(canReorderDoubled(v1)){
            
        }else{
            
        }
        return 0;
    } 

    int canReorderDoubled_test_2(){
        vector<int> v1;
        v1.emplace_back(2);
        v1.emplace_back(1);
        v1.emplace_back(2);
        v1.emplace_back(1);
        v1.emplace_back(1);
        v1.emplace_back(1);
        v1.emplace_back(2);
        v1.emplace_back(2);
        if(canReorderDoubled(v1)){
            
        }else{
            
        }
        return 0;
    } 

    int canReorderDoubled_test_3(){
        vector<int> v1;
        v1.emplace_back(3);
        v1.emplace_back(1);
        v1.emplace_back(3);
        v1.emplace_back(6);
        if(canReorderDoubled(v1)){
            
        }else{
            
        }
        return 0;
    } 

    int canReorderDoubled_test_4(){
        vector<int> v1;
        v1.emplace_back(2);
        v1.emplace_back(1);
        v1.emplace_back(2);
        v1.emplace_back(6);
        if(canReorderDoubled(v1)){
            
        }else{
            
        }
        return 0;
    } 
};



class Solution3 {
public:
    int func1(string &password){//只进行插入
        int nums1 = 0, nums2 = 0, nums3 = 0, sum_nums ;
        for(unsigned int i = 0; i < password.size(); i++){
            if(password[i] >= 'a' && password[i] <= 'z') nums1 = 1;
            if(password[i] >= 'A' && password[i] <= 'Z') nums2 = 1;
            if(password[i] >= '0' && password[i] <= '9') nums3 = 1;
        }
        sum_nums = nums1 + nums2 + nums3;
        if((3 - sum_nums) > (6 - (int)password.size())){
            return 3 - sum_nums;
        }else return 6 - password.size();
    }
    int func2(string &password){//只进行替换
        int repeat_counts = 0, c_counts = 0, nums1 = 0, nums2 = 0, nums3 = 0, sum_nums = 0;
        unsigned char c = 0;
        for(unsigned int i = 0; i < password.size(); i++){
            if( c == password[i]) 
                c_counts++;
            else {
                c = password[i];
                c_counts = 1;
            }
            if(c_counts == 3){
                c_counts = 0;
                repeat_counts++;
            }
            if(password[i] >= 'a' && password[i] <= 'z') nums1 = 1;
            if(password[i] >= 'A' && password[i] <= 'Z') nums2 = 1;
            if(password[i] >= '0' && password[i] <= '9') nums3 = 1;
        }
        sum_nums = nums1 + nums2 + nums3;
        if((repeat_counts + sum_nums) >= 3) return repeat_counts;
        else return repeat_counts + 3 - (repeat_counts + sum_nums);
    }
    int func3(string &password){//以删除为主，替换为辅
        int temp_array[50] = {0};//存放需要删除或者替换的位置
        int repeat_counts = 0, c_counts = 0, nums1 = 0, nums2 = 0, nums3 = 0, sum_nums = 0;
        unsigned char c = 0;
        int real_length = password.size();
        int j = 0;
        //将连续相同的字符最后一个字符的相同的次数记录下来
        for(unsigned int i = 0; i < password.size(); i++){
            if( c == password[i]) 
                c_counts++;
            else {
                
                if(c_counts >= 3){
                    temp_array[repeat_counts] = c_counts;
                    repeat_counts++;
                }
                c = password[i];
                c_counts = 1;
            }  
            if(password[i] >= 'a' && password[i] <= 'z') nums1 = 1;
            if(password[i] >= 'A' && password[i] <= 'Z') nums2 = 1;
            if(password[i] >= '0' && password[i] <= '9') nums3 = 1;
        }
        sum_nums = nums1 + nums2 + nums3;
        if(c_counts >= 3){
                temp_array[repeat_counts] = c_counts;
                repeat_counts++;
        }
        int shengyu = repeat_counts;
        
        //将连续重复按照下列的删除规律进行删除，直到将重复的删除完，或者删除到还剩20个
        while(shengyu > 0 && real_length > 20){
            j = 0;
            while(shengyu > 0 && real_length > 20 && j < repeat_counts){
                if(temp_array[j] < 3) shengyu--;
                if(temp_array[j] >= 3 && temp_array[j] % 3 == 0){
                    temp_array[j]--;
                    real_length--;
                }
                j++;
            }
            j = 0;
            while(shengyu > 0 && real_length > 20 && j < repeat_counts){
                if(temp_array[j] < 3) shengyu--;
                if(temp_array[j] >= 3 && temp_array[j] % 3 == 1){
                    if(real_length == 21){
                        temp_array[j] -= 1;
                        real_length -= 1;
                        break;
                    }else{
                        temp_array[j] -= 2;
                        real_length -= 2;
                    }
                }
                j++;
            }
            j = 0;
            while(shengyu > 0 && real_length > 20 && j < repeat_counts){
                if(temp_array[j] < 3) shengyu--;
                if(temp_array[j] >= 3 && temp_array[j] % 3 == 2){
                    if(real_length == 21){
                        temp_array[j] -= 1;
                        real_length -= 1;
                        break;
                    }else if(real_length == 22){
                        temp_array[j] -= 2;
                        real_length -= 2;
                        break;
                    }else{
                        temp_array[j] -= 3;
                        real_length -= 3;
                    }
                }
                j++;
            }
        }
        //查看还有多少需要替换的
        int shengyu_1 = 0;
        if(shengyu){
            shengyu_1 = 0;
            for(int i = 0; i < repeat_counts; i++){
                
                if(temp_array[i] >= 3){
                    shengyu_1 += temp_array[i] / 3;
                }
            }
        }
        if(real_length != 20){
            
            //说明连续出现3次及以上的所有字符已经被删除值低于3次
            if(sum_nums == 3){
                return password.size() - 20;
            }else{
                return password.size() - real_length + real_length - 20 + 3 - sum_nums;
            }
        }else{
            //说明还有连续出现3次及以上的字符
            
            
            
            if((sum_nums + shengyu_1) >= 3){
                return password.size() - real_length + shengyu_1;
            }else{
                return password.size() - real_length + shengyu_1 + 3 - (sum_nums + shengyu_1);
            }
        }
        return 0;
    }
    int strongPasswordChecker(string password) {
           //unsigned int length = password.size();
            if(password.size() < 6){
                return func1(password);
            }else if(password.size() >= 6 && password.size() <= 20){
                return func2(password);
            } else {
                return func3(password);
            }
    }

    int strongPasswordChecker_test() {
           // string password1="bbaaaaaaaaaaaaaaacccccc";
            //string password1 = "ABABABABABABABABABAB1";
            string password1 =  "FFFFFFFFFFFFFFF11111111111111111111AAA";
            
            return 0;
    }
};

//template<class int>
class Tree_Array{
    vector<int> a;
    vector<int> tree_a;
public:
    int lowbit(int i){
        return i & (~i + 1);
    }     
    int build(vector<int> &v1){
        a = v1;
        for(unsigned int i = 0; i < v1.size(); i++){
            int depth = lowbit(i + 1);
            int d = 1;
            int sum = v1[i];
            int j = i - 1;
            while(d < depth){
                sum += tree_a[j];
                d += lowbit(j + 1);
            }
            tree_a.push_back(sum);
        }
        return 0;
    }
    /*单点修改 将数组中的值更新为k*/
    int update(int index, int k){
        if(index < 0 || index >= (int)tree_a.size()) return -1;
        int d_value = k - a[index];
        a[index] = k;
        while(index < (int)tree_a.size()){
            tree_a[index] += d_value;
            index = lowbit(index + 1) + index;
        }
        return 0;
    }
    // int Printf(){
    //     for(unsigned int i = 0; i < tree_a.size(); i++){
    //         
    //     }
    //     
    // }
    /*单点修改 将数组指定位置的值加上k*/
    int add(int index, int k){
        if(index < 0 || index >= (int)tree_a.size()) return -1;
        while(index < (int)tree_a.size()){
            tree_a[index] += k;
            index = lowbit(index + 1) + index;
        }
        return 0;
    }
    /*区间查询 返回数组前（index+1）项和*/
    int sum_to_index(int index){
        int sum = 0;
        if(index < 0) return 0;
        if(index >= (int)tree_a.size()) index = (int)tree_a.size() - 1;
        while(index >= 0){
            sum += tree_a[index];
            index -= lowbit(index + 1);
        }
        return sum;
    }
    /*区间查询  返回区间[l,r]之间的和*/
    int sum(int l, int r){
        if(l == 0){
            return sum_to_index(r);
        }
        return sum_to_index(r) - sum_to_index(l - 1);
    }
    int test_1(){

        vector<int> v1;
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        v1.push_back(1);
        
        build(v1);
        
        
        
        
        
        update(3, 100);
        

        
        
        update(7, 100);
        
        return 0;
    }
};

/*
线段树，满足区间查询与区间修改

*/
#if 0
class Segment_Tree{
    class Segment_Tree_Node{
    public:
        int l, r;
        long long  value;
        long long  lazy;
        Segment_Tree_Node (int l1, int r1, long long lazy1 = 0) : l(l1), r(r1), lazy(lazy1){}
    };
    vector<*Segment_Tree_Node> tree_a;
    int size;
    public:
    long long build_dfs(int l, int r, vector<int> &v, vector<*Segment_Tree_Node> &tree_a, int pos){
        Segment_Tree_Node *node = new Segment_Tree_Node(l, r);
        if(l == r){
            node->value = v[l];   
        }else{
            node->value = build_dfs(l, (l + r) / 2;, v, tree_a,  pos * 2 + 1 ) + build_dfs((l + r) / 2 + 1, r, v, tree_a,  pos * 2 + 2);
        }
        tree_a[pos] = node;
        return node->value; 
    }
/*
***********************************************************
 *函数名:build
 *功   能:建树，利用dfs
 *输  入:     
 *输  出:
 *返回值： 成功，则返回0，失败返回响应错误码
 *说  明:		
 *************************************************************
 */
void build(vector<int> &v){
    size = 1;
    while(size < v.size()){
        size *= 2;
    }
    tree_a = vector<*Segment_Tree_Node>(size, NULL);
    build_dfs(0, v.size() - 1, v, tree_a, 0);
}
/*
***********************************************************
 *函数名:区间查询
 *功   能:
 *输  入:     
 *输  出:
 *返回值： 成功，则返回0，失败返回响应错误码
 *说  明:		
 *************************************************************
 */

    long long query_dfs(int l, int r, int pos){
       if(l <= tree_a[pos]->l && r >= tree_a[pos]->r) return tree_a[pos]->value;
       
    }
    long long query(int l, int r){
        return query_dfs(l, r, 0);
    }
    



};


#endif



class Solution_3 {
public:
    bool isValid(string code) {
        //得到去除第一个闭环标签中的TAG_CONTENT子字符串
        stack<string> strs;
        int n = code.size();
        int i = 0;
        while(i < n){
            if(code[i] == '<'){
                i++;
                if(i >= n) return false;
                if(code[i] == '/'){//表示为结束标签
                    i++;
                    int pos = code.find(">", i);    
                    if(pos == (int)string::npos) return false;
                    string sub = code.substr(i, pos - i);
                    if(sub.empty() || strs.empty() || strs.top() != sub) return false;
                    strs.pop();
                    i = pos + 1;
                    if(strs.empty() && i != n) return false;
                }else if(code[i] == '!'){
                    i++;
                    int pos = code.find("[CDATA[", i);
                    if(pos != i) return false;
                    i += 7;
                    pos = code.find("]]>", i); 
                    if(pos ==  (int)string::npos) return false;
                    string sub = code.substr(i, pos - i);
                    i = pos + 1;
                }else{
                    int pos = code.find(">", i);    
                    if(pos == (int)string::npos) return false;
                    string sub = code.substr(i, pos - i);
                    if(sub.empty() || 
                        !all_of(sub.begin(), sub.end(), [](unsigned char c){ return c >= 'A' && c <=  'Z';})) {
                            return false;
                        }
                    strs.push(sub);
                    i = pos + 1;
                }
            }else{
                if(strs.empty()){ return false;
                } 
                i++;
            }
        }
        if(!strs.empty()) return false;
        return true;
    }
    int test_1(){
        string str = "<DIV>This is the first line <![CDATA[<div>]]></DIV>";
        return 0;
    }
   
};





class Solution4 {
public:
/*
共有 n 名小伙伴一起做游戏。小伙伴们围成一圈，按 顺时针顺序 从 1 到 n 编号。确切地说，从第 i 名小伙伴顺时针移动一位会到达第 (i+1) 名小伙伴的位置，其中 1 <= i < n ，从第 n 名小伙伴顺时针移动一位会回到第 1 名小伙伴的位置。

游戏遵循如下规则：

从第 1 名小伙伴所在位置 开始 。
沿着顺时针方向数 k 名小伙伴，计数时需要 包含 起始时的那位小伙伴。逐个绕圈进行计数，一些小伙伴可能会被数过不止一次。
你数到的最后一名小伙伴需要离开圈子，并视作输掉游戏。
如果圈子中仍然有不止一名小伙伴，从刚刚输掉的小伙伴的 顺时针下一位 小伙伴 开始，回到步骤 2 继续执行。
否则，圈子中最后一名小伙伴赢得游戏。
给你参与游戏的小伙伴总数 n ，和一个整数 k ，返回游戏的获胜者。
*/
//解题思路：此题为约瑟夫环问题，
//采用递归，时间复杂度为O（n）
    int dfs(int n, int k, int i){
        if(i == 1){
            int ret = k % n;
            return ret == 0 ? n : ret; 
        }else{
            int ret = (dfs(n - 1, k , i  - 1) + k) % n;
            return ret == 0 ? n : ret; 
        };
    }
    int findTheWinner(int n, int k) {
        return dfs(n, k, n);
    }
};


// /*二项树*/
// template<class T>
// class BinomialTree{
//     public:
// };

// /*二项堆*/
// template<class T>
// class BinomialHeap{
//     public:
    

// };


// class Solution5 {
// public:
//     void dfs(int i, int j, int t_i, int t_j, int &min_step, int curr_step, vector<vector<int>>& forest, vector<vector<int>> &visited){  
//         if(curr_step < min_step){
//             int n = forest.size(); 
//             int m = forest[0].size();
//             if(i == t_i && j == t_j){
//                 if(curr_step < min_step){
//                     min_step = curr_step;
//                     forest[i][j] = 1;
//                 } 
//             }else if(i >= 0 && i < n && j >= 0 && j < m && forest[i][j] == 1 && visited[i][j] == 0){
//                 visited[i][j] = 1;
//                 dfs(i - 1, j, t_i, t_j, min_step, curr_step + 1, forest, visited);
//                 dfs(i + 1, j, t_i, t_j, min_step, curr_step + 1, forest, visited);
//                 dfs(i, j - 1, t_i, t_j, min_step, curr_step + 1, forest, visited);
//                 dfs(i, j + 1, t_i, t_j, min_step, curr_step + 1, forest, visited);
//                 visited[i][j] = 0;
//             }
//         }
//     }
//     int cutOffTree(vector<vector<int>>& forest) {
//         int min_step = INT_MAX;
//         if(forest.size() <= 0) return 0;
//         int n = forest.size();
//         int m = forest[0].size();
//         vector<vector<int>> vv;
//         vector<pair<int, int>> trees;
//         trees.push_back(make_pair(0, 0));
//         for(int i = 0; i < forest.size(); i++){
//             vv.push_back(vector<int>(forest[i].size(), 0));
//             for(int j = 0; j < forest[i].size(); j++){
//                 if((i != 0 || j != 0) && forest[i][j] > 1){
//                     //
//                     trees.push_back(make_pair(i, j));
//                 } 
//             }
//         }
        
        
//         if(trees.size() == 1) return 0;


//         sort(trees.begin(), trees.end(), [&](const pair<int, int> &a, const pair<int, int> &b){ 
//             return forest[a.first][a.second] < forest[b.first][b.second];
//             });
//         if(trees[0].first != 0 || trees[0].second != 0) {
//             
//             return -1;
//         }
//         int sum_step = 0;
//         forest[0][0] = 1;
//         for(int i = 1; i < trees.size(); i++){
//             min_step = INT_MAX;
//             
//             
//             dfs(trees[i - 1].first, trees[i - 1].second, trees[i].first, trees[i].second, min_step, 0, forest, vv);
//             //
//             if(min_step == INT_MAX) return -1;
            
//             sum_step += min_step;
//         }
//         return sum_step;
//     }
// };



#define DRAW 0
//该状态表示老鼠为必赢状态，猫为必输状态
#define M_WIN 1 
//该状态表示猫为必赢状态，老鼠为必输状态
#define C_WIN 2

#define MOUSE 0
#define CAT 1

class Solution6 {
public:
    struct STATUS{
        int m;
        int c;
        int t;
        int r;
        STATUS(int a, int b, int d, int r1){
            m = a;
            c = b;
            t = d;
            r = r1;
        }
    };
    int catMouseGame(vector<vector<int>>& graph) {
        //
        int n = graph.size();
        //每一个状态包括三个参数 老鼠的位置，猫的位置及轮到谁移动
        //定义一个三维数组，保存每一个状态的度 表示该状态下继续移动的话，还有多少种移动方法
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2)));//[mouse][cat][0/1].,0:moust, 1:cat
        //定义一个三维数组，保存每一个状态的结果
        vector<vector<vector<int>>> result(n, vector<vector<int>>(n, vector<int>(2)));
        queue<STATUS> q;
        //初始化下 每一个状态的度，i:为老鼠， j为猫，M为轮到老鼠， C为轮到猫
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                degree[i][j][MOUSE] =  graph[i].size();
                degree[i][j][CAT] =  graph[j].size();
            }
        }
        //
        //将猫移动下一次能够移动到0位置的状态的度减一
        for(int i = 0; i < n; i++){
            for(int j = 0; j < (int)graph[0].size(); j++){
                degree[i][graph[0][j]][CAT]--;
            }
        }
        //
        //将所有状态的结果都初始化而为平局状态
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                result[i][j][MOUSE] =  DRAW;
                result[i][j][CAT] =  DRAW;
            }
        }
        //
        //将老鼠的位置为0的状态都设置为  老鼠赢
        for(int i = 1; i < n; i++){
            result[0][i][MOUSE] =  M_WIN;
            result[0][i][CAT] =  M_WIN;
            STATUS s1(0,i,MOUSE, M_WIN), s2(0,i,CAT, M_WIN);
            q.push(s1);
            q.push(s2);
        }
        //
        //将所有老鼠的位置与猫的位置重合且都不为0的状态都设为猫赢
        for(int i = 1; i < n; i++){
            result[i][i][MOUSE] =  C_WIN;
            result[i][i][CAT] =  C_WIN;
            STATUS s1(i,i,MOUSE, C_WIN), s2(i,i,CAT, C_WIN);
            q.push(s1);
            q.push(s2);
        }
       // 
        while(!q.empty()){
            STATUS s = q.front();
            if(s.r == M_WIN){
                if(s.t == MOUSE){
                    
                    for(unsigned int i = 0; i < graph[s.c].size(); i++){
                        //
                        //
                        //
                        if(graph[s.c][i] != 0  && result[s.m][graph[s.c][i]][CAT] == DRAW){
                            if(degree[s.m][graph[s.c][i]][CAT] == 1){
                                degree[s.m][graph[s.c][i]][CAT] = 0;
                                result[s.m][graph[s.c][i]][CAT] = M_WIN;
                                STATUS s1(s.m, graph[s.c][i], CAT, M_WIN);
                                q.push(s1);
                            }else{
                                degree[s.m][graph[s.c][i]][CAT]--;
                            }
                        }
                    }
                }else{
                    //
                    for(unsigned int i = 0; i < graph[s.m].size(); i++){
                        if(graph[s.m][i] != 0 && result[graph[s.m][i]][s.c][MOUSE] == DRAW){
                            //
                            //
                            result[graph[s.m][i]][s.c][MOUSE] = M_WIN;
                            STATUS s1(graph[s.m][i], s.c, MOUSE, M_WIN);
                            q.push(s1);
                        }
                    }
                }
            }else{
                if(s.t == CAT){
                    for(unsigned int i = 0; i < graph[s.m].size(); i++){
                        //
                        if(graph[s.m][i] != 0  && result[graph[s.m][i]][s.c][MOUSE] == DRAW){
                            if(degree[graph[s.m][i]][s.c][MOUSE] == 1){
                                degree[graph[s.m][i]][s.c][MOUSE] = 0;
                                result[graph[s.m][i]][s.c][MOUSE] = C_WIN;
                                STATUS s1(graph[s.m][i], s.c, MOUSE, C_WIN);
                                q.push(s1);
                            }else{
                                degree[graph[s.m][i]][s.c][MOUSE]--;
                            }
                        }
                    }
                }else{
                    for(unsigned int i = 0; i < graph[s.c].size(); i++){
                        if(graph[s.c][i] != 0 && result[s.m][graph[s.c][i]][CAT] == DRAW){
                            result[s.m][graph[s.c][i]][CAT] = C_WIN;
                            STATUS s1(s.m, graph[s.c][i], CAT, C_WIN);
                            q.push(s1);
                        }
                    }
                }
            }
            q.pop();
        }
        return result[1][2][MOUSE];
    }
    int test_1(){
        vector<vector<int>> graph;
        //graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
        vector<int> v1(2);
        v1[0] = 2; 
        v1[1] = 5;
        vector<int> v2(1);
        v2[0] = 3; 
        vector<int> v3(3);
        v3[0] = 0;
        v3[1] = 4;
        v3[2] = 5;
        vector<int> v4(3);
        v4[0] = 1;
        v4[1] = 4;
        v4[2] = 5;
        vector<int> v5(2);
        v5[0] = 2;
        v5[1] = 3;
        vector<int> v6(3);
        v6[0] = 0;
        v6[1] = 2;
        v6[2] = 3;
        graph.push_back(v1);
        graph.push_back(v2);
        graph.push_back(v3);
        graph.push_back(v4);
        graph.push_back(v5);
        graph.push_back(v6);
        catMouseGame(graph);
        
        return 0;
    }
    int test_2(){
        vector<vector<int>> graph;
        //graph = [[1,3],[0],[3],[0,2]]
        vector<int> v1(2);
        v1[0] = 1; 
        v1[1] = 3;
        vector<int> v2(1);
        v2[0] = 0; 
        vector<int> v3(1);
        v3[0] = 3;
        vector<int> v4(2);
        v4[0] = 0;
        v4[1] = 2;
        
        graph.push_back(v1);
        graph.push_back(v2);
        graph.push_back(v3);
        graph.push_back(v4);
        catMouseGame(graph);
        
        return 0;
    }
    int test_3(){
        vector<vector<int>> graph;
        //graph = [[2,3],[3,4],[0,4],[0,1],[1,2]]
        vector<int> v1 = {2,3};
        vector<int> v2 = {3,4};
        vector<int> v3 = {0,4};
        vector<int> v4 = {0,1};
        vector<int> v5 = {1,2};
        
        graph.push_back(v1);
        graph.push_back(v2);
        graph.push_back(v3);
        graph.push_back(v4);
        graph.push_back(v5);
        catMouseGame(graph);
        
        return 0;
    }
};







class Solution9 {
public:
    int bfs(vector<int> &dp, int seq, vector<string> &stickers, string &target){
        if(dp[seq] != -1){
            return dp[seq];
        }else{
            int m = target.size();
            dp[seq] = m + 1;      
            for(int i = 0; i < (int)stickers.size(); i++){
                int left_seq = seq;
                int cnt[26] = {0};
                for(int j = 0; j < (int)stickers[i].size(); j++){
                    cnt[stickers[i][j] - 'a']++;
                }
                for(int k = 0; k < m; k++){
                    if((left_seq & 1 << k) && cnt[target[k] - 'a'] > 0){
                        cnt[target[k] - 'a']--;
                        left_seq ^= 1 << k;
                    }
                }
                if(left_seq < seq){
                    dp[seq] =  min(dp[seq], bfs(dp, left_seq, stickers, target) + 1);
                }
            }
            return dp[seq];
        }
    }
    int minStickers(vector<string>& stickers, string target) {
        int m = target.size();
        vector<int> dp(1 << m, -1);
        dp[0] = 0;
        int res = bfs(dp, (1 << m) - 1, stickers, target);
        
        return res > m ? -1 : res; 
    }
};

/*
该方法用于解决判断，是否一个只含有'('或')'的字符串是否属于合规的字符串
合规字符串
*/
class Solution10 {
public:
    
    int longestValidParentheses(string s) {
        //用来记录每一个位置的'('或')'是否有对应的')'或'('
        //如果有则对应位置的值为1，否则为0
        int l_counts = 0;//表示当前有效字符中'('的个数
        int r_counts = 0;//表示当前有效字符中')'的个数
        int i = 0;
        int max_len = 0;
        while(i < (int)s.size()){
            s[i] == '(' ? l_counts++ : r_counts++;
            if(l_counts == r_counts) max_len = max(max_len, l_counts + r_counts);
            else if(r_counts > l_counts){
                l_counts = 0;
                r_counts = 0;
            }
            i++;
        }  
        i = s.size() - 1;
        l_counts = 0;
        r_counts = 0;
        while(i >= 0){
            s[i] == ')' ? l_counts++ : r_counts++;
            if(l_counts == r_counts) max_len = max(max_len, l_counts + r_counts);
            else if(r_counts > l_counts){
                l_counts = 0;
                r_counts = 0;
            }
            i--;
        }
        return max_len;
    }
};


class Solution11 {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        //表示p中前i与s中的前j个字符是否完全匹配
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true; 
        //让s为空，求出p中所有前i个字符与空字符的匹配结果
        for(int i = 1; i <= n; i++){
            if(p[i - 1] == '*') dp[i][0] = dp[i - 1][0];                      
        }
        for(int i = 1; i <= n; i++){
            if(p[i - 1] == '?'){
                for(int j = 1; j <= m; j++){
                        dp[i][j] = dp[i - 1][j - 1];      
                        
                        
                }
            }else if(p[i - 1] == '*'){     
                for(int j = 1; j <= m; j++){
                        dp[i][j] = dp[i - 1][j] | dp[i][j - 1];   
                        
                        
                }
            }else{
                for(int j = 1; j <= m; j++){
                    if(p[i - 1] == s[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                    
                    
                }   
            } 
        }
        return dp[n][m];
    }
    int test_1(){
        string s = "abcabczzzde";
        string p = "*abc???de*";
        
        return 0;
    }
};




class Solution12 {
public:
    int getindex(char c){
        if(c >= 'a' && c <= 'z') return c - 'a';
        else return c - 'A' + 26;
    }
    string minWindow(string s, string t) {
        if(s.size() < t.size()) return "";
        //queue<int> qu;
        vector<int> records(52, 0), exist;
        vector<int> curr(52, 0);
        for(int i = 0; i < (int)t.size(); i++){
            records[getindex(t[i])]++;
        }
        exist = records;
        int n = t.size();
        int i = 0;
        int l, r;
        int m = s.size() - t.size();
        int min_len = s.size() + 1;
        int k, j;
        int index;
        while(i < (int)s.size()){
            index  = getindex(s[i]);
            if(records[index] > 0){
                records[index]--;
                n--;
            }
            curr[index]++;
            if(n == 0){
                l = 0; r = i;
                min_len = r - l  + 1;
                break;
            }
            i++;
        }
        
        if(n != 0) return "";
        k = 0;
        j = i;
        int pre_c;
        while(k <= m){
            index = getindex(s[k]);
            while(curr[index] > exist[index]){
                curr[index]--;
                k++;
                index = getindex(s[k]);
            }
            //说明当前的k与j符合条件的其中一个
            if(min_len > (j - k + 1)){
                min_len = (j - k + 1);
                l = k;;
            }
            
            
            pre_c = s[k];
            k++;          
            j++;
            while(j < (int)s.size() && s[j] != pre_c){
                index = getindex(s[j]);
                curr[index]++;
                j++;
            }
            
            
            if(j == (int)s.size()) break;
        }
        return s.substr(l, min_len);;
    }
    int test_1(){
        string s = "ADOBECODEBANC";
        string t = "ABC";
        
        return 0;
    }
};



/* 一，题目描述 
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。
*/

/* 二，题目来源 

leetcode 84. 柱状图中最大的矩形
*/


/*  解题思路，，
    1,依次1求出每一个元素左边小于其自身高度的最近的一个柱子位置，及右边小于其自身自高的最近的一个柱子的位置, 并分别保存
    2, 一次遍历步骤1中保存的数据，筛选出最大值

*/

/* 三，考察内容 */
/*
  通过通过单调栈（递增）来获取步骤1的结果
*/

/* 四，细节描述 */


class Solution13 {
public:
    int largestRectangleArea(vector<int>& heights) {
        //
        //两次遍历，维持一个单调栈（递增）
        //一次正序编列，得到每一个柱子左边低于自己高度最近的柱子的位置。
        //一次倒序遍历，得到每一个柱子右边不高于自己高度最近的柱子的位置。
        vector<int> l(heights.size(), -1), r(heights.size(), heights.size());
        stack<int> sta;
        int max_area = 0;
        int i= 0;
        
        while(i < (int)heights.size()){
            
            while(!sta.empty() && heights[sta.top()] >= heights[i]){
                //
                r[sta.top()] = i;
                sta.pop();
            }
            if(sta.empty()){
                l[i] = -1;
            }else{
                l[i] = sta.top();
            }
            sta.push(i);
            i++;
        }
        i = 0;
        while(i < (int)heights.size()){
            //
            max_area = max(max_area, (r[i] - l[i] - 1) * heights[i]);
            i++;
        }
        return max_area;
    }
};






/* 一，题目描述 
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
*/

/* 二，题目来源 

leetcode 85. 最大矩形
*/


/*  解题思路，，
    1， 按行遍历，求出每个元素 左边连续为1的个数（从自己开始）：这里可使用动态规划，将求出的数据保存
    2，将步骤1中求出的数据，按照列的方式划分，每一列的数据，可转化为《条形图，求最大面积的问题》
    3，步骤2中的《条形图，求最大面积的问题》可使用单调栈解决
    4，然后取出每一列中的最大值中的最大值。

*/

/* 三，考察内容 */
/*
  将复杂问题转为为单一问题的重复组合，
  找出解决单一问题的方案
*/

/* 四，细节描述 */

class Solution14 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        //求出每个元素(包括自己)左边连续一的个数
        int n = matrix.size();
        int m =matrix[0].size();
        int max_eara = 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        //求出先求出第一列元素左边连续的为1的个数
        for(int i = 0; i < n; i++){  
            //
            if(matrix[i][0] == '1'){
                
                dp[0][i] = 1;
            } 
            //
        }
        for(int i = 0; i < n; i++ ){
            for(int j = 1; j < m; j++){
                if(matrix[i][j] == '1'){
                    dp[j][i]  = dp[j - 1][i] + 1;
                }
                //
            }
        }
        
        //根据单调栈获取每个柱状图的最大面积
        //这里需要遍历dp中每一列，将每一列当作一个条状图，求每一列的最大面积
        for(int i = 0; i < m; i++){
            stack<int> sta;//需要位置一个单调栈（递增）
            //分别表示每一元素左边最近小于dp
            vector<int> l(n, -1), r(n, n);
            int j = 0;
            
            while(j < n){
                // if(i == 3){
                //     
                // }

                while(!sta.empty() && dp[i][sta.top()] >= dp[i][j]){
                    r[sta.top()] = j;
                    // if(i == 3){
                    //     
                    // }  
                    sta.pop();   
                }
                if(!sta.empty()){
                    l[j] = sta.top(); 
                }
                // if(i == 3){
                //     
                // } 
                sta.push(j);
                j++; 
            }
            
            for(int k = 0; k < n; k++){
                //
                max_eara = max(max_eara, (r[k] - l[k] - 1) * dp[i][k]);
            }
            
        }
        return max_eara;
    }
};








/* 一，题目描述 
给你一个字符串 s，找到 s 中最长的回文子串。
*/

/* 二，题目来源 

leetcode 5. 最长回文子串
*/


/*  解题思路，


方案一:利用动态规划
    dp[i][j]:表示 s中i到j的字串是否为回文子串
    状态转移方程：dp[i][j] = dp[i + 1][j - 1] & s[i] == s[j]


方案二:中心扩展法
    1，对最终回文字串为偶数及奇数两种情况分别讨论，
    //略
    我们知道，如果一个字符串是回文串，那么该字符串必是中心对称的。故我们可以选择一个中心，从它开始，向两边逐一判断字符是否相同，拓展回文串长度。
    由于回文串可以是奇回文串也可以是偶回文串，我们需要选择一个字符或者选择两个字符中间作为中心进行逐一判断。

方案二:manacher算法---（马拉车算法）
    1，对最终回文字串为偶数及奇数分别遍历，
    manacher算法是一种可以在O(N)时间复杂度下求字符串所有回文子串的算法，也是求最大回文子串最高效的算法。
    这种算法在进行遍历的时候，充分利用了回文串的特性，减少了许多不必要的计算，使得时间复杂度降低到了线性水平。
    该算法的难度在于理解，一旦理解后，代码是非常简单的。

*/

/* 三，考察内容

*/

/* 四，细节描述 */

class Solution15 {
public:
    // 求字符串中没有 
      

    //一，使用动态规划解决该问题
    string longestPalindrome_1(string s) {
        //dp[i][j]表示i与j之间的子字符串是否为回文字符串,默认情况下都不是回文串
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), true));
        vector<vector<bool>> records(s.size(), vector<bool>(s.size(), 1));
        int l = 0, r = 0;
        int tmp_max = 0;
        for(int i = (int)s.size() - 2; i  >= 0; i--){
            for(int j = i + 1; j < (int)s.size(); j++){
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
                if(dp[i][j]) records[i][j] = dp[i + 1][j - 1] + 2;
            }
        }
        for(int i = 0; i < (int)s.size(); i++){
            for(int j = i; j < (int)s.size(); j++){
                if(dp[i][j] && (j - i + 1) >tmp_max) {
                    tmp_max = j - i + 1;
                    l = i;
                    r = j;
                }
            }
        }
        return s.substr(l, r - l + 1);
    }


    //三，manacher算法，马拉车算法
    int get_radius(string &p, int c, int l){
        int n = p.size();
        int r = c * 2 - l;
        //
        while(l >= 0 &&  r < n && p[l] == p[r]){
            l--;
            r++;
        }
        return r - c - 1;
    }
    //使用马拉车算法
    string longestPalindrome_3(string s) {
        string str  = "#";
        int M1 = 0;
        int R = 0;
        int MAX_R = 0;
        int MAX_pos = 0;
        vector<int>  P(s.size() * 2 + 1, 1);
        for(unsigned int i  = 0;  i < s.size(); i++){
            str.push_back(s[i]);
            str.push_back('#');
        }
        for(int i = 0; i < (int)str.size(); i++){
                int l = i < R ? i - min(P[M1 * 2 - i], R - i) - 1 : i - 1;
                P[i] = get_radius(str, i, l);
                if(P[i] > MAX_R){
                    MAX_R = P[i];
                    MAX_pos = i;
                }
                if((P[i] + i) > R){
                    M1 = i;
                    R = P[i] + i;
                }
        }
        return s.substr((MAX_pos - MAX_R) / 2, MAX_R);
    }

    int test_1(){
        vector<vector<vector<vector<int>>>> dp(30, vector<vector<vector<int>>>(30, vector<vector<int>>(30, vector<int>(30, false))));
        //string s = "ccc";
        //string s = "cbbd";
        //string s = "xaabacxcabaaxcabaax";
        string s = "babadada";
        return 0;
    }
};






/* 买卖股票问题模板 */




/* 一，题目描述 
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

*/

/* 二，题目来源 

leetcode 5. 123. 买卖股票的最佳时机 股票买卖问题
*/


/*  解题思路，


方案一:利用动态规划
  dp[j][0]:表示第j次交易 买入后的状态利润;dp[j][1]:表示第j次交易卖出后的状态利润
    dp[j][0] = max(dp[j - 1][1] - prices[i], dp[j][0]);
    dp[j][1] = max(dp[j][0] + prices[i], dp[j][1]);
*/

/* 三，考察内容

*/

/* 四，细节描述 */

class Solution16 {
public:
    /*
    ***********************************************
    输  入:prices[in]:prices[i]表示第i天股票的价格
    输  出:
    返回值:返回最优策略下的利润
    说  明:没有次数限制
    ********************************************
    */
    int maxProfit_1(vector<int>& prices) {
        //dp[i][0]:表示第（i+1）次交易买入时，所能获取的利润，，每次交易包含一次买入，一次卖出，dp[i][1]:表示第（i+1）次交易卖出时时，所能获取的利润
        int buy = -prices[0];
        int sell = 0;
        for(int i = 0; i < (int)prices.size(); i++){
            buy = max(sell - prices[i], buy);
            sell = max(buy + prices[i], sell);
        }
        return sell;
    }
    /*
    ***********************************************
    输  入:prices[in]:prices[i]表示第i天股票的价格;k[in]:最大交易次数
    输  出:
    返回值:返回最优策略下的利润
    说  明:有交易次数限制
    ********************************************
    */
    int maxProfit_2(vector<int>& prices, int k) {
        vector<vector<int>> dp(k + 1, vector<int>(2, 0));
        //初始化 每一次买入的最小值
        for(int i = 0; i <= k; i++){
            dp[i][0] = INT_MIN;
            dp[i][1] = 0;
        }
        int max_profit = 0;
        for(int i = 0; i < (int)prices.size(); i++){
            for(int j = 1; j <= k; j++){
                dp[j][1] = max(dp[j][1], dp[j][0] + prices[i]);
                dp[j][0] = max(dp[j][0], dp[j - 1][1] - prices[i]);
                max_profit = max(max_profit, dp[j][1]);
            }
        }
        return max_profit;
    }
    /*
    ***********************************************
    输  入:prices[in]:prices[i]表示第i天股票的价格;k[in]:最大交易次数;fee[in]:每笔交易的手续费
    输  出:
    返回值:返回最优策略下的利润
    说  明:有交易次数限制
    ********************************************
    */
    int maxProfit_3(vector<int>& prices, int k, int fee) {
        vector<vector<int>> dp(k + 1, vector<int>(2, 0));
        //初始化 每一次买入的最小值
        for(int i = 0; i <= k; i++){
            dp[i][0] = INT_MIN;
            dp[i][1] = 0;
        }
        int max_profit = 0;
        for(int i = 0; i < (int)prices.size(); i++){
            for(int j = 1; j <= k; j++){
                dp[j][1] = max(dp[j][1], dp[j][0] + prices[i] - fee);
                dp[j][0] = max(dp[j][0], dp[j - 1][1] - prices[i]);
                max_profit = max(max_profit, dp[j][1]);
            }
        }
        return max_profit;
    }

    int test_1(){
        vector<int> prices;
        prices.push_back(1);
        prices.push_back(2);
        prices.push_back(3);
        prices.push_back(4);
        prices.push_back(5);
        prices.push_back(6);
        prices.push_back(7);
        prices.push_back(8);
        prices.push_back(9);
        prices.push_back(10);
        
        
        return 0;
    }

};




/* 
    最小生成树问题 

一，题目描述 
    最小生成树定义：
对于一个带权连通无向图G=(V,E)，生成树不同，每棵树的权（树中所有边上的权值和）也不同，设R为G的所有生成树的集合，若T为R中权值和最小的生成树，则T称为G的最小生成树（Minimum-Spanning-Tree，MST）

注：
1、最小生成树可能有多个，但边的权值之和总是唯一且最小的

2、最小生成树的边数=定点数-1，砍掉一条则不连通，增加一条则会出现回路

3、若一个连通图本身就是一颗树，则其最小生成树就是它本身

4、只有连通图才有生成树，非连通图只有生成森林

二，题目来源 

三, 解题思路，


方案一:普利姆算法(Prim)
    从某一个顶点（所以存在多个最小生成树）开始构建生成树，每次将代价最小的新顶点纳入生成树，直到所有顶点都纳入为止
类似贪心算法


方案二:克鲁斯卡尔算法(Kruskal)
    每次选择权值最小的边，使这条边的两头连通（原本已近连通则不选）直到所有结点都连通


四，考察内容


五，细节描述 

*/

class Solution17{
    public:

};








/* 
    最短路径问题 

一，题目描述 
1,求图中两指定节点的路径中边数最少的路径
2,求图中两指定节点之间的最小路径值(带权值)
3,求图中指定节点到其他所有节点的最小路径(带权值)
4,求图中所有节点之间的最小路径值(带权值)

二，题目来源 

三, 解题思路，
    第一题:先从开始点通过bfs按层进行遍历，得到逆向的图(记得剪枝)，再通过dfs遍历逆向的图，即可得到所有可行的路径
    第二题:使用 dfs 算法，得到所有的路径，找到最小的
    第三题:采用 Dijkstra(迪杰斯特拉算法，只能用于边权值为正的情况下)或者 Bellman-Ford算法(边权值正负都可以)或者SPFA算法(Bellman-ford的优化版,边权值正负都可以)
    第四题:采用 Floyd(弗洛伊德算法，边权值正负都可以)
    
    备注：上面五个题目，都只用于有向图，(对于无向图,可以转化为有向图)
四，考察内容

五，细节描述 

*/

class Solution18{
    public:
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
        返回值:返回边数最少时，所有可行的路径
        说  明:先从开始点通过bfs安层进行遍历，得到逆向的图，再通过dfs遍历逆向的图，即可得到所有可行的路径，第一题
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




    
};


/*
***********************************************
输  入:map[in]:数组下标为节点的值,map[i]表示节点i的所有邻接点;
      begin:开始点
      end:结束点
输  出:
返回值:返回路径最小时的所有可行的路径
说  明:

1，给定图，求给定两点之间的最小路径
********************************************
*/

class Solution19 {
public:
    bool ischayi(string &s1, string &s2){
        int dif = 0;
        for(int i = 0; i < (int)s1.size(); i++){
            if(s1[i] != s2[i]){
                if(dif == 0) dif++;
                else return false;
            }
        }
        if(dif == 1) return true;
        else return false;
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {  
        //从 beginWord开始建图 ，
        vector<vector<string>> res;
        vector<vector<int>> res1;
        vector<string> vv;
        vector<vector<int>> map;
        vv.push_back(beginWord);
        int end = -1;
        for(int i = 0; i < (int)wordList.size(); i++){
            if(beginWord != wordList[i]){
                vv.push_back(wordList[i]);
                if(endWord == wordList[i]){
                    end = vv.size() - 1;
                } 
            } 
        }
        if(end == -1) return res;
        map.resize(vv.size());
        //将字符串转化为下标， 这一步建图 完成
        for(int i = 0; i < (int)vv.size() - 1; i++){
            for(int j = i + 1; j < (int)vv.size(); j++){
                if(ischayi(vv[i], vv[j])){
                    map[i].push_back(j);
                    map[j].push_back(i);
                }
            }
        }
        //初始化
        // 调用求解问题子模块
        
        res1 = minimal_path_with_special_two_vertex(map, 0, end);    
        //将小标转化为 字符串
        res.resize(res1.size());
        for(int i = 0; i < (int)res1.size(); i++){
            for(int j = (int)res1[i].size() - 1; j >= 0; j--){
                res[i].push_back(vv[res1[i][j]]);
            }
        }
        return res;
    }
    int test_1(){
        vector<string> wordlist = {
"aaaaa","caaaa","cbaaa","daaaa","dbaaa","eaaaa","ebaaa","faaaa","fbaaa","gaaaa","gbaaa","haaaa","hbaaa","iaaaa","ibaaa","jaaaa","jbaaa","kaaaa","kbaaa","laaaa",
"lbaaa","maaaa","mbaaa","naaaa","nbaaa","oaaaa","obaaa","paaaa","pbaaa","bbaaa","bbcaa","bbcba","bbdaa","bbdba","bbeaa","bbeba","bbfaa","bbfba","bbgaa","bbgba",
"bbhaa","bbhba","bbiaa","bbiba","bbjaa","bbjba","bbkaa","bbkba","bblaa","bblba","bbmaa","bbmba","bbnaa","bbnba","bboaa","bboba","bbpaa","bbpba","bbbba","abbba",
"acbba","dbbba","dcbba","ebbba","ecbba","fbbba","fcbba","gbbba","gcbba","hbbba","hcbba","ibbba","icbba","jbbba","jcbba","kbbba","kcbba","lbbba","lcbba","mbbba",
"mcbba","nbbba","ncbba","obbba","ocbba","pbbba","pcbba","ccbba","ccaba","ccaca","ccdba","ccdca","cceba","cceca","ccfba","ccfca","ccgba","ccgca","cchba","cchca",
"cciba","ccica","ccjba","ccjca","cckba","cckca","cclba","cclca","ccmba","ccmca","ccnba","ccnca","ccoba","ccoca","ccpba","ccpca","cccca","accca","adcca","bccca",
"bdcca","eccca","edcca","fccca","fdcca","gccca","gdcca","hccca","hdcca","iccca","idcca","jccca","jdcca","kccca","kdcca","lccca","ldcca","mccca","mdcca","nccca",
"ndcca","occca","odcca","pccca","pdcca","ddcca","ddaca","ddada","ddbca","ddbda","ddeca","ddeda","ddfca","ddfda","ddgca","ddgda","ddhca","ddhda","ddica","ddida",
"ddjca","ddjda","ddkca","ddkda","ddlca","ddlda","ddmca","ddmda","ddnca","ddnda","ddoca","ddoda","ddpca","ddpda","dddda","addda","aedda","bddda","bedda","cddda",
"cedda","fddda","fedda","gddda","gedda","hddda","hedda","iddda","iedda","jddda","jedda","kddda","kedda","lddda","ledda","mddda","medda","nddda","nedda","oddda",
"oedda","pddda","pedda","eedda","eeada","eeaea","eebda","eebea","eecda","eecea","eefda","eefea","eegda","eegea","eehda","eehea","eeida","eeiea","eejda","eejea",
"eekda","eekea","eelda","eelea","eemda","eemea","eenda","eenea","eeoda","eeoea","eepda","eepea","eeeea","ggggg","agggg","ahggg","bgggg","bhggg","cgggg","chggg",
"dgggg","dhggg","egggg","ehggg","fgggg","fhggg","igggg","ihggg","jgggg","jhggg","kgggg","khggg","lgggg","lhggg","mgggg","mhggg","ngggg","nhggg","ogggg","ohggg",
"pgggg","phggg","hhggg","hhagg","hhahg","hhbgg","hhbhg","hhcgg","hhchg","hhdgg","hhdhg","hhegg","hhehg","hhfgg","hhfhg","hhigg","hhihg","hhjgg","hhjhg","hhkgg",
"hhkhg","hhlgg","hhlhg","hhmgg","hhmhg","hhngg","hhnhg","hhogg","hhohg","hhpgg","hhphg","hhhhg","ahhhg","aihhg","bhhhg","bihhg","chhhg","cihhg","dhhhg","dihhg",
"ehhhg","eihhg","fhhhg","fihhg","ghhhg","gihhg","jhhhg","jihhg","khhhg","kihhg","lhhhg","lihhg","mhhhg","mihhg","nhhhg","nihhg","ohhhg","oihhg","phhhg","pihhg",
"iihhg","iiahg","iiaig","iibhg","iibig","iichg","iicig","iidhg","iidig","iiehg","iieig","iifhg","iifig","iighg","iigig","iijhg","iijig","iikhg","iikig","iilhg",
"iilig","iimhg","iimig","iinhg","iinig","iiohg","iioig","iiphg","iipig","iiiig","aiiig","ajiig","biiig","bjiig","ciiig","cjiig","diiig","djiig","eiiig","ejiig",
"fiiig","fjiig","giiig","gjiig","hiiig","hjiig","kiiig","kjiig","liiig","ljiig","miiig","mjiig","niiig","njiig","oiiig","ojiig","piiig","pjiig","jjiig","jjaig",
"jjajg","jjbig","jjbjg","jjcig","jjcjg","jjdig","jjdjg","jjeig","jjejg","jjfig","jjfjg","jjgig","jjgjg","jjhig","jjhjg","jjkig","jjkjg","jjlig","jjljg","jjmig",
"jjmjg","jjnig","jjnjg","jjoig","jjojg","jjpig","jjpjg","jjjjg","ajjjg","akjjg","bjjjg","bkjjg","cjjjg","ckjjg","djjjg","dkjjg","ejjjg","ekjjg","fjjjg","fkjjg",
"gjjjg","gkjjg","hjjjg","hkjjg","ijjjg","ikjjg","ljjjg","lkjjg","mjjjg","mkjjg","njjjg","nkjjg","ojjjg","okjjg","pjjjg","pkjjg","kkjjg","kkajg","kkakg","kkbjg",
"kkbkg","kkcjg","kkckg","kkdjg","kkdkg","kkejg","kkekg","kkfjg","kkfkg","kkgjg","kkgkg","kkhjg","kkhkg","kkijg","kkikg","kkljg","kklkg","kkmjg","kkmkg","kknjg",
"kknkg","kkojg","kkokg","kkpjg","kkpkg","kkkkg","ggggx","gggxx","ggxxx","gxxxx","xxxxx","xxxxy","xxxyy","xxyyy","xyyyy","yyyyy","yyyyw","yyyww","yywww","ywwww",
"wwwww","wwvww","wvvww","vvvww","vvvwz","avvwz","aavwz","aaawz","aaaaz"};
        string begin = "aaaaa";
        string end = "ggggg";
        struct timeval start_t, end_t;
        vector<vector<string>> res;
        gettimeofday(&start_t, NULL);
        res = findLadders(begin, end, wordlist);

        gettimeofday(&end_t, NULL);

        
        return 0;
    }
    int test_2(){
        vector<string> wordlist = {"hot","dot","dog","lot","log","cog"};
        string begin = "hit";
        string end = "cog";
        struct timeval start_t, end_t;
        vector<vector<string>> res;
        gettimeofday(&start_t, NULL);
        res = findLadders(begin, end, wordlist);

        gettimeofday(&end_t, NULL);

        return 0;
    }
};




/***********************************************
输  入:
输  出:
返回值:
说  明:先从开始点通过bfs安层进行遍历，得到逆向的图，再通过dfs遍历逆向的图，即可得到所有可行的路径,

1，给定二叉树：序列化二叉树及反序列化二叉树（前序遍历）
********************************************
*/


class Solution20 {
public:

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void serialize_dfs(TreeNode* root, string &s){
        if(root){
            s += to_string(root->val) + ",";
            serialize_dfs(root->left, s);
            serialize_dfs(root->right, s);
        }else{      
            s += "N,";
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        serialize_dfs(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root = NULL;
        stack<pair<TreeNode*, int>> sta;
        long unsigned int pre = 0, pos = 0;
        //
        while(string::npos != (pos = data.find(",", pre))){
            pair<TreeNode*, int> p;
            p.first = NULL;
            p.second = 0;
            string s = data.substr(pre, pos - pre);
            
            pre = pos + 1;
            if(s != "N"){
                p.first = new TreeNode(atoi(s.c_str()));
                p.second = 0;
            }
            if(!root){
                root = p.first;
            }
            if(!sta.empty()){
                if(sta.top().second == 0){
                    sta.top().first->left = p.first;
                    sta.top().second = 1;
                }else{
                    sta.top().first->right = p.first;
                    sta.pop();
                }
            }
            if(p.first){
                sta.push(p);
            }
        }
        return root;
    }

    int test_1(){
        TreeNode *n1 = new TreeNode(1);
        TreeNode *n2 = new TreeNode(2);
        TreeNode *n3 = new TreeNode(3);
        TreeNode *n4 = new TreeNode(4);
        TreeNode *n5 = new TreeNode(5);
        n1->left = n2;
        n1->right = n3;
        n3->left = n4;
        n3->right = n5;
        string s = serialize(n1);
        
        deserialize(s);
        
        return 0;
    }
};







/***********************************************
输  入:
输  出:
返回值:
说  明:
编写一个方法，计算从 0 到 n (含 n) 中数字 m(m的范围为[1-9]) 出现的次数。
示例:
输入: 25
输出: 9
解释: (2, 12, 20, 21, 22, 23, 24, 25)(注意 22 应该算作两次)
提示：n <= 10^9
********************************************
*/


class Solution21 {
public:
    long long numberOfMsInRange(int n, int m) {
        long long sum = 0;
        long long  k = 10;
        long long k1 = 1;
        while(n / k1 != 0){
            int value = (n % k) / k1;
            if(value == m){
                sum += n / k * k1 + n % k1 + 1;
            }else if(value > m){
                sum += n / k * k1 + k1;
            }else{
                sum += (n / k - 1) * k1 + k1;
            }
            k *= 10;
            k1 *= 10;
        }
        return sum;
    }
};


class Solution100 {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        int s_t1, e_t1;
        int s_t2, e_t2;
        s_t1 = stoi(event1[0].substr(0, 2)) * 60 +  stoi(event1[0].substr(2, 2));
        e_t1 = stoi(event1[1].substr(0, 2)) * 60 +  stoi(event1[1].substr(2, 2));
        s_t2 = stoi(event2[0].substr(0, 2)) * 60 +  stoi(event2[0].substr(2, 2));
        e_t2 = stoi(event2[1].substr(0, 2)) * 60 +  stoi(event2[1].substr(2, 2));
        if (e_t1 < s_t2 || e_t2 < s_t1) return false;
        return true;
    }
};

/***********************************************
301. 删除无效的括号
*/
class Solution301 {
public:
    int isvalid(string s)
    {
        stack<char> st1;
        for (auto c : s)
        {
            if (c == ')' && !st1.empty() && st1.top() == '(')
            {
                st1.pop();
            }
            else if (c == '(')
            {
                st1.push('(');
            }
        }
        return st1.empty();
    }

    void isvalid_1(string &s, vector<size_t> &v1, set<string> &set1)
    {
        string temp_s;
        if (v1.size() == 0)
        {
            if (isvalid(s))
            {
                set1.insert(s);
            }
        }
        size_t i = 0;
        size_t j = 0;
        while (i < s.size())
        {
            if (i == v1[j])
            {
                j++;
                i++;
            }
            else
            {
                temp_s.push_back(s[i]);
                i++;
            }
        }
        if (isvalid(temp_s))
        {
            set1.insert(temp_s);
        }
    }
    void dfs(string s, vector<size_t> &v1, set<string> &set1, int l, int r, size_t pos)
    {
        if (l == 0 && r == 0)
        {
            isvalid_1(s, v1, set1);
            return;
        }
        
        if (pos >= s.length())
        {
            return;
        }
        
        dfs(s, v1, set1, l, r, pos + 1);
        if (s[pos] == '(' &&  l > 0)
        {
            v1.push_back(pos);
            dfs(s, v1, set1, l - 1, r, pos + 1);
            v1.pop_back();
        }
        else if(s[pos] == ')' && r > 0)
        {
            v1.push_back(pos);
            dfs(s, v1, set1, l, r - 1, pos + 1);
            v1.pop_back();
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        // 通过栈原理找出所有多余的'('与')'个数
        int l = 0;
        int r = 0;
        stack<char> st1;
        for (auto c : s)
        {
            if (c == '(' || c == ')')
            {
                if (st1.empty())
                {
                    st1.push(c);
                }
                else
                {
                    if (st1.top() == '(' && c == ')')
                    {
                        st1.pop();
                    }
                    else
                    {
                        st1.push(c);
                    }
                }
            } 
        }

        while (!st1.empty())
        {
            if (st1.top() == '(')
            {
                l++;
            }
            else
            {
                r++;
            }
            st1.pop();
        }
        // 深度优先遍历
        set<string> set1;
        vector<size_t> v1;
        dfs(s, v1, set1, l, r, 0);
        return set_to_vector(set1);
    }

    void test(){
        string s = "()())()";
        vector<string> res = removeInvalidParentheses(s);

        // s = "(a)())()";
        // res = removeInvalidParentheses(s);

        // s = "(a)())()";
        // res = removeInvalidParentheses(s);

        // s = ")(";
        // res = removeInvalidParentheses(s);
        cout << "hello world" << endl;
        for (auto s : res)
        {
            cout << s << endl;
        }
    }
};

