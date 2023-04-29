#include "main.h"

struct fStringNode{
		string data;
		int fre;
		fStringNode *left, *right;
};

fStringNode* createHuffmanTree(fStringNode *&root,fStringNode *&newNode)
{
	fStringNode * head = new fStringNode();
	head->data = "#";
	head->fre = root->fre + newNode->fre;
	head->left = newNode;
	head->right = root;
	return head;
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
	string strTemp;
	int	numTemp;
	for(int i = 0, index = 0; i<size-1; i++)
	{
		index = i;
		for(int j = i+1; j<size; j++)
		{
			if(arrayNode[j]->fre < arrayNode[index]->fre)
			{
				strTemp = arrayNode[index]->data;
				numTemp = arrayNode[index]->fre;
				arrayNode[index]->data	= arrayNode[j]->data;
				arrayNode[index]->fre	=	arrayNode[j]->fre;
				arrayNode[j]->data = strTemp;
				arrayNode[j]->fre = numTemp;
			}
		}
	}
	
	fStringNode *root = new fStringNode();
	root->data = arrayNode[0]->data;
	root->fre = arrayNode[0]->fre;
	for(int i = 1; i<size; i++)
	{
		root = createHuffmanTree(root, arrayNode[i]);
	}
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
