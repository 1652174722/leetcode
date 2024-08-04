#include "search_binary_tree.h"
#include "gtest/gtest.h"

using namespace SEARCH_BINARY_TREE;

TEST(search_binary_tree, get_closed_gt_test)
{
    TreeNode<double> a(4);
    TreeNode<double> b(2);
    TreeNode<double> c(5);
    TreeNode<double> d(1);
    TreeNode<double> e(3);
    TreeNode<double> f(4.5);
    TreeNode<double> g(6);
    TreeNode<double> h(2.5);
    TreeNode<double> i(3.5);
    TreeNode<double> j(2.1);
    TreeNode<double> k(3.6);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    c.left = &f;
    c.right = &g;

    e.left = &h;
    e.right = &i;

    h.left = &j;

    i.right = &k;

    TreeNode<double> *node = nullptr;
    node = get_closed_gt<double>(&a, 7);
    ASSERT_EQ(true, node == nullptr);

    node = get_closed_gt<double>(&a, 6);
    ASSERT_EQ(true, node == nullptr);

    node = get_closed_gt<double>(&a, 5.5);
    ASSERT_EQ(true, node != nullptr && node->val == 6);

    node = get_closed_gt<double>(&a, 4);
    ASSERT_EQ(true, node != nullptr && node->val == 4.5);

    node = get_closed_gt<double>(&a, 3.1);
    ASSERT_EQ(true, node != nullptr && node->val == 3.5);

    node = get_closed_gt<double>(&a, 2.6);
    ASSERT_EQ(true, node != nullptr && node->val == 3);

    node = get_closed_gt<double>(&a, 2);
    ASSERT_EQ(true, node != nullptr && node->val == 2.1);

    node = get_closed_gt<double>(&a, 1);
    ASSERT_EQ(true, node != nullptr && node->val == 2);

    node = get_closed_gt<double>(&a, 0.9);
    ASSERT_EQ(true, node != nullptr && node->val == 1);

    node = get_closed_gt<double>(&a, 0);
    ASSERT_EQ(true, node != nullptr && node->val == 1);
}

TEST(search_binary_tree, get_closed_lt_test)
{
    TreeNode<double> a(4);
    TreeNode<double> b(2);
    TreeNode<double> c(5);
    TreeNode<double> d(1);
    TreeNode<double> e(3);
    TreeNode<double> f(4.5);
    TreeNode<double> g(6);
    TreeNode<double> h(2.5);
    TreeNode<double> i(3.5);
    TreeNode<double> j(2.1);
    TreeNode<double> k(3.6);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    c.left = &f;
    c.right = &g;

    e.left = &h;
    e.right = &i;

    h.left = &j;

    i.right = &k;

    TreeNode<double> *node = nullptr;
    node = get_closed_lt<double>(&a, 7);
    ASSERT_EQ(true, node != nullptr && node->val == 6);

     node = get_closed_lt<double>(&a, 6.5);
    ASSERT_EQ(true, node != nullptr && node->val == 6);

    node = get_closed_lt<double>(&a, 6);
    ASSERT_EQ(true, node != nullptr && node->val == 5);

    node = get_closed_lt<double>(&a, 5.5);
    ASSERT_EQ(true, node != nullptr && node->val == 5);

    node = get_closed_lt<double>(&a, 4);
    ASSERT_EQ(true, node != nullptr && node->val == 3.6);

    node = get_closed_lt<double>(&a, 3.1);
    ASSERT_EQ(true, node != nullptr && node->val == 3);

    node = get_closed_lt<double>(&a, 2.6);
    ASSERT_EQ(true, node != nullptr && node->val == 2.5);

    node = get_closed_lt<double>(&a, 2);
    ASSERT_EQ(true, node != nullptr && node->val == 1);

    node = get_closed_lt<double>(&a, 1);
    ASSERT_EQ(true, node == nullptr);

    node = get_closed_lt<double>(&a, 0.9);
    ASSERT_EQ(true, node == nullptr);
}

TEST(search_binary_tree, get_eq_test)
{
    TreeNode<double> a(4);
    TreeNode<double> b(2);
    TreeNode<double> c(5);
    TreeNode<double> d(1);
    TreeNode<double> e(3);
    TreeNode<double> f(4.5);
    TreeNode<double> g(6);
    TreeNode<double> h(2.5);
    TreeNode<double> i(3.5);
    TreeNode<double> j(2.1);
    TreeNode<double> k(3.6);

    a.left = &b;
    a.right = &c;

    b.left = &d;
    b.right = &e;

    c.left = &f;
    c.right = &g;

    e.left = &h;
    e.right = &i;

    h.left = &j;

    i.right = &k;

    TreeNode<double> *node = nullptr;
    node = get_eq<double>(&a, 7);
    ASSERT_EQ(true, node == nullptr);

    node = get_eq<double>(&a, 8);
    ASSERT_EQ(true, node == nullptr);

    node = get_eq<double>(&a, 0);
    ASSERT_EQ(true, node == nullptr);

    node = get_eq<double>(&a, 6);
    ASSERT_EQ(true, node != nullptr && node->val == 6);

    node = get_eq<double>(&a, 5);
    ASSERT_EQ(true, node != nullptr && node->val == 5);

    node = get_eq<double>(&a, 4);
    ASSERT_EQ(true, node != nullptr && node->val == 4);

    node = get_eq<double>(&a, 1);
    ASSERT_EQ(true, node != nullptr && node->val == 1);

    node = get_eq<double>(&a, 2);
    ASSERT_EQ(true, node != nullptr && node->val == 2);

    node = get_eq<double>(&a, 2.5);
    ASSERT_EQ(true, node != nullptr && node->val == 2.5);

    node = get_eq<double>(&a, 2.1);
    ASSERT_EQ(true, node != nullptr && node->val == 2.1);

    node = get_eq<double>(&a, 3.5);
    ASSERT_EQ(true, node != nullptr && node->val == 3.5);

    node = get_eq<double>(&a, 3.6);
    ASSERT_EQ(true, node != nullptr && node->val == 3.6);
}


