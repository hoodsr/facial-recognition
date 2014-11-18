/****************************************************************
 * Header file for Homework 3 on indexing words.
 *
 * Author/copyright:  Duncan Buell
 * Modified and submitted by: Victor Reynolds
 * Date: 20 February 2014
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
