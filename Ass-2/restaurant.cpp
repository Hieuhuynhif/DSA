#include "main.h"

struct fStringNode{
		string data;
		int fre;
		fStringNode *left, *right;
};
struct Customer{
	int id = -1;
	int result = -1;
	int num = -1;
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
bool addSea(Customer *&seaList, int &result)
{
		int id = result%MAXSIZE + 1;
		int index = result%(MAXSIZE/2);
		if(seaList[index].id == -1)
		{
			seaList[index].id = id;
			seaList[index].result = result;
			seaList[index].num = id;
			return true;
		}
		else
		{
			int current = index + 1;
			while(current != index)
			{
				if(seaList[current].id == -1)
				{
					seaList[current].id = id;
					seaList[current].result = result;
					seaList[current].num = id;
					return true;
				}
				current++;
				if(current == MAXSIZE/2)
				{
					current = 0;
				}
			}
			return false;
		}
}
bool addMountain(int &result)
{
	int id = result%MAXSIZE + 1;

}
void REG(string &token, Customer * seaList, int &seaSize, int &mountainSize)
{
	int count[150];
	int size = 0;
	int result;
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

	if(result % 2)
	{
		if(!addSea(seaList, result))
		{
			if(!addMountain(result))
			{
				
			}
		}
	}
	else
	{
		if(!addMountain(result))
		{
			if(!addSea(seaList, result))
			{

			}
		}

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
	Customer seaList[MAXSIZE/2];
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
			REG(token, seaList, seaSize, mountainSize);
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
