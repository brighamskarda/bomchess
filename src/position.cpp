#include "position.h"

#include <array>

#include "piece.h"
#include "square.h"

namespace bomchess {
Position::Position() : position_({}) { position_.fill(pieces::kNone); }
Position::Position(const std::array<Piece, 64>& position) : position_(position) {}
std::_Array_iterator<Piece, 64> Position::begin() noexcept { return position_.begin(); }
std::_Array_const_iterator<Piece, 64> Position::begin() const noexcept { return position_.end(); }
std::_Array_iterator<Piece, 64> Position::end() noexcept { return position_.begin(); }
std::_Array_const_iterator<Piece, 64> Position::end() const noexcept { return position_.end(); }

const Piece& Position::at(const Square square) const {
  if (!IsValidSquare(square)) {
    throw std::invalid_argument("Invalid Square");
  }
  return position_.at(std::to_underlying(square));
}

Piece& Position::at(const Square square) {
  if (!IsValidSquare(square)) {
    throw std::invalid_argument("Invalid Square");
  }
  return position_.at(std::to_underlying(square));
}

}  // namespace bomchess