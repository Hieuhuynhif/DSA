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
void addMountain(Customer *&mountainList, Customer ctm)
{

}

void replace()
{

}
void REG(string &token, Customer * seaList, Customer * mountainList, Customer * list, int &seaSize, int &mountainSize)
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

		}
	}

}

void CLE(string token, Customer * list, Customer * seaList, Customer * mountainList, int &seaSize, int &mountainSize)
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
			for(int i =0; i< MAXSIZE/2; i++)
			{
				mountainList[i] = temp;
			}
			for(int i = 1; i<=MAXSIZE; i++)
			{
				if(list[i].kv == 2)
				{
					list[i] = temp;
				}
			}
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

				}
			}
			else
			{
				return;
			}
		}
	}
	
}
void PrintHT(Customer * seaList)
{
	for(int i = 0; i<MAXSIZE/2; i++)
	{
		if(seaList[i].id != -1)
		{
			cout<<seaList[i].id<<"-"<<seaList[i].result<<"-"<<seaList[i].num<<endl;
		}
	}
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
	Customer mountainList[MAXSIZE/2];
	Customer list[MAXSIZE+1];
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
			REG(token, seaList, mountainList, list, seaSize, mountainSize);
		}
		else if(method == "CLE")
		{
			CLE(token, list, seaList, mountainList, seaSize, mountainSize);
		}
		else if(method == "PrintHT")
		{
			PrintHT(seaList);
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

	cout<<"---"<<seaSize<<" "<<mountainSize<<" ";
	cout<<endl;
	return;
}
