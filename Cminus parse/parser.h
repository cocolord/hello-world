#include<string>
#include<fstream>
using namespace std;
//19种节点类型，分别表示int、id、void、数值、变量声明、数组声明、函数声明、函数声明参数列表、函数声明参数、复合语句体、if、while、return、赋值、运算、数组元素、函数调用、函数调用参数列表、未知节点
typedef enum {IntK, IdK, VoidK, ConstK, Var_DeclK, Arry_DeclK, FunK, ParamsK, ParamK, CompK, Selection_StmtK, Iteration_StmtK, Return_StmtK, AssignK, OpK, Arry_ElemK, CallK, ArgsK, UnkownK} Nodekind;
typedef enum {Void,Integer} ExpType;

const string TREE = "CMinus_TokenTree.txt";


ofstream fout_Tree(TREE);//输出语法树到文件

const int MAXCHILDREN = 4;
//treeNode定义 包括子节点、兄弟节点、所处行号、节点类型、属性、表达式返回类型
typedef struct treeNode
{
	struct treeNode *  child[MAXCHILDREN];
	struct treeNode *  sibling;
	int lineno;
    Nodekind nodekind;
	union { TokenType op; int val; const char * name;} attr;
    ExpType type;
} TreeNode;

class Parser
{
public:
	Parser();
	void startParse();
	TreeNode * program(void);
	TreeNode * syntaxTree;//语法树根节点
	
private:
	Scanner scanner;
	Token currentToken;//当前获取的Token
	Token lastToken;//前一个Token
	int tokenIndex;//配合getToken使用，每获取一次，tokenIndex自增
	bool Error;//语法分析是否出错
	int step;//用于节点输出时表征节点的先行空格
	
	Token getToken();//获取保存在scanner中TokenList数组中的Token，每次获取完之后数组下标指向下一个
	void printSpace(int n);//打印n个空格
	
	void syntaxError(string s);//报错的函数，报告出错位置（行号）、出错位置附近的Token
	void match(TokenType ex);//与目标Token类型ex匹配，如果匹配成功则获取下一个Token（为currentToken赋值），否则报错
	void printTree(TreeNode * t);//打印生成的语法树
	TreeNode * newNode(Nodekind k);//根据节点类型新建节点
	
	TreeNode * declaration_list(void);
	TreeNode * declaration(void);
	TreeNode * params(void);
	TreeNode * param_list(TreeNode * k);
	TreeNode * param(TreeNode * k);
	TreeNode * compound_stmt(void);
	TreeNode * local_declaration(void);
	TreeNode * statement_list(void);
	TreeNode * statement(void);	
	TreeNode * expression_stmt(void);
	TreeNode * selection_stmt(void);
	TreeNode * iteration_stmt(void);
	TreeNode * return_stmt(void);
	TreeNode * expression(void);
	TreeNode * var(void);
	TreeNode * simple_expression(TreeNode * k);
	TreeNode * additive_expression(TreeNode * k);
	TreeNode * term(TreeNode * k);
	TreeNode * factor(TreeNode * k);	
	TreeNode * call(TreeNode * k);
	TreeNode * args(void);
};