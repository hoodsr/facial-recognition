/****************************************************************
 * Header file for the fileparser.
 *
 * Authors: Shannon Hood and Victor Reynolds
 * Date: 17 November 2014
 * 
**/

#ifndef FILEPARSER_H
#define FILEPARSER_H

using namespace std;

class FileParser
{
public:
  FileParser();
  ~FileParser();
  vector<double> vectorFromFile(const string& filename);
  vector< vector<double> > vectorListFromTemplate(const string& filename);
  map<int, double> findNearestPairsFromTemplate(const vector<double>& query, string templateName);
private:
  string fileToString(const string& filename);
  vector<double> stringToDoubleVector(const string& str);
};

#endif
