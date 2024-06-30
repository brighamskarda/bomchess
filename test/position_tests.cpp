#define BOOST_TEST_MODULE "bomchess"

#include <array>
#include <sstream>
#include <stdexcept>

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
  for (bomchess::Position test_pos{}; const bomchess::Piece piece : test_pos) {
    BOOST_CHECK_EQUAL(piece, bomchess::pieces::kNone);
  }
}