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
	string temp;
	stringstream ss(s);
	while(ss>>temp)
	{
		cur++;
		buffer[cur++] = temp;
	}
    cout<<cur<<endl;
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
// inline void splitcolon(string s)
// {
//     if(s[s.size()-1]==";")
//     {
//         if(isNum(s))
//         {
//             out<<lineno<<":     ";
//             out<<"NUM, val = ";
//         }
//         if(isID(s))
//         {
//             out<<lineno<<":     ";
//             out<<"ID, name = ";
//         }
//         for(int i= 0;i<s.size()-1;i++)
//             out<<s[i];
//     }
//     out<<endl;
//     out<<s[i]<<endl;
// }
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
		int cur = processLine(buffer,s);
		for(int i = 0;i<cur;i++)
		{
            // if(i==cur-1)
            // {
            //     splitcolon(buffer[i]);
            // }
            flag = incomment(buffer[i]);
            if(buffer[i]==" "||buffer[i]=="\t"||buffer[i]=="\n")
                continue;
            if(!flag && lookupReserved(buffer[i]))
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
