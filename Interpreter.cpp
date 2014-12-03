/****************************************************************
* This is the file where the meat of the calculations is done.
* Once the data is read from the files, the nearest pairs
* are calculated here.
*
* Authors: Shannon Hood and Victor Reynolds
* Date: 17 November 2014
**/

#include "Interpreter.h"
Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}

// I realized after I made this that if we want our program to be fast, it might be
// best to try to do the calculations as the actual files are read.
void Interpreter::nearestPairsFromIds(string dir, int templateId, string queryNum)
{
  //FileParser parser;
  string formattedId = this->formatId(templateId);

  string queryName = dir  + formattedId + "_AU" + queryNum + "_query.dat";
  string templateName = dir + formattedId + "_template.dat";
  
  vector<double> query = this->vectorFromFile(queryName);
  //vector<double> query01 = this->vectorFromFile(queryName01); or use instance vector for 3 query names
  //vector<double> query12 = this->vectorFromFile(queryName12);
  //vector<double> query17 = this->vectorFromFile(queryName17);


  cout << queryName << endl;

  // Perform the calculations
  this->findNearestIndicesFromTemplate(query, templateName);
}

void Interpreter::findNearestIndicesFromTemplate(const vector<double>& query, string templateName)
{
  multimap<double, int> result;

  ifstream myFile(templateName.c_str());

  string str;
  double templateVal;
  int templateIndex = 1; // I belive that in the examples the template rows are
                         // 1 indexed rather than 0 indexed.

  // We should name these differently,
  // but these correspond to the parts of
  // the equation on the powerpoint slide.
  double dotProduct = 0;
  double vectorXSquared = 0;
  double vectorYSquared = 0;
  while (getline(myFile, str))
  {
    stringstream ss (str);
    dotProduct = 0;
    vectorXSquared = 0;
    vectorYSquared = 0;
    int templateRowIndex = 0;
    while (ss >> templateVal)
    {
      dotProduct += templateVal * query[templateRowIndex];
      vectorXSquared += query[templateRowIndex] * query[templateRowIndex];
      vectorYSquared += templateVal * templateVal;
      templateRowIndex++;
    }
    // 1 - cosine similarity reverses order because higher values have greater similarity
    double vectorYLength = sqrt(vectorYSquared); // Will be the same for all three queries
    double s = 1 - (dotProduct / (sqrt (vectorXSquared) * vectorYLength));
    result.insert(pair<double, int>(s, templateIndex)); 
    templateIndex++;
  }

  int count = 0;
  for (multimap<double, int>::iterator it=result.begin(); count < 10 && it != result.end(); ++it)
  {
    cout << it->second << endl;
    count++;
  }
  // Right now this is just returning an empty map
  //return result1;
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

vector<double> Interpreter::vectorFromFile(const string& filename)
{
  ifstream is(filename.c_str());
  istream_iterator<double> start(is), end;
  vector<double> numbers(start, end);  
  return numbers;
}
/*
vector<double> Interpreter::vectorFromFile(const string& filename)
{
  string contents = fileToString(filename);
  return stringToDoubleVector(contents);
}
* This command is used on the ***_template.dat files because
 * each line of the template file corresponds to a vector to be compared
 * to the query files.

vector<vector<double> > Interpreter::vectorListFromTemplate(const string& filename)
{
  vector<string> template;
  ifstream myFile(filename.c_str());
  string str;
  while (getline(myFile, str))
  {
    vals.push_back(stringToDoubleVector(str);
  }

  return vals;
}


string Interpreter::fileToString(const string& filename)
{
  ifstream myFile(filename.c_str());
  stringstream buffer;
  buffer << myFile.rdbuf();
  return buffer.str();
}

vector<double> Interpreter::stringToDoubleVector(const string& str)
{
  vector<double> numbers;
  stringstream ss (str);

  double val;
  while (ss >> val) {
    numbers.push_back(val);
  }
    
  return numbers;
}*/
