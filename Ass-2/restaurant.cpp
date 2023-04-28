#include "main.h"

struct fchar{
	char c;
	int f;
};

void REG(string &token)
{
	fchar count[token.length()];
	int size = 0;
	bool check = false;
	int index;
	fchar temp;
	for(int i = 0; i<token.length(); i++)
	{
		check = false;
		for(int j = 0; j<size; j++)
		{
			if(token[i] == count[j].c)
			{
				count[j].f++;
				check = true;
				break;
			}
		}
		if(!check)
		{
			count[size].c = token[i];
			count[size].f = 1;
			size++;
		}
	}
	for(int i = 0; i< size-1; i++)
	{
		index = i;
		for(int j = i+1; j<size; j++)
		{
			if(count[j].f < count[index].f)
			{
				index = j;
			}
		}
		if(index != i)
		{
			temp = count[i];
			count[i] = count[index];
			count[index] = temp;
		}
	}
	for(int i = 0; i< size; i++)
	{
		cout<<count[i].c<<count[i].f<<" ";
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
			REG(token);
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
