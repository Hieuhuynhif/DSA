#include "main.h"

struct fStringNode{
		string data;
		int fre;
		fStringNode *left, *right;
};
struct Customer{
	string name = "-1";
	int id		= -1;
	int result	= -1;
	int num		= -1;
	int kv		= -1;
	Customer *left, *right;
};

class Node
{
    public:
    Customer key;
    Node *left;
    Node *right;
    int height;
};
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
int max(int a, int b)
{
    return (a > b)? a : b;
}
Node* newNode(Customer key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
int getBalance(Node *N)
{
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}
Node* insert(Node *& node, Customer key)
{
    /* 1. Perform the normal BST insertion */
    if (node == nullptr)
        return(newNode(key));
 
    if (key.result < node->key.result)
        node->left = insert(node->left, key);
    else if (key.result >= node->key.result)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key.result < node->left->key.result)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key.result > node->right->key.result)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key.result > node->left->key.result)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key.result < node->right->key.result)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
Node * minValueNode(Node* &node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
Node* deleteNode(Node* &root, Customer key)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key.result < root->key.result )
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key.result > root->key.result )
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}


fStringNode* createHuffmanTree(fStringNode *&root,fStringNode ** arrayNode, int &size, int current)
{
	if(current == size-1)
	{
		return root;
	}
	else
	{
		fStringNode *head = new fStringNode();
		head->data = "#";
		head->fre = arrayNode[current]->fre + arrayNode[current+1]->fre;
		head->left = arrayNode[current];
		head->right = arrayNode[current + 1];
		arrayNode[current+1] = head;
		current++;
		fStringNode *temp;
		for(int i = current, index, in; i<size-1; i++)
		{
			index = i;
			for(int j = i+1; j<size; j++)
			{
				if(arrayNode[j]->fre < arrayNode[index]->fre)
				{
					index = j;
				}
			}
			if(index != i)
			{
				temp = arrayNode[i];
				arrayNode[i] = arrayNode[index];
				arrayNode[index] = temp;
			}
		}

		return createHuffmanTree(arrayNode[current], arrayNode, size, current);
	}
}

void pathStr(fStringNode *root, string str, string current, string &path)
{
	if(root == nullptr)
	{
		return;
	}
	if(root->data == str)
	{
		path = current;
	}
	else
	{
		pathStr(root->left, str, current+"0", path);
		pathStr(root->right, str, current+"1", path);
	}
}
void addSea(Customer *&seaList, Customer ctm)
{
	int hashtable = ctm.result%(MAXSIZE/2);
	if(seaList[hashtable].id == -1)
	{
		seaList[hashtable] = ctm;
	}
	else
	{
		int current = hashtable + 1;
		while (current != hashtable)
		{
			if(seaList[current].id == -1)
			{
				seaList[current] = ctm;
				break;
			}
			current++;
			if(current == MAXSIZE/2)
			{
				current = 0;
			}
		}	
	}
}
void updateSea(Customer *&seaList, string name)
{
	for(int i = 0; i<MAXSIZE/2; i++)
	{
		if(seaList[i].name == name)
		{
			seaList[i].num++;
		}
	}
}
void addMountain(Node *&mountainList, Customer ctm)
{
	mountainList =  insert(mountainList, ctm);
}

void replace(Customer * seaList, Node *&mountainList, int &result, queue<int> a)
{
	int OPT = result%3;
	if(OPT == 0)
	{
		if(result%2)
		{

		}
		else
		{

		}
	}
	else if(OPT == 1)
	{
		if(result%2)
		{

		}
		else
		{
			
		}
	}
	else
	{
		if(result%2)
		{

		}
		else
		{
			
		}
	}
}
void REG(string &token, Customer * seaList, Node *&mountainList, Customer * list, int &seaSize, int &mountainSize, queue<int> &queue)
{
	int count[150];
	int size = 0;
	int result;
	int id;
	for(int i = 0; i< 150; i++)
	{
		count[i] = 0;
	}
	for(int i = 0; i<token.length(); i++)
	{
		count[token[i]]++;
	}
	for(int i = 0; i<150; i++)
	{
		if(count[i] != 0)
		{
			size++;
		}
	}
	fStringNode * arrayNode[size];
	for(int i = 0, index = 0; i<150 ; i++)
	{
		if(count[i] != 0)
		{
			arrayNode[index] = new fStringNode();
			arrayNode[index]->data = i;
			arrayNode[index]->fre = count[i];
			index++;
		}
	}
	fStringNode *temp;
	for(int i = 0, index = 0; i<size-1; i++)
	{
		index = i;
		for(int j = i+1; j<size; j++)
		{
			if(arrayNode[j]->fre < arrayNode[index]->fre)
			{
				index = j;
			}
		}
		if(index != i)
		{
			temp = arrayNode[i];
			arrayNode[i] = arrayNode[index];
			arrayNode[index] = temp;
		}
	}

	fStringNode *root = new fStringNode();
	root = createHuffmanTree(root, arrayNode, size, 0);

	string binaryCode = "";
	string str;
	string path;
	for(int i = 0; i<token.length(); i++)
	{
		str = token[i];
		pathStr(root, str, "", path);
		binaryCode += path;
	}
	if(token.length() == 1)
	{
		binaryCode = "1";
	}
	else if(binaryCode.length() > 15)
	{
		binaryCode = binaryCode.substr(binaryCode.length()-15, 15);
	}
	result = 0;
	for(int i = 0; i<binaryCode.length(); i++)
	{
		if(binaryCode[i] == 48)
		{
			result = result*2 + 0;
		}
		else
		{
			result = result*2 + 1;
		}
	}

	bool check = false;
	for(int i= 0; i<MAXSIZE; i++)
	{
		if(list[i].name == token)
		{
			list[i].num++;
			updateSea(seaList, list[i].name);
			check = true;
			queue.push(list[i].id);
			break;
		}
	}

	if(!check)
	{
		if(seaSize+mountainSize < MAXSIZE)
		{
			id = result%MAXSIZE +1;
			if(list[id].id == -1)
			{
				list[id].name = token;
				list[id].id = id;
				list[id].result = result;
				list[id].num = 1;
			}
			else
			{
				int current = id + 1;
				while (current != id)
				{
					if(list[current].id == -1)
					{
						id = current;
						break;
					}
					current++;
					if(current > MAXSIZE)
					{
						current = 1;
					}
				}
				list[id].name = token;
				list[id].id = id;
				list[id].result = result;
				list[id].num = 1;
			}
			queue.push(list[id].id);
			Customer ctm;
			if(result % 2)
			{
				if(seaSize < MAXSIZE/2)
				{
					list[id].kv = 1;
					ctm = list[id];
					addSea(seaList, ctm);
					seaSize++;
				}
				else
				{
					list[id].kv = 2;
					ctm = list[id];
					addMountain(mountainList, ctm);
					mountainSize++;
					
				}

			}
			else
			{
				if(mountainSize < MAXSIZE/2)
				{
					list[id].kv = 2;
					ctm = list[id];
					addMountain(mountainList, ctm);
					mountainSize++;
				}
				else
				{
					list[id].kv = 1;
					ctm = list[id];
					addSea(seaList, ctm);
					seaSize++;
				}

			}
		}
		else
		{
			replace(seaList, mountainList, result, queue);
		}
	}

}

void CLE(string token, Customer * list, Customer * seaList, Node *& mountainList, int &seaSize, int &mountainSize, queue<int> &queue)
{
	int num = 0;
	int kv = -1;
	if(token[0] == 45 || token[0] == 48)
	{
		Customer temp;
		for(int i =0; i< MAXSIZE/2; i++)
		{
			seaList[i] = temp;
		}
		for(int i = 1; i<=MAXSIZE; i++)
		{
			if(list[i].kv == 1)
			{
				list[i] = temp;
			}
		}
		seaSize = 0;
	}
	else
	{
		for(int i = 0; i<token.length(); i++)
		{
			num = num*10 +(token[i]-48);
		}
		if(num > MAXSIZE)
		{
			Customer temp;
			for(int i = 1; i<=MAXSIZE; i++)
			{
				if(list[i].kv == 2)
				{
					mountainList = deleteNode(mountainList, list[i]);
					list[i] = temp;
				}
			}
			mountainSize = 0;
		}
		else
		{
			Customer temp;
			if(list[num].id != -1)
			{
				if(list[num].kv == 1)
				{
					list[num] = temp;
					for(int i = 0 ; i< MAXSIZE/2; i++)
					{
						if(seaList[i].id == num)
						{
							seaList[i] = temp;
							break;
						}
					}
					seaSize--;
				}
				else
				{
					mountainList = deleteNode(mountainList, list[num]);
					mountainSize--;
				}
			}
			else
			{
				return;
			}
		}
	}
	
}
void PrintHT(Customer * seaList, int &seaSize)
{
	if(seaSize !=0)
	{
		for(int i = 0; i<MAXSIZE/2; i++)
		{
			if(seaList[i].id != -1)
			{
				cout<<seaList[i].id<<"-"<<seaList[i].result<<"-"<<seaList[i].num<<endl;
			}
		}
	}
}
void PrintAVL(Node *& mountainList, int &mountainSize)
{
	if(mountainSize !=0)
	{
		cout<<mountainList->key.id<<"-"<<mountainList->key.result<<"-"<<mountainList->key.num<<endl;;
	}
}
void PrintMH()
{
cout<<"mh";
}

void simulate(string filename)
{
	Customer seaList[MAXSIZE/2];
	Node *mountainList = nullptr;
	Customer list[MAXSIZE+1];
	queue<int> queue;
	int seaSize = 0;
	int mountainSize = 0;
	string token;
	string method, strLine;
	ifstream MyReadFile(filename);

	while(getline(MyReadFile, strLine))
	{
		method = strLine.substr(0, strLine.find(" "));
		strLine.erase(0, strLine.find(' ')+1);
		token = strLine;
		if(method == "REG")
		{
			REG(token, seaList, mountainList, list, seaSize, mountainSize, queue);
		}
		else if(method == "CLE")
		{
			CLE(token, list, seaList, mountainList, seaSize, mountainSize, queue);
		}
		else if(method == "PrintHT")
		{
			PrintHT(seaList, seaSize);
		}
		else if(method == "PrintAVL")
		{
			PrintAVL(mountainList, mountainSize);
		}
		else if(method == "PrintMH")
		{
			PrintMH();
		}
	}

	cout<<"---"<<seaSize<<" "<<mountainSize<<" ";
	cout<<endl;

	return;
}
