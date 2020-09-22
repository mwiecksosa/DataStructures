/**
 * @file proj3.cpp
 * \mainpage
 *
 * CISC 2200, Data Structures<br>
 * Project 2: Recognizing Infix Arithmetic Expressions<p>
 *
 * Brief discussion
 *
 * Program asks user for input of an arithmetic expression and returns its result
 *
 * @author Michael Wieck-Sosa
 * @date March 20, 2019
 */

 /*
  * includes
  */

#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

/**
 * Using integer value type for stacks and functions defined below
 */
using ValueType = int;



/**
 * @class IllegalExprException
 * Exception class thrown by illegal expression when operator not + - * /
 */
class IllegalExprException : public runtime_error
{
public:
	/**
	* Constructor for IllegalExprException
	*
	*@constructor IllegalExprException
	*/
	IllegalExprException() : runtime_error("Illegal expression: operator must be + - * /") {}
};

/**
 * @class ZeroDivideException
 * Exception class thrown by division by zero
 */
class ZeroDivideException : public runtime_error
{
public:
	/**
	* Constructor for ZeroDivideException
	*
	*@constructor ZeroDivideException
	*/
	ZeroDivideException() : runtime_error("Illegal expression: attempted to divide by zero") {}
};

/**
 * @class missingOperand
 * Exception class thrown by missing operand
 */
class missingOperand : public runtime_error
{
public:
	/**
	* Constructor for missingOperand
	*
	*@constructor missingOperand
	*/
	missingOperand() : runtime_error("Illegal expression: missing operand") {}
};

/**
 * @class missingOperator
 * Exception class thrown by missing operator
 */
class missingOperator : public runtime_error
{
public:
	/**
	* Constructor for missingOperator
	*
	*@constructor missingOperator
	*/
	missingOperator() : runtime_error("Illegal expression: missing operator") {}
};

/**
 * @class missingLeftParen
 * Exception class thrown by missing left parenthesis
 */
class missingLeftParen : public runtime_error
{
public:
	/**
	* Constructor for missingLeftParen
	*
	*@constructor missingLeftParen
	*/
	missingLeftParen() : runtime_error("Illegal expression: missing left parenthesis") {}
};

/**
 * @class missingRightParen
 * Exception class thrown by missing right parenthesis
 */
class missingRightParen : public runtime_error
{
public:
	/**
	* Constructor for missingRightParen
	*
	*@constructor missingRightParen
	*/
	missingRightParen() : runtime_error("Illegal expression: missing right parenthesis") {}
};



/**
 * Determine the value of an infix expression
 *
 * @param expr a string, supposedly representing an infix expression
 * @return the value of <code>expr</code>
 * @throw IllegalExprException if <code>expr</code> is not a legal infix
 * expression
 * @throw ZeroDivideException if <code>expr</code> involves a division
 * by zero
 * @throw missingOperand if <code>expr</code> has no second operand, aka
 * if valStack too short
 * @throw missingOperator if <code>expr</code> has no operator
 * @throw missingLeftParen if <code>expr</code> has a missing left parenthesis
 * @throw missingRightParen if <code>expr</code> has a missing right parenthesis
 */
ValueType processExpression(const string& expr); //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen);

/**
 * Boolean of whether response is valid input 'Y' or 'N'
 *
 * @param response a char representing the user input
 */
bool isValidResponse(char response);

/**
 * Boolean of whether response is 'Y'
 *
 * @param response a char representing the user input
 */
bool isYesResponse(char response);

/**
 * Function to determine the precedence of operators in given arithmetic expression
 *
 * @param op a char representing the operator
 */
int precedence(char op);

/**
 * Void function returning help output, if user input 'Y' for help request
 *
 * @param void represents no input necessary
 */
void provideHelpIfNecessary(void);

/**
 * Executes calculation of arithmetic expression
 *
 * @param valstack a stack of ValueType = int, representing stack of values
 * @param opStack a stack of char, representing stack of operators
 * @throw IllegalExprException if <code>expr</code> is not a legal infix
 * expression
 * @throw ZeroDivideException if <code>expr</code> involves a division
 * by zero
 * @throw missingOperand if <code>expr</code> has no second operand, aka
 * if valStack too short
 * @throw missingOperator if <code>expr</code> has no operator
 * @throw missingLeftParen if <code>expr</code> has a missing left parenthesis
 * @throw missingRightParen if <code>expr</code> has a missing right parenthesis
 */
void execute(stack<ValueType>& valstack, stack<char>& opStack); //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen);

/**
 * Does operation of two operands
 *
 * @param operandL a ValueType = int, representing the left operand
 * @param operation a char, representing the operation
 * @param operandR a ValueType = int, representing the right operand
 * @throw IllegalExprException if <code>expr</code> is not a legal infix
 * expression
 * @throw ZeroDivideException if <code>expr</code> involves a division
 * by zero
 * @throw missingOperand if <code>expr</code> has no second operand, aka
 * if valStack too short
 * @throw missingOperator if <code>expr</code> has no operator
 * @throw missingLeftParen if <code>expr</code> has a missing left parenthesis
 * @throw missingRightParen if <code>expr</code> has a missing right parenthesis
 */
ValueType doOperation(ValueType operandL, char operation, ValueType operandR); //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen);

int main(void)
{
	//provideHelpIfNecessary();

	//while (true) {
		cout << "Expression? ";
		string myExpr;                    // holds the supposed expression

		getline(cin, myExpr);
		if (myExpr.length() == 0) {
			cout << "Length of infix expression is 0" << endl;
			//break;
		}
		cout << "Trying to process expression..." << endl;
		try {
			cout << "Calculating infix expression..." << endl;
			ValueType result = processExpression(myExpr);
			cout << "Done calculating..." << endl;
			cout << "Result is: " << result << endl;
		}
		catch (IllegalExprException& illegalExpr) {
			cerr << "Exception: " << illegalExpr.what() << endl;
		}
		catch (ZeroDivideException& divByZero) {
			cerr << "Exception: " << divByZero.what() << endl;
		}
		catch (missingOperand& missOperand) {
			cerr << "Exception: " << missOperand.what() << endl;
		}
		catch (missingOperator& missOperator) {
			cerr << "Exception: " << missOperator.what() << endl;
		}
		catch (missingLeftParen& missLeftP) {
			cerr << "Exception: " << missLeftP.what() << endl;
		}
		catch (missingRightParen& missingRightP) {
			cerr << "Exception: " << missingRightP.what() << endl;
		}
	//} // end while
	cout << "Program is done..." << endl;
} // end main

void provideHelpIfNecessary(void)
{
	char response = -1;
	while (!isValidResponse(response)) {
		cout << "Do you need help (Y/N)?";
		cin >> response;
		if (isValidResponse(response)) {
			if (isYesResponse(response)) {
				cout << "Enter an infix expression at the prompt." << endl;
				cout << "The program will tell you its value." << endl;
				cout << "To stop the program, just hit 'return' at the prompt." << endl;
				//will exit while loop because 'Y' is valid response
			}
			//else do nothing because 'N' for no help is the only other valid response
			//will exit while loop because 'N' is valid response
		}
		else
			cout << "Response must be 'Y' or 'N'." << endl; //return to beginning of while loop
	}
} // end provideHelpIfNecessary

ValueType processExpression(const string& expr) //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen)
{
	//stack for ValueType = int values
	stack<ValueType> myValStack;
	//stack for operators
	stack<char> myOpStack;


	unsigned int i;
	for (i = 0; i < expr.length(); i++) {
		//skip if current element is a space
		if (expr[i] == ' ')
			continue;
		//push to op stack if current element is opening brace
		else if (expr[i] == '(') {
			myOpStack.push(expr[i]);
		}
		//push to val stack if current element is a digit
		else if (isdigit(expr[i]))
			myValStack.push(expr[i]);
		//execute if current element is a closing brace
		else if (expr[i] == ')') {
			//while not empty and before opening brace execute algebraic expression
			while (!myOpStack.empty() && myOpStack.top() != '(') {
				execute(myValStack, myOpStack);
			}
			myOpStack.pop(); //pop the opening brace
		}
		//else, current element is an operator + - * /
		else {
			//while top of op stack has >= precedence to current element operator
			//apply operator on the top of op stack to the top 2 elements of val stack
			while (!myOpStack.empty() && precedence(myOpStack.top()) >= precedence(expr[i])) {
				execute(myValStack, myOpStack);
			}
			myOpStack.push(expr[i]);
		}
	}

	//apply remaining operations to remaining values
	while (!myOpStack.empty())
		execute(myValStack, myOpStack);

	return myValStack.top();
}

bool isValidResponse(char response)
{
	if (response == 'Y' || response == 'N')
		return true;
	else
		return false;
} // end isValidResponse

bool isYesResponse(char response)
{
	if (response == 'Y')
		return true;
	else
		return false;
} // end isYesResponse

int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
} // end precedence

void execute(stack<ValueType>& valStack, stack<char>& opStack) //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen)
{
	if (valStack.size() >= 2 && opStack.size() >= 1) {
		ValueType myOperandR = valStack.top(); //right operand <- top of value stack
		valStack.pop();
		ValueType myOperandL = valStack.top(); //left operand <- new top of value stack
		valStack.pop();
		char myOperation = opStack.top(); //oper is top of op stack
		opStack.pop();
		valStack.push(doOperation(myOperandL, myOperation, myOperandR));
	}
	//exception: only 1 operand, 1+ operators
	else if (valStack.size() == 1 && opStack.size() >= 1) {
		throw missingOperand();
	}
	//only 1 operand, no operator => return top of valStack
	else if (valStack.size() == 1 && opStack.size() == 0) {
		ValueType myOperand = valStack.top();
		valStack.pop();
		valStack.push(myOperand);
	}
	else if (valStack.size() >= 2 && opStack.size() == 0) {
		throw missingOperator();
	}

} // end execute


ValueType doOperation(ValueType operandL, char operation, ValueType operandR) //throw (IllegalExprException, ZeroDivideException, missingOperand, missingOperator, missingLeftParen, missingRightParen)
{
	if (operation == '+')
		return operandL + operandR;
	else if (operation == '-')
		return operandL - operandR;
	else if (operation == '*')
		return operandL * operandR;
	else if (operation == '/') {
		if (operandR == 0)
			throw ZeroDivideException();
		else
			return operandL / operandR;
	}
	else
		throw IllegalExprException();
} //end doOperation
