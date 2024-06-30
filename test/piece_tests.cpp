#define BOOST_TEST_MODULE "bomchess"

#include <sstream>
#include <stdexcept>

#include "boost/test/unit_test.hpp"

#include "piece.h"

BOOST_AUTO_TEST_CASE(PieceFromString) {
  BOOST_CHECK_EQUAL(bomchess::PieceFromString("r"), bomchess::pieces::kBlackRook);
  BOOST_CHECK_EQUAL(bomchess::PieceFromString("Q"), bomchess::pieces::kWhiteQueen);
}

BOOST_AUTO_TEST_CASE(PieceFromSymbol) {
  BOOST_CHECK_EQUAL(bomchess::PieceFromString("♜"), bomchess::pieces::kBlackRook);
  BOOST_CHECK_EQUAL(bomchess::PieceFromString("♕"), bomchess::pieces::kWhiteQueen);
}

BOOST_AUTO_TEST_CASE(PieceFromStringThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::PieceFromString("a"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(PieceOstream) {
  std::ostringstream test_stream;
  test_stream << bomchess::pieces::kWhitePawn;
  BOOST_CHECK_EQUAL(test_stream.str(), "P");

  test_stream.str("");
  test_stream << bomchess::pieces::kBlackPawn;
  BOOST_CHECK_EQUAL(test_stream.str(), "p");

  test_stream.str("");
  test_stream << bomchess::pieces::kWhiteKnight;
  BOOST_CHECK_EQUAL(test_stream.str(), "N");
}

BOOST_AUTO_TEST_CASE(PieceToSymbols) {
  std::string_view test_string = bomchess::ToSymbol(bomchess::pieces::kWhitePawn);
  BOOST_CHECK_EQUAL(test_string, "♙");

  test_string = bomchess::ToSymbol(bomchess::pieces::kBlackPawn);
  BOOST_CHECK_EQUAL(test_string, "♟");

  test_string = bomchess::ToSymbol(bomchess::pieces::kWhiteKnight);
  BOOST_CHECK_EQUAL(test_string, "♘");
}