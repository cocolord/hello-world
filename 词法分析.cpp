#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<string>
using namespace std;

static int lineno = 1;

const string Reserverd[20] = {"if","then","else","end","repeat","until","read","write"};

//string buffer[100];

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
    if(s=="<"||s==">"||s=="="||s==":="||s=="*"||s=="/"||s==";"||s=="("||s==")"||s=="+"||s=="-")
        return true;
    return false;
}
bool isNum(string s)
{
    int i;
    for(i = 0;i<s.size();i++)
    {
        if(s[i]-'0'>=0 && s[i] - '0' <=9)
            ;
        else
            break;
    }
    if(i==s.size() && i!=0)
        return true; 
    else 
        return false;
}
int processLine(string buffer[],string s)
{
	int cur = 0;
	string temp = "";
	stringstream ss(s);
	while(ss>>temp)
	{
        if(!temp.empty() && temp[0]>=33 && temp[0]<=126)
        {
            buffer[cur] = temp;
            cur++;
        }
	}

	return cur;
}
bool incomment(string s)
{
    if(s=="{")
    {
        return true;
    }
    else if(s=="}")
    {
        return false;
    }
    return false;
}
bool isID(string s)
{
    if(s[0]>='a'&&s[0]<='z')
        return true;
    return false;
}
inline bool splitcolon(string s,ofstream &out,int lineno)
{
    int i ;
    if(s[s.size()-1] == ';')
    {
        
        if(s[s.size()-2]>='0' && s[s.size()-2]<='9')
        {
            out<<lineno<<":     NUM, val = ";
        }
        else if(isID(s))
        {
            out<<lineno<<":     ";
            out<<"ID, name = ";
        }
        for(i= 0;i<s.size()-1;i++)
            out<<s[i];
        out<<endl;
        out<<lineno<<"      ;"<<endl;
        return true;
    }
    return false;
}
void ReadandWrite()
{
    ifstream fin("test.tiny");  
    string s;
	int cur = 0;
    bool flag = false;
    ofstream out("out.text",ios::app);
    out <<"*****************************************\n    TINY Lexical Analazer Result:\n*****************************************\n";
	while(getline(fin,s))
	{
        string buffer[100];
		int cur = processLine(buffer,s);
        //out<<s<<' '<<cur<<endl;
		for(int i = 0;i<cur;i++)
		{
            //out<<"***test***"<<i<<buffer[i]<<endl;
            flag = incomment(buffer[i]);
            if(i==cur-1 && splitcolon(buffer[i],out,lineno))
            {
                continue;
            }
            else if(!flag && lookupReserved(buffer[i]))
            {
			    out<<lineno<<":     ";
                out<<"Reserved Words: ";
		        out<<buffer[i]<<'\n';
            }
            else if(!flag && isSymbol(buffer[i]))
            {
			    out<<lineno<<":     ";
			    out<<buffer[i]<<'\n';
            }
            else if(!flag && isNum(buffer[i]))
            {
			    out<<lineno<<":     ";
                out<<"NUM, val = "<<buffer[i]<<'\n';
            }
            else if(!flag && isID(buffer[i]))
            {
			    out<<lineno<<":     ";
                out<<"ID, name = "<<buffer[i]<<'\n';
            }
            else
                continue;
		}
		lineno++;
	}
}


int main()
{
	ReadandWrite();
}
