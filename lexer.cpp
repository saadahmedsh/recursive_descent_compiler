#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <list>
#include <stdio.h>
using namespace std;

enum OPERATOR
{
    EQUALTO = 256,
    GREATERTHAN,
    GREATERTHANEQUALTO,
    LESSTHAN,
    LESSTHANEQUALTO,
    OTHER,
    NOTOPERATOR,
};

enum ASSIGNMENT
{

    ASSIGN = 264,
    NOTASSIGNMENT

};

enum ARITHMETIC
{

    ADDITION = 266,
    MULTIPLICATION,
    SUBSTRACTION,
    DIVISION,
    MODULO,
    NOTARITHMETIC

};

enum KEYWORDS
{
    FUNC = 272,
    ELSE,
    INT,
    FOR,
    CHAR,
    PRINT,
    CALL,
    PRINTLN,
    IF,
    RETURN,
    ELIF,
    IN,
    BEGIN,
    END,
    NOTKEYWORD
};
bool isSpecialCharatcer(char obj)
{
    char special[] = {'!', '@', '#', '%', '&', '^', '*', '(', ')', '_', '+'};
    for (size_t i = 0; i < strlen(special) + 1; i++)
    {
        if (special[i] == obj)
        {
            return true;
        }
    }

    return false;
}

bool isSign(char obj)
{
    if (obj == '+' || obj == '-')
    {
        return true;
    }

    return false;
}

bool compareStrings(vector<char> arr1, const char *arr2)
{
    bool flag = true;
    for (int i = 0; i < arr1.size() - 1; i++)
    {
        if (arr1[i] != arr2[i])
        {
            flag = false;
        }
    }
    return flag;
}

void printVector(vector<char> buffer, ofstream &fout)
{
    for (int i = 0; i < buffer.size(); i++)
    {      
        fout << buffer[i];
    }
}

KEYWORDS returnKeyword(vector<char> arr)
{

    if (compareStrings(arr, "begin"))
    {
        return BEGIN;
    }

    if (compareStrings(arr, "func"))
    {
        return FUNC;
    }

    if (compareStrings(arr, "else"))
    {
        return ELSE;
    }

    if (compareStrings(arr, "int"))
    {
        return INT;
    }

    if (compareStrings(arr, "for"))
    {
        return FOR;
    }

    if (compareStrings(arr, "char"))
    {
        return CHAR;
    }

    if (compareStrings(arr, "print"))
    {
        return PRINT;
    }

    if (compareStrings(arr, "call"))
    {
        return CALL;
    }

    if (compareStrings(arr, "println"))
    {
        return PRINTLN;
    }

    if (compareStrings(arr, "return"))
    {
        return RETURN;
    }

    if (compareStrings(arr, "elif"))
    {
        return ELIF;
    }

    if (compareStrings(arr, "in"))
    {
        return IN;
    }

    if (compareStrings(arr, "if"))
    {
        return IF;
    }

    if (compareStrings(arr, "end"))
    {
        return END;
    }

    return NOTKEYWORD;
}

bool isLetter(char obj)
{
    if ((obj >= 'a' && obj <= 'z') || (obj >= 'A' && obj <= 'Z'))
    {
        return true;
    }
    return false;
}

bool isDigit(char obj)
{
    if ((obj >= '0' && obj <= '9'))
    {
        return true;
    }
    return false;
}

ARITHMETIC returnArithmeticOperator(vector<char> arithmeticOperator)
{
    if (arithmeticOperator.front() == '+')
    {
        return ADDITION;
    }
    if (arithmeticOperator.front() == '-')
    {
        return SUBSTRACTION;
    }
    if (arithmeticOperator.front() == '/')
    {
        return DIVISION;
    }
    if (arithmeticOperator.front() == '*')
    {
        return MULTIPLICATION;
    }
    if (arithmeticOperator.front() == '%')
    {
        return MODULO;
    }

    return NOTARITHMETIC;
}

void removeFromVector(vector<char> &buffer, const char *arr)
{
    int count = 0;
    vector<char> tempBuffer = buffer;
    bool flag = true;
    int i = 0;

    while (flag)
    {
        if (tempBuffer[i] == arr[i] && tempBuffer[i] != '\0')
        {
            count++;
            i++;
        }
        else
        {
            flag = false;
        }
    }

    list<char> copy;

    for (int i = count; i < buffer.size(); i++)
    {
        copy.push_back(tempBuffer[i]);
    }

    for (int i = 0; i < copy.size(); i++)
    {
        char check = copy.front();

        if (check == ' ')
        {
            copy.pop_front();
        }
    }

    buffer.clear();

    int size = copy.size();

    for (int i = 0; i < size; i++)
    {
        if (!copy.empty())
        {
            buffer.push_back(copy.front());
            copy.pop_front();
        }
    }
}

void removeSingleCharacter(vector<char> &buffer)
{

    list<char> copy;

    for (int i = 0; i < buffer.size(); i++)
    {
        copy.push_back(buffer[i]);
    }

    copy.pop_front();

    while (copy.front() == ' ')
    {
        copy.pop_front();
    }

    buffer.clear();

    if (copy.size() != 0)
    {
        int size = copy.size();
        while (copy.size() != 0)
        {
            buffer.push_back(copy.front());
            copy.pop_front();
        }
    }
}

void initializeVector(vector<char> &buffer, const char *arr)
{
    for (int i = 0; i < strlen(arr) + 1; i++)
    {
        buffer.push_back(arr[i]);
    }
}

OPERATOR returnOperatorType(vector<char> arr)
{
    if (arr.front() == '>')
    {
        if (arr[1] == '=')
        {
            return GREATERTHANEQUALTO;
        }
        return GREATERTHAN;
    }

    if (arr.front() == '<' && arr[1] != '-')
    {
        if (arr[1] == '=')
        {
            return LESSTHANEQUALTO;
        }
        return LESSTHAN;
    }

    if (arr.front() == '=')
    {
        return EQUALTO;
    }

    if (arr.front() == '~' && arr[1] == '=')
    {
        return OTHER;
    }

    return NOTOPERATOR;
}

void checkOperator(vector<char> &arr, ofstream &fout)
{
    if (!arr.empty())
    {
        OPERATOR state = NOTOPERATOR;
        bool flag = true;
        int i = 0;

        switch (returnOperatorType(arr))
        {
        case GREATERTHANEQUALTO:
       
            fout << "(" << "RO" << ","
                 << ">=)" << endl;
            state = NOTOPERATOR;
            removeFromVector(arr, ">=");
            break;

        case GREATERTHAN:
            
            fout << "(" << "RO" << ","
                 << ">)" << endl;
            state = NOTOPERATOR;
            removeSingleCharacter(arr);
            break;

        case LESSTHAN:
      
            fout << "(" << "RO" << ","
                 << "<)" << endl;
            state = NOTOPERATOR;
            removeSingleCharacter(arr);
            break;
        case LESSTHANEQUALTO:
        
            fout << "(" << "RO" << ","
                 << "<=)" << endl;
            state = NOTOPERATOR;
            removeFromVector(arr, "<=");
            break;

        case OTHER:
        
            fout << "(" << "RO" << ","
                 << "~=)" << endl;
            state = NOTOPERATOR;
            removeFromVector(arr, "~=");
            break;

        case NOTOPERATOR:
            break;
        }
    }
}

void checkAssignment(vector<char> &arr, ofstream &fout)
{
    if (arr.front() == '<' && arr[1] == '-')
    {
       
        fout << "(" << "ASSIGN" << ", <-)" << endl;
        removeFromVector(arr, "<-");
    }
}

void checkArithmetic(vector<char> &arr, ofstream &fout)
{
    if (!arr.empty())
    {
        ARITHMETIC state = NOTARITHMETIC;
        bool flag = true;
        int i = 0;

        switch (returnArithmeticOperator(arr))
        {
        case ADDITION:
       
            fout << "(" << "ADDITION" << ",+)"<<endl;
            state = NOTARITHMETIC;
            removeSingleCharacter(arr);
            break;
        case SUBSTRACTION:
          
            fout << "(" << "SUBSTRACTION" << ", -)"<<endl;
            state = NOTARITHMETIC;
            removeSingleCharacter(arr);
            break;
        case DIVISION:
         
            fout << "(" << "DIVISION" << ", /)"<<endl;;
            state = NOTARITHMETIC;
            removeSingleCharacter(arr);
            break;
        case MULTIPLICATION:
      
            fout << "(" << "MULTIPLICATION" << ", *)"<<endl;
            state = NOTARITHMETIC;
            removeSingleCharacter(arr);
            break;

        case MODULO:
         
            fout << "(" << "MODULO" << ", % )"<<endl;
            state = NOTARITHMETIC;
            removeSingleCharacter(arr);
            break;
        case NOTARITHMETIC:
            break;
          

        }
    }
}

void checkIdentifierOrKeyword(vector<char> &arr, ofstream &fout)
{
    if (!arr.empty())
    {
        int state = 1;
        vector<char> buffer;
        int a = 0;
        int i = 0;
        bool flag = true;
        char *temp = nullptr;
        while (flag)
        {
            switch (state)
            {
            case 1:
                if (isLetter(arr[i]))
                {
                    buffer.push_back(arr[i]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 4;
                    break;
                }
                break;

            case 2:
                if (isLetter(arr[i]) || isDigit(arr[i]) || arr[i] == '_')
                {
                    buffer.push_back(arr[i]);
                    break;
                }
                else
                {
                    state = 3;
                    break;
                }
            case 3:
                if (returnKeyword(buffer) != 286 && buffer.size() != 1) // It is a keyword
                {
                   

                    fout << "(KEYWORD,";
                    printVector(buffer, fout);
                    fout << ")" << endl;

                    temp = new char[buffer.size() + 1];
                    for (int i = 0; i < buffer.size(); i++)
                    {
                        temp[i] = buffer[i];
                    }
                    removeFromVector(arr, temp);
                    state = 4;
                    delete[] temp;
                    break;
                }
                else
                {
                   
                    fout << "(IDENTIFIER,";
                    printVector(buffer, fout);
                    fout << ")" << endl;

                    temp = new char[buffer.size() + 1];
                    for (int i = 0; i < buffer.size(); i++)
                    {
                        temp[i] = buffer[i];
                    }
                    removeFromVector(arr, temp);
                    delete[] temp;
                    state = 4;
                    break;
                }
            case 4:
                flag = false;
                break;
            }
            i++;
        }
    }
}

void checkDigit(vector<char> &arr, ofstream &fout)
{

    int state = 1;
    bool flag = true;
    vector<char> buffer;
    int i = 0;
    char *temp = nullptr;

    if (!arr.empty())
    {

        while (flag)
        {

            switch (state)
            {
            case 1:
                if (isDigit(arr[i]) || isSign(arr[i]))
                // if (isDigit(arr[i]))
                {
                    state = 2;
                    buffer.push_back(arr[i++]);
                    break;
                }
                else
                {
                    state = 9;
                    break;
                }

            case 2:
                if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else if (arr[i] == '.')
                {
                    buffer.push_back(arr[i++]);
                    state = 4;
                    break;
                }
                else if (arr[i] == '^')
                {
                    buffer.push_back(arr[i++]);
                    state = 3;
                    break;
                }
                else
                {
                    state = 8;
                    break;
                }

            case 3:
                if (isSign(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 5;
                    break;
                }
                else if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 6;
                    break;
                }
                else
                {
                    state = 9;
                    break;
                }

            case 4:
                if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 7;
                    break;
                }
                else
                {
                    state = 9;
                    break;
                }

            case 5:
                if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 6;
                    break;
                }
                else
                {
                    state = 9;
                    break;
                }
            case 6:
                if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 6;
                    break;
                }
                else
                {
                    state = 8;
                    break;
                }

            case 7:
                if (isDigit(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 7;
                    break;
                }
                else if (arr[i] == '^')
                {
                    buffer.push_back(arr[i++]);
                    state = 3;
                    break;
                }
                else
                {
                    state = 8;
                    break;
                }

            case 8:
              
                fout << "(DIGIT,";
                printVector(buffer, fout);
                fout << ")" << endl;

                temp = new char[buffer.size() + 1];
                for (int i = 0; i < buffer.size(); i++)
                {
                    temp[i] = buffer[i];
                }
                removeFromVector(arr, temp);
                delete[] temp;
                state = 9;
                break;

            case 9:
                flag = false;
                break;
            }
        }
    }
}

void checkIfCharacter(vector<char> &arr, ofstream &fout)
{
    int state = 1;
    bool flag = true;
    char delimeter[] = "'";
    int i = 0;
    vector<char> buffer;
    char *temp = nullptr;

    if (!arr.empty())
    {

        while (flag)
        {
            switch (state)
            {
            case 1:

                if (arr[i] == delimeter[0])
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 5;
                    break;
                }
            case 2:
                if (isdigit(arr[i]) || isLetter(arr[i]) || isSpecialCharatcer(arr[i]))
                {
                    buffer.push_back(arr[i++]);
                    state = 3;
                    break;
                }
                else
                {
                    state = 5;
                    break;
                }

            case 3:

                if (arr[i] == delimeter[0])
                {
                    buffer.push_back(arr[i++]);
                    state = 4;
                    break;
                }
                else
                {
                    state = 5;
                    break;
                }
            case 4:
                

                fout << "(Character,";
                printVector(buffer, fout);
                fout << ")" << endl;

                temp = new char[buffer.size() + 1];
                for (int i = 0; i < buffer.size(); i++)
                {
                    temp[i] = buffer[i];
                }
                removeFromVector(arr, temp);
                delete[] temp;
                state = 5;
                break;

            case 5:
                flag = false;
                break;
            }
        }
    }
}

void checkIfString(vector<char> &arr, ofstream &fout)
{
    int state = 1;
    bool flag = true;
    char delimeter = '"';
    int i = 0;
    vector<char> buffer;
    char *temp = nullptr;

    if (!arr.empty())
    {

        while (flag)
        {
            switch (state)
            {
            case 1:

                if (arr[i] == delimeter)
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 5;
                    break;
                }
            case 2:
                if (arr[i] != delimeter && int(arr[i]) != 0)
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 3;
                    break;
                }

            case 3:
                buffer.push_back(arr[i++]);
                state = 4;
                break;

            case 4:
               

                fout << "(String,";
                printVector(buffer, fout);
                fout << ")" << endl;

                temp = new char[buffer.size() + 1];
                for (int i = 0; i < buffer.size(); i++)
                {
                    temp[i] = buffer[i];
                }
                removeFromVector(arr, temp);
                delete[] temp;
                state = 5;
                break;

            case 5:
                flag = false;
                break;
            }
        }
    }
}

void checkIfComment(vector<char> &arr, ofstream &fout)
{
    int state = 1;
    bool flag = true;
    vector<char> buffer;

    int i = 0;
    char *temp;

    if (!arr.empty())
    {
        while (flag)
        {
            switch (state)
            {

            case 1:
                if (arr[i] == '#')
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 4;
                    break;
                }
            case 2:
                if (int(arr[i]) != 0)
                {
                    buffer.push_back(arr[i++]);
                    state = 2;
                    break;
                }
                else
                {
                    state = 3;
                    break;
                }
            case 3:
                if (int(arr[i]) == 0 || int(arr[i]) == 9)
                {
                
                    temp = new char[buffer.size() + 1];
                    for (int i = 0; i < buffer.size(); i++)
                    {
                        temp[i] = buffer[i];
                    }
                    removeFromVector(arr, temp);
                    delete[] temp;
                    state = 4;
                    break;
                }
                else
                {
                    state = 4;
                    break;
                }

            case 4:
                flag = false;
                break;
            }
        }
    }
}

void isSpecialCharacter(vector<char> &arr, ofstream &fout)
{
    if (arr.front() == ':')
    {
        
        fout << ("(COLON,:)");
        fout<<endl;
        removeSingleCharacter(arr);
    }
    if (arr.front() == ';')
    {
  
        fout << ("(SEMICOLON,;)");
        fout<<endl;
        removeSingleCharacter(arr);
    }
    if (arr.front() == ',')
    {
        
        fout << ("(COMMA,,)");
        fout<<endl;
        removeSingleCharacter(arr);
    }
    if (arr.front() == '#')
    {
        // cout << ("(SPECIAL,#)");
        // fout << ("(HASH,#)");
        // fout<<endl;
        // removeSingleCharacter(arr);
    }
}

int main(int argc, char * argv[])
{

    char *buffer = new char[100];
    vector<char> arr;
    ifstream fopen;
    ofstream fout;
    fopen.open(argv[1]);
    fout.open("output.txt");
    if (fopen.is_open())
    {

        while (!fopen.eof())
        {
            fopen.getline(buffer, 100);
            initializeVector(arr, buffer);
        }
    }

    while (arr.size() >= 1)
    {
         if (int(arr[0]) == 0 || int(arr[0]) == 9)
        {
            removeSingleCharacter(arr);
        }
        checkIfComment(arr, fout);
        checkIdentifierOrKeyword(arr, fout);
        checkArithmetic(arr,fout);
        isSpecialCharacter(arr, fout);
        checkAssignment(arr, fout);
        checkDigit(arr, fout);
        checkIfCharacter(arr, fout);
        checkIfString(arr, fout);
        checkOperator(arr, fout);
    

     
        
    }

 
   


    


    fopen.close();
    fout.close();

    return 0;
}