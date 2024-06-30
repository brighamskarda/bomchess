#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "square.h"

namespace bomchess {
struct Move {
 public:
  Square from_square;
  Square to_squard;
  Piece promotion;
};
}  // namespace bomchess

#endif  // MOVE_H
