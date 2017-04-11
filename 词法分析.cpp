#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<string>
using namespace std;

static int lineno = 0;

const string Reserverd[20] = {"if","then","else","end","repeat","until","read","write"};

string buffer[100];

bool lookupReserved(string s)
{
    for(int i = 0;i<8;i++)
    {
        if(s==Reserverd[i])
            return true;
    }
    return false;
}

bool isSymbol(string s)
{
    if(s=="<"||s==">"||s=="="||s==":="||s=="*"||s=="/"||s==";"||s=="("||s==")")
        return true;
    return false;
}
bool isNum(string s)
{
    for(int i = 0;i<s.size();i++)
    {
        if(isdigit(s[i]))
            ;
        else
            return false;
    }
    return true;
}
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
    bool incomment = false;
	int cur = 0;
    ofstream out("out.text",ios::app);
    out <<"*****************************************\nTINY Lexical Analazer Result:\n*****************************************\n";
	while(getline(fin,s))
	{
		int cur = processLine(buffer,s);
		for(int i = 0;i<cur;i++)
		{
            if(lookupReserved(buffer[i]))
            {
			    out<<lineno<<":     ";
                out<<"Reserved Words: ";
		        out<<buffer[i]<<'\n';
            }
            else if(isSymbol(buffer[i]))
            {
			    out<<lineno<<":     ";
			    out<<buffer[i]<<'\n';
            }
            else if(isNum(buffer[i]))
            {
			    out<<lineno<<":     ";
                out<<"NUM, val = "<<buffer[i]<<'\n';
            }
            else 
            {
			    out<<lineno<<":     ";
                out<<"ID, name = "<<buffer[i]<<'\n';
            }
		}
		lineno++;
	}
}


int main()
{
	ReadandWrite();
}
