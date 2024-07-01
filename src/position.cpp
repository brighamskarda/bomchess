#include "position.h"

#include <array>
#include <ranges>
#include <sstream>
#include <string>

#include "piece.h"
#include "square.h"

namespace bomchess {
namespace {
std::string ToStringNotFlipped(const Position& position) {
  std::ostringstream string_stream;
  size_t previous_stream_size = string_stream.str().size();
  char file = 'a';
  char rank = '8';
  for (const Piece piece : position) {
    string_stream << piece;
    if (string_stream.str().size() <= previous_stream_size) {
      throw std::invalid_argument("Invalid piece detected in position");
    }
    previous_stream_size = string_stream.str().size();
    if (file == 'h') {
      string_stream << rank << '\n';
      rank -= 1;
      file = 'a' - 1;
    }
    file += 1;
  }
  string_stream << "ABCDEFGH";
  return string_stream.str();
}

std::string ToStringFlipped(const Position& position) {
  std::ostringstream string_stream;
  size_t previous_stream_size = string_stream.str().size();
  char file = 'h';
  char rank = '1';
  for (const auto kAllSquare : std::ranges::reverse_view(kAllSquares)) {
    const Piece piece = position.at(kAllSquare);
    string_stream << piece;
    if (string_stream.str().size() <= previous_stream_size) {
      throw std::invalid_argument("Invalid piece detected in position");
    }
    previous_stream_size = string_stream.str().size();
    if (file == 'a') {
      string_stream << rank << '\n';
      rank += 1;
      file = 'h' + 1;
    }
    file -= 1;
  }
  string_stream << "HGFEDCBA";
  return string_stream.str();
}
}  // namespace

Position::Position() : position_({}) { position_.fill(pieces::kNone); }
Position::Position(const std::array<Piece, 64>& position) : position_(position) {}
std::_Array_iterator<Piece, 64> Position::begin() noexcept { return position_.begin(); }
std::_Array_const_iterator<Piece, 64> Position::begin() const noexcept { return position_.begin(); }
std::_Array_iterator<Piece, 64> Position::end() noexcept { return position_.end(); }
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

std::string ToString(const Position& position, const bool flip) {
  if (flip) {
    return ToStringFlipped(position);
  }
  return ToStringNotFlipped(position);
}

}  // namespace bomchess