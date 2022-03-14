#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;
using namespace stack_namespace;

// Func Declarations
void OperatorToStack(string& p, const string& o, Stack<string>& st);
bool IsOperator(const string& o);
void PrintAndPop(string& p, Stack<string>& st);
double PostfixEvaluation(string p, bool& error);
bool HasVariables(string s);
bool CheckInvalidInfix(string p);

int main()
{
  Stack<string> stack; // stack of strings for infix to postfix conversion
  string line, s, last; // string line for each line read, s for each word in line
                        // last is the word read in previous iteration of while loop

  // INFIX TO POSTFIX CONVERSION
  while (! cin.eof())
  {
    string postfix; // Stores postfix notation for the line, appends as we go
    bool VariableOperands = false; // Default that this infix only contains numerical
                                   // operands

    cout << "Enter infix expression (\"exit\" to quit): \n";
    getline(cin, line);      // read in until newline
    istringstream iss(line); // create string stream for line

    while (iss >> s) // WHILE LINE IS STILL BEING READ
    {
      if (s == "exit") // exit program
        return 0;
      if (s == "(") // opening parentheses case
        stack.push("(");
      else if ( IsOperator(s) ) // operator case
        OperatorToStack(postfix, s, stack);
      else if ( s == ")" ) // closing parentheses case
      {
        if ( IsOperator(last) ) // If last iteration we read in an operator
        {
          cout << "\nError encountered. Last input processed was an operator but "
               << "current input is ')'.\n";
          return 1;
        }
        else // Else, we are good to proceed
        {
          if (stack.empty()) // Cannot call top function on empty stack,
          {                  // check if empty first
            last = s;
            continue;        // Update last and continue to next iteration
          }
          while (stack.top() != "(") // Now, we can check if top of stack is "("
          {
            PrintAndPop(postfix, stack); // If not, append to infix and pop unti
            if (stack.empty())         // it is empty
            {
              cout << "\nError encountered. Stack empty and '(' expected.\n";
              return 2; // Should find a matching parenthesis in the stack
            }
          }
          stack.pop(); //Pop stack one more time to discard the parentheses
        }
      } // END OF CLOSING PARENTHESES CASE
      else           // operand case
      {
        stack.push(s); // Push operand to stack
        if (HasVariables(s)) // Check here to see if there is a variable operand
          VariableOperands = true;
      }

      last = s;      // Update last string before next iteration
    } // END OF INNER WHILE LOOP -- FOR INDIVIDUAL LINE

    if ( IsOperator(last) || last == "(") // If made it through line and last word
    {                                     // was an operator or parenthesis, error
      cout << "\nError encountered. Last input was operator or '('.\n";
      return 3;
    }
    else // Otherwise, PrintAndPop the remainder of the stack
    {
      while (! stack.empty())
      {
        if (stack.top() == "(") // If there is an opening parenthesis left in the
        {                       // stack, also an error
          cout << "\nError encountered. Remaining '(' in stack.\n";
          return 4;
        }
        PrintAndPop(postfix, stack);
      }
    } // MADE IT THROUGH STACK FOR A LINE, infix expression for that line currently
      // stored in string infix

    // PRINT POSTFIX STRING to stdout
    cout << "Postfix expression: " << postfix << "\n";

    // PRINT POSTFIX EVALUATION to stdout
    if (! VariableOperands) // If there were no variable operands in the line
    {                       // then we can also perform postfix evaluation and print
      bool PostfixEvalFailure = false;
      double d = PostfixEvaluation(postfix, PostfixEvalFailure);

      if (PostfixEvalFailure == true) // If there was an error in postfix evalution
        return d;                     // error, return to end program
      else                            // Else, print result of postfix evaluation
        cout << "Postfix evaluation: " << postfix << " = " << d << "\n";
    }
    else
    {
      if (CheckInvalidInfix(postfix)) // Check if infix expression is valid for
        return 7;                     // expression with variables -- numerical
                                      // expressions checked in PostfixEvaluation()
      cout << "Postfix evaluation: " << postfix << " = " << postfix << "\n";
    }
  } // END OF WHILE LOOP

  return 0; // If end of input stream and no "exit" is encountered, assume termination
} // END OF MAIN


//FUNCTIONS
// If operator encountered in input stream, update stack appropriately
void OperatorToStack(string& p, const string& o, Stack<string>& st)
{
  while (! st.empty() ) // Check if stack is empty first -- cannot check top()
  {                     // on an empty stack
    if (st.top() == "(")
      break;
    else if ( (o == "*" || o == "/") && (st.top() == "+" || st.top() == "-") )
      break;
    else
      PrintAndPop(p, st); // Print and pop until one of these conditions are made
  }
  st.push(o); // Finally, push o onto the stack
}

// Return true if character is an operator, false otherwise
bool IsOperator(const string& o)
{
  if (o == "+" || o == "-" || o == "*" || o == "/")
    return true;
  else
    return false;
}

// Print top of stack and pop it
// Print here is appending the top of stack to in string,
// We could alter this append to a cout statement to print in string as code goes
void PrintAndPop(string& p, Stack<string>& st)
{
  p.append(st.top());
  p.append(" ");
  st.pop();
}

// Perform postfix evaluation from infix string
double PostfixEvaluation(string p, bool& error)
{
  Stack<double> operand;   // create operand stack
  istringstream iss(p); // create string stream for line
  string s;
  double a, b, c;

  while (iss >> s)
  {
    if (! IsOperator(s)) // NOT AN OPERATOR
      operand.push( stod(s) ); // convert to a double and push into stack operand
    else //IS AN OPERATOR
    {
      if (operand.size() < 2) // Need two arguments for a binary operator
      {                       // End program
        error = true;
        cout << "\nError encountered in postix evaluation. Operator missing operand.\n";
        return 5;
      }
      else
      {
        a = operand.top(); // store doubles of last two operands in stack
        operand.pop();     // and pop them off the stack
        b = operand.top();
        operand.pop();

        if (s == "+")      // NUMERIC EVALUATION
          c = b + a;
        else if (s == "-")
          c = b - a;
        else if (s == "*")
          c = b * a;
        else  // s == "/"
          c = b / a;

        operand.push(c);   // Push resulting double back onto the stack
      }
    }
  } // END OF WHILE LOOP

  if (operand.size() > 1) // If more than 1 operand remaining after evaluation,
  {                       // error, end program
    error = true;
    cout << "\nError encountered. >1 operand remains after postix evaluation.\n";
    return 6;
  }
  else if (operand.size() == 1) // If exactly one operand, return that
    return operand.top();
  else                          // If no operand, return 0
    return 0;
}


// If passed in string has any letters or an underscore, return true
// -- makes it a variable operand rather than numerical
// (This works assuming we are passed in valid operand names)
bool HasVariables(string s)
{
  for (int i = 0; i < s.size(); i++) //Iterate through string and check characters
  {
    if ( ((int) s[i] >= 65 && (int) s[i] <= 90) || ((int) s[i] >= 97 && (int) s[i] <= 122) ||
         ((int) s[i] == 95) )
      return true; //Return true if there is a letter or underscore
  }
  return false; //else, it is numerical
}

// Numerical infix expression will be checked through postfix evaluations
// But this function will chceck syntax of any infix expression (including
// expressions containing variables) to see if it will calculate properly
bool CheckInvalidInfix(string p)
{
  Stack<string> check;
  istringstream iss(p); // create string stream for line
  string s;

  while (iss >> s)
  {
    if (! IsOperator(s)) // NOT AN OPERATOR
      check.push(s); // convert to a double and push into stack operand
      else // IS AN OPERATOR
      {
        if (check.size() < 2) // Need two arguments for a binary operator
        {                     // End program
          cout << "\nError. Operator missing corresponding operand(s) in infix "
               << "expression with variables.\n";
          return true;
        }
        else               // Mock postfix evaluation -- not actually calculating result
          check.pop();     // POP ONCE, instead of popping twice, performing operation,
                           // and then pushing back into stack
      }
  } // END OF WHILE LOOP

  if (check.size() > 1) // If more than 1 operand remaining after evaluation,
  {                       // error, end program
    cout << "\nError encountered. Operand missing corresponding operator in infix "
         << "expression with variables.\n";
    return true;
  }
  else // Postfix expression WILL work correctly for infix string
    return false;
}
