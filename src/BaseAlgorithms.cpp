#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "BaseAlgorithms.h"

namespace needleman_wunsch_basealgorithms {

using namespace std;
using namespace needleman_wunsch_base;

BaseAlgorithms::BaseAlgorithms() {
  resultX = new Base("");
  resultY = new Base("");
}
BaseAlgorithms::~BaseAlgorithms() {
  delete resultX;
  delete resultY;
}
void BaseAlgorithms::Alignment(const Base &inputSequence1, const Base &inputSequence2) {
  // initialize parameter and matrix
  cout << "\n::: Alignment :::" << endl;
  cout << "Initialize phase..." << endl;
  AlignmentInit(inputSequence1, inputSequence2);
  // calculate alignment matrix
  cout << "Calculating alignment score..." << endl;
  CalcAlignmentScore(inputSequence1, inputSequence2);
  //traceback
  cout << "Traceback phase..." << endl;
  Traceback(inputSequence1, inputSequence2);
  // delete variables
  AlignmentCleanUp();
}
void BaseAlgorithms::AlignmentInit(const Base &inputSequence1, const Base &inputSequence2) {
  // set penalties and parameters
  kMatch    =   1;
  kMismatch =  -1;
  kGap      =  -1;
  kMatSizeX = inputSequence1.SequenceSize();
  kMatSizeY = inputSequence2.SequenceSize();
  kMatSize  = (kMatSizeX+1) * (kMatSizeY+1);
  scoreMatrix = new Score[ kMatSize ];
  // initialize scoreMatrix
  for ( unsigned int i = 0; i < kMatSize; ++i ) {
    scoreMatrix[i].score = 0;
    scoreMatrix[i].previousX = 0;
    scoreMatrix[i].previousY = 0;
    scoreMatrix[i].XAlignWithGap = -100;
    scoreMatrix[i].YAlignWithGap = -100;
  }
  // boundary conditions
  ComesFrom(0, 0, kOrigin);
  for ( unsigned int x = 1; x <= kMatSizeX; ++x ) {
    Mat(0, x)->score = kMismatch * static_cast<int>(x);
    ComesFrom(0, x, kEdgeTop);
  }
  for ( unsigned int y = 1; y <= kMatSizeY; ++y ) {
    Mat(y, 0)->score = kMismatch * static_cast<int>(y);
    ComesFrom(y, 0, kEdgeLeft);
  }
}
void BaseAlgorithms::CalcAlignmentScore(const Base &inputSequence1, const Base &inputSequence2) {
  int s;
  for ( unsigned int y = 0; y < kMatSizeY; ++y ) {   // y-axis
    for ( unsigned int x = 0; x < kMatSizeX; ++x ) {   // x-axis
      s = inputSequence1.GetBase(x) == inputSequence2.GetBase(y) ? kMatch : kMismatch;
      Max(y+1, x+1, s);
    }
  }
}
void BaseAlgorithms::Traceback(const Base &inputSequence1, const Base &inputSequence2) {
  cout << "Start tracebacking from mat["<< kMatSizeY << "," << kMatSizeX << "]:" << endl;
  clock_t start, end;
  start = clock();
  TracebackRecursive(kMatSizeY, kMatSizeX, inputSequence1, inputSequence2);
  end = clock();
  cout << "time(ms): " << (end - start)*1000./CLOCKS_PER_SEC << endl;
}
void BaseAlgorithms::TracebackRecursive(const int y, const int x,
                                        const Base &inputSequence1, const Base &inputSequence2) {
  cout << "(" << y << "," << x << ")->";
  if ( !y && !x ) {
    cout << "Tracebacking end.\n\n";
    return;
  }
  TracebackRecursive(Mat(y, x)->previousY, Mat(y, x)->previousX,
                     inputSequence1, inputSequence2);
  // insert gaps
  if ( Mat(y, x)->XAlignWithGap ) {
    resultX->SetBase(g);
    if ( !y ) { // first string
      resultY->SetBase(inputSequence2.GetBase(y));
    } else {
      resultY->SetBase(inputSequence2.GetBase(y-1));
    }
  } else if ( Mat(y, x)->YAlignWithGap ) {
    if ( !x ) { // first string
      resultX->SetBase(inputSequence1.GetBase(x));
    } else {
      resultX->SetBase(inputSequence1.GetBase(x-1));
    }
    resultY->SetBase(g);
  } else { // if bases matched
    resultX->SetBase(inputSequence1.GetBase(x-1));
    resultY->SetBase(inputSequence2.GetBase(y-1));
  }
}
// show and save the alignment result
void BaseAlgorithms::PrintAlignment() { SaveAlignment(&cout); }
void BaseAlgorithms::SaveAlignment(std::ostream *fout) {
  unsigned int match = 0;
  resultX->SaveString(fout);
  for (int pos = 0; pos < resultX->SequenceSize(); pos++ ) {
    if ( resultX->GetBase(pos) == resultY->GetBase(pos) ) {
      *fout << "|";
      match++;
    } else { *fout << " ";}
  }
  *fout << endl;
  resultY->SaveString(fout);
  *fout << "scoring:  match = " << kMatch << ",  mismatch = " << kMismatch << ", indel = " << kGap << endl;
  *fout << "matches: " << match << ",  score: " << Mat(kMatSizeY, kMatSizeX)->score <<"\n" << endl;
}
int BaseAlgorithms::Max(const int y, const int x, const int s) {
  // calculate score
  const int up   = Mat(y-1,   x)->score + kGap;
  const int left = Mat(  y, x-1)->score + kGap;
  const int mid  = Mat(y-1, x-1)->score + s;
  const int maxScore = max(up, max(mid, left));
  Mat(y, x)->score = maxScore;
  // --- for trace back ---
  if ( maxScore == mid ) {
    ComesFrom(y, x, kUpperLeft);    // from upper left
    return 0;
  } else if ( maxScore == up ) {
    ComesFrom(y, x, kAbove);        // from above
    return 0;
  } else if ( maxScore == left ) {
    ComesFrom(y, x, kLeft);         // from left
    return 0;
  }
  return -1;
}
void BaseAlgorithms::ComesFrom(const int y, const int x, const Direction &direction) {
  switch (direction) {
    case kEdgeTop:
      SetParameters(y, x, x-1,   y, 0, 1); break;
    case kEdgeLeft:
      SetParameters(y, x,   x, y-1, 1, 0); break;
    case kUpperLeft:
      SetParameters(y, x, x-1, y-1, 0, 0); break;
    case kAbove:
      SetParameters(y, x,   x, y-1, 1, 0); break;
    case kLeft:
      SetParameters(y, x, x-1,   y, 0, 1); break;
    case kOrigin:
      SetParameters(y, x,   0,   0, 0, 0); break;
  }
}
void BaseAlgorithms::SetParameters(const int    y, const int x,
                                   const int preX, const int preY,
                                   const int XGap, const int YGap) {
  Mat(y, x)->previousX = preX;
  Mat(y, x)->previousY = preY;
  Mat(y, x)->XAlignWithGap = XGap;
  Mat(y, x)->YAlignWithGap = YGap;
}

} // namespace needleman_wunsch_basealgorithms
