#include "square.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace bomchess {
Square SquareFromFileRank(const char file, const char rank) {
  const char16_t lowercase_file = std::tolower(file);
  if (lowercase_file < 'a' || lowercase_file > 'h') {
    throw std::invalid_argument("Invalid file");
  }
  if (rank < '1' || rank > '8') {
    throw std::invalid_argument("Invalid rank");
  }
  const int file_offset = lowercase_file - 'a';
  const int rank_offset = ('8' - rank) * 8;
  return static_cast<Square>(file_offset + rank_offset);
}

Square SquareFromString(const std::string_view string) {
  if (string.size() != 2) {
    throw std::invalid_argument("Invalid square string");
  }
  return SquareFromFileRank(string.at(0), string.at(1));
}

char GetFile(const Square square) {
  if (std::to_underlying(square) < 0 || std::to_underlying(square) >= kAllSquares.size()) {
    throw std::invalid_argument("Can't get file from invalid square.");
  }
  return static_cast<char>('a' + std::to_underlying(square) % 8);
}

char GetRank(const Square square) {
  if (std::to_underlying(square) < 0 || std::to_underlying(square) >= kAllSquares.size()) {
    throw std::invalid_argument("Can't get file from invalid square.");
  }
  return static_cast<char>('8' - std::to_underlying(square) / 8);
}

std::ostream& operator<<(std::ostream& os, const Square square) noexcept {
  try {
    os << GetFile(square) << GetRank(square);
  } catch (std::exception&) {
    os << "";
  }
  return os;
}

int8_t RankDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(std::abs(GetRank(square_1) - GetRank(square_2)));
}

int8_t FileDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(std::abs(GetFile(square_1) - GetFile(square_2)));
}

int8_t ChebyshevDistance(const Square square_1, const Square square_2) {
  return std::max(RankDistance(square_1, square_2), FileDistance(square_1, square_2));
}

int8_t ManhattanDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(RankDistance(square_1, square_2) + FileDistance(square_1, square_2));
}
int8_t KnightDistance(const Square square_1, const Square square_2) {
  if (std::to_underlying(square_1) < 0 || std::to_underlying(square_1) >= kAllSquares.size() ||
      std::to_underlying(square_2) < 0 || std::to_underlying(square_2) >= kAllSquares.size()) {
    throw std::invalid_argument("Invalid Squares");
  }
  // Implementation details at
  // https://www.chessprogramming.org/Knight-Distance#By_Absolute_Rank-File_Distance
  // clang-format off
  const std::array<int8_t, 64> knight_distance = {
    0, 3, 2, 3, 2, 3, 4, 5,
    3, 2, 1, 2, 3, 4, 3, 4,
    2, 1, 4, 3, 2, 3, 4, 5,
    3, 2, 3, 2, 3, 4, 3, 4,
    2, 3, 2, 3, 4, 3, 4, 5,
    3, 4, 3, 4, 3, 4, 5, 4,
    4, 3, 4, 3, 4, 5, 4, 5,
    5, 4, 5, 4, 5, 4, 5, 6};
  const std::array<int8_t, 64> corner = {
    1, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 1};
  // clang-format on
  const auto rank_difference =
      static_cast<int8_t>((std::to_underlying(square_1) | 7) - (std::to_underlying(square_2) | 7));
  const auto file_difference =
      static_cast<int8_t>((std::to_underlying(square_1) & 7) - (std::to_underlying(square_2) & 7));
  const auto rank_file_distance = static_cast<int8_t>(std::abs(rank_difference) + std::abs(file_difference));
  const auto distance = static_cast<int8_t>(knight_distance.at(rank_file_distance) +
                                            2 * (rank_file_distance == 9 & (corner.at(std::to_underlying(square_1)) ^
                                                                            corner.at(std::to_underlying(square_2)))));
  return distance;
}

}  // namespace bomchess