#include "main.h"

void REG()
{
	cout<<"reg";
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

	string method, strLine;
	ifstream MyReadFile(filename);
	while(getline(MyReadFile, strLine))
	{
		method = strLine.substr(0, strLine.find(" "));
		strLine.erase(0, strLine.find(' ')+1);
		if(method == "REG")
		{
			REG();
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
