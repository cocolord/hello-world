#include "scanner.h"
#include "parser.h"
#include<iostream>
#include<string>

using namespace std;


Parser :: Parser()
{
	step = 0;
	tokenIndex = 0;
	Error = false;
}

//获取保存在scanner中TokenList数组中的Token，每次获取完之后数组下标指向下一个
Token Parser :: getToken()
{
	lastToken = currentToken;
	currentToken = scanner.getTokenIn(tokenIndex);
	tokenIndex++;
	return currentToken;
}

void Parser :: syntaxError(string s)
{  
	fout_Tree<<s<<"  出现错误的行号: "<<currentToken.lineNo<<"，错误的Token是: "<<currentToken.tokenString<<"，Token的类型是："<<tokenTypeString[currentToken.tokenType]<<endl;
    Error = true;
}

void Parser :: match(TokenType ex)
{
	if(currentToken.tokenType==ex) 
	{ 
		getToken();
	}
	else
	{   
		fout_Tree << "匹配到错误的类型："+tokenTypeString[ex] << "  出现错误的行号: " << currentToken.lineNo << "，错误的Token是: " << currentToken.tokenString <<"，Token的类型是：" << tokenTypeString[currentToken.tokenType] << endl;
	}
}

void Parser :: printTree(TreeNode * t)
{ 
	int i;
	while(t!=NULL)
	{
		int temp = step;
		fout_Tree << temp;
		while(temp--)
			fout_Tree<<"----";
		
		if(t->nodekind == VoidK)
			fout_Tree << "VoidK" << endl;
		else if(t->nodekind == IntK)
			fout_Tree << "IntK" << endl;
		else if(t->nodekind == IdK)
			fout_Tree << "IdK: " << t->attr.name << endl;
		else if(t->nodekind == ConstK)
			fout_Tree << "ConstK: "<< t->attr.val<<endl;
		else if(t->nodekind == Var_DeclK)
			fout_Tree << "Var_DeclK" << endl;
		else if(t->nodekind == Arry_DeclK)
			fout_Tree << "Arry_DeclK" << endl;
		else if(t->nodekind == FunK)
			fout_Tree << "FunK: "<< t->attr.name << endl;
		else if(t->nodekind == ParamsK)
			fout_Tree << "ParamsK" << endl;
		else if(t->nodekind == ParamK)
			fout_Tree << "ParamK" << endl;
		else if(t->nodekind == CompK)
			fout_Tree << "CompK" << endl;
		else if(t->nodekind == Selection_StmtK)
			fout_Tree << "if" << endl;
		else if(t->nodekind == Iteration_StmtK)
			fout_Tree << "while" << endl;
		else if(t->nodekind == Return_StmtK)
			fout_Tree << "return" << endl;
		else if(t->nodekind == AssignK)
			fout_Tree << "AssignK" << endl;
		else if(t->nodekind == OpK)
			fout_Tree << "Op: " << tokenTypeStr[t->attr.op] << endl;
		else if(t->nodekind == Arry_ElemK)
			fout_Tree << "Arry_ElemK" << endl;
		else if(t->nodekind == CallK)
			fout_Tree << "CallK: " << t->attr.name << endl;
		else if(t->nodekind == ArgsK)
			fout_Tree << "ArgsK" << endl;
		else
			fout_Tree << "UnknownK" << t->attr.name << endl;
	
		step++;
		for(i = 0; i < MAXCHILDREN; i++)
		{ 
			if(t->child[i] != NULL)
				printTree(t->child[i]);
		}
		step--;
		t = t->sibling;
	}
}

TreeNode * Parser :: newNode(Nodekind kind)
{
	TreeNode * p = (TreeNode *)malloc(sizeof(TreeNode));
	int k = 0;
	while(k < MAXCHILDREN)
	{
		p->child[k] = NULL;
		k++;
	}
	p->sibling = NULL;
	p->nodekind = kind;
	p->lineno = currentToken.lineNo;
	if(kind == OpK || kind == IntK)
	{
		p->type = Integer;
	}
	if(kind == IdK)
	{
		p->type = Integer;
		p->attr.name = "";
	}
	if(kind == ConstK)
		p->attr.val = 0;	
	return p;
}

//语法数分析入口，同Tiny
//program→declaration-list
TreeNode * Parser :: program(void)
{
	TreeNode * t;
	currentToken = getToken();
	lastToken = currentToken;
	t = declaration_list();
	if(currentToken.tokenType!=ENDFILE)
	{ 
		syntaxError("结束错误");
	}
	return t;
}

//declaration-list -> declaration[declaration]
TreeNode * Parser :: declaration_list()
{ 
	TreeNode * t = declaration();
	TreeNode * p = t;
	
	while((currentToken.tokenType!=INT)&&(currentToken.tokenType!=VOID)&&(currentToken.tokenType!=ENDFILE))
	{   
		syntaxError("");
		getToken();
		if(currentToken.tokenType==ENDFILE)
			break;
	}
	while((currentToken.tokenType==INT)||(currentToken.tokenType==VOID))
	{    
		TreeNode * q;
		q = declaration();
		if(q != NULL)
		{
			if(t == NULL)  
			{ 
				t = p = q;
			}
			else
			{  
				p -> sibling = q;
				p = q;
			}
		}
	}
	match(ENDFILE);
	return t;
}

/*
declaration → var-declaration | fun-declaration
var-declaration → type-specifier ID; | type-specifier ID [NUM];
fun-declatation→type-specifier ID (params) | compound-stmt
type-specifier → int | void
*/
TreeNode * Parser :: declaration(void)
{
	TreeNode * t = NULL;
	TreeNode * p = NULL;
	TreeNode * q = NULL;
	TreeNode * s = NULL;
	if(currentToken.tokenType==INT)
	{ 
		p = newNode(IntK);
		match(INT);
	}
	else if(currentToken.tokenType==VOID)
	{  
		p = newNode(VoidK);
		match(VOID);
	}
	else
	{
		syntaxError("类型匹配错误");
	}
	
	if((p != NULL) && (currentToken.tokenType == ID))
	{ 
		q = newNode(IdK);     
		q->attr.name = currentToken.tokenString.c_str();
		match(ID);
		
		//fun-declatation→type-specifier ID (params) | compound-stmt
		if(currentToken.tokenType == LPAREN)//'('：函数情况
		{ 
			t = newNode(FunK);
			t->attr.name = lastToken.tokenString.c_str();
			t->child[0] = p;
			t->child[1] = q;
			match(LPAREN);
			t->child[2] = params();
			match(RPAREN);
			t->child[3] = compound_stmt();
		}
		//var-declaration → type-specifier ID; | type-specifier ID [NUM];
		else if(currentToken.tokenType==LMBRACKET)//'['：数组声明
		{ 
			t = newNode(Var_DeclK);
			//新建一个数组节点
			TreeNode * m = newNode(Arry_DeclK);
			
			match(LMBRACKET);
//			match(NUM);
			s = newNode(ConstK);
//			s->attr.val = atoi(lastToken.tokenString.c_str());

			s->attr.val = atoi(currentToken.tokenString.c_str());
			match(NUM);

			t->child[0] = p;
			t->child[1] = m;
			m->child[0] = q;
			m->child[1] = s;
			
			match(RMBRACKET);
			match(SEMI);
		}
		else if(currentToken.tokenType==SEMI)//';'结尾：普通变量声明
		{
			t = newNode(Var_DeclK);
			t->child[0] = p;
			t->child[1] = q;
			match(SEMI);
		}
		else
		{  
			syntaxError("");
		}
	} 
	else
	{  
		syntaxError("");
	}	
	return t;
}

//params → param_list | void
//param_list → param[, param]
TreeNode * Parser :: params(void)
{  
	TreeNode * t = newNode(ParamsK);
	TreeNode * p = NULL;
	if(currentToken.tokenType == VOID)//开头为void，参数列表可能是(void)和(void id,[……])两种情况
	{  
		p = newNode(VoidK);
		match(VOID);
		if(currentToken.tokenType == RPAREN)//参数列表为(void)
		{
			if(t!=NULL)
				t->child[0] = p;
		}
		else//参数列表为(void id,[……])  ->void类型的变量
		{
			t->child[0] = param_list(p);
		}
	}
	else if(currentToken.tokenType == INT)//参数列表为(int id,[……])
	{ 
		t->child[0] = param_list(p);
	}
	else
	{ 
		syntaxError("");
	}	
	return t;
}

//param_list → param[, param]
// param→ type-specifier ID[[ ]]
//k可能是已经被取出来的VoidK，但又不是(void)类型的参数列表，所以一直传到param中去，作为其一个子节点
TreeNode * Parser :: param_list(TreeNode * k)
{  
	TreeNode * t = param(k);
	TreeNode * p = t; 
	//没有要传给param的VoidK，所以将k设为NULL
	k = NULL;
	while(currentToken.tokenType==COMMA)
	{ 
		TreeNode * q = NULL;
		match(COMMA);
		q = param(k);
		if(q!=NULL)
		{
			if(t==NULL) 
			{ 
				t = p = q;
			}
			else
			{
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

// param→ type-specifier ID[[ ]]
TreeNode * Parser :: param(TreeNode * k)
{  
	TreeNode * t = newNode(ParamK);
	TreeNode * p = NULL;//ParamK的第一个子节点
	TreeNode * q = NULL;//ParamK的第二个子节点
	
	if(k == NULL && currentToken.tokenType == INT)
	{
		p = newNode(IntK);
		match(INT);
	}
	else if(k != NULL)
	{
		p = k;
	}
	if(p != NULL)
	{
		t->child[0] = p;		
		if(currentToken.tokenType == ID)
		{ 			
			q = newNode(IdK);
			q->attr.name = currentToken.tokenString.c_str(); 
			t->child[1] = q;
			match(ID);
		}
		else
		{ 
			syntaxError("");
		}

		if((currentToken.tokenType==LMBRACKET)&&(t->child[1]!=NULL))
		{
			match(LMBRACKET);
			t->child[2] = newNode(IdK);
			match(RMBRACKET);
		}
		else 
		{  
			return t; 
		}		
	}
	else
	{ 
		syntaxError("");
	}
	return t;
}

//compound-stmt→{ local-declaration statement-list}
TreeNode * Parser :: compound_stmt(void)
{  
	TreeNode * t = newNode(CompK);
	match(LBBRACKET);
	t->child[0] = local_declaration();
	t->child[1] = statement_list(); 
	match(RBBRACKET);
	return t;
}

//local-declarations → empty [var-declaration]
TreeNode * Parser :: local_declaration(void)
{  
	TreeNode * t = NULL;
	TreeNode * q = NULL;
	TreeNode * p = NULL;
	while(currentToken.tokenType == INT || currentToken.tokenType == VOID)
	{ 
		p = newNode(Var_DeclK);
		if(currentToken.tokenType==INT)
		{
			TreeNode * q1 = newNode(IntK);
			p->child[0] = q1;
			match(INT);
		}
		else if(currentToken.tokenType==VOID)
		{
			TreeNode * q1 = newNode(VoidK);
			p->child[0] = q1;
			match(INT);
		}
		if((p!=NULL)&&(currentToken.tokenType==ID))
		{ 
			TreeNode * q2 = newNode(IdK);     
			q2->attr.name = currentToken.tokenString.c_str();
			p->child[1] = q2;
			match(ID);
			
			if(currentToken.tokenType==LMBRACKET)
			{ 
				TreeNode * q3 = newNode(Var_DeclK);
				p->child[3] = q3;
				match(LMBRACKET);
				match(RMBRACKET);
				match(SEMI);
			}
			else if(currentToken.tokenType==SEMI)
			{
				match(SEMI);
			}
			else
			{
				match(SEMI);
			}
		} 
		else
		{ 
			syntaxError("");
		}
		if(p!=NULL)
		{
			if(t==NULL)
				t = q = p;
			else
			{
				q->sibling = p;
				q = p;
			}
		}
	}
	return t;
}

/*
statement-list→ empty [statement]
statement→expression-stmt | compound-stmt | selection-stmt | iteration-stmt | return-stmt
compound-stmt→{local-declaration statement-list}
expression-stmt→ [expression];
selection-stmt→if (expression) statement [else statement]
iteration-stmt→while (expression)statement
return-stmt→return [expression];
*/
TreeNode * Parser :: statement_list(void)
{  
	TreeNode * t = statement();   
	TreeNode * p = t;
	while (IF == currentToken.tokenType || LBBRACKET == currentToken.tokenType || 
		ID == currentToken.tokenType || WHILE == currentToken.tokenType || 
		RETURN == currentToken.tokenType || SEMI == currentToken.tokenType || 
		LPAREN == currentToken.tokenType || NUM == currentToken.tokenType)
	{  
		TreeNode * q;
		q = statement();
		if(q!=NULL)
		{
			if(t==NULL)  
			{ 
				t = p = q;
			}
			else
			{  
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

//statement→expression-stmt | compound-stmt | selection-stmt | iteration-stmt | return-stmt
TreeNode * Parser :: statement(void)
{  
	TreeNode * t = NULL;
	switch(currentToken.tokenType)
	{
	case IF:
		t = selection_stmt(); 
		break;
	case WHILE:
		t = iteration_stmt(); 
		break;
	case RETURN:
		t = return_stmt(); 
		break;
	case LBBRACKET:
		t = compound_stmt(); 
		break;
	case ID: case SEMI: case LPAREN: case NUM: 
		t = expression_stmt(); 
		break;
	default:
		syntaxError("");
		currentToken = getToken();
		break;
	}
	return t;
}

//selection-stmt→if (expression) statement [else statement]
TreeNode * Parser :: selection_stmt(void)
{  
	TreeNode * t = newNode(Selection_StmtK);
	match(IF);
	match(LPAREN);
	if(t!=NULL) 
	{
		t->child[0] = expression();
	}
	match(RPAREN);
	t->child[1] = statement();
	if(currentToken.tokenType==ELSE)
	{ 
		match(ELSE);
		if(t!=NULL) 
		{ 
			t->child[2] = statement();
		}
	}
	return t;
}

//expression-stmt→ [expression];
TreeNode * Parser :: expression_stmt(void)
{  
	TreeNode * t = NULL;
	if(currentToken.tokenType==SEMI)  
	{ 
		match(SEMI);
		return t;
	}
	else 
	{
		t = expression();
		match(SEMI);
	}
	return t;
}

//iteration-stmt→while (expression)statement
TreeNode * Parser :: iteration_stmt(void)
{  
	TreeNode * t = newNode(Iteration_StmtK);
	match(WHILE);
	match(LPAREN);
	if(t!=NULL) 
	{ 
		t->child[0] = expression();
	}
	match(RPAREN);
	if(t!=NULL) 
	{ 
		t->child[1] = statement();
	}
	return t;
}

//return-stmt→return [expression];
TreeNode * Parser :: return_stmt(void)
{  
	TreeNode * t = newNode(Return_StmtK);
	match(RETURN);
	if (currentToken.tokenType==SEMI)
	{  
		match(SEMI);
		return t;
	}
	else
	{ 
		if(t!=NULL) 
		{ 
			t->child[0] = expression();
		} 
	}
	match(SEMI);
	return t;
}

//expression→ var = expression | simple-expression
TreeNode * Parser :: expression(void)
{  
	TreeNode * t = var();
	if(t==NULL)//不是以ID开头，只能是simple_expression情况
	{ 
		t = simple_expression(t); 
	}
	else//以ID开头，可能是赋值语句，或simple_expression中的var和call类型的情况
	{    
		TreeNode * p = NULL;
		if(currentToken.tokenType==ASSIGN)//赋值语句
		{ 
			p = newNode(AssignK);
			p->attr.name = lastToken.tokenString.c_str();
			match(ASSIGN);
			p->child[0] = t;
			p->child[1] = expression();
			return p;
		}
		else //simple_expression中的var和call类型的情况
		{ 
			t = simple_expression(t);
		}
	}	   
	return t;
}

//simple-expression－>additive-expression [relop additive-expression]
TreeNode * Parser :: simple_expression(TreeNode * k)
{   
	TreeNode * t = additive_expression(k);
	k = NULL;
	if(EQ==currentToken.tokenType || GT==currentToken.tokenType || GEQ==currentToken.tokenType || LT==currentToken.tokenType || LEQ==currentToken.tokenType || NEQ==currentToken.tokenType)
	{  
		TreeNode * q = newNode(OpK);
		q->attr.op = currentToken.tokenType; 
		q->child[0] = t;
		t = q;
		match(currentToken.tokenType);
		t->child[1] = additive_expression(k);		 
		return t;
	}
	return t;
}

//additive-expression→term [addop term]
TreeNode * Parser :: additive_expression(TreeNode * k)
{  
	TreeNode * t = term(k);
	k = NULL;
	while((currentToken.tokenType==PLUS)||(currentToken.tokenType==MINUS))
	{ 
		TreeNode * q = newNode(OpK);
		q->attr.op = currentToken.tokenType; 
		q->child[0] = t; 
		match(currentToken.tokenType);
		q->child[1] = term(k);
		t = q;		
	}
	return t;
}

//term→factor [mulop factor]
TreeNode * Parser :: term(TreeNode * k)
{  
	TreeNode * t = factor(k);
	k = NULL;
	while((currentToken.tokenType==TIMES)||(currentToken.tokenType==OVER))
	{ 
		TreeNode * q = newNode(OpK);
		q->attr.op = currentToken.tokenType; 
		q->child[0] = t; 
		t = q;
		match(currentToken.tokenType);
		q->child[1] = factor(k);
	}
	return t;
}

//factor→(expression) | var | call | NUM
TreeNode * Parser :: factor(TreeNode * k)
{  
	TreeNode * t = NULL;
	if(k!=NULL)//k为上面传下来的已经解析出来的以ID开头的var,可能为call或var
	{
		if(currentToken.tokenType==LPAREN && k->nodekind!=Arry_ElemK) //call
		{ 
			t = call(k);
		}
		else 
		{ 
			t = k; 
		}
	}
	else//没有从上面传下来的var
	{ 
		switch(currentToken.tokenType)
		{
		case LPAREN:
			match(LPAREN);
			t = expression();
			match(RPAREN);
			break;
		case ID:
			k = var();
			if(LPAREN==currentToken.tokenType && k->nodekind!=Arry_ElemK) 
			{ 
				t = call(k);
			}
			break;
		case NUM:
			t = newNode(ConstK);
			if((t!=NULL)&&(currentToken.tokenType==NUM))
			{ 
				t->attr.val = atoi(currentToken.tokenString.c_str()); 
			}
			match(NUM);
			break;
		default:
			syntaxError("");
			currentToken = getToken();
			break;
		} 
	}
	return t;
}

//var→ID | ID [expression]
TreeNode * Parser :: var(void)
{  
	TreeNode * t = NULL;
	TreeNode * p = NULL;
	TreeNode * q = NULL;
	if(currentToken.tokenType==ID)
	{
		p = newNode(IdK);
		p->attr.name = currentToken.tokenString.c_str(); 
		match(ID);
		if(currentToken.tokenType==LMBRACKET) 
		{ 
			match(LMBRACKET);
			q = expression();
			match(RMBRACKET);

			t = newNode(Arry_ElemK);
			t->child[0] = p;
			t->child[1] = q;
		}
		else
		{
			t = p;
		}
	}
	return t;
}

//call→ID ( args )
TreeNode * Parser :: call(TreeNode * k)
{  
	TreeNode * t = newNode(CallK);
	t->attr.name = currentToken.tokenString.c_str();
	if(k!=NULL)
		t->child[0] = k;
	match(LPAREN);
	if(currentToken.tokenType==RPAREN)  
	{  
		match(RPAREN);
		return t;
	}
	else if(k!=NULL)
	{ 
		t->child[1] = args();
		match(RPAREN);
	}
	return t;
}

//args→arg-list | empty
//arg-list→ expression [, expression]
TreeNode * Parser :: args(void)
{  
	TreeNode * t = newNode(ArgsK);
	TreeNode * s = NULL;
	TreeNode * p = NULL;
	if(currentToken.tokenType!=RPAREN)
	{
		s = expression();
		p = s;
		while(currentToken.tokenType==COMMA)
		{   
			TreeNode * q;
			match(COMMA);
			q = expression();
			if(q!=NULL)
			{
				if(s==NULL)  
				{ 
					s = p = q;
				}
				else
				{  
					p->sibling = q;
					p = q;
				}
			}
		}
	}	
	if(s!=NULL)
	{
		t->child[0] = s;
	}
	return t;
}

void Parser :: startParse()
{
	string path = "main.txt";
	scanner.getSourseStringFromFile(path);
	scanner.deleteComments();
	scanner.startScanner();
	if(scanner.scanSuccess)
	{
		if(scanner.scanSuccess)
		{
			cout<<"开始递归下降的语法分析"<<endl;
			syntaxTree = program();
			printTree(syntaxTree);
			if(Error)
				cout<<"语法分析错误！"<<endl;
			else
				cout<<"完成语法分析！"<<endl;
		}
	}
}

int main(int argc, char  * argv[])
{
	Parser p;
	p.startParse();
    system("PAUSE");
    return 0;
}