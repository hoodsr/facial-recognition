/****************************************************************
 * Header file for the interpreter.
 *
 * Author: Shannon Hood and Victor Reynolds
 * Date: 17 November 2014
 *
**/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <math.h>

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>

using namespace std;

class Interpreter
{
public:
  Interpreter();
  ~Interpreter();
  void nearestPairsFromIds(string dir, int templateId);
  void findCosineSim();


private:
  string formatId(int id);
  vector<double> stringToDoubleVector(const string& str);
  string fileToString(const string& filename);
  vector<double> vectorFromFile(const string& filename); 
  vector<vector<double> > vectorListFromTemplate(const string& filename); 

  vector<vector<double> > vectorTemplate;
  vector<double> query01;
  vector<double> query12;
  vector<double> query17;
  vector<string> queryNames;
};

#endif
