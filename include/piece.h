#ifndef PIECE_H
#define PIECE_H

#include <bitset>
#include <ostream>

#include "color.h"

namespace bomchess {
enum class PieceType { kPawn, kRook, kKnight, kBishop, kQueen, kKing, kNone };

struct Piece {
  Color color;
  PieceType type;

  constexpr bool operator==(const Piece&) const = default;
};

/**
 * @param piece_string A string representing a chess piece. Can be represented by either letters, or the utf chess
 * symbols.
 * @exception std::invalid_argument Throws if the string is not a valid chess piece.
 */
[[nodiscard]] Piece PieceFromString(std::string_view piece_string);

[[nodiscard]] std::string_view ToString(Piece piece) noexcept;
[[nodiscard]] std::string_view ToSymbol(Piece piece) noexcept;

std::ostream& operator<<(std::ostream& os, Piece piece) noexcept;

namespace pieces {
constexpr Piece kWhitePawn{Color::kWhite, PieceType::kPawn};
constexpr Piece kWhiteRook{Color::kWhite, PieceType::kRook};
constexpr Piece kWhiteKnight{Color::kWhite, PieceType::kKnight};
constexpr Piece kWhiteBishop{Color::kWhite, PieceType::kBishop};
constexpr Piece kWhiteQueen{Color::kWhite, PieceType::kQueen};
constexpr Piece kWhiteKing{Color::kWhite, PieceType::kKing};
constexpr Piece kBlackPawn{Color::kBlack, PieceType::kPawn};
constexpr Piece kBlackRook{Color::kBlack, PieceType::kRook};
constexpr Piece kBlackKnight{Color::kBlack, PieceType::kKnight};
constexpr Piece kBlackBishop{Color::kBlack, PieceType::kBishop};
constexpr Piece kBlackQueen{Color::kBlack, PieceType::kQueen};
constexpr Piece kBlackKing{Color::kBlack, PieceType::kKing};
constexpr Piece kNone{Color::kNone, PieceType::kNone};

}  // namespace pieces
}  // namespace bomchess

template <>
struct std::hash<bomchess::Piece> {
  std::size_t operator()(const bomchess::Piece& piece) const noexcept;
};

#endif  // PIECE_H
