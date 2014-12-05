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
void Interpreter::nearestPairsFromIds(string dir, int templateId)
{
  //FileParser parser;
  string formattedId = this->formatId(templateId);
  queryNames.push_back(dir  + formattedId + "_AU01_query.dat");
  queryNames.push_back(dir  + formattedId + "_AU12_query.dat");
  queryNames.push_back(dir  + formattedId + "_AU17_query.dat");

  string templateName = dir + formattedId + "_template.dat";
  
  vectorTemplate = this->vectorListFromTemplate(templateName);

  //vector<double> query = this->vectorFromFile(queryNames);
  query01 = this->vectorFromFile(queryNames.at(0));
  query12 = this->vectorFromFile(queryNames.at(1));
  query17 = this->vectorFromFile(queryNames.at(2));

  // Perform the calculations
  this->findCosineSim();
}

/*vector<string> Interpreter::templateFromFile(string templateName)
{
  vector<string> yValues;
  ifstream myFile(templateName.c_str());
  string str;
  while (getline(myFile, str))
  {
    yValues.push_back(str);
  }
  return yValues;
}
*/
void Interpreter::findCosineSim()
{
  multimap<double, int> result01;
  multimap<double, int> result12;
  multimap<double, int> result17;
  ofstream outFile("output.txt", ios::app);


  double dotProduct01, dotProduct12, dotProduct17;
  double xSquared01, xSquared12, xSquared17;
  double ySquared;
  for(int i = 0; i < 138; i++)
  {
    dotProduct01 = 0, dotProduct12 = 0, dotProduct17 = 0;
    xSquared01 = 0, xSquared12 = 0, xSquared17 = 0;
    ySquared = 0;
    for(int j = 0; j < 5632; j++)
    {     
      dotProduct01 += vectorTemplate[i][j]*query01[j];
      dotProduct12 += vectorTemplate[i][j]*query12[j];
      dotProduct17 += vectorTemplate[i][j]*query17[j];
      xSquared01 += query01[j]*query01[j];
      xSquared12 += query12[j]*query12[j];
      xSquared17 += query17[j]*query17[j];

      ySquared += vectorTemplate[i][j]*vectorTemplate[i][j];
    }
    // 1 - cosine similarity reverses order because higher values have greater similarity
    double vectorYLength = sqrt(ySquared); // Will be the same for all three queries
    double cosSim01 = 1 - (dotProduct01 / (sqrt(xSquared01) * vectorYLength));
    double cosSim12 = 1 - (dotProduct12 / (sqrt(xSquared12) * vectorYLength));
    double cosSim17 = 1 - (dotProduct17 / (sqrt(xSquared17) * vectorYLength));

    result01.insert(pair<double, int>(cosSim01, i+1)); 
    result12.insert(pair<double, int>(cosSim12, i+1)); 
    result17.insert(pair<double, int>(cosSim17, i+1)); 
  }
  outFile << "\ntest01" << endl;
  int count = 0;
  for (multimap<double, int>::iterator it=result01.begin(); count < 10; ++it)
  {
    outFile << it->second << " ";
    count++;
  }

  outFile << "\ntest12" << endl;
  count = 0;
  for (multimap<double, int>::iterator it=result12.begin(); count < 10; ++it)
  {
    outFile << it->second << " ";
    count++;
  }

  outFile << "\ntest17" << endl;
  count = 0;
  for (multimap<double, int>::iterator it=result17.begin(); count < 10; ++it)
  {
    outFile << it->second << " ";
    count++;
  }
  // Right now this is just returning an empty map
  //return result1;
  outFile << endl;
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

/*vector<double> Interpreter::vectorFromFile(const string& filename)
{
  ifstream is(filename.c_str());
  istream_iterator<double> start(is), end;
  vector<double> numbers(start, end);  
  return numbers;
}*/

vector<double> Interpreter::vectorFromFile(const string& filename)
{
  string contents = fileToString(filename);
  return stringToDoubleVector(contents);
}
/*** This command is used on the ***_template.dat files because
 * each line of the template file corresponds to a vector to be compared
 * to the query files.
*/
vector<vector<double> > Interpreter::vectorListFromTemplate(const string& filename)
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


vector<double> Interpreter::stringToDoubleVector(const string& str)
{
  vector<double> numbers;
  stringstream ss (str);

  double val;
  while (ss >> val) {
    numbers.push_back(val);
  }
    
  return numbers;
}


string Interpreter::fileToString(const string& filename)
{
  ifstream myFile(filename.c_str());
  stringstream buffer;
  buffer << myFile.rdbuf();
  return buffer.str();
}
///////////////////////////////////////////

/*for(int j = 0; j < 5632; j++)
    {
      double templateVal, query01, query12, query17;
      query01SS >> query01;
      query12SS >> query12;
      query17SS >> query17;
      templateSS >> templateVal;

      dotProduct01 += templateVal*query01;
      dotProduct12 += templateVal*query12;
      dotProduct17 += templateVal*query17;

      xSquared01 += query01*query01;
      xSquared12 += query12*query12;
      xSquared17 += query17*query17;

      ySquared += templateVal*templateVal;}*/
    