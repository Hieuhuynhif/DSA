#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

//
// ---------- kDtree method-----------------------------
kDTree::kDTree(int k)
{
    k = k;
    root = nullptr;
}
//
kDTree::~kDTree()
{
}
//
kDTree const &kDTree::operator=(const kDTree &other)
{
}
//
void kDTree::inorderTraversal() const
{
}
//
void kDTree::preorderTraversal() const
{
}
//
void kDTree::postorderTraversal() const
{
}
//
int kDTree::height() const
{
}
//
int kDTree::nodeCount() const
{
}
//
int kDTree::leafCount() const
{
}
//
void kDTree::insert(const vector<int> &point)
{
}
//
void kDTree::remove(const vector<int> &point)
{
}
//
bool kDTree::search(const vector<int> &point)
{
}
//
void kDTree::buildTree(const vector<vector<int>> &pointList)
{
}
//
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best)
{
}
//
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
}
//
// ---------- kNN method--------------------------------------------

kNN::kNN(int k)
{
}
//
void kNN::fit(Dataset &X_train, Dataset &y_train)
{
}
//
Dataset kNN::predict(Dataset &X_test)
{
}
//
double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
}
//
