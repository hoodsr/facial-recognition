/****************************************************************
*
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

map<int, double> Interpreter::nearestPairsFromIds(string dir, int templateId, string queryNum)
{
  FileParser parser;
  string formattedId = formatId(templateId);

  string queryName = dir  + formattedId + "_AU" + queryNum + "_query.dat";
  string templateName = dir + formattedId + "_template.dat";
  
  vector<double> query = parser.vectorFromFile(queryName);
  vector< vector<double> > templ = parser.vectorListFromTemplate(templateName);

  cout << query.size() << endl;
  cout << templ.size() << endl;
  cout << templ[0].size() << endl;

  map<int, double> results;
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
