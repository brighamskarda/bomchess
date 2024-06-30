#ifndef SQUARE_H
#define SQUARE_H

#include <array>
#include <cstdint>
#include <ostream>

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
[[nodiscard]] Square SquareFromFileRank(char file, char rank);

/**
 * @exception std::invalid_argument Throws if string cannot be parsed to square.
 */
[[nodiscard]] Square SquareFromString(std::string_view string);

/**
 * @return Returns the square's file as a character. (ex. GetFile(Square::kA8) == 'a')
 * @exception std::invalid_argument Throws if Square is not a valid chess square.
 */
[[nodiscard]] char GetFile(Square square);

/**
 * @return Returns the square's rank as a character. (ex. GetFile(Square::kA8) == 'a')
 * @exception std::invalid_argument Throws if Square is not a valid chess square.
 */
[[nodiscard]] char GetRank(Square square);

std::ostream& operator<<(std::ostream& os, Square square) noexcept;

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid ranks.
 */
[[nodiscard]] int8_t RankDistance(Square square_1, Square square_2);

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
[[nodiscard]] int8_t FileDistance(Square square_1, Square square_2);

/**
 * @return The Chebyshev distance between two squares. The number of king moves between two squares.
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
[[nodiscard]] int8_t ChebyshevDistance(Square square_1, Square square_2);

/**
 * @return The Manhattan distance between two squares. The number of orthogonal king moves between two squares.
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
[[nodiscard]] int8_t ManhattanDistance(Square square_1, Square square_2);

/**
 * @exception std::invalid_argument Throws if either of the squares are invalid.
 */
[[nodiscard]] int8_t KnightDistance(Square square_1, Square square_2);

}  // namespace bomchess

#endif  // SQUARE_H
