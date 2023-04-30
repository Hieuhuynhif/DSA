#include "main.h"

struct fStringNode{
		string data;
		int fre;
		fStringNode *left, *right;
};

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

void REG(string &token, string &name, int &iD, int &maxSize, int &result)
{
	int count[150];
	int size = 0;
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
	cout<<binaryCode;
	
}

void CLE()
{
cout<<"cle";
}
void PrintHT()
{
cout<<"ht";
}
void PrintAVL()
{
cout<<"avl";
}
void PrintMH()
{
cout<<"mh";
}

void simulate(string filename)
{
	string name;
	int num;
	int iD;
	int maxSize;
	int result;
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
			REG(token, name, iD, maxSize, result);
		}
		else if(method == "CLE")
		{
			CLE();
		}
		else if(method == "PrintHT")
		{
			PrintHT();
		}
		else if(method == "PrintAVL")
		{
			PrintAVL();
		}
		else if(method == "PrintMH")
		{
			PrintMH();
		}
	}
	return;
}
