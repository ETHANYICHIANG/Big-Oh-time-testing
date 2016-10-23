//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cmath> // for log and pow
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;
  //srand(time(0));

  char* token;
  char buf[1000];
  const char* const tab = "\t";

  int count = 0;
  int n = 8000;
  string bigOh = "O(n)";
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;
  
  for(int cycle = 0; cycle < 4; cycle++, n *= 2)
  {
    clock_t startTime = clock(); // start clock
    ifstream fin;
    fin.open("dvc-schedule.txt");
    if(!fin.good()) throw "I/O error";
    count = 0;

    while(count < n)
    {
      // read the line
      string line;
      getline(fin, line);
      strcpy(buf, line.c_str());
      if (buf[0] == 0) continue; // skip blank lines

      // parse the line
      const string term(token = strtok(buf, tab));
      const string section(token = strtok(0, tab));
      const string course((token = strtok(0, tab)) ? token : "");
      const string instructor((token = strtok(0, tab)) ? token : "");
      const string whenWhere((token = strtok(0, tab)) ? token : "");
      if(course.find('-') == string::npos) continue; // invalid line: no dash in course name
      const string subjectCode(course.begin(), course.begin() + course.find('-'));
      count++;
    }

    fin.close();
    clock_t endTime = clock(); // stop clock
    
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