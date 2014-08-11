#ifndef BASEALIGNMENT_H_
#define BASEALIGNMENT_H_

#include "Base.h"

namespace needleman_wunsch_basealgorithms {

using namespace needleman_wunsch_base;

class BaseAlgorithms {
 public:
  BaseAlgorithms();
  ~BaseAlgorithms();
  // DO alignment
  void Alignment(const Base &inputSequence1, const Base &inputSequence2);
  void PrintAlignment();                    // show the alignment result
  void SaveAlignment(std::ostream *fout);   // save the alignment result

 private:
  typedef enum {
    kOrigin, kEdgeTop, kEdgeLeft, kUpperLeft, kAbove, kLeft
  } Direction;
  typedef struct {
    int score;           // element of alignment score matrix
    int previousX;       // x-coordinate of the previous element
    int previousY;       // y-coordinate of the previous element
    int XAlignWithGap;   // the flag to insert gaps
    int YAlignWithGap;   // the flag to insert gaps
  } Score;

  // --- for Global Alignment ---
  // initialization
  void AlignmentInit(const Base &inputSequence1, const Base &inputSequence2);
  // calculate the alignment score matrix
  void CalcAlignmentScore(const Base &inputSequence1, const Base &inputSequence2);
  void Traceback(const Base &inputSequence1, const Base &inputSequence2);
  void TracebackRecursive(const int y, const int x,
                        const Base &inputSequence1, const Base &inputSequence2);
  int  Max(const int i, const int j, const int s);
  void AlignmentCleanUp() { delete [] scoreMatrix; };

  // access indexes of pseudo 2D array
  Score* Mat(const int y, const int x) {
    return &scoreMatrix[y * (kMatSizeX+1) + x];
  }
  // calculation for traceback
  void ComesFrom(const int i, const int j, const Direction &direction);
  void SetParameters(const int    i, const int j,
                     const int preX, const int preY,
                     const int XGap, const int YGap);

  Base  *resultX;          // result sequence1
  Base  *resultY;          // result sequence2
  Score *scoreMatrix;
  int   kMatch;            // matched score
  int   kMismatch;         // mismatched score
  int   kGap;              // gap penalty
  unsigned int kMatSizeX;  // size of input sequence1
  unsigned int kMatSizeY;  // size of input sequence2
  unsigned int kMatSize;   // size of scoreMatrix
};

} // namespace needleman_wunsch_basealgorithms

#endif // BASEALIGNMENTG_H_
