#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string token;
string lexeme;
string prev_token;
string prev_lexeme;
ifstream reader;
ofstream writer;
ofstream symbol_writer;
vector<string> identifiers;

int lines = 1;
int temp_count = 0;
int backpatch_lines = 0;

string current_tmp;
string current_identifier;
string current_print_statement;
string current_condition;

// Prototype
void E();
string T();
void R(string);
string F();

void match(string strObj);
void assign();
void init();
void X();
void print();
void pst();
void match_lexeme(string strObj);
void condition();
string ro();
void _return();
void input();
void _for();
void _if();
void next();
void _else();
void _elseif();
void _function();
void params();
void param();
void code();
void Q();
void parserMain();
void z();

// Gonna use for backpatching
vector<string> back;

// File reading

char *nextLine(ifstream &fin)
{
	char *line = NULL;
	if (!fin.eof())
	{
		line = new char[100];
		fin.getline(line, 100);
	}
	else
	{
		cout << "END OF FILE" << endl;
	}

	return line;
}

// Seperates and returns Tokens and Lexeme from the line
bool getToken(const char *line)
{
	if (int(*line) == 0)
	{
		return false;
	}

	if (line != nullptr)
	{
		string token_temp = "";
		string lexeme_temp = "";
		int i = 1;

		// Reading Token (till the comma)
		for (i; line[i] != ','; i++)
		{
			token_temp.push_back(line[i]);
		}

		// Removing unnecessary spaces
		if (token_temp.back() == ' ')
		{
			token_temp.pop_back();
		}
		i++;

		// Not removing spaces for Constant Parameters of print and println
		if (token_temp.compare("String") != 0)
		{
			for (i; line[i] != '\0'; i++)
			{
				if (line[i] != ' ')
				{
					lexeme_temp.push_back(line[i]);
				}
			}
		}
		else
		{
			if (line[i] == ' ')
			{
				i++;
			}
			for (i; line[i] != '\0'; i++)
			{
				lexeme_temp.push_back(line[i]);
			}
		}
		lexeme_temp.pop_back();
		token = token_temp;
		lexeme = lexeme_temp;
		return true;
	}
	else
	{
		return false;
	}
}

// returns New Tokens
bool nextToken()
{
	if (getToken(nextLine(reader)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ReadFile(ifstream &fin)
{
	fin.open("output.txt");
	if (!fin.is_open())
	{
		cout << "File not Open" << endl;
		exit(0);
	}
}
// Helper Functions
void match_lexeme(string strObj)
{
	if (lexeme.compare(strObj) == 0)
	{
		// cout<<lexeme;
		prev_lexeme = lexeme;
		prev_token = token;

		nextToken();
	}
	else
	{
		cout << "Syntax Error" << endl;
		exit(1);
	}
}
void match(string strObj)
{
	if (token.compare(strObj) == 0)
	{

		// cout << lexeme;
		prev_lexeme = lexeme;
		prev_token = token;

		nextToken();
	}
	else
	{
		cout << "Syntax Error" << endl;
		exit(1);
	}
}

string newTemp()
{
	string newtemp = "T" + to_string(temp_count);
	temp_count++;
	return newtemp;
}

// emit functions
string emit(string temp, string a, string opcode, string b)
{
	// string str_buffer = temp + "=" + a + opcode + b;

	current_tmp = a + opcode + b;
	return current_tmp;

	// return str_buffer;
}

string emit(string id, string value)
{

	return id + "=" + value;
}

string emit(string str)
{

	return "out " + str;
}

string emit_input(string id)
{

	return "in " + id;
}

string emit_return(string obj)
{
	return "ret " + obj;
}

string emit_if(string cond, int line_number)
{

	return "if " + cond + " goto " + to_string(line_number);
}

// Expression

void E()
{

	string v = T();
	R(v);
}

string T()
{
	string v = F();
	return v;
}

void R(string i)
{
	if (token.compare("ADDITION") == 0)
	{
		match("ADDITION");
		string v = T();
		string tmp = newTemp();
		emit(tmp, i, "+", v);
	}
	else if (token.compare("SUBSTRACTION") == 0)
	{
		match("SUBSTRACTION");
		string v = T();
		string tmp = newTemp();
		emit(tmp, i, "-", v);
	}
	else if (lexeme.compare("*") == 0)
	{
		match_lexeme("*");
		string v = T();
		string tmp = newTemp();
		emit(tmp, i, "*", v);
	}

	else if (lexeme.compare("/") == 0)
	{
		match_lexeme("/");
		string v = T();
		string tmp = newTemp();
		emit(tmp, i, "*", v);
	}
	else
	{
		current_tmp = i;
	}
}

string F()
{
	if (token.compare("IDENTIFIER") == 0)
	{
		match("IDENTIFIER");
		return prev_lexeme;
	}
	else if (token.compare("DIGIT") == 0)
	{
		match("DIGIT");
		return prev_lexeme;
	}
	else
	{
		cout << "Syntax Error" << endl;
		exit(1);
	}
}

// Expression end

// print start
void print()
{

	if (lexeme.compare("print") == 0)
	{

		match("KEYWORD");
		pst();
		match("SEMICOLON");
		back.push_back(emit(current_print_statement));
		lines++;
	}
}

void pst()
{
	if (token.compare("String") == 0)
	{
		match("String");
		current_print_statement = prev_lexeme;
	}
	else
	{
		E();
		current_print_statement = current_tmp;
	}
}

// print end

// condition start
void condition()
{

	E();
	string opt = ro();
	current_condition += current_tmp + opt;
	E();
	current_condition += current_tmp;
}

string ro()
{
	if (lexeme.compare("=") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else if (lexeme.compare("<") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else if (lexeme.compare("<=") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else if (lexeme.compare(">") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else if (lexeme.compare(">=") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else if (lexeme.compare("~=") == 0)
	{
		match("RO");
		return prev_lexeme;
	}
	else
	{
		cout << "Syntax Error" << endl;
		exit(1);
	}
}

// condition end

// input start
void input()
{
	match_lexeme("in");
	current_identifier = lexeme;
	match("IDENTIFIER");
	match("SEMICOLON");
	back.push_back(emit_input(current_identifier));
	lines++;
}

// input end

// for loop start
void _for()
{

	match_lexeme("for");
	current_identifier = lexeme;

	match("IDENTIFIER");
	match("ASSIGN");
	E();

	match("COMMA");
	current_condition = "";
	condition();
	match("COMMA");

	match("IDENTIFIER");
	match("ASSIGN");
	E();
	match("COLON");

	match_lexeme("begin");
	back.push_back(emit_if(current_condition, lines + 2));
	int temp = lines;
	lines++;

	back.push_back("goto ");
	int back_patch_line = lines - 1;
	lines++;
	back.push_back(emit(current_identifier, current_tmp));
	lines++;

	code();

	lines++;
	back[back_patch_line] = "goto " + to_string(lines + 1);
	back.push_back("goto " + to_string(temp));

	lines++;
	match_lexeme("end");
}
// for loop end

// if else statement start
void _if()
{
	vector<int> back_elif;
	bool contain_elif = false;

	match_lexeme("if");
	condition();
	match("COLON");
	match_lexeme("begin");
	back.push_back(emit_if(current_condition, lines + 2));
	lines++;



	back.push_back("goto ");
	int back_patch_line = lines - 1;
	lines++;

	code();

	back[back_patch_line] = "goto " + to_string(lines + 1);
	match_lexeme("end");

	
	back.push_back("goto ");
	back_elif.push_back(lines);
	lines++;

	while (lexeme.compare("elif") == 0)
	{
		contain_elif = true;
		match_lexeme("elif");
		current_condition = "";
		condition();
		match("COLON");
		match_lexeme("begin");
		back.push_back(emit_if(current_condition, lines + 2));
		lines++;
	

	
		back.push_back("goto ");
		int back_patch_line = lines - 1;
		lines++;

		code();
	
		back[back_patch_line] = "goto " + to_string(lines + 1);
		match_lexeme("end");


		back.push_back("goto ");
		back_elif.push_back(lines);
		lines++;
	}

	if (contain_elif)
	{
		if (lexeme.compare("else") == 0)
		{
			match_lexeme("else");
			match("COLON");
			match_lexeme("begin");
			code();
			match_lexeme("end");
		}
		else
		{
			cout << "Syntax Error!" << endl;
		}
	}

	for (size_t i = 0; i < back_elif.size(); i++)
	{
		back[back_elif[i] - 1] = "goto " + to_string(lines);
	}
	

	// next();
}

void next()
{
	_else();
	// next();
}

void _else()
{

	if (lexeme.compare("else") == 0)
	{

		match_lexeme("else");
		match("COLON");
		match_lexeme("begin");
		code();
		match_lexeme("end");
	}
	else
	{
		// DO NOTHING
	}
}
// if else statement end

// return start

void _return()
{
	match_lexeme("return");
	E();
	match("SEMICOLON");
	back.push_back(emit_return(current_tmp));
	lines++;

}

// return end

void _function()
{
	match_lexeme("func");
	if (lexeme.compare("int") == 0 || lexeme.compare("char") == 0)
	{
		// match("kEYWORD");
		match_lexeme(lexeme);
	}
	match("IDENTIFIER");
	// params();
	match("COLON");
	match_lexeme("begin");
	code();
	match_lexeme("end");
}

void params()
{
	if (token.compare("IDENTIFIER") == 0)
	{
		param();
		params();
	}
	else
	{
		// DO NOTHING
	}
}

void param()
{
	match("IDENTIFIER");

	if (lexeme.compare("int") == 0 || lexeme.compare("char") == 0)
	{
		match("kEYWORD");
	}
}

// function end

// runner
void code()
{

	if (token.compare("IDENTIFIER") == 0)
	{

		current_identifier = lexeme;
		if (find(identifiers.begin(), identifiers.end(), lexeme) != identifiers.end())
		{
			// Already exists
		}
		else
		{
			symbol_writer << lexeme << ",";
			identifiers.push_back(lexeme);
		}

		match("IDENTIFIER");

		if (lexeme.compare("int") == 0 || lexeme.compare("char") == 0)
		{
			symbol_writer << lexeme << ","
						  << "0" << endl;
			match("KEYWORD");
			match("SEMICOLON");

			code();
		}
		else
		{
			match("ASSIGN");
			E();
			if (lexeme.compare("int") == 0 || lexeme.compare("char") == 0)
			{
				symbol_writer << lexeme << "," << current_tmp << endl;
				match("KEYWORD");
			}
			match("SEMICOLON");
			back.push_back(emit(current_identifier, current_tmp));
			lines++;
			code();

			

		}
	}
	else if (lexeme.compare("print") == 0)
	{

		print();
		code();
	}
	else if (lexeme.compare("if") == 0)
	{

		_if();
		code();
	}
	else if (lexeme.compare("for") == 0)
	{

		_for();
		code();
	}
	else if (lexeme.compare("return") == 0)
	{
		_return();
		code();
	}
	else if (lexeme.compare("in") == 0)
	{

		input();
		code();
	}
	else
	{
		// Do NOTHING
	}
}

// parser start
void parserMain()
{
	_function();
	z();
}

void z()
{

	if (lexeme.compare("func") == 0)
	{
		match_lexeme("func");
		z();
	}
	else
	{

		// DO NOTHING
	}
}
// parser end

int main()
{

	writer.open("TAC.txt");

	if (!writer.is_open())
	{
		return 0;
	}
	else
	{
		// do nothing
	}

	symbol_writer.open("symbol_table.txt");

	if (!symbol_writer.is_open())
	{
		cout << "Symbol table not initialized!!!" << endl;
		return 0;
	}
	else
	{
		// DO nothing
	}

	ReadFile(reader); // Reading Tokens from Lexical Analyzer
	nextToken();
	parserMain();

	for (size_t i = 0; i < back.size(); i++)
	{
		writer << back[i] << endl;
	}

	writer.close();
	reader.close();
	symbol_writer.close();

	return 0;
}