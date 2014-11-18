/****************************************************************
 * The main file for our basic text-analysis program.
 *
 * This program takes a stoplist file and an input file.
 * The stoplist should list words that are considered by the 
 * user to not have significance. This program then
 * counts the number of occurrences of each word in the input
 * file, noting the words that are listed in the stoplist file
 * as stopwords. It then writes to an output file an
 * alphabetized list of the words in the input file as well
 * as their number of occurrences, beginning with the
 * stopwords and following with the rest of the words.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Modified and submitted by: Victor Reynolds 
 * Date: 20 February 2014
 *
**/

#include <map>

#include "Main.h"
#include "Interpreter.h"
#include "FileParser.h"

const int idCount = 47;

int main(int argc, char *argv[])
{
 // FileParser parser;
//  vector<double> test = parser.vectorFromFile("../data/001_AU01_query.dat");
  //vector< vector<double> > testtwo = parser.vectorListFromTemplate("../data/001_template.dat");
  if (argc == 2)
  {
    Interpreter worker;
    string directory(argv[1]);
    for (int i = 1; i < idCount + 1; i++)
    {
       map<int, double> results01 = worker.nearestPairsFromIds(directory, i, "01");
       map<int, double> results12 = worker.nearestPairsFromIds(directory, i, "12");
       map<int, double> resutls17 = worker.nearestPairsFromIds(directory, i, "17");
    }
  }
  else
  {
    cout << "Usage: findNearestPairs [datadirectory]" << endl;
  }
  return 0;
}
