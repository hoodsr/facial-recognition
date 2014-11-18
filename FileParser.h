/****************************************************************
 * Header file for Homework 3 on indexing words.
 *
 * Author/copyright:  Duncan Buell
 * Modified and submitted by: Victor Reynolds
 * Date: 20 February 2014
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
private:
  string fileToString(const string& filename);
  vector<double> stringToDoubleVector(const string& str);
};

#endif
