// NimGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleHandler.h"
#include <iostream>

using namespace std;
using namespace ConsoleHandler;

int main()
{
  cout << "Multiply two numbers: " << endl;
  double result = ConsoleHandlerCore::Multiply(12.4, 8.4);
  printf("Result: %f", result);
  cin.get();
    return 0;
}

