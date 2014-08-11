#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "main.h"

void printDate(std::ostream *fout);    // print time stamp
void usage();                          // show usage

using namespace std;
using namespace needleman_wunsch_base;
using namespace needleman_wunsch_basealgorithms;

int main(int argc, char **argv)
{
  // --- open files ---
  ifstream inputFile1, inputFile2;
  ofstream outputFile;
  if (argc < 4) {
    usage();
    exit(EXIT_FAILURE);
  } else {
    inputFile1.open(argv[1]);
    inputFile2.open(argv[2]);
    outputFile.open(argv[3], ios::app);
  }
  if (inputFile1.fail() || inputFile2.fail() || outputFile.fail()) {
    cerr << "Error: Could not open files\n";
    usage();
    exit(EXIT_FAILURE);
  }
  // --- read sequences from files ---
  string input1, input2;
  inputFile1 >> input1;
  inputFile2 >> input2;
  if (input1.empty() || input2.empty()) {
    cerr << "Error: invalid files\n";
    usage();
    exit(EXIT_FAILURE);
  }
  // translate input_files into Base-type
  Base seq1(input1), seq2(input2);
  cout << "input file1:\n";
  seq1.PrintString();              // print input_file1
  cout << "input file2:\n";
  seq2.PrintString();              // print input_file2
  BaseAlgorithms tmp;              // create an instance for alignment
  tmp.Alignment(seq1, seq2);       // DO alignment
  tmp.PrintAlignment();            // print alignment result
  printDate(&outputFile);          // save time stamp to output_file
  tmp.SaveAlignment(&outputFile);  // save result to output_file
}
void printDate(ostream *fout) {
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);
    *fout << local->tm_year + 1900 << " "   // year
          << local->tm_mon + 1 << "/"       // month
          << local->tm_mday << " "          // day
          << local->tm_hour << ":"          // hour
          << local->tm_min  << ":"          // minute
          << local->tm_sec                  // second
          << endl;
}
void usage() {
  cout << "\n  Usage: nw  input_file1  input_file2  output_file" << endl;
}
