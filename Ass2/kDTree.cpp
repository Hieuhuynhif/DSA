#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// ---------- kDtree method-----------------------------

kDTree::kDTree(int k)
{
    k = k;
    root = nullptr;
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
    { // Check for self-assignment
        // Clear existing tree
        destroyTree(root);

        // Perform deep copy
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
            cout << ",";
    }
    cout << ")";

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
            cout << ",";
    }
    cout << ")";

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
            cout << ",";
    }
    cout << ")";
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
    insertHelper(root, point, 0, k);
}

//
kDTreeNode *findMin(kDTreeNode *root, int index, int depth, int k)
{
    if (root == nullptr)
        return nullptr;

    index = depth % k;

    if (index == 0)
    {
        if (root->left == nullptr)
            return root;
        return findMin(root->left, index, depth + 1, k);
    }
    else
    {
        kDTreeNode *leftMin = findMin(root->left, index, depth + 1, k);
        kDTreeNode *rightMin = findMin(root->right, index, depth + 1, k);

        if (leftMin == nullptr)
            return rightMin;
        if (rightMin == nullptr)
            return leftMin;

        if (leftMin->data[index] < rightMin->data[index])
            return leftMin;
        return rightMin;
    }
}

// Function to remove a point from the KD-tree
kDTreeNode *removeHelper(kDTreeNode *root, const vector<int> &point, int depth, int k)
{
    if (root == nullptr)
        return nullptr;

    int index = depth % k;

    if (root->data == point)
    {
        if (root->right != nullptr)
        {
            kDTreeNode *successor = findMin(root->right, index, depth + 1, k);
            root->data = successor->data;
            root->right = removeHelper(root->right, successor->data, depth + 1, k);
        }
        else if (root->left != nullptr)
        {
            kDTreeNode *predecessor = findMin(root->left, index, depth + 1, k);
            root->data = predecessor->data;
            root->right = removeHelper(root->left, predecessor->data, depth + 1, k);
            root->left = nullptr;
        }
        else
        {
            delete root;
            return nullptr;
        }
    }
    else
    {
        if (point[index] < root->data[index])
            root->left = removeHelper(root->left, point, depth + 1, k);
        else
            root->right = removeHelper(root->right, point, depth + 1, k);
    }
    return root;
}
void kDTree::remove(const vector<int> &point)
{
    removeHelper(root, point, 0, k);
}

//
bool pointsEqual(const vector<int> &point1, const vector<int> &point2)
{
    if (point1.size() != point2.size())
        return false;
    for (size_t i = 0; i < point1.size(); ++i)
    {
        if (point1[i] != point2[i])
            return false;
    }
    return true;
}

// Function to search for a point in the KD-tree
bool searchHelper(kDTreeNode *root, const vector<int> &target)
{
    if (root == nullptr)
        return false;

    // If the current node's point matches the target point, return true
    if (pointsEqual(root->data, target))
        return true;

    int k = target.size();
    int dim = root->data.size();

    // Calculate the dimension to compare
    int depth = 0;
    while (depth < dim && root->data[depth % k] == target[depth % k])
    {
        ++depth;
    }

    // Decide whether to search left or right subtree based on the comparison
    if (depth == dim)
    {
        if (root->data.size() > dim)
        {
            return searchHelper(root->left, target);
        }
        return false;
    }
    if (target[depth % k] < root->data[depth % k])
    {
        return searchHelper(root->left, target);
    }
    else
    {
        return searchHelper(root->right, target);
    }
}
bool kDTree::search(const vector<int> &point)
{
    return searchHelper(root, point);
}

//
void merge(vector<vector<int>> &points, int start, int mid, int end, int index)
{
    vector<vector<int>> merged(end - start + 1);
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
        if (points[i][index] <= points[j][index])
        {
            merged[k++] = points[i++];
        }
        else
        {
            merged[k++] = points[j++];
        }
    }

    while (i <= mid)
    {
        merged[k++] = points[i++];
    }

    while (j <= end)
    {
        merged[k++] = points[j++];
    }

    for (int idx = start; idx <= end; ++idx)
    {
        points[idx] = merged[idx - start];
    }
}

// Helper function to perform merge sort recursively
void mergeSort(vector<vector<int>> &points, int start, int end, int index)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        mergeSort(points, start, mid, index);
        mergeSort(points, mid + 1, end, index);
        merge(points, start, mid, end, index);
    }
}

// Helper function to build the KD-tree recursively
kDTreeNode *buildTreeRecursive(vector<vector<int>> &points, int depth, int k)
{
    if (points.empty())
        return nullptr;

    int index = depth % k;

    // Sort points based on the current dimension using merge sort
    mergeSort(points, 0, points.size() - 1, index);

    // Find the median point
    int medianIndex = points.size() / 2;
    vector<int> medianPoint = points[medianIndex];

    // Create a new node with the median point
    kDTreeNode *newNode = new kDTreeNode(medianPoint);

    // Recursively build left and right subtrees
    vector<vector<int>> leftPoints(points.begin(), points.begin() + medianIndex);
    vector<vector<int>> rightPoints(points.begin() + medianIndex + 1, points.end());

    newNode->left = buildTreeRecursive(leftPoints, depth + 1, k);
    newNode->right = buildTreeRecursive(rightPoints, depth + 1, k);

    return newNode;
}
void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    vector<vector<int>> points = pointList;
    root = buildTreeRecursive(points, 0, k);
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

void nearestNeighbourHelper(const vector<int> &target, kDTreeNode *current, kDTreeNode *&best, double &bestDist)
{
    if (current == nullptr)
        return;

    double currentDist = distance(target, current->data);
    if (currentDist < bestDist)
    {
        best = current;
        bestDist = currentDist;
    }

    int axis = current->data.size() % target.size(); // Select axis based on dimension
    double axisDist = target[axis] - current->data[axis];

    kDTreeNode *nearChild = (axisDist < 0) ? current->left : current->right;
    kDTreeNode *farChild = (axisDist < 0) ? current->right : current->left;

    nearestNeighbourHelper(target, nearChild, best, bestDist);

    if (fabs(axisDist) < bestDist)
    {
        nearestNeighbourHelper(target, farChild, best, bestDist);
    }
}
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best)
{
    if (root == nullptr)
        return;

    const double MAX_DISTANCE = 1e18; // A large value to represent "infinity"
    double bestDist = MAX_DISTANCE;   // Initialize to a large value
    nearestNeighbourHelper(target, root, best, bestDist);
}

//
void insertIntoBestList(vector<kDTreeNode *> &bestList, kDTreeNode *node, const vector<int> &target, int k)
{
    double currentDist = distance(target, node->data);
    // If bestList is not full, simply add the node
    if (bestList.size() < k)
    {
        bestList.push_back(node);
        return;
    }
    // Find the farthest node in the list
    double farthestDist = distance(target, bestList.back()->data);

    // If the current node is closer than the farthest node in the list, replace it
    if (currentDist < farthestDist)
    {
        bestList.pop_back();
        bestList.push_back(node);
        // Maintain the sorted order by distance
        for (int i = bestList.size() - 1; i > 0; --i)
        {
            if (distance(target, bestList[i]->data) < distance(target, bestList[i - 1]->data))
            {
                swap(bestList[i], bestList[i - 1]);
            }
            else
            {
                break;
            }
        }
    }
}

void kNearestNeighbourHelper(const vector<int> &target, int k, kDTreeNode *current, vector<kDTreeNode *> &bestList)
{
    if (current == nullptr)
        return;

    // Insert current node into bestList if applicable
    insertIntoBestList(bestList, current, target, k);

    // Recurse into children based on axis
    int axis = current->data.size() % target.size(); // Select axis based on dimension

    double axisDist = target[axis] - current->data[axis];

    kDTreeNode *nearChild = (axisDist < 0) ? current->left : current->right;
    kDTreeNode *farChild = (axisDist < 0) ? current->right : current->left;

    kNearestNeighbourHelper(target, k, nearChild, bestList);

    if (fabs(axisDist) < distance(target, bestList.back()->data))
    {
        kNearestNeighbourHelper(target, k, farChild, bestList);
    }
}
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    kNearestNeighbourHelper(target, k, root, bestList);
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
