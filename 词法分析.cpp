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
        if(temp[0]=='{')
            break;
        if(!temp.empty() && temp[0]>=33 && temp[0]<=126)
        {
            buffer[cur] = temp;
            cur++;
        }

	}

	return cur;
}
bool isID(string s)
{
    if(s[0]>='a'&&s[0]<='z')
        return true;
    return false;
}
//s 是一行
inline bool splitcolon(string s,ofstream &out,int lineno)
{
    int i ;
    //
    string buffer[100];
    int cur = processLine(buffer,s);
    if(buffer[cur-1][1]==';')
    {
        out<<lineno<<":     ID, name = "<<buffer[cur-1][0]<<endl;
        out<<lineno<<"      ;"<<endl;
        return true;
    }
    //
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

//last one
//buffer 储存词素
//fin读文件对象，使用函数getline
//假设'}'存在一行末尾
//s 是一整行
//i 是当前指向的词，判断是否从该词开始注释
//注释'{''}'不会和别的任何字符挨着；

bool incomment(int &i,string s,ofstream &out,string buffer[],ifstream &fin)
{
    bool flag = false;
    if(buffer[i][0]!='{')   
        return false;
    else
    {
        if(s[s.size()-1]=='}')
            return true;
        else
        {
            string tmp;
            while(getline(fin,tmp))
            {     
                lineno++;
                if(tmp[tmp.size()-1]=='}')
                    return true;
            }
        }
    }
    return flag;
}

void ReadandWrite()
{
    ifstream fin("example.tiny");  
    string s;
	int cur = 0;
    bool flag = false;
    ofstream out("out.txt",ios::app);
    out <<"*****************************************\n    TINY Lexical Analazer Result:\n*****************************************\n";
	while(getline(fin,s))
	{
        string buffer[100];
		int cur = processLine(buffer,s);
		for(int i = 0;i<cur;i++)
		{
            //out<<"***test***"<<i<<buffer[i]<<endl;
            //如果是注释，推出再读一行
            if(incomment(i,s,out,buffer,fin))
                break;
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
    out<<"EOF"<<endl;
}


int main()
{
	ReadandWrite();
}
