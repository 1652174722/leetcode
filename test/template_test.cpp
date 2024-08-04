#include <iostream>
#include <vector>
#include <algorithm>

#include "template.h"
#include "gtest/gtest.h"

TEST(template_test, cmp_test)
{
    size_t loops = 10;
    // sort test
#define VECTOR_CMP_TEST(v) \
    vector<object> v;\
    FOR_EACH(i, 0, loops)\
    {\
        object b;\
        b.k1 = 10 - i;\
        b.k2 = to_string(loops - i);\
        v.push_back(b);\
    }

    /* class type cmp test */ 
    VECTOR_CMP_TEST(v1);
    sort(v1.begin(), v1.end(), class_obj_cmp1<object>());
    FOR_EACH(i, 0, v1.size())
    {
        cout << "index:" << i << " value:" << v1[i].k1 << " " << v1[i].k2 << endl;\
    }
    
    /* func type cmp test */
    VECTOR_CMP_TEST(v2);
    sort(v2.begin(), v2.end(), func_obj_cmp1<object>);
    FOR_EACH(i, 0, v2.size())
    {
        cout << "index:" << i << " value:" << v2[i].k1 << " " << v2[i].k2 << endl;
    }

    FOR_EACH_IT(iter, v2)
    {
        cout << "value:" << iter->k1 << " " << iter->k2 << endl;
    }
    
    /* set cmp test */
    
#define SET_CMP_TEST(s) \
    FOR_EACH(i, 0, loops)\
    {\
        object b;\
        b.k1 = 10 - i;\
        b.k2 = to_string(loops - i);\
        s.insert(b);\
    }\
    FOR_EACH_IT(iter, s)\
    {\
        cout << "value:" << iter->k1 << " " << iter->k2 << endl;\
    }

    /* set class cmp test */
    set<object, class_obj_cmp1<object>> s1;
    SET_CMP_TEST(s1);

    /* set func cmp test */
    set<object, bool(*)(object, object)> s2(func_obj_cmp1);
    SET_CMP_TEST(s2);
}

