#include <iostream>
#include <algorithm>
#include "Base.h"

namespace needleman_wunsch_base
{

using namespace std;

Base::Base() { SetString(""); }
Base::Base(const string &in) { SetString(in); }
// copy input sequence to class member
void Base::SetString(const string &in) {
  inputString = in;
  StringToBase(in, &sequence);
}
// push a base to class member
void Base::SetBase(const kBase base) {
  sequence.push_back(base);
}
// return i-th base
kBase Base::GetBase(const int i) const { return sequence[i]; }
int Base::SequenceSize() const {
  return sequence.size();
}
// translate Base-type into character (A, C, G, T)
void Base::BaseToString(const vector<kBase> &in, string *seq) {
  for ( auto i = in.begin(); i < in.end(); ++i ) {
    if ( *i == A )
      seq->push_back('A');
    else if ( *i == C )
      seq->push_back('C');
    else if ( *i == G )
      seq->push_back('G');
    else if ( *i == T )
      seq->push_back('T');
    else if ( *i == g )
      seq->push_back('-');
    else
      seq->push_back('/');
  }
}
// translate character into Base-type
void Base::StringToBase(const string &in, vector<kBase> *seq) {
  for ( auto i = in.begin(); i < in.end(); ++i ) {
    if ( *i == 'A' )
      seq->push_back(A);
    else if ( *i == 'C' )
      seq->push_back(C);
    else if ( *i == 'G' )
      seq->push_back(G);
    else if ( *i == 'T' )
      seq->push_back(T);
    else if ( *i == '-' )
      seq->push_back(g);
    else
      seq->push_back(nop);
  }
}
// --- functions for output ---
void Base::PrintString() { SaveString(&cout); }
void Base::SaveString(ostream *fout) {
  string out("");
  BaseToString(sequence, &out);
  Show(out, fout);
}
void Base::PrintInputString() { SaveInputString(&cout); }
void Base::SaveInputString(ostream *fout) { Show(inputString, fout); }
void Base::PrintBase() { SaveBase(&cout); }
void Base::SaveBase(std::ostream *fout) { Show(sequence, fout); }
template <class T>
void Base::Show(const T &tmp, ostream *fout) {
  for ( auto i = tmp.begin(); i < tmp.end(); ++i ) {
    *fout << *i;
  }
  *fout << endl;
}

} // namespace needleman_wunsch_base
