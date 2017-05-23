#include<string>
#include<vector>
using namespace std;
//�����Token������(31��)���ֱ��Ӧ��else��if��int��return��void��while��+��-��*��/��<��<=��>��>=��==��!=��=��;��,��(��)��[��]��{��}��/*��*/��num��id�����󡢽���
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
//�����Token�ṹ�壬�������͡���Ӧ�Ĵ������ڴ�����к�

struct Token
{
	TokenType tokenType;
	string tokenString;
	int lineNo;
}; 
//ÿ��TokenType��Ӧ�Ĵ�����tokenTypeString[ELSE]=="ELSE"
const string tokenTypeString[32] = {"OTHER", "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE", "PLUS", "MINUS", "TIMES", "OVER", "LT", "LEQ", "GT", "GEQ", "EQ", "NEQ", "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LMBRACKET", "RMBRACKET", "LBBRACKET", "RBBRACKET", "LCOMMENT", "RCOMMENT", "NUM", "ID", "ERROR", "ENDFILE"};

const string tokenTypeStr[32] = {"OTHER", "else", "if", "int", "return", "void", "while", "+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!=", "=", ";", ",", "(", ")", "[", "]", "{", "}", "/*", "*/"};

const string SRC = "CMinus_SourceCode.txt";
const string TOKEN = "CMinus_Token.txt";

class Scanner
{
public:
	bool scanSuccess;//�ʷ������Ƿ�ɹ��ı�־
	void getSourseStringFromFile(string s);//ͨ���ṩ���ļ�����ȡԴ����
	void deleteComments();//ɾ��ע��
	Scanner();
	Token getTokenIn(int);//�����±��tokenList�����л�ȡToken
	void startScanner(void);//�ʷ���������������Token����tokenList������

private:
	DFAState charType(char);//�����ַ������ͣ��磺�ո�2������3����ĸ��
	char getNextChar();//��ȡ����һ���ַ�
	void backToLastChar();
	TokenType returnTokenType(string s);//�����ַ�������Token����
	void printToken();//���ʷ������õ�Token������ļ�Token.txt��
	string sourseString;//��ȡԴ������ַ���
	int charIndex;//���getNextChar()��ָ��Ҫȡ���ַ�λ��
	string str;//�ڷ��������б���Token��Ӧ�Ĵ�
	bool commentFlag;//��עע�Ϳ�ʼ�ı�־
	int lineCount;//���кż�����ÿ�λ�ȡ��'/n'������
	vector<Token> tokenList;//�����Token����
	
};
