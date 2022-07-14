#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

ifstream fin;
vector<char *> statements;
vector<char *> symbols;

// helper functions
string truncate_back(string rest, int s)
{
    string temp = "";
    if (rest != "")
    {
        for (int i = 0; i < s; i++)
        {
            temp += rest[i];
        }
    }
    return temp;
}

bool checkIfDigits(string str)
{
    bool flag = false;

    for (int i = 0; i < 10; i++)
    {
        if (str.at(0) == '0' + i)
        {
            flag = true;
        }
    }
    return flag;
}

bool checkIfDigit(char str)
{

    if (str >= '0' && str <= '1')
    {
        return true;
    }

    return false;
}

bool checkIfLetter(char str)
{

    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
    {
        return true;
    }

    return false;
}

string truncate(string rest, int s)
{
    string temp = "";
    if (rest != "")
    {
        for (int i = s; i < rest.size(); i++)
        {
            temp += rest[i];
        }
    }
    return temp;
}

class symbol
{

    string identifier;
    string value;
    string datatype;

public:
    symbol()
    {
        // Do nothing
    }

    symbol(string id, string val, string type)
    {
        this->identifier = id;
        this->value = val;
        this->datatype = type;
    }

    void setIdentifier(string id)
    {
        this->identifier = id;
    }

    void setValue(string val)
    {
        this->value = val;
    }

    void setDatatype(string type)
    {
        this->datatype = type;
    }

    string getDataType()
    {
        return this->datatype;
    }

    string getValue()
    {
        return this->value;
    }

    string getId()
    {
        return this->identifier;
    }

    void printSymbol()
    {
        cout << "Type: " << this->datatype << " value: " << this->value << " Id: " << this->identifier << endl;
    }

    ~symbol()
    {
        // do nothing
    }
};

// using for symbol table
vector<symbol> entries;

string getIdDatatype(string a)
{
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getId().compare(a) == 0)
        {
            return entries[i].getDataType();
        }
    }

    return "";
}

string getVal(string a)
{
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getId().compare(a) == 0)
        {
            return entries[i].getValue();
        }
    }

    return "";
}

void updateIdValue(string a, int val)
{
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getId().compare(a) == 0)
        {
            entries[i].setValue(to_string(val));
            break;
        }
    }
}

void applyOperator(string dest, int var_1, int var_2, string op)
{

    if (op.compare("+") == 0)
    {

        updateIdValue(dest, var_1 + var_2);
    }

    if (op.compare("-") == 0)
    {
        updateIdValue(dest, var_1 - var_2);
    }

    if (op.compare("/") == 0)
    {
        updateIdValue(dest, var_1 / var_2);
    }

    if (op.compare("*") == 0)
    {
        updateIdValue(dest, var_1 * var_2);
    }
}

void performOperation(string a, string b, string op, string dest)
{

    if (getIdDatatype(a).compare("int") == 0 && getIdDatatype(b).compare("int") == 0)
    {

        if (getIdDatatype(a).compare(getIdDatatype(b)) == 0)
        {
            if (getVal(a).compare("NA") != 0 && getVal(b).compare("NA") != 0)
            {
                int var_1 = stoi(getVal(a));
                int var_2 = stoi(getVal(b));


                applyOperator(dest,var_1,var_2,op);
            }
            else
            {
                cout << "Values not intialized" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Datatype not compatible!" << endl;
            exit(0);
        }
    }
    else
    {
        cout << "Invalid operation!" << endl;
        exit(0);
    }
}

void performOperation(string a, int b, string op, string dest)
{
    int val;

    try
    {
        val = stoi(getVal(a));
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Not a variable!!" << endl;
        exit(0);
    }

   applyOperator(dest,val,b,op);
}

void performOperation(int a, int b, string op, string dest)
{
    applyOperator(dest,a,b,op);
}

void readFile(char *filename, vector<char *> &type)
{
    ifstream fin;
    fin.open(filename);

    char *line_buffer;

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            line_buffer = new char[100];
            fin.getline(line_buffer, 100);

            if (line_buffer != NULL)
            {

                type.push_back(line_buffer);
            }
        }
    }
}

void printSt(string st)
{

    bool flag = false;
    string printStatement = "";

    // if (st.find("\n"))
    // {

    //     cout << endl; // printing new lines
    // }

    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getId().compare(st) == 0)
        {
            flag = true;
            break;
        }
    }

    if (flag)
    {
        cout << getVal(st);
    }
    else
    {

        for (size_t i = 0; i < st.length(); i++)
        {

            if (checkIfLetter(st.at(i)) || st.at(i) == ' ' || st.at(i) == ':')
            {
                if (st.at(i) != '\n')
                {

                    printStatement += st.at(i);
                }
            }
        }

        cout << printStatement << endl;
    }
}

void handleInput(string id)
{

    int val;
    cin >> val;
    updateIdValue(id, val);
}

void updateIdValue(string a, string b)
{

    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getId().compare(b) == 0)
        {
            int val = stoi(entries[i].getValue());
            updateIdValue(a, val);
            break;
        }
    }
}

bool checkCondition(string cond)
{

    string cond_op;
    string var_1;
    string var_2;

    for (int i = 0; i < cond.length(); i++) // extracting variables and conditions
    {

        while (checkIfLetter(cond.at(i)))
        {
            var_1 += cond.at(i);
            i++;

            if (i == cond.length())
            {
                break;
            }
        }

        cond_op += cond.at(i);
        i++;

        if (i == cond.length())
        {
            break;
        }

        while (checkIfLetter(cond.at(i)) || checkIfDigit(cond.at(i)))
        {
            var_2 += cond.at(i);
            i++;
            if (i == cond.length())
            {
                break;
            }
        }
    }

    int val_1 = stoi(getVal(var_1));
    int val_2;

    try
    {
        val_2 = stoi(var_2);
    }
    catch (const std::exception &e)
    {
        val_2 = stoi(getVal(var_2));
        // std::cerr << e.what() << '\n';
    }

    if (cond_op.compare(">=") == 0)
    {
        return (val_1 >= val_2);
    }
    if (cond_op.compare("<=") == 0)
    {
        return (val_1 <= val_2);
    }
    if (cond_op.compare(">") == 0)
    {
        return (val_1 > val_2);
    }
    if (cond_op.compare("<") == 0)
    {
        return (val_1 < val_2);
    }

    if (cond_op.compare("=") == 0)
    {
        return (val_1 == val_2);
    }

    return false;
}

void driver()
{
    int i = 0;

    while (i < statements.size())
    {
        string curr_line = statements[i];

        if (curr_line == "")
        {
            i = statements.size() + 3;
            break;
        }

        int index = curr_line.find(" ");
        string prev, rest;

        if (index != -1)
        {
            prev = truncate_back(curr_line, index);
            rest = truncate(curr_line, index + 1);
        }

        if (prev.compare("out") == 0)
        {
            printSt(rest);
            i++;
        }
        else if (prev.compare("in") == 0)
        {

            handleInput(rest);
            i++;
        }
        else if (prev.compare("goto") == 0)
        {
            i = stoi(rest) - 1;
        }
        else if (prev.compare("if") == 0)
        {

            int exp = rest.find("goto") - 1;
            string expression = truncate_back(rest, exp);
            int line = rest.find("goto") + 5;
            string gotoline = truncate(rest, line);
            bool flag = checkCondition(expression);

            if (flag)
            {
                i = stoi(gotoline) - 1;
            }
            else
            {
                i++;
            }
        }
        else
        {
            int end = curr_line.find('=');
            string var = truncate_back(curr_line, end);
            rest = truncate(curr_line, end);

            if (rest.length() == 2)
            { // assignment

                rest = rest.substr(rest.find("=") + 1, rest.length());

                if (checkIfDigits(rest))
                {

                    updateIdValue(var, stoi(rest));
                }
                else
                {

                    updateIdValue(var, rest);
                }
            }

            if (rest.length() > 2)
            {

                rest = rest.substr(1, rest.length());

                string op;
                string a;
                string b;

                for (int j = 0; j < rest.length(); j++) // extracting variables and conditions
                {

                    while (checkIfDigit(rest.at(j)) || checkIfLetter(rest.at(j)))
                    {
                        a += rest.at(j);
                        j++;

                        if (i == rest.length())
                        {
                            break;
                        }
                    }

                    op += rest.at(j);
                    j++;

                    if (j == rest.length())
                    {
                        break;
                    }

                    while (checkIfDigit(rest.at(j)) || checkIfLetter(rest.at(j)))
                    {
                        b += rest.at(j);
                        j++;
                        if (j == rest.length())
                        {
                            break;
                        }
                    }
                }

                if (!checkIfDigits(a) && !checkIfDigits(b))
                {
                    performOperation(a, b, op, var);
                }
                if (checkIfDigits(a))
                {
                    if (!checkIfDigits(b))
                    {
                        try
                        {
                            int val = stoi(getVal(b));
                            performOperation(a, val, op, var);
                        }
                        catch (const std::exception &e)
                        {
                            // std::cerr << e.what() << '\n';
                            cout << "Not a variable!" << endl;
                            exit(0);
                        }
                    }
                }
                if (!checkIfDigits(a))
                {

                    if (checkIfDigits(b))
                    {
                        try
                        {
                            int val = stoi(b);
                            performOperation(a, val, op, var);
                        }
                        catch (const std::exception &e)
                        {
                            // std::cerr << e.what() << '\n';
                            cout << "Not a variable!" << endl;
                            exit(0);
                        }
                    }
                }

                if (checkIfDigits(a))
                {

                    if (checkIfDigits(b))
                    {
                        try
                        {

                            performOperation(stoi(a), stoi(b), op, var);
                        }
                        catch (const std::exception &e)
                        {
                            // std::cerr << e.what() << '\n';
                            cout << "Not a variable!" << endl;
                            exit(0);
                        }
                    }
                }
            }

            i++;
        }
    }
}

int main(int argc, char *argv[])
{

    readFile(argv[1], statements); // reading the three address code
    readFile(argv[2], symbols);

    for (size_t i = 0; i < symbols.size(); i++)
    {

        vector<char *> symbol_buffer;

        char *token = strtok(symbols[i], ",");
        symbol_buffer.push_back(token);

        for (size_t i = 0; i < 3; i++)
        {
            token = strtok(NULL, ",");
            symbol_buffer.push_back(token);
        }

        symbol sym;

        try
        {
            sym.setIdentifier(string(symbol_buffer[0]));
            sym.setDatatype(string(symbol_buffer[1]));
            sym.setValue(string(symbol_buffer[2]));
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            break;
        }

        entries.push_back(sym);
        symbol_buffer.clear();
    }

    driver();

    fin.close();

    return 0;
}