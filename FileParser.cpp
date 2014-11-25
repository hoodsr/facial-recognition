/****************************************************************
 * This is where the data is read in from the files.
 *
 * Authors: Shannon Hood and Victor Reynolds
 * Date: 17 November 2014
**/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

#include "FileParser.h"

FileParser::FileParser()
{
}

FileParser::~FileParser()
{
}

/* This command is used on the AU** files because they are all
 * just lists of double values.
*/
vector<double> FileParser::vectorFromFile(const string& filename)
{
  string contents = fileToString(filename);
  return stringToDoubleVector(contents);
}

/* This command is used on the ***_template.dat files because
 * each line of the template file corresponds to a vector to be compared
 * to the query files.
*/
vector< vector<double> > FileParser::vectorListFromTemplate(const string& filename)
{
  vector< vector<double> > vals;
  ifstream myFile(filename.c_str());
  string str;
  while (getline(myFile, str))
  {
    vals.push_back(stringToDoubleVector(str));
  }

  return vals;
}

Map<int, double> FileParser::findNearestPairsFromTemplate(const vector<double>& query, string templateName)
{
  Map<int, double> result;
  return result;
}

string FileParser::fileToString(const string& filename)
{
  ifstream myFile(filename.c_str());
  stringstream buffer;
  buffer << myFile.rdbuf();
  return buffer.str();
}

vector<double> FileParser::stringToDoubleVector(const string& str)
{
  vector<double> numbers;
  stringstream ss (str);

  double val;
  while (ss >> val) {
    numbers.push_back(val);
  }
    
  return numbers;
}
