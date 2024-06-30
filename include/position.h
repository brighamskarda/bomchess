#ifndef POSITION_H
#define POSITION_H

#include <array>
#include <ostream>

#include "piece.h"
#include "square.h"

namespace bomchess {

class Position {
 public:
  Position();
  explicit Position(const std::array<Piece, 64>& position);
  bool operator==(const Position&) const = default;
  [[nodiscard]] std::_Array_iterator<Piece, 64> begin() noexcept;
  [[nodiscard]] std::_Array_const_iterator<Piece, 64> begin() const noexcept;
  [[nodiscard]] std::_Array_iterator<Piece, 64> end() noexcept;
  [[nodiscard]] std::_Array_const_iterator<Piece, 64> end() const noexcept;
  /**
   * @exception std::invalid_argument if the square is not a valid chess square.
   */
  [[nodiscard]] const Piece& at(Square square) const;
  /**
   * @exception std::invalid_argument if the square is not a valid chess square.
   */
  [[nodiscard]] Piece& at(Square square);

 private:
  std::array<Piece, 64> position_;
};

}  // namespace bomchess

#endif  // POSITION_H
