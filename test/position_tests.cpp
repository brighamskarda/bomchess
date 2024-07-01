#define BOOST_TEST_MODULE "bomchess"

#include <array>
#include <sstream>
#include <stdexcept>
#include <string>

#include "boost/test/unit_test.hpp"

#include "piece.h"
#include "position.h"
#include "square.h"

BOOST_AUTO_TEST_CASE(EmptyPositionInitalization) {
  bomchess::Position test_pos{};
  for (const bomchess::Square square : bomchess::kAllSquares) {
    BOOST_CHECK_EQUAL(test_pos.at(square), bomchess::pieces::kNone);
  }
}

BOOST_AUTO_TEST_CASE(PositionInitialization) {
  std::array<bomchess::Piece, 64> position_array{};
  position_array.fill(bomchess::pieces::kBlackKnight);
  bomchess::Position test_pos(position_array);
  for (const bomchess::Square square : bomchess::kAllSquares) {
    BOOST_CHECK_EQUAL(test_pos.at(square), bomchess::pieces::kBlackKnight);
  }

  position_array.at(33) = bomchess::pieces::kWhiteKing;
  test_pos = bomchess::Position(position_array);
  for (const bomchess::Square square : bomchess::kAllSquares) {
    if (std::to_underlying(square) != 33) {
      BOOST_CHECK_EQUAL(test_pos.at(square), bomchess::pieces::kBlackKnight);
    } else {
      BOOST_CHECK_EQUAL(test_pos.at(square), bomchess::pieces::kWhiteKing);
    }
  }
}

// This test won't compile if the iterator isn't set up correctly.
BOOST_AUTO_TEST_CASE(PositionIterator) {
  int8_t counter = 0;
  for (bomchess::Position test_pos{}; const bomchess::Piece piece : test_pos) {
    BOOST_CHECK_EQUAL(piece, bomchess::pieces::kNone);
    counter++;
  }
  BOOST_CHECK_EQUAL(counter, 64);
}

BOOST_AUTO_TEST_CASE(PositionToString) {
  const std::string empty_position_string =
      "--------8\n--------7\n--------6\n--------5\n--------4\n--------3\n--------2\n--------1\nABCDEFGH";
  BOOST_CHECK_EQUAL(bomchess::ToString(bomchess::Position()), empty_position_string);

  const std::string default_position_string =
      "rnbqkbnr8\npppppppp7\n--------6\n--------5\n--------4\n--------3\nPPPPPPPP2\nRNBQKBNR1\nABCDEFGH";
  // clang-format off
  const bomchess::Position default_position = bomchess::Position({
    bomchess::pieces::kBlackRook, bomchess::pieces::kBlackKnight, bomchess::pieces::kBlackBishop, bomchess::pieces::kBlackQueen, bomchess::pieces::kBlackKing, bomchess::pieces::kBlackBishop, bomchess::pieces::kBlackKnight, bomchess::pieces::kBlackRook,
    bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn,
    bomchess::pieces::kWhiteRook, bomchess::pieces::kWhiteKnight, bomchess::pieces::kWhiteBishop, bomchess::pieces::kWhiteQueen, bomchess::pieces::kWhiteKing, bomchess::pieces::kWhiteBishop, bomchess::pieces::kWhiteKnight, bomchess::pieces::kWhiteRook
  });
  // clang-format on
  BOOST_CHECK_EQUAL(bomchess::ToString(default_position), default_position_string);
}

BOOST_AUTO_TEST_CASE(PositionToStringFlipped) {
  const std::string empty_position_string =
      "--------1\n--------2\n--------3\n--------4\n--------5\n--------6\n--------7\n--------8\nHGFEDCBA";
  BOOST_CHECK_EQUAL(bomchess::ToString(bomchess::Position(), true), empty_position_string);

  const std::string default_position_string =
      "RNBKQBNR1\nPPPPPPPP2\n--------3\n--------4\n--------5\n--------6\npppppppp7\nrnbkqbnr8\nHGFEDCBA";
  // clang-format off
  const bomchess::Position default_position = bomchess::Position({
    bomchess::pieces::kBlackRook, bomchess::pieces::kBlackKnight, bomchess::pieces::kBlackBishop, bomchess::pieces::kBlackQueen, bomchess::pieces::kBlackKing, bomchess::pieces::kBlackBishop, bomchess::pieces::kBlackKnight, bomchess::pieces::kBlackRook,
    bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn, bomchess::pieces::kBlackPawn,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone, bomchess::pieces::kNone,
    bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn, bomchess::pieces::kWhitePawn,
    bomchess::pieces::kWhiteRook, bomchess::pieces::kWhiteKnight, bomchess::pieces::kWhiteBishop, bomchess::pieces::kWhiteQueen, bomchess::pieces::kWhiteKing, bomchess::pieces::kWhiteBishop, bomchess::pieces::kWhiteKnight, bomchess::pieces::kWhiteRook
  });
  // clang-format on
  BOOST_CHECK_EQUAL(bomchess::ToString(default_position, true), default_position_string);
}