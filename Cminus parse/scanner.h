#include<string>
#include<vector>
using namespace std;
//定义的Token的类型(31种)，分别对应于else、if、int、return、void、while、+、-、*、/、<、<=、>、>=、==、!=、=、;、,、(、)、[、]、{、}、/*、*/、num、id、错误、结束
typedef enum
{
	ELSE = 1,IF,INT,RETURN,VOID,WHILE,
	PLUS,MINUS,TIMES,OVER,LT,LEQ,GT,GEQ,EQ,NEQ,ASSIGN,SEMI,COMMA,LPAREN,RPAREN,LMBRACKET,RMBRACKET,LBBRACKET,RBBRACKET,LCOMMENT,RCOMMENT,
	NUM,ID,ERROR,ENDFILE
} TokenType;
typedef enum
{
	START = 1, INNUM, INID, INDBSYM, DONE
} DFAState;
//定义的Token结构体，包括类型、对应的串、所在代码的行号

struct Token
{
	TokenType tokenType;
	string tokenString;
	int lineNo;
}; 
//每种TokenType对应的串，如tokenTypeString[ELSE]=="ELSE"
const string tokenTypeString[32] = {"OTHER", "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE", "PLUS", "MINUS", "TIMES", "OVER", "LT", "LEQ", "GT", "GEQ", "EQ", "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LMBRACKET", "RMBRACKET", "LBBRACKET", "RBBRACKET", "LCOMMENT", "RCOMMENT", "NUM", "ID", "ERROR", "ENDFILE"};

const string tokenTypeStr[32] = {"OTHER", "else", "if", "int", "return", "void", "while", "+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!=", "=", ";", ",", "(", ")", "[", "]", "{", "}", "/*", "*/"};

const string SRC = "CMinus_SourceCode.txt";
const string TOKEN = "CMinus_Token.txt";

class Scanner
{
public:
	bool scanSuccess;//词法分析是否成功的标志
	void getSourseStringFromFile(string s);//通过提供的文件名获取源代码
	void deleteComments();//删除注释
	Scanner();
	Token getTokenIn(int);//根据下标从tokenList数组中获取Token
	void startScanner(void);//词法分析，将分析的Token放在tokenList数组中

private:
	DFAState charType(char);//返回字符的类型，如：空格2：数字3：字母等
	char getNextChar();//获取到下一个字符
	void backToLastChar();
	TokenType returnTokenType(string s);//根据字符串返回Token类型
	void printToken();//将词法分析好的Token输出到文件Token.txt中
	string sourseString;//获取源代码的字符串
	int charIndex;//配合getNextChar()，指定要取的字符位置
	string str;//在分析过程中保存Token对应的串
	bool commentFlag;//标注注释开始的标志
	int lineCount;//对行号计数，每次获取到'/n'就自增
	vector<Token> tokenList;//保存的Token序列
	
};
