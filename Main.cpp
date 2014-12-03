/****************************************************************
 * The main file for our nearest pairs program. This program
 * goes through the data directory looking for 47 sets of
 * files. For each set, it compares the three Au01, AU12,
 * and AU17 files to the template files to find the
 * 10 nearest pairs.
 *
 * Authors: Shannon Hood and Victor Reynolds
 * Date: 17 November 2014
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
    //for (int i = 1; i < idCount + 1; i++)
    int i = 3;
    {
       map<double, int> results01 = worker.nearestPairsFromIds(directory, i, "01");
       map<double, int> results12 = worker.nearestPairsFromIds(directory, i, "12");
       map<double, int> resutls17 = worker.nearestPairsFromIds(directory, i, "17");
    }
  }
  else
  {
    cout << "Usage: findNearestPairs [datadirectory]" << endl;
  }
  return 0;
}
