/****************************************************************
 * Header file for the interpreter.
 *
 * Author: Shannon Hood and Victor Reynolds
 * Date: 17 November 2014
 *
**/

#ifndef INTERPRETER_H
#define INTERPRETER_H

using namespace std;

class Interpreter
{
public:
  Interpreter();
  ~Interpreter();
  map<int, double> nearestPairsFromIds(string dir, int templateId, string queryNum);
private:
  string formatId(int id); 
};

#endif
