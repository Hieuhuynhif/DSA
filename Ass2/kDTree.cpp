#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// ---------- kDtree method-----------------------------

kDTree::kDTree(int k)
{
    this->k = k;
    this->root = nullptr;
}

//
kDTreeNode *deepCopy(const kDTreeNode *node)
{
    if (node == nullptr)
        return nullptr;

    kDTreeNode *newNode = new kDTreeNode(node->data);
    newNode->left = deepCopy(node->left);
    newNode->right = deepCopy(node->right);
    return newNode;
}
void destroyTree(kDTreeNode *node)
{
    if (node != nullptr)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
kDTree::~kDTree()
{
    destroyTree(root);
}

//
kDTree::kDTree(const kDTree &other)
{
    root = deepCopy(other.root);
}

//
kDTree const &kDTree::operator=(const kDTree &other)
{
    if (this != &other)
    {
        destroyTree(root);

        root = deepCopy(other.root);
    }
    return *this;
}

//
void inorderHelper(kDTreeNode *root)
{
    if (root == nullptr)
        return;
    // First on left
    inorderHelper(root->left);
    // Now print
    cout << "(";
    for (unsigned int i = 0; i < root->data.size(); ++i)
    {
        cout << root->data[i];

        if (i != root->data.size() - 1)
            cout << ", ";
    }
    cout << ") ";

    // then on right
    inorderHelper(root->right);
}
void kDTree::inorderTraversal() const
{
    inorderHelper(root);
}

//
void preorderHelper(kDTreeNode *root)
{

    if (root == nullptr)
        return;

    // Now print
    cout << "(";
    for (unsigned int i = 0; i < root->data.size(); ++i)
    {
        cout << root->data[i];

        if (i != root->data.size() - 1)
            cout << ", ";
    }
    cout << ") ";

    // First on left
    preorderHelper(root->left);
    // then on right
    preorderHelper(root->right);
}
void kDTree::preorderTraversal() const
{
    preorderHelper(root);
}

//
void postorderHelper(kDTreeNode *root)
{
    if (root == nullptr)
        return;

    // First on left
    postorderHelper(root->left);
    // then on right
    postorderHelper(root->right);
    // Now print
    cout << "(";
    for (unsigned int i = 0; i < root->data.size(); ++i)
    {
        cout << root->data[i];

        if (i != root->data.size() - 1)
            cout << ", ";
    }
    cout << ") ";
}
void kDTree::postorderTraversal() const
{
    postorderHelper(root);
}

//
int getHeight(kDTreeNode *root)
{
    if (root == nullptr)
        return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + max(leftHeight, rightHeight);
}

int kDTree::height() const
{
    return getHeight(root);
}

//
int nodeCountHelper(kDTreeNode *root)
{
    if (root == nullptr)
        return 0;

    int leftCount = nodeCountHelper(root->left);
    int rightCount = nodeCountHelper(root->right);

    return 1 + leftCount + rightCount;
}
int kDTree::nodeCount() const
{
    return nodeCountHelper(root);
}

//
int leafCountHelper(kDTreeNode *root)
{
    if (root == nullptr)
        return 0;

    // If the current node is a leaf node, return 1
    if (root->left == nullptr && root->right == nullptr)
        return 1;

    // Recursively count leaf nodes in the left and right subtrees
    int leftCount = leafCountHelper(root->left);
    int rightCount = leafCountHelper(root->right);

    // Return the total number of leaf nodes in the tree
    return leftCount + rightCount;
}
int kDTree::leafCount() const
{
    return leafCountHelper(root);
}

//
kDTreeNode *insertHelper(kDTreeNode *root, const vector<int> &point, int depth, int k)
{
    if (root == nullptr)
    {
        return new kDTreeNode(point);
    }

    int index = depth % k;

    if (point[index] < root->data[index])
    {
        root->left = insertHelper(root->left, point, depth + 1, k);
    }
    else
    {
        root->right = insertHelper(root->right, point, depth + 1, k);
    }

    return root;
}
void kDTree::insert(const vector<int> &point)
{
    root = insertHelper(root, point, 0, k);
}

//
kDTreeNode *findMin(kDTreeNode *node, int dimension)
{
    if (node == nullptr)
        return nullptr;

    kDTreeNode *minNode = node;
    kDTreeNode *leftMin = findMin(node->left, dimension);
    kDTreeNode *rightMin = findMin(node->right, dimension);

    if (leftMin != nullptr && leftMin->data[dimension] < minNode->data[dimension])
    {
        minNode = leftMin;
    }

    if (rightMin != nullptr && rightMin->data[dimension] < minNode->data[dimension])
    {
        minNode = rightMin;
    }

    return minNode;
}
// Function to remove a point from the KD-tree
kDTreeNode *removeHelper(kDTreeNode *node, const vector<int> &point, int depth, int k)
{
    if (node == nullptr)
        return nullptr;

    int dim = depth % k;

    if (node->data == point)
    {
        if (node->right != nullptr)
        {
            kDTreeNode *minNode = findMin(node->right, dim);
            node->data = minNode->data;
            node->right = removeHelper(node->right, minNode->data, depth + 1, k);
        }
        else if (node->left != nullptr)
        {
            kDTreeNode *minNode = findMin(node->left, dim);
            node->data = minNode->data;
            node->right = node->left;
            node->left = nullptr;
            node->right = removeHelper(node->right, minNode->data, depth + 1, k);
        }
        else
        {
            delete node;
            return nullptr;
        }
    }
    else if (point[dim] < node->data[dim])
    {
        node->left = removeHelper(node->left, point, depth + 1, k);
    }
    else
    {
        node->right = removeHelper(node->right, point, depth + 1, k);
    }

    return node;
}
void kDTree::remove(const vector<int> &point)
{
    this->root = removeHelper(root, point, 0, k);
}

//
bool searchHelper(kDTreeNode *node, const vector<int> &point, int depth, int k)
{
    if (node == nullptr)
        return false;

    if (node->data == point)
        return true;

    int dim = depth % k;
    if (point[dim] < node->data[dim])
        return searchHelper(node->left, point, depth + 1, k);
    else
        return searchHelper(node->right, point, depth + 1, k);
}
bool kDTree::search(const vector<int> &point)
{
    return searchHelper(root, point, 0, k);
}

//
// Merge sort
void merge(vector<vector<int>> &arr, int l, int m, int r, int axis)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<vector<int>> L(arr.begin() + l, arr.begin() + m + 1);
    vector<vector<int>> R(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i][axis] <= R[j][axis])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>> &arr, int l, int r, int axis)
{
    if (l >= r)
        return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m, axis);
    mergeSort(arr, m + 1, r, axis);
    merge(arr, l, m, r, axis);
}

// Helper function to build the KD-tree recursively
kDTreeNode *buildTreeHelper(vector<vector<int>> &pointList, int start, int end, int depth, int k)
{
    if (start > end)
        return nullptr;

    int axis = depth % k;

    int mid = (start + end) / 2;

    // Sort based on current axis using merge sort
    mergeSort(pointList, start, end, axis);

    kDTreeNode *node = new kDTreeNode(pointList[mid]);
    node->left = buildTreeHelper(pointList, start, mid - 1, depth + 1, k);
    node->right = buildTreeHelper(pointList, mid + 1, end, depth + 1, k);

    return node;
}
void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    vector<vector<int>> point = pointList;
    root = buildTreeHelper(point, 0, pointList.size() - 1, 0, k);
}

//

double distance(const vector<int> &p1, const vector<int> &p2)
{
    double dist = 0.0;
    for (size_t i = 0; i < p1.size(); ++i)
    {
        dist += pow(p1[i] - p2[i], 2);
    }
    return sqrt(dist);
}

double minDistToPlane(const vector<int> &target, kDTreeNode *node)
{
    double dist = 0.0;
    for (size_t i = 0; i < target.size(); ++i)
    {
        dist += pow(target[i] - node->data[i], 2);
    }
    return sqrt(dist);
}

void nearestNeighbourHelper(const vector<int> &target, kDTreeNode *current, kDTreeNode *&best, double &bestDist, int depth, int k)
{
    if (current == nullptr)
        return;

    double currentDist = distance(target, current->data);

    if (currentDist < bestDist)
    {
        best = current;
        bestDist = currentDist;
    }

    int dim = depth % k;

    if (target[dim] < current->data[dim])
    {
        nearestNeighbourHelper(target, current->left, best, bestDist, depth + 1, k);
        if (current->right != nullptr && minDistToPlane(target, current) <= bestDist)
        {
            nearestNeighbourHelper(target, current->right, best, bestDist, depth + 1, k);
        }
    }
    else
    {
        nearestNeighbourHelper(target, current->right, best, bestDist, depth + 1, k);
        if (current->left != nullptr && minDistToPlane(target, current) <= bestDist)
        {
            nearestNeighbourHelper(target, current->left, best, bestDist, depth + 1, k);
        }
    }
}
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best)
{
    double bestDist = 1e18;
    nearestNeighbourHelper(target, root, best, bestDist, 0, k);
}

//
int calculateDistance(const vector<int> &a, const vector<int> &b, int &k)
{
    int distance = 0;
    for (int i = 0; i < k; ++i)
    {
        int diff = a[i] - b[i];
        distance += diff * diff;
    }
    return distance;
}
void kNearestNeighbourHelper(const vector<int> &target, int k, vector<kDTreeNode *> &bestList, kDTreeNode *node, int depth, int &dimensions)
{
    if (node == nullptr)
        return;

    // Calculate distance between target and current node
    int distance = calculateDistance(target, node->data, dimensions);

    // Update bestList if necessary
    if (bestList.size() < k || distance < calculateDistance(target, bestList.back()->data, dimensions))
    {
        if (bestList.size() == k)
        {
            bestList.pop_back();
        }
        // Find the position to insert the new node in bestList to maintain sorted order
        auto it = bestList.begin();
        while (it != bestList.end() && calculateDistance(target, (*it)->data, dimensions) < distance)
        {
            ++it;
        }
        bestList.insert(it, node);
    }

    // Decide which subtree to explore first based on the dimension of the current node
    int dim = depth % k;
    if (target[dim] < node->data[dim])
    {
        kNearestNeighbourHelper(target, k, bestList, node->left, depth + 1, dimensions);
        if (node->right != nullptr && (bestList.size() < k || pow(target[dim] - node->data[dim], 2) <= calculateDistance(target, bestList.back()->data, dimensions)))
        {
            kNearestNeighbourHelper(target, k, bestList, node->right, depth + 1, dimensions);
        }
    }
    else
    {
        kNearestNeighbourHelper(target, k, bestList, node->right, depth + 1, dimensions);
        if (node->left != nullptr && (bestList.size() < k || pow(target[dim] - node->data[dim], 2) <= calculateDistance(target, bestList.back()->data, dimensions)))
        {
            kNearestNeighbourHelper(target, k, bestList, node->left, depth + 1, dimensions);
        }
    }
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    kNearestNeighbourHelper(target, k, bestList, root, 0, this->k);
}

// ---------- kNN method--------------------------------------------

kNN::kNN(int k)
{
    this->k = k;
}

//
void kNN::fit(Dataset &X_train, Dataset &y_train)
{

    kDTree *xTrainKDT = new kDTree(784);

    vector<vector<int>> xTrainVT;

    for (const auto &innerList : X_train.data)
    {
        vector<int> innerVector(innerList.begin(), innerList.end());
        xTrainVT.push_back(innerVector);
    }

    xTrainKDT->buildTree(xTrainVT);

    vector<vector<int>> yTrainVT;

    for (const auto &innerList : y_train.data)
    {
        vector<int> innerVector(innerList.begin(), innerList.end());
        yTrainVT.push_back(innerVector);
    }

    // defining
    this->xTrainKDT = xTrainKDT;
    this->xTrainVT = xTrainVT;
    this->yTrainVT = yTrainVT;
}

//
Dataset kNN::predict(Dataset &X_test)
{

    Dataset y_pred;
    vector<string> lb = {"label"};
    y_pred.columnName = lb;

    vector<vector<int>> vectorOfVectors;

    for (const auto &innerList : X_test.data)
    {
        vector<int> innerVector(innerList.begin(), innerList.end());
        vectorOfVectors.push_back(innerVector);
    }

    for (vector<int> vt : vectorOfVectors)
    {
        list<int> row;

        vector<kDTreeNode *> bestList;

        this->xTrainKDT->kNearestNeighbour(vt, k, bestList);

        vector<int> labels;

        for (const auto &node : bestList)
        {

            bool found = false;
            int index = -1;

            // Iterate through the vector of vectors
            for (int i = 0; i < xTrainVT.size(); ++i)
            {
                // Compare each inner vector with the target vector
                if (xTrainVT[i] == node->data)
                {
                    found = true;
                    index = i;
                    break;
                }
            }

            if (index != 0)
            {
                labels.push_back(index);
            }
        }

        for (int i = 0; i < labels.size(); ++i)
        {
            int num = labels[i];
            labels[i] = this->yTrainVT[num][0];
        }

        int element;
        int max = 0;

        for (int i = 0; i < labels.size(); i++)
        {
            int counter = 0;
            for (int j = i; j < labels.size(); j++)
            {
                if (labels[j] == labels[i])
                    counter++;
            }
            if (counter > max || (counter == max && labels[i] < element))
            {
                max = counter;
                element = labels[i];
            }
        }

        row.push_back(element);
        y_pred.data.push_back(row);
    }
    return y_pred;
}

//
double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{

    vector<vector<int>> y_testVT;

    for (const auto &innerList : y_test.data)
    {
        vector<int> innerVector(innerList.begin(), innerList.end());
        y_testVT.push_back(innerVector);
    }

    vector<vector<int>> y_predVT;

    for (const auto &innerList : y_pred.data)
    {
        vector<int> innerVector(innerList.begin(), innerList.end());
        y_predVT.push_back(innerVector);
    }

    int hit = 0;
    for (int i = 0; i < y_predVT.size(); ++i)
    {
        if (y_testVT[i][0] == y_predVT[i][0])
            hit++;
    }
    double accuracy = (hit * 1.0) / y_predVT.size();
    return accuracy;
}
//
