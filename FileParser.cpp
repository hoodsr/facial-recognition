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
#include <math.h>

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

map<int, double> FileParser::findNearestPairsFromTemplate(const vector<double>& query, string templateName)
{
  map<int, double> result;
  ifstream myFile(templateName.c_str());

  string str;
  double templateVal;
  int templateIndex = 1; // I belive that in the examples the template rows are
                         // 1 indexed rather than 0 indexed.

  // We should name these differently,
  // but these correspond to the parts of
  // the equation on the powerpoint slide.
  double topHalf = 0;
  double bottomLeft = 0;
  double bottomRight = 0;
  double nearestPair = 0;
  int nearestPairIndex = 0;
  while (getline(myFile, str))
  {
    stringstream ss (str);
    topHalf = 0;
    bottomLeft = 0;
    bottomRight = 0;
    int templateRowIndex = 0;
    while (ss >> templateVal)
    {
      topHalf += templateVal * query[templateRowIndex];
      bottomLeft += query[templateRowIndex] * query[templateRowIndex];
      bottomRight += templateVal * templateVal;
      templateRowIndex++;
    }
    double s = topHalf / (sqrt (bottomLeft) * sqrt (bottomRight));
    if (s > nearestPair || 0 == nearestPair) {
      nearestPair = s;
      nearestPairIndex = templateIndex;
    }
    templateIndex++;
  }

  cout << nearestPairIndex << endl;

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
