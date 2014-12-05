/**
 * This is the file where the meat of the calculations is done.
 * Once the data is read from the files, the nearest pairs
 * are calculated here.
 *
 * Authors: Shannon Hood and Victor Reynolds
 * Date: 04 December 2014
 */

#include "Interpreter.h"

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}

/**
 * Formats the names of the files and stores the template
 * and query data into vectors. Calls the method findCosineSim, 
 * where the calculations are performed.
 *
 * @param dir name of the directory
 * @param templateId the template id
 */
void Interpreter::nearestNeighborsFromIds(string dir, int templateId)
{
  // Format the template and query filenames.
  string formattedId = this->formatId(templateId);
  queryNames.push_back(dir  + formattedId + "_AU01_query.dat");
  queryNames.push_back(dir  + formattedId + "_AU12_query.dat");
  queryNames.push_back(dir  + formattedId + "_AU17_query.dat");
  string templateName = dir + formattedId + "_template.dat";
  
  // Read in the template data.
  vectorTemplate = this->vectorListFromTemplate(templateName);

  // Read in the queries.
  query01 = this->vectorFromFile(queryNames.at(0));
  query12 = this->vectorFromFile(queryNames.at(1));
  query17 = this->vectorFromFile(queryNames.at(2));

  // Perform the calculations.
  this->findCosineSim();
}

/**
 * Where the actual calculations are performed. This method computes the cosine
 * similarity between the three queries and every line of the template. The 
 * computed values are then stored in a multimap using the cosine similariy as
 * the key and the index in the template as the value.
 * The ten most similar indices for each of the three queries is then printed 
 * to the console.
 */
void Interpreter::findCosineSim()
{
  multimap<double, int> result01;
  multimap<double, int> result12;
  multimap<double, int> result17;

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
    // 1 - cosine similarity reverses order because higher values have greater similarity.
    double vectorYLength = sqrt(ySquared); // Will be the same for all three queries.
    double cosSim01 = 1 - (dotProduct01 / (sqrt(xSquared01) * vectorYLength));
    double cosSim12 = 1 - (dotProduct12 / (sqrt(xSquared12) * vectorYLength));
    double cosSim17 = 1 - (dotProduct17 / (sqrt(xSquared17) * vectorYLength));

    result01.insert(pair<double, int>(cosSim01, i+1)); 
    result12.insert(pair<double, int>(cosSim12, i+1)); 
    result17.insert(pair<double, int>(cosSim17, i+1)); 
  }

  // Print out results for first query.
  cout << "\n" << queryNames[0] << ": ";
  int count = 0;
  for(multimap<double, int>::iterator it=result01.begin(); count < 10; ++it)
  {
    cout << it->second << " ";
    count++;
  }

  // Print out results for second query.
  cout << "\n" << queryNames[1] << ": ";
  count = 0;
  for(multimap<double, int>::iterator it=result12.begin(); count < 10; ++it)
  {
    cout << it->second << " ";
    count++;
  }

  // Print out results for third query.
  cout << "\n" << queryNames[2] << ": ";
  count = 0;
  for(multimap<double, int>::iterator it=result17.begin(); count < 10; ++it)
  {
    cout << it->second << " ";
    count++;
  }

  cout << endl;
}

/**
 * Formats the id number of the name of the file 
 * byadding leading zeros.
 *
 * @param id id of file
 * @return formatted id
 */
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

/**
 * Reads the content of a query file into the program as
 * a vector of doubles.
 *
 * @param fileName name of file
 * @return contents of query file
 */
vector<double> Interpreter::vectorFromFile(const string& fileName)
{
  ifstream is(fileName.c_str());
  istream_iterator<double> start(is), end;
  vector<double> numbers(start, end);  
  return numbers;
}

/** 
 * This command is used on the ***_template.dat files because
 * each line of the template file corresponds to a vector to be compared
 * to the query files.
 * 
 * @param fileName the name of the file
 * @return contents of template file
 */
vector<vector<double> > Interpreter::vectorListFromTemplate(const string& fileName)
{
  vector<vector<double> > vals;
  ifstream myFile(fileName.c_str());
  string str;
  while (getline(myFile, str))
  {
    vals.push_back(stringToDoubleVector(str));
  }

  return vals;
}

/** 
 * Parses a given string into a vector of doubles. This is used in reading
 * in both the template and query files.
 * 
 * @param string the string to be parsed
 * @return numbers 
 */
vector<double> Interpreter::stringToDoubleVector(const string& str)
{
  vector<double> numbers;
  stringstream ss (str);

  double val;
  while (ss >> val)
  {
    numbers.push_back(val);
  }

  return numbers;
}

