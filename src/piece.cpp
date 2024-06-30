#include "piece.h"

#include <ostream>
#include <stdexcept>
#include <unordered_set>

#include "color.h"

namespace {
constexpr std::string_view kWhitePawnSymbol = "♙";
constexpr std::string_view kWhiteRookSymbol = "♖";
constexpr std::string_view kWhiteKnightSymbol = "♘";
constexpr std::string_view kWhiteBishopSymbol = "♗";
constexpr std::string_view kWhiteQueenSymbol = "♕";
constexpr std::string_view kWhiteKingSymbol = "♔";
constexpr std::string_view kBlackPawnSymbol = "♟";
constexpr std::string_view kBlackRookSymbol = "♜";
constexpr std::string_view kBlackKnightSymbol = "♞";
constexpr std::string_view kBlackBishopSymbol = "♝";
constexpr std::string_view kBlackQueenSymbol = "♛";
constexpr std::string_view kBlackKingSymbol = "♚";

constexpr bomchess::PieceType GetPieceType(const std::string_view piece) noexcept {
  if (piece == "P" || piece == kWhitePawnSymbol || piece == "p" || piece == kBlackPawnSymbol) {
    return bomchess::PieceType::kPawn;
  }
  if (piece == "R" || piece == kWhiteRookSymbol || piece == "r" || piece == kBlackRookSymbol) {
    return bomchess::PieceType::kRook;
  }
  if (piece == "N" || piece == kWhiteKnightSymbol || piece == "n" || piece == kBlackKnightSymbol) {
    return bomchess::PieceType::kKnight;
  }
  if (piece == "B" || piece == kWhiteBishopSymbol || piece == "b" || piece == kBlackBishopSymbol) {
    return bomchess::PieceType::kBishop;
  }
  if (piece == "Q" || piece == kWhiteQueenSymbol || piece == "q" || piece == kBlackQueenSymbol) {
    return bomchess::PieceType::kQueen;
  }
  if (piece == "K" || piece == kWhiteKingSymbol || piece == "k" || piece == kBlackKingSymbol) {
    return bomchess::PieceType::kKing;
  }
  return bomchess::PieceType::kNone;
}

bomchess::Color GetPieceColor(const std::string_view piece) noexcept {
  const static std::unordered_set<std::string_view> whitePieces{"P",
                                                                "R",
                                                                "N",
                                                                "B",
                                                                "Q",
                                                                "K",
                                                                kWhitePawnSymbol,
                                                                kWhiteRookSymbol,
                                                                kWhiteKnightSymbol,
                                                                kWhiteBishopSymbol,
                                                                kWhiteQueenSymbol,
                                                                kWhiteKingSymbol};
  const static std::unordered_set<std::string_view> blackPieces{"p",
                                                                "r",
                                                                "n",
                                                                "b",
                                                                "q",
                                                                "k",
                                                                kBlackPawnSymbol,
                                                                kBlackRookSymbol,
                                                                kBlackKnightSymbol,
                                                                kBlackBishopSymbol,
                                                                kBlackQueenSymbol,
                                                                kBlackKingSymbol};
  if (whitePieces.contains(piece)) {
    return bomchess::Color::kWhite;
  }
  if (blackPieces.contains(piece)) {
    return bomchess::Color::kBlack;
  }
  return bomchess::Color::kNone;
}
}  // namespace

namespace bomchess {
Piece PieceFromString(const std::string_view piece_string) {
  const Piece piece{GetPieceColor(piece_string), GetPieceType(piece_string)};
  if (piece.color == Color::kNone || piece.type == PieceType::kNone) {
    throw std::invalid_argument("Invalid piece string.");
  }
  return piece;
}

std::string_view ToString(const Piece piece) noexcept {
  if (piece == pieces::kWhitePawn) {
    return "P";
  }
  if (piece == pieces::kWhiteRook) {
    return "R";
  }
  if (piece == pieces::kWhiteKnight) {
    return "N";
  }
  if (piece == pieces::kWhiteBishop) {
    return "B";
  }
  if (piece == pieces::kWhiteQueen) {
    return "Q";
  }
  if (piece == pieces::kWhiteKing) {
    return "K";
  }
  if (piece == pieces::kBlackPawn) {
    return "p";
  }
  if (piece == pieces::kBlackRook) {
    return "r";
  }
  if (piece == pieces::kBlackKnight) {
    return "n";
  }
  if (piece == pieces::kBlackBishop) {
    return "n";
  }
  if (piece == pieces::kBlackQueen) {
    return "q";
  }
  if (piece == pieces::kBlackKing) {
    return "k";
  }
  return "";
}

std::string_view ToSymbol(const Piece piece) noexcept {
  if (piece == pieces::kWhitePawn) {
    return kWhitePawnSymbol;
  }
  if (piece == pieces::kWhiteRook) {
    return kWhiteRookSymbol;
  }
  if (piece == pieces::kWhiteKnight) {
    return kWhiteKnightSymbol;
  }
  if (piece == pieces::kWhiteBishop) {
    return kWhiteBishopSymbol;
  }
  if (piece == pieces::kWhiteQueen) {
    return kWhiteQueenSymbol;
  }
  if (piece == pieces::kWhiteKing) {
    return kWhiteKingSymbol;
  }
  if (piece == pieces::kBlackPawn) {
    return kBlackPawnSymbol;
  }
  if (piece == pieces::kBlackRook) {
    return kBlackRookSymbol;
  }
  if (piece == pieces::kBlackKnight) {
    return kBlackKnightSymbol;
  }
  if (piece == pieces::kBlackBishop) {
    return kBlackBishopSymbol;
  }
  if (piece == pieces::kBlackQueen) {
    return kBlackQueenSymbol;
  }
  if (piece == pieces::kBlackKing) {
    return kBlackKingSymbol;
  }
  return "";
}

std::ostream& operator<<(std::ostream& os, const Piece piece) noexcept {
  os << ToString(piece);
  return os;
}
}  // namespace bomchess

std::size_t std::hash<bomchess::Piece>::operator()(const bomchess::Piece& piece) const noexcept {
  size_t hash_value = std::hash<bomchess::Color>{}(piece.color);
  hash_value ^= std::hash<bomchess::PieceType>{}(piece.type) << 1;
  return hash_value;
}