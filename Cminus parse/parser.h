#include<string>
#include<fstream>
using namespace std;
//19�ֽڵ����ͣ��ֱ��ʾint��id��void����ֵ���������������������������������������������б�����������������������塢if��while��return����ֵ�����㡢����Ԫ�ء��������á��������ò����б�δ֪�ڵ�
typedef enum {IntK, IdK, VoidK, ConstK, Var_DeclK, Arry_DeclK, FunK, ParamsK, ParamK, CompK, Selection_StmtK, Iteration_StmtK, Return_StmtK, AssignK, OpK, Arry_ElemK, CallK, ArgsK, UnkownK} Nodekind;
typedef enum {Void,Integer} ExpType;

const string TREE = "CMinus_TokenTree.txt";


ofstream fout_Tree(TREE);//����﷨�����ļ�

const int MAXCHILDREN = 4;
//treeNode���� �����ӽڵ㡢�ֵܽڵ㡢�����кš��ڵ����͡����ԡ����ʽ��������
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
	TreeNode * syntaxTree;//�﷨�����ڵ�
	
private:
	Scanner scanner;
	Token currentToken;//��ǰ��ȡ��Token
	Token lastToken;//ǰһ��Token
	int tokenIndex;//���getTokenʹ�ã�ÿ��ȡһ�Σ�tokenIndex����
	bool Error;//�﷨�����Ƿ����
	int step;//���ڽڵ����ʱ�����ڵ�����пո�
	
	Token getToken();//��ȡ������scanner��TokenList�����е�Token��ÿ�λ�ȡ��֮�������±�ָ����һ��
	void printSpace(int n);//��ӡn���ո�
	
	void syntaxError(string s);//����ĺ������������λ�ã��кţ�������λ�ø�����Token
	void match(TokenType ex);//��Ŀ��Token����exƥ�䣬���ƥ��ɹ����ȡ��һ��Token��ΪcurrentToken��ֵ�������򱨴�
	void printTree(TreeNode * t);//��ӡ���ɵ��﷨��
	TreeNode * newNode(Nodekind k);//���ݽڵ������½��ڵ�
	
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