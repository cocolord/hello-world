#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include<vector>
using namespace std;

Scanner :: Scanner()
{
	scanSuccess = true;
	charIndex = 0;
	str = "";
	commentFlag = true;
	sourseString = "";
	lineCount = 0;
}


Token Scanner :: getTokenIn(int tokenIndex)
{
	Token token;
	token.lineNo = lineCount;
	token.tokenString = "";
	token.tokenType = ENDFILE;
	if(tokenIndex<tokenList.size())
	{
		token = tokenList.at(tokenIndex++);
	}
	return token;
}

void Scanner :: getSourseStringFromFile(string path)
{
	ifstream fin(path.c_str());
	string temp;   
	sourseString = "";
	cout << "源代码内容如下：" << endl;
	while(getline(fin,temp))
	{
		sourseString += temp;
		sourseString += '\n';
		cout << temp << endl;
	}  
	fin.close();	
	charIndex = 0;
}

void Scanner :: deleteComments()
{
	ofstream fout_Sourse(SRC);
	int state = 1;
	char ch;
	while((state < 6) && '\0' != (ch = getNextChar()))
	{
		if(1 == state)
		{
			if('/' == ch)
				state = 2;
			else
			{
				state = 1;
				fout_Sourse<<ch;
			}
		}		
		else if(2 == state)
		{
			if('*' == ch)
			{
				state = 3;
				commentFlag = false;
			}	 
			else
			{
				state = 1;
				fout_Sourse<<"/"<<ch;
			}
		}		
		else if(3 == state)
		{
			if('*' == ch)
				state = 4;
			else
			{
				state = 3;
			}
		}		
		else if(4 == state)
		{
			if('*' == ch)
				state = 4;
			else if('/' == ch)
				state = 5;
			else
			{
				state = 3;
			}
		}		
		if(5 == state)//结束状态，处理
		{
			commentFlag = true;
			state = 1;
		}
	}
	if(!commentFlag)
	{
		cout<<"对不起，删除注释过程发生错误！"<<endl;
		scanSuccess = false;
	}
	fout_Sourse.close();
}

TokenType Scanner :: returnTokenType(string s)//返回Token的类型
{
	TokenType t = ERROR;
	for(int i = 1; i < 28; i++)
	{
		if(s == tokenTypeStr[i])
		{
			t = (TokenType)i;
			return t;
		}
	}
	if(2 == charType(s[s.length()-1]))
	{
		t = NUM;
	}
	else if(3 == charType(s[s.length()-1]))
	{
		t = ID;
	}
	return t;
}

DFAState Scanner :: charType(char c)//返回字符的类型，数字？字母？符号？
{
	if('\n' == c || '\r' == c || '\t' == c ||' ' == c)
		return START;
    else if(c >= '0' && c <= '9')
		return INNUM;
    else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return INID;
	else if(c == '<' || c == '>' || c == '=' || c == '!')
		return INDBSYM;
    else
		return DONE;
	
}

char Scanner :: getNextChar()
{
	if(charIndex<sourseString.length())
	{
		char ch =  sourseString[charIndex];
		charIndex++;
		if('\n'==ch)
			lineCount++;
		return ch;
	}
	else
		return '\0';
}

void Scanner :: backToLastChar()
{
	if(charIndex>0)
	{
		char ch =  sourseString[charIndex-1];
		charIndex--;
		if('\n'==ch)
			lineCount--;
	}
}

//参照树上56页格式
void Scanner :: printToken()
{
	ofstream fout_Token(TOKEN);
	ifstream fin(SRC);
	string temp;
	Token t ;
	int lineCount = 0;
	int index = 0;
	while(getline(fin,temp))
	{
		fout_Token << lineCount << ": " << temp << endl;
		while(index < tokenList.size())
		{
			t = tokenList.at(index);
			if(lineCount == t.lineNo)
			{
				fout_Token << "	" << lineCount << ": ";
				index++;
				int width = 10;
				if(t.tokenType>=1&&t.tokenType<=6)
				{
					fout_Token << "keyword：" << t.tokenString << endl;
				}
				else if(t.tokenType>=7&&t.tokenType<=27)
				{
					fout_Token << t.tokenString << endl;
				}
				else if(t.tokenType==28)
				{
					fout_Token << "NUM" << ", val= " << t.tokenString << endl;
				}
				else if(t.tokenType==29)
				{
					fout_Token << "ID" << ", name= " << t.tokenString << endl;
				}
				else if(t.tokenType==30)
				{
					fout_Token << "error：" << t.tokenString << endl;
				}
				else if(t.tokenType==ENDFILE)
				{
					fout_Token << lineCount << ": " << t.tokenString << endl;
				}
			}			
			if(lineCount<t.lineNo)
			break;
		}
		lineCount++;
	}
	fout_Token << lineCount << ": EOF" << endl;
	fin.close();
	fout_Token.close();
}
void Scanner :: startScanner()
{
	cout<<"词法分析——开始！"<<endl;
	bool doubleSym = false;	
	int state = START;
	lineCount = 0;
	getSourseStringFromFile(SRC);

	char ch;
	while(state<6)
	{
		ch = getNextChar();
		if('\0'==ch)
		{
			Token t;
			t.lineNo = lineCount;
			t.tokenString = "";
			t.tokenType = ENDFILE;
			tokenList.push_back(t);
			break;
		}

		if(START == state)
		{
			state = charType(ch);
			if(state!=START)
				str += ch;
		}
		else if(INNUM == state)
		{
			state = charType(ch);
			if(state!=INNUM)
				state = DONE;
			else
				str += ch;
		}		
		else if(INID == state)
		{
			state = charType(ch);
			if(state != INID)
				state = DONE;
			else
				str += ch;
		}		
		else if(INDBSYM == state)
		{
			if('=' == ch)
			{	
				str += ch;
				doubleSym = true;
			}
			else
				doubleSym = false;
			state = DONE;
		}
		if(DONE == state)
		{
			int tp = 0;
			if('\n' == ch)
				tp = 1;
			Token t;
			t.lineNo = lineCount-tp;
			t.tokenString = str;
			t.tokenType = returnTokenType(str);
			tokenList.push_back(t);
			if(ERROR == t.tokenType)
				scanSuccess = false;			
			int lastState = charType(str[str.length()-1]);
			if(lastState == INNUM || lastState == INID || (lastState == INDBSYM && doubleSym == false))
				backToLastChar();
			str = "";
			state = START;
			if(doubleSym == true)
				doubleSym = false;
		}
     }

	if(scanSuccess)
		cout<<"词法分析——结束！"<<endl;
	else
		cout<<"词法分析——错误！"<<endl;
	printToken();
}
