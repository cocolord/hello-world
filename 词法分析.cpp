#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<string>
using namespace std;

static int lineno = 0;

const string Reserverd[20] = {"if","then","else","end","repeat","until","read","write"};

string buffer[100];

int processLine(string buffer[],string s)
{
	int cur = 0;
	string temp;
	stringstream ss(s);
	while(ss>>temp)
	{
		cur++;
		buffer[cur++] = temp;
	}
	return cur;
}

void ReadandWrite()
{
    ifstream fin("test.tiny");  
    string s;
	int cur = 0;
	while(getline(fin,s))
	{
		int cur = processLine(buffer,s);
		ofstream out("out.text",ios::app);
		for(int i = 0;i<cur;i++)
		{
			cout<<lineno;
			out<<buffer[i]<<'\n';
		}
		lineno++;
	}
}

//自动机
void getToken()
{

}

int main()
{
	ReadandWrite();
}
