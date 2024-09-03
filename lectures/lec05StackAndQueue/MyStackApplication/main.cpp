/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "SimpleTest.h"
#include "stack.h"
using namespace std;


/**
 * if @param ch is (, ), +, -, *, /,  ' '(whitespace character)
 *    and number between 0 and 9,
 *    then @return true;
 * or @return false.
 */
bool isCharacterLegal(char ch){
    if(isdigit(ch)){
        return true;
    }
    if(ch=='(' || ch == ')' || ch=='+' ||
       ch=='-' || ch == '*' || ch=='/'||
       ch==' ' ){
        return true;
    }
    return false;
}

/**
 * if each char in @param expression is ( ) + - * /  ' '(whitespace character)
 * or the number between 0 and 9,then @return true.
 * otherwise @return false
 */
bool isExpressionLegal(const string & expression){
    for(char ch:expression){
        if(!isCharacterLegal(ch)){
            return false;
        }
    }
    return true;
}

/**
 *
 * @param opertor1 is the top operator in the operator stack.
 * it can be (, +, -, *, /
 * @param opertor2 is the operator that is just scanned.
 * it can be  +, -, *, /
 * @return if the priority of  opertor1 is smaller than the one
 * of opertor2,then return -1; bigger,return 1.
 * There are NO EQUAL priority.
 */
int characterPriority(char opertor1,char opertor2){
    if(opertor1=='('){
        return -1;
    }
    if(opertor1=='+' || opertor1=='-'){
        if(opertor2=='+' || opertor2=='-'){
            return 1;
        }else{//opertor2=='*' || opertor2=='/'
            return -1;
        }

    }

    //opertor1=='*' || opertor1=='/'
    return 1;
}




/**
 *
 * @return posfix expression corressponds to @param infix
 */
string infixToPostfix(const string & infix){
    Stack <char> opertorStack;
    string postfix;
    char lastCh = ' ';
    for(char ch : infix){

        //operator
        if(isdigit(ch)){
            postfix+=ch;
        }else{//operand
            if(isdigit(lastCh)){
                postfix+=' ';//distinguish operands!!!
            }
            if(ch=='('){
                opertorStack.push(ch);
            }else if(ch==')'){
                while(true){
                    if(opertorStack.isEmpty()){
                        cout<<"the infix expression is ILLEGAL";
                        return "";
                    }
                    char top = opertorStack.pop();
                    if(top=='('){
                        break;
                    }
                    postfix+=top;
                    postfix+=' ';
                }
            }else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' ) {
                while(!opertorStack.isEmpty()){
                    //the priority of the top operator in the stack is smaller than the one of ch
                    if(characterPriority(opertorStack.peek(),ch)<0){
                        break;
                    }else{
                        postfix+=opertorStack.pop();
                        postfix+=' ';
                    }
                }
                opertorStack.push(ch);
            }
            //omit the whitespace character
        }
        lastCh=ch;
    }
    //for consistence
    if(isdigit(lastCh)){
        postfix+=' ';
    }
    while(!opertorStack.isEmpty()){
        postfix+=opertorStack.pop();
        postfix+=' ';
    }
    return postfix;
}

int calulate(char calculteSign,int leftOperand,int rightOperand){
    if(calculteSign=='+'){
        return leftOperand + rightOperand;
    }
    if(calculteSign== '-'){
        return leftOperand - rightOperand;
    }
    if(calculteSign=='*'){
        return leftOperand * rightOperand;
    }
    //calculteSign== /
    return leftOperand / rightOperand;
}

int calculateByPostfix(const string & postfix){
    int p=0;
    Stack <int> numberStack;
    while(p<postfix.size()){
        if(isdigit(postfix[p])){
            int q = p+1;
            //a number can not be overflow in the postfix
            while(isdigit(postfix[q]) ){
                q++;
            }
            int substrLength = q-p;
            int number = stoi(postfix.substr(p,substrLength));
            numberStack.push(number);
            p=q;
        }else if(postfix[p]==' '){
            p++;
        }else {//postfix[p]== + - * /
            if(numberStack.isEmpty()){
                cout<<"The postfix is Illegal";
                return -1;
            }
            int rightOperand = numberStack.pop();
            if(numberStack.isEmpty()){
                cout<<"The postfix is Illegal";
                return -1;
            }
            int leftOperand = numberStack.pop();
            int number = calulate(postfix[p],leftOperand,rightOperand);
            numberStack.push(number);
            p++;
        }
    }

    if(numberStack.isEmpty()){
        cout<<"The postfix is Illegal";
        return -1;
    }

    int result = numberStack.pop();

    //if the numberStack is NOT empty
    if(!numberStack.isEmpty()){
        cout<<"The postfix is Illegal";
        return -1;
    }

    return result;
}


STUDENT_TEST("Test expression is legal"){
    EXPECT(isExpressionLegal("1+2)"));
    EXPECT(!isExpressionLegal("1+2!"));
}

STUDENT_TEST("Test infix to postfix"){
    EXPECT_EQUAL(infixToPostfix("3 + 5 * 2 - 12 / ( 2 * 3 )"),"3 5 2 * + 12 2 3 * / - ");
    EXPECT_EQUAL(infixToPostfix("(3 + 5) * (2 - 8) / 4"),"3 5 + 2 8 - * 4 / ");
    EXPECT_EQUAL(infixToPostfix("(7 - (2 + 3) * (4 / 2)) + 5"),"7 2 3 + 4 2 / * - 5 + ");
    EXPECT_EQUAL(infixToPostfix("((1 + 2) * 3) - 4 / 2"),"1 2 + 3 * 4 2 / - ");
    EXPECT_EQUAL(infixToPostfix("5 + 6 * (7 - 3) / 2"),"5 6 7 3 - * 2 / + ");
}

STUDENT_TEST("Test calculte postfix"){
    EXPECT_EQUAL(calculateByPostfix("3 5 2 * + 12 2 3 * / - "),11);
    EXPECT_EQUAL(calculateByPostfix("3 5 + 2 8 - * 4 / "),-12);
    EXPECT_EQUAL(calculateByPostfix("7 2 3 + 4 2 / * - 5 + "),2);
    EXPECT_EQUAL(calculateByPostfix("1 2 + 3 * 4 2 / - "),7);
    EXPECT_EQUAL(calculateByPostfix("5 6 7 3 - * 2 / + "),17);

}

int main(){

    if(runSimpleTests(SELECTED_TESTS)){
        cout<<"test cases passed"<<endl;
    }
    return 0;
}
