/*
Name: Jackie Ramsey
Class: CPSC 122, Section 1
Date Submitted: April 21, 2021
Assignment: Project 13
Description: Part 2 of Calculator Assignment 
To Compile: make
To Execute: ./calc "(121+12)"
*/
#include <iostream>
using namespace std;

#include "calc.h"
#include <cstring>


//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn) : Stack()
{
  CheckTokens();
  MakeValueTbl();
  Parse();
  CheckParens();
  InFixToPostFix();
  
  if(CheckTokens() == false) {
    cout << "There was an error, exiting now" << endl;
    exit(EXIT_FAILURE);
  }
  
  if(CheckParens() == false) {
    cout << "There was an error, exiting now" << endl;
    exit(EXIT_FAILURE);
  }
}

Calc::~Calc()
{
  delete[] inFix;
  delete[] postFix;
  delete[] valueTbl;
  
  while(stk->GetLength() != 0) 
  {
    stk->Pop();
  }
  stk = NULL;
}

bool Calc::CheckTokens()
{
  int i = 0;
  while(inFix[i] != '\0')
  {
     if(isupper(inFix[i])) {
       return true;
     }
     else if(isdigit(inFix[i])) {
       return true;
     }
     else if(inFix[i] == '/' || '*' || '+' || '-') {
       return true;
     }
     else if(inFix[i] == '(' || ')') {
       return true;
     } 
     else {
       return false;
     } 
    i++;
  }
  return false;
}

void Calc::MakeValueTbl()
{
  valueIdx = 0;
  valueTbl = new int[26];
  
  for(int i = 0; i < 26; i++)
  {
    valueTbl[i] = 0;
  }  
}

void Calc::Parse() {
  int i = 0;
  int count = 0;
  valueIdx = 0;
  char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  
  while(inFix[i] != '\0')
  {
    if(isdigit(inFix[i])) {
      valueTbl[count] = inFix[i];
      inFix[i] = alphabet[count];
      count++;
    }
    i++;
  }

}

bool Calc::CheckParens()
{
  int count = 0, i = 0;
  while(inFix[i] != '\0')
  {
    if(inFix[i] = '(') {
      count++;
    }
    if(inFix[i] = ')') {
      count--;
    }
    i++;
  }
  
  if(count == 0) {
    return true;
  }
  else {
    return false;
  }
}

void Calc::DisplayInFix()
{
  for(int i = 0; inFix[i] != '\0'; i++) 
  {
    cout << inFix[i] << endl;
  }
}

void Calc::InFixToPostFix()
{
  Stack stk;
  for(int i = 0; inFix[i] != '\0'; i++) 
  {
    if(inFix[i] = '(') {
      stk.Push(inFix[i]);
    }
    if(inFix[i] = ')') {
      while(stk.Peek() != '(') {
        postFix = postFix + stk.Peek();
        stk.Pop();
      }
      stk.Pop();
    }
    if(inFix[i] == '/' || '*' || '+' || '-') {
      postFix = postFix + inFix[i];
    }
  }
}

void Calc::DisplayPostFix()
{
  for(int i = 0; postFix[i] != '\0'; i++) 
  {
    cout << postFix[i] << endl;
  }
}


int Calc::Evaluate()
{
  Stack stk;
  int i = 0;
  while(postFix[i] != '\0') {
    if(isupper(postFix[i])) {
      stk.Push(postFix[i]);
    }
    if(postFix[i] == '/' || '*' || '+' || '-') {
      //int val1 = stk.Pop();
      //int val2 = stk.Pop();
      int val1, val2;
      
      if(postFix[i] == '/') {
        stk.Push(val2 / val1);
        break;
      }
      if(postFix[i] == '*') {
        stk.Push(val2 * val1);
        break;
      }
      if(postFix[i] == '+') {
        stk.Push(val2 + val1);
        break;
      }
      if(postFix[i] == '-') {
        stk.Push(val2 - val1);
        break;
      }
    }
    i++;
  }
  return 0;
 //return stk.Pop();
}

