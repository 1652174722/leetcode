#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__ 

#include <set>
#include <string>
using namespace std;

#define FOR_EACH(i, s, e) for(size_t (i) = (size_t)(s); (i) < (size_t)(e); (i)++)
#define R_FOR_EACH(i, s, e) for(size_t i = (size_t)(s); (i) > (size_t)(e); (i)--)

#define FOR_EACH_IT(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define R_FOR_EACH_IT(it, v) for(auto it = v.rcbegin(); it != v.rcend(); it++)

// 定义类比较器
class object
{
public:
    // keys
    int k1;
    string k2;

    // values
    int v1;
    string v2;

    static bool cmp1(object &a, object &b)
    {
        return a.k1 != b.k1 ? a.k1 < b.k1 : a.k2 < b.k2;
    }

    static bool cmp2(object &a, object &b)
    {
        return a.k1 != b.k1 ? a.k1 < b.k1 : a.k2 < b.k2;
    }

    /* define multiple different comparion funtions */
    /* ... */
};

template<class T> 
class class_obj_cmp1 {
public:
    bool operator ()(T a, T b)
    {
        // 升序排列
        return T::cmp1(a, b);
    }
};

template<class T> 
class class_obj_cmp2 {

    bool operator ()(T &a, T &b)
    {
        // 升序排列
        return T::cmp2(a, b);
    }
};

/* define multiple different comparion class */
/* ... */

// 定义函数比较器模板
template<class T>
bool func_obj_cmp1(T a, T b)
{
    return T::cmp1(a, b);
}

#endif