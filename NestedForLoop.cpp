//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <iostream> // for cout, ios, and endl
#include <string> // for string
using namespace std;

#include <cassert> // for assert
#include <cmath> // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;
  srand(time(0)); rand(); // seed the random number generator (in case you need it)

  // programmer customizations go here
  int n = 500; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  string bigOh = "O(n squared)"; // YOUR PREDICTION: O(n), O(n log n), or O(n squared)
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;

  cout.setf(ios::fixed);
  cout.precision(4);
  for (int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // problem setup goes here -- create a data structure of size n
    int* a = new int [n];
    for(int i = 0; i < n; i++) // fill array
    {
    	a[i] = rand();
    }

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    // do something where n is the "size" of the problem
    for(int i = 0; i < n; i++)
    	for(int j = i+1; j < n; j++)
    		if(a[j] < a[i])
    			swap(a[i], a[j]);
    clock_t endTime = clock(); 
    
    // validation block -- assure that process worked if applicable
    for(int i = 1; i < n; i++)
    	assert(a[i-1] <= a[i]);

    // cleanup if applicable
    delete [ ] a;

    // compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if (cycle == 0)
      elapsedSecondsNorm = elapsedSeconds;
    else if (bigOh == "O(n)")
      expectedSeconds = factor * elapsedSecondsNorm;
    else if (bigOh == "O(n log n)")
      expectedSeconds = factor * log(double(n)) / log(n / factor) * elapsedSecondsNorm;
    else if (bigOh == "O(n squared)")
      expectedSeconds = factor * factor * elapsedSecondsNorm;

    // reporting block
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << elapsedSeconds;
    if (cycle == 0) cout << " (expected " << bigOh << ')';
    else cout << " (expected " << expectedSeconds << ')';
    cout << " for n=" << n << endl;
  }

  return 0;
}