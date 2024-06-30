#include "move.h"

#include <sstream>
#include <string_view>
#include <utility>

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

std::string ToUCI(const Move move) {
  if (!IsValidSquare(move.from_square) || !IsValidSquare(move.to_square)) {
    throw std::invalid_argument("Move has invalid squares.");
  }
  const auto promotion_underlying = std::to_underlying(move.promotion);
  if (promotion_underlying > 6 || promotion_underlying < 0) {
    throw std::invalid_argument("Move has invalid promotion.");
  }
  std::stringstream uci;
  uci << move.from_square << move.to_square;
  const Piece promotion(Color::kWhite, move.promotion);
  uci << promotion;
  return uci.str();
}

std::ostream& operator<<(std::ostream& os, const Move move) noexcept {
  try {
    os << ToUCI(move);
  } catch (std::exception&) {
  }
  return os;
}
}  // namespace bomchess