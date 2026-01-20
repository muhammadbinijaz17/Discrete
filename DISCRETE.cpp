#include<iostream>
#include<cstring>
#include<cmath>
#include<fstream>

using namespace std;

//max len of expresssion
const int exp_s = 100;

//stack for operator
char cstack[exp_s];
//stack empty
int ctop = -1;

//stack for integer 0 or 1
int istack[exp_s];
int itop = -1;

//transfer char to stack
void pushch(char a)
{	//if not exceed the stack than
    if (ctop < exp_s - 1)
    {	//for next 
        ctop++;
        //add character
        cstack[ctop] = a;
    }
}

//exit a value
char popch()
{	// if char in stack greater than 0
    if (ctop >= 0)
    {	//return the value then n decrease the top as well
        return cstack[ctop--];
    }
    else
    {	// null
        return '\0';
    }
}

//only show the top value
char peekch()
{
    if (ctop >= 0)
    {
        return cstack[ctop];
    }
    else
    {
        return '\0';
    }
}
//check wheterher the char stack empty or not
bool ch_empty()
{
    if (ctop == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// psuck int to a stack
void push(int a)
{
    if (itop < exp_s - 1)
    {
        itop++;
        istack[itop] = a;
    }
}
//exit or pop the top value
int pop()
{
    if (itop >= 0)
    {
        return istack[itop--];
    }
    else
    {
        return 0;
    }
}
//true if uppercase
bool var(char a)
{
    if (a >= 'A' && a <= 'Z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//check priority of the operators n return value
int pri(char a)
{
    if (a == '!')
    {
        return 3;
    }
    if (a == '&')
    {
        return 2;
    }
    if (a == '|')
    {
        return 1;
    }

    if (a == '>')
    {
        return 0;
    }
    if (a == '=')
    {
        return 0;
    }

    return -1;
}
//check if correct or incorrect
bool valid(const char in[])
{	//store len of the input char aaray
    int len = strlen(in);
	//if zero 
    if (len == 0)
    {
        cout << "Invalid entry" << endl;
        return 0;
    }
	
    int par = 0;	//for paranthesis
    
    char lst = '\0'; //last null char
    
    bool any = 0;	
	//loop until the values of the input charater by character
    for (int i = 0; i < len; i++)
    {	//c store value
        char c = in[i];
        //space ignore
        if (c == ' ') 
        {
            continue;
        }
		// any become 1 in loop
        any = 1;
        //reject other than theses variables
        if (!((c >= 'A' && c <= 'Z') || c == '!' || c == '&' || c == '|' || c == '>' || c == '=' || c == '(' || c == ')'))
        {
            cout << "Invalid entry" << endl;
            return 0;
        }
		//par increae means baracket starts
        if (c == '(') 
        {
            par++;
        }
        //decrease when close
        else if (c == ')') 
        {
            par--;
        }
		//less than zero means invalid bracker entry
        if (par < 0)
        {
            cout << "Invalid entry" << endl;
            return 0;
        }
		
        bool ops = (c == '&' || c == '|' || c == '>' || c == '=');
        bool lop = (lst == '&' || lst == '|' || lst == '>' || lst == '=');

        if (ops && lop)
        {
            cout << "Invalid entry" << endl;
            return 0;
        }

        if (ops && (lst == '\0' || lst == '('))
        {
            cout << "Invalid entry" << endl;
            return 0;
        }

        if (c == ')' && lop)
        {
            cout << "Invalid entry" << endl;
            return 0;
        }

        lst = c;
    }

    if (par != 0)
    {
        cout << "Invalid entry" << endl;
        return 0;
    }

    if (lst == '&' || lst == '|' || lst == '>' || lst == '=' || lst == '!')
    {
        cout << "Invalid entry" << endl;
        return 0;
    }
    //if all spaces
    if(!any) 
    {
        cout << "Invalid entry" << endl;
        return 0;
    }

    return 1;
}
void postfix(const char in[], char outexpr[])
{
    ctop = -1;
    int j = 0;
    for (int i = 0; i < strlen(in); i++)
    {
        char ch = in[i];
        if (ch == ' ')
        {
            continue;
        }

        if (var(ch))
        {
            outexpr[j] = ch;
            j++;
        }
        else if (ch == '(')
        {
            pushch(ch);
        }
        else if (ch == ')')
        {
            while (!ch_empty() && peekch() != '(')
            {
                outexpr[j] = popch();
                j++;
            }
            popch();
        }
        else
        {
            
        while (!ch_empty() && peekch() != '(' && pri(peekch()) >= pri(ch))
            {
                outexpr[j] = popch();
                j++;
            }
            pushch(ch);
        }
    }
     while (!ch_empty())
    {
        outexpr[j] = popch();
        j++;
    }
    outexpr[j] = '\0';
}

int  varcount(const char input[], char vars[])
{
    int count = 0 ;
    int i = 0 ;
    while (input[i] != '\0')
    {
        char c = input[i] ;
        if (c >= 'A' && c <= 'Z')
        {
            bool vr = 0;
            for (int k = 0; k < count; k++)
            {
                if (vars[k] == c)
                {
                    vr = 1 ;
                    break;
                }
            }
            if (vr == 0)
            {
                vars[count] = c;
                count++;
            }
        }
    i++;
    }
    return count;
}

int evaluate(char postfix[],char vars[],int vals[], int vcount)
{
    itop = -1;
    for (int i = 0; i < strlen(postfix); i++)
    {
        char ch = postfix[i];
        if (var(ch))
        {
            int val = 0;
            for (int k = 0; k< vcount; k++)
            {
                if (vars[k] == ch)
                {
                    val = vals[k];
                    break;
                }
            }
            push(val);
        }
        else
        {
            if (ch == '!')
            {
                int a = pop();
                if (a == 0)
                {
                    push(1);
                }
                else
                {
                    push(0); 
                }
            }
            else
            {
                int b = pop();
                
                int a = pop();


                if (ch == '&')
                {
                    if (a == 1 && b == 1)
                    {
                        push(1);
                    }
                    else
                    {
                        push(0);
                    }
                }
                else if (ch == '|')
                {
                    if (a == 1 || b == 1)
                    {
                        push(1);
                    }
                    else
                    {
                        push(0);
                    }
                }
                else if (ch == '>')
                {
                    if (a == 1 && b == 0)
                    {
                        push(0);
                    }
                    else
                    {
                        push(1);
                    }
                }
                else if  (ch == '=')
                {
                    if (a == b)
                    {
                        push(1);
                    }
                    else
                    {
                        push(0);
                    }
                }
            }
        }
    }
    return pop() ;
    
}

void truthtable(char input[])
{
    while(1)
    {
        cout << endl << " Enter An Expression : " ;
        cin.getline(input, exp_s);
        if(valid(input))
        {
            break;
        }
    }

    char expr[exp_s];
    postfix(input, expr);

    char vars[exp_s];
    int vcount = varcount(input, vars);

    if (vcount > 5)
    {
        cout << "Invalid entry" << endl;
        return;
    }

    for (int i = 0; i < vcount; i++)
    {
        cout << vars[i] << "\t";
    }
    cout << "Result" << endl;
    cout << "-----------------------------------" << endl;

    int zeros[exp_s]; 
    for(int k=0; k<vcount; k++) 
    {
        zeros[k] = 0; 
    }    
    int trow = pow(2, vcount); 
    
    for (int row = 0; row < trow; row++)
    {        
          for (int j = 0; j < vcount; j++)
        {
            cout << zeros[j] << "\t";
        }
        
      int result = evaluate(expr,vars,zeros,vcount);
        cout << result << endl;
        
        for (int k = vcount-1;k >= 0; k--)
        {
            if (zeros[k] == 0)
            {
                zeros[k] = 1;
                break; 
            }
            else
            {
                zeros[k] = 0; 
            }
        }
    }
    
    char fchoice;
    cout << "Do you want to save results? (Y/N): ";
    cin >> fchoice;
    
    if (fchoice == 'Y' || fchoice == 'y')
    {
        char fname[50];
        cout << "Enter filename (e.g output.txt): ";
        cin >> fname;

        ofstream f;
        f.open(fname);
        if(f.is_open())
        {
            f << "TRUTH TABLE FOR : " << input << endl << endl;
            for (int i = 0; i < vcount; i++)
            {
                f << vars[i] << "\t";
            }
            f << "Result" << endl << "-----------------------------------" << endl;

            for(int k=0; k<vcount; k++) zeros[k] = 0;
            
            for (int row = 0; row < trow; row++)
            {
                for (int j = 0; j < vcount; j++)
                {
                    f << zeros[j] << "\t";
                }
                int result = evaluate(expr,vars,zeros,vcount);
                f << result << endl;
                
                for (int k = vcount-1;k >= 0; k--)
                {
                    if (zeros[k] == 0)
                    {
                        zeros[k] = 1;
                        break;
                    }
                    else
                    {
                        zeros[k] = 0;
                    }
                }
            }
            f.close();
            cout << "Saved to " << fname << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
}

void equivalnce()
{
    char expr1[exp_s]; 
    char pfexpr1[exp_s];
    
    char expr2[exp_s]; 
    char pfexpr2[exp_s];

    cout << "\nLOGICAL EQUIVALENCE CHECKER" << endl;
    
    cin.ignore();
    while(1)
    {
        cout << "Enter Expression 1 : ";
        cin.getline(expr1, exp_s);
        if(valid(expr1))
        {
            break;
        }
    }
    postfix(expr1, pfexpr1); 

    while(1)
    {
        cout << "Enter Expression 2 : ";
        cin.getline(expr2, exp_s);
        if(valid(expr2))
        {
            break;
        }
    }
    postfix(expr2, pfexpr2); 

    char vars[5];
    int vcount = 0;

    int k = 0;
    while(expr1[k] != '\0')
    {
        char c = expr1[k];
        if(c >= 'A' && c <= 'Z') 
        {
            bool found = 0;
            for(int j=0; j<vcount; j++) 
            {
                if(vars[j] == c) 
                {
                    found = 1;
                }
            }
            
            if(found == 0) 
            { 
                if (vcount >= 5) 
                {
                    cout << "Invalid entry" << endl;
                    return;
                }
                vars[vcount] = c; 
                vcount++; 
            }
        }
        k++;
    }

    k = 0;
    while(expr2[k] != '\0')
    {
        char c = expr2[k];
        if(c >= 'A' && c <= 'Z') 
        {
            bool found = 0;
            for(int j=0; j<vcount; j++)
            {
                if(vars[j] == c) 
                {
                    found = 1;
                }
            } 

            if(found == 0) 
            { 
                if (vcount >= 5) 
                {
                    cout << "Invalid entry" << endl;
                    return;
                }
                vars[vcount] = c; 
                vcount++; 
            }
        }
        k++;
    }

    int zeros[5];
    for(int i=0; i<vcount; i++)
    {
        zeros[i] = 0; 
    }
    
    int trows = pow(2, vcount); 
    bool equivalent = 1;            
    int diff_row[5];
    int res1 = 0, res2 = 0;

    cout << endl << "Comparing" << endl;

    for(int row=0; row < trows; row++)
    {
        int result1 = evaluate(pfexpr1, vars, zeros, vcount);
        int result2 = evaluate(pfexpr2, vars, zeros, vcount);

        if(result1 != result2)
        {
            cout << "------------------------------------------------" << endl <<endl;
            cout << "DIFFERENCE " << endl <<endl ;
            cout << "At row  " <<endl ;
            for(int j=0;j<vcount; j++) 
            {
                cout << vars[j] << "=" << zeros[j] << " ";
                diff_row[j] = zeros[j];
            }
            cout << endl;
            cout << "Expression 1 gives: " << result1 << endl <<endl;
            cout << "Expression 2 gives: " << result2 << endl <<endl;
            res1 = result1;
            res2 = result2;
            
            equivalent = 0; 
            break; 
        }
        for (int k = vcount -1; k>= 0; k--)
        {
            if (zeros[k] == 0) 
            { 
                zeros[k] = 1 ; 
                break; 
            }
            else zeros[k] = 0 ;
        }
    }

    cout << "----------------------------------------------" << endl;
    if (equivalent)
    {
        cout << "RESULT: LOGICALLY EQUIVALENT" << endl;
        cout << "They act exactly the same in every scenario." << endl;
    }
    else
    {
        cout << "RESULT: NOT EQUIVALENT" << endl;
    }

    char choice;
    cout << "Do you want to save results? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        char fname[50];
        cout << "Enter filename (e.g., output.txt): ";
        cin >> fname;

        ofstream f;
        f.open(fname);
        if(f.is_open())
        {
            f << "Equivalence Check Report " << endl;
            f << "Expr 1: " << expr1 << endl;
            f << "Expr 2: " << expr2 << endl << endl;

            if (equivalent)
            {
                f << "RESULT: LOGICALLY EQUIVALENT" << endl;
                f << "Both expressions are identical in all scenarios." << endl;
            }
            else
            {
                f << "RESULT: NOT EQUIVALENT" << endl;
                f << "Difference found at row: ";
                for(int j=0; j<vcount; j++) 
                {
                      f << vars[j] << "=" << diff_row[j] << " ";
                }
                f << endl;
                f << "Expr1: " << res1 << " | Expr2: " << res2 << endl;
            }
            f.close();
            cout << "Saved to " << fname << endl;
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
}

void view()
{
    char filename[50];
    cout << "\nEnter the filename to open: ";
    cin >> filename;
    ifstream f(filename);

    if (!f.is_open())
    {
        cout << "Could not open file  " << filename << " ." << endl;
        return; 
    }
    cout <<endl << "-----------------------------------------------" << endl;  
    char line[200]; 
    while(f.getline(line, 200))
    { 
        cout << line << endl; 
    } 

    cout <<"-----------------------------------------------" << endl;
    f.close();
}

int main() 
{
    char choice;
    char input[exp_s]; 

    do {
        cout << "==========================" << endl;
        cout << "\tMAIN MENU" << endl;
        cout << "==========================" << endl;
        cout << "1. GENERATE TRUTH TABLE" << endl << endl;
        cout << "2. CHECK EQUIVALENCE " << endl << endl;
        cout << "3. VIEW / LOAD SAVED RESULTS " << endl << endl;
        cout << "4. EXIT " << endl << endl;
        cout << "==========================" << endl;
        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;

        switch (choice) 
        {
            case '1': 
            {
                cin.ignore(); 
                truthtable(input); 
                break;
            }
            case '2': 
            {
                 equivalnce();
                 break;
            }

            case '3': 
            {
                view();
                break;
            }

            case '4':
            {
                cout << "  Goodbye" << endl;
                break;
            }
            default: 
            {
                cout << "Invalid Choice Please try again" << endl;
            }
        } 
    } while (choice != '4');

    return 0;
}
