/****************************************************************
* This is the file where the meat of the calculations is done.
* Once the data is read from the files, the nearest pairs
* are calculated here.
*
* Authors: Shannon Hood and Victor Reynolds
* Date: 17 November 2014
**/

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Interpreter.h"
#include "FileParser.h"

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}

// I realized after I made this that if we want our program to be fast, it might be
// best to try to do the calculations as the actual files are read.
map<double, int> Interpreter::nearestPairsFromIds(string dir, int templateId, string queryNum)
{
  FileParser parser;
  string formattedId = formatId(templateId);

  string queryName = dir  + formattedId + "_AU" + queryNum + "_query.dat";
  string templateName = dir + formattedId + "_template.dat";
  
  vector<double> query = parser.vectorFromFile(queryName);
  // vector< vector<double> > templ = parser.vectorListFromTemplate(templateName);

  cout << queryName << endl;
  //cout << templ.size() << endl;
  //cout << templ[0].size() << endl;

  map<double, int> results = parser.findNearestPairsFromTemplate(query, templateName);
  // Do the algorithm here.

  return results;
}

string Interpreter::formatId(int id)
{
  string formatted = "";
  if (id < 10)
  {
    formatted = "00";
  }
  else
  {
    formatted = "0";
  }

  stringstream s;
  s << formatted << id;

  return s.str();
}
