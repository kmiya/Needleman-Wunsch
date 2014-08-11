#ifndef BASE_H_
#define BASE_H_

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

namespace needleman_wunsch_base {

// Base name (g = gap = '-')
typedef enum {
  A, C, G, T, g, space, nop
} kBase;
class Base {
 public:
  Base();
  Base(const std::string &in);
  void  SetString(const std::string &in);  // input base-stream to sequence
  void  SetBase(const kBase base);         // push-back bases to sequence
  kBase GetBase(const int i) const;        // return bases at i
  int   SequenceSize() const;              // return sequence size

  // convert string to base
  void StringToBase(const std::string &in, std::vector<kBase> *seq);
  // convert base to string
  void BaseToString(const std::vector<kBase> &in, std::string *seq);
  void PrintString();
  void SaveString(std::ostream *fout);       // print sequence as string
  // print input sequence
  void PrintInputString();                   // print to std::cout
  void SaveInputString(std::ostream *fout);  // print to given ofstream
  // print sequence as kBase
  void PrintBase();                          // print to std::cout
  void SaveBase(std::ostream *fout);         // print to given ofstream

 private:
  std::string inputString;
  std::vector<kBase> sequence;
  template <class T> void Show(const T &tmp, std::ostream *fout);
};

} // namespace needleman_wunsch_base

#endif // BASE_H_
