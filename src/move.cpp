#include "move.h"

#include <string_view>

#include "piece.h"
#include "square.h"

namespace bomchess {
Move FromUCI(const std::string_view move_string) {
  if (move_string.length() > 5) {
    throw std::invalid_argument("UCI move string is too long.");
  }

  Move move{};
  try {
    move.from_square = SquareFromFileRank(move_string.at(0), move_string.at(1));
    move.to_square = SquareFromFileRank(move_string.at(2), move_string.at(3));
    if (move_string.length() > 4) {
      move.promotion = PieceFromString(move_string.substr(4, 1)).type;
    } else {
      move.promotion = PieceType::kNone;
    }
  } catch (std::exception&) {
    throw std::invalid_argument("Invalid UCI move string.");
  }
  return move;
}

std::string ToUCI(Move move) { return ""; }

std::ostream& operator<<(std::ostream& os, Move move) noexcept { return os; }
}  // namespace bomchess