#ifndef SQUARE_H
#define SQUARE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <stdexcept>

namespace bomchess {
// clang-format off
/**
 * A representation of each square on a chess board.
 */
enum class Square {
  kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8,
  kA7, kB7, kC7, kD7, kE7, kF7, kG7, kH7,
  kA6, kB6, kC6, kD6, kE6, kF6, kG6, kH6,
  kA5, kB5, kC5, kD5, kE5, kF5, kG5, kH5,
  kA4, kB4, kC4, kD4, kE4, kF4, kG4, kH4,
  kA3, kB3, kC3, kD3, kE3, kF3, kG3, kH3,
  kA2, kB2, kC2, kD2, kE2, kF2, kG2, kH2,
  kA1, kB1, kC1, kD1, kE1, kF1, kG1, kH1,
  kNone
};

/**
 * All Square as they are represented on the board. Starts in top left corner (A8) and procedes across each row until
 * square H1.
 */
constexpr std::array<Square, 64> kAllSquares {
  Square::kA8, Square::kB8, Square::kC8, Square::kD8, Square::kE8, Square::kF8, Square::kG8, Square::kH8,
  Square::kA7, Square::kB7, Square::kC7, Square::kD7, Square::kE7, Square::kF7, Square::kG7, Square::kH7,
  Square::kA6, Square::kB6, Square::kC6, Square::kD6, Square::kE6, Square::kF6, Square::kG6, Square::kH6,
  Square::kA5, Square::kB5, Square::kC5, Square::kD5, Square::kE5, Square::kF5, Square::kG5, Square::kH5,
  Square::kA4, Square::kB4, Square::kC4, Square::kD4, Square::kE4, Square::kF4, Square::kG4, Square::kH4,
  Square::kA3, Square::kB3, Square::kC3, Square::kD3, Square::kE3, Square::kF3, Square::kG3, Square::kH3,
  Square::kA2, Square::kB2, Square::kC2, Square::kD2, Square::kE2, Square::kF2, Square::kG2, Square::kH2,
  Square::kA1, Square::kB1, Square::kC1, Square::kD1, Square::kE1, Square::kF1, Square::kG1, Square::kH1,
};
// clang-format on

/**
 * @param file Square file represented as a char. (ex. 'a')
 * @param rank Square rank represented as a char, not an int. (ex. '1' not 1)
 * @exception std::invalid_argument Throws if rank or file are invalid.
 */
inline [[nodiscard]] Square SquareFromFileRank(const char file, const char rank) {
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

/**
 * @exception std::invalid_argument Throws if string cannot be parsed to square.
 */
inline [[nodiscard]] Square SquareFromString(const std::string_view string) {
  if (string.size() != 2) {
    throw std::invalid_argument("Invalid square string");
  }
  return SquareFromFileRank(string.at(0), string.at(1));
}

/**
 * @return Returns the square's file as a character. (ex. GetFile(Square::kA8) == 'a')
 * @exception std::invalid_argument Throws if Square is not a valid chess square.
 */
constexpr [[nodiscard]] char GetFile(const Square square) {
  if (std::to_underlying(square) < 0 || std::to_underlying(square) >= kAllSquares.size()) {
    throw std::invalid_argument("Can't get file from invalid square.");
  }
  return static_cast<char>('a' + std::to_underlying(square) % 8);
}

/**
 * @return Returns the square's rank as a character. (ex. GetFile(Square::kA8) == 'a')
 * @exception std::invalid_argument Throws if Square is not a valid chess square.
 */
constexpr [[nodiscard]] char GetRank(const Square square) {
  if (std::to_underlying(square) < 0 || std::to_underlying(square) >= kAllSquares.size()) {
    throw std::invalid_argument("Can't get file from invalid square.");
  }
  return static_cast<char>('8' - std::to_underlying(square) / 8);
}

inline std::ostream& operator<<(std::ostream& os, const Square square) noexcept {
  try {
    os << GetFile(square) << GetRank(square);
  } catch (std::exception&) {
    os << "Invalid Square";
  }
  return os;
}

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid ranks.
 */
inline [[nodiscard]] int8_t RankDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(std::abs(GetRank(square_1) - GetRank(square_2)));
}

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
inline [[nodiscard]] int8_t FileDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(std::abs(GetFile(square_1) - GetFile(square_2)));
}

/**
 * @return The Chebyshev distance between two squares. The number of king moves between two squares.
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
inline [[nodiscard]] int8_t ChebyshevDistance(const Square square_1, const Square square_2) {
  return std::max(RankDistance(square_1, square_2), FileDistance(square_1, square_2));
}

/**
 * @return The Manhattan distance between two squares. The number of orthogonal king moves between two squares.
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
inline [[nodiscard]] int8_t ManhattanDistance(const Square square_1, const Square square_2) {
  return static_cast<int8_t>(RankDistance(square_1, square_2) + FileDistance(square_1, square_2));
}

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
inline [[nodiscard]] int8_t KnightDistance(const Square square_1, const Square square_2) {
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

#endif  // SQUARE_H
