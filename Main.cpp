/**
 * The main file for our nearest pairs program. This program
 * goes through the data directory looking for 47 sets of
 * files. For each set, it compares the three Au01, AU12,
 * and AU17 files to the template files to find the
 * 10 nearest pairs.
 *
 * Authors: Shannon Hood and Victor Reynolds
 * Date: 04 December 2014
 */
 
#include "Main.h"
#include "Interpreter.h"

const int idCount = 47;

int main(int argc, char *argv[])
{
  clock_t t = clock();
  if (argc == 2)
  {
    // Get the directory from the command line.
    string directory(argv[1]);
    for (int i = 1; i < idCount + 1; i++)
    {
      // Find the nearest vectors from each template.
      Interpreter worker;
      worker.nearestNeighborsFromIds(directory, i);
    }
    // Print the run time.
    cout << "\nRun time:  " << ((float)clock()-t)/CLOCKS_PER_SEC << " s" << endl;
  }
  else
  {
    cout << "Usage: findNearestPairs [datadirectory]" << endl;
  }

  return 0;
}
