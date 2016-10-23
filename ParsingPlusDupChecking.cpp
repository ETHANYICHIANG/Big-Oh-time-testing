//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cmath> // for log and pow
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

#include "DynamicArray.h"

//prototpyes
void updateClass(DynamicArray<string>&, const string, const string subjectCode, int&, int&, int&);

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  char* token;
  char buf[1000];
  const char* const tab = "\t";

  DynamicArray<string> readClass(100); // entered subjectCode

  int count = 0;
  int n = 800;
  int recordIndex = 0;
  int classIndex = 0;
  int duplication = 0;
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
      string classCode = term + "." + section;
      updateClass(readClass, classCode, subjectCode, classIndex, recordIndex, duplication);

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

// functions
void updateClass(DynamicArray<string>& readClass, const string classCode, const string subjectCode, int& classIndex, int& recordIndex, int& duplication)
{
  bool found = false;

  // found if is a duplication
  for(int i = 0; i < classIndex; i++)
  {
    if(readClass[i] == classCode)
    {
      found = true;
      duplication++;
      break;
    }
  }
}