#include"leetcode_algorithm_lib.h"
using namespace std;

int set_bound_test()
{
    set<int> s1;
    s1.insert(1);
    s1.insert(5);
    // s1.insert(3);
    // s1.insert(3);
    set<int>:: iterator upper, lower;
    upper = s1.upper_bound(3); // 获取 没有排在3 前面的 第一个元素
    lower = s1.lower_bound(3); // 获取排在3 后面的第一个元素  
    cout << *upper << "  " << *lower << endl;

    upper = upper_bound(s1.begin(), s1.end(), 3); // 获取 没有排在3 前面的 第一个元素 less(默认)，，不带也行
    lower = lower_bound(s1.begin(), s1.end(), 3); // 获取排在3 后面的第一个元素  
    cout << __LINE__ << " "<< *upper << "  " << *lower << endl;

    upper = upper_bound(s1.begin(), s1.end(), 3, less<int>()); // 获取 没有排在3 前面的 第一个元素 less(默认)，，不带也行
    lower = lower_bound(s1.begin(), s1.end(), 3, less<int>()); // 获取排在3 后面的第一个元素   
    cout << __LINE__ << " "<< *upper << "  " << *lower << endl;


    // sort(s1.begin(), s1.end(), greater<int>());
    upper = upper_bound(s1.begin(), s1.end(), 3, greater<int>());// 获取 没有排在3 后面的 第一个元素
    lower = lower_bound(s1.begin(), s1.end(), 3, greater<int>());// 获取排在3 前面的第一个元素
    if (s1.end() == upper)
    {
        cout << __LINE__ << " " << "upper is end" << endl;
    }
    if (s1.end() == lower)
    {
        cout << __LINE__ << " " << "lower is end" << endl;
    }
    cout << __LINE__ << " " << *upper << "  " << *lower << endl;


    upper = upper_bound(s1.begin(), s1.end(), 5, greater<int>());// 获取 排在3 前面的 第一个元素
    lower = lower_bound(s1.begin(), s1.end(), 5, greater<int>());// 获取没有排在3 后面的第一个元素
    if (s1.end() == upper)
    {
        cout << __LINE__ << " " << "upper is end" << endl;
    }
    if (s1.end() == lower)
    {
        cout << __LINE__ << " " << "lower is end" << endl;
    }
    cout << __LINE__ << " " << *upper << "  " << *lower << endl;
    return 0;
}

int vector_bound_test()
{

    vector<int> s1 = {1, 3, 5, 7, 9};


    cout << s1.end() - s1.begin() << "  " << s1.size() << endl; 

    cout << max(1, (int)(s1.end() - s1.begin())) << endl;
    
    vector<int>::iterator upper, lower;
    upper = upper_bound(s1.begin(), s1.end(), 3, less<int>()); // 获取 没有排在3 前面的 第一个元素 less(默认)，，不带也行
    lower = lower_bound(s1.begin(), s1.end(), 3, less<int>()); // 获取排在3 后面的第一个元素   
    cout << __LINE__ << " "<< *upper << "  " << *lower << endl;


    // sort(s1.begin(), s1.end(), greater<int>());
    upper = upper_bound(s1.begin(), s1.end(), 3, greater<int>());// 获取 没有排在3 后面的 第一个元素
    lower = lower_bound(s1.begin(), s1.end(), 3, greater<int>());// 获取排在3 前面的第一个元素
    if (s1.end() == upper)
    {
        cout << __LINE__ << " " << "upper is end" << endl;
    }
    if (s1.end() == lower)
    {
        cout << __LINE__ << " " << "lower is end" << endl;
    }
    cout << __LINE__ << " " << *upper << "  " << *lower << endl;


    upper = upper_bound(s1.begin(), s1.end(), 5, greater<int>());// 获取 排在3 前面的 第一个元素
    lower = lower_bound(s1.begin(), s1.end(), 5, greater<int>());// 获取没有排在3 后面的第一个元素
    if (s1.end() == upper)
    {
        cout << __LINE__ << " " << "upper is end" << endl;
    }
    if (s1.end() == lower)
    {
        cout << __LINE__ << " " << "lower is end" << endl;
    }
    cout << __LINE__ << " " << *upper << "  " << *lower << endl;
    return 0;
}
