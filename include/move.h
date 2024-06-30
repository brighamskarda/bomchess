#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "square.h"

namespace bomchess {
struct Move {
 public:
  Square from_square;
  Square to_square;
  PieceType promotion;

  constexpr bool operator==(const Move&) const = default;
};

/**
 * @exception std::invalid_argument if the move string is not a valid UCI move as defined at
 * https://www.chessprogramming.org/Algebraic_Chess_Notation#UCI
 */
[[nodiscard]] Move FromUCI(std::string_view move_string);

/**
 * @exception std::invalid_argument if the move contains invalid information.
 */
[[nodiscard]] std::string ToUCI(Move move);

/**
 * Outputs the UCI form of the move to the ostream.
 */
std::ostream& operator<<(std::ostream& os, Move move) noexcept;

}  // namespace bomchess

#endif  // MOVE_H
