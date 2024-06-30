#define BOOST_TEST_MODULE "bomchess"

#include <sstream>
#include <stdexcept>

#include "boost/test/unit_test.hpp"

#include "square.h"

BOOST_AUTO_TEST_CASE(SquareOStream) {
  std::ostringstream square_strings;
  square_strings << bomchess::Square::kA1;
  BOOST_CHECK_EQUAL(square_strings.str(), "a1");

  square_strings.str("");
  square_strings << bomchess::Square::kH1;
  BOOST_CHECK_EQUAL(square_strings.str(), "h1");

  square_strings.str("");
  square_strings << bomchess::Square::kA8;
  BOOST_CHECK_EQUAL(square_strings.str(), "a8");

  square_strings.str("");
  square_strings << bomchess::Square::kH8;
  BOOST_CHECK_EQUAL(square_strings.str(), "h8");

  square_strings.str("");
  square_strings << bomchess::Square::kC5;
  BOOST_CHECK_EQUAL(square_strings.str(), "c5");
}

BOOST_AUTO_TEST_CASE(SquareGetFile) {
  BOOST_CHECK_EQUAL(bomchess::GetFile(bomchess::Square::kA1), 'a');
  BOOST_CHECK_EQUAL(bomchess::GetFile(bomchess::Square::kA8), 'a');
  BOOST_CHECK_EQUAL(bomchess::GetFile(bomchess::Square::kH2), 'h');
  BOOST_CHECK_EQUAL(bomchess::GetFile(bomchess::Square::kC3), 'c');
}

BOOST_AUTO_TEST_CASE(SquareGetFileThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::GetFile(static_cast<bomchess::Square>(-1)), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::GetFile(static_cast<bomchess::Square>(64)), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(SquareGetRank) {
  BOOST_CHECK_EQUAL(bomchess::GetRank(bomchess::Square::kA1), '1');
  BOOST_CHECK_EQUAL(bomchess::GetRank(bomchess::Square::kA8), '8');
  BOOST_CHECK_EQUAL(bomchess::GetRank(bomchess::Square::kH2), '2');
  BOOST_CHECK_EQUAL(bomchess::GetRank(bomchess::Square::kC3), '3');
}

BOOST_AUTO_TEST_CASE(SquareGetRankThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::GetRank(static_cast<bomchess::Square>(-1)), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::GetRank(static_cast<bomchess::Square>(64)), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(SquareFromFileRank) {
  BOOST_CHECK_EQUAL(bomchess::SquareFromFileRank('a', '1'), bomchess::Square::kA1);
  BOOST_CHECK_EQUAL(bomchess::SquareFromFileRank('A', '1'), bomchess::Square::kA1);
  BOOST_CHECK_EQUAL(bomchess::SquareFromFileRank('h', '2'), bomchess::Square::kH2);
}

BOOST_AUTO_TEST_CASE(SquareFromFileRankThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::SquareFromFileRank('a', 1), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::SquareFromFileRank('1', 'a'), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(SquareFromString) {
  BOOST_CHECK_EQUAL(bomchess::SquareFromString("a1"), bomchess::Square::kA1);
  BOOST_CHECK_EQUAL(bomchess::SquareFromString("A1"), bomchess::Square::kA1);
  BOOST_CHECK_EQUAL(bomchess::SquareFromString("H2"), bomchess::Square::kH2);
}

BOOST_AUTO_TEST_CASE(SquareFromStringThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::SquareFromString("a 1"), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::SquareFromString("i5"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(ChebyshevDistance) {
  BOOST_CHECK_EQUAL(bomchess::ChebyshevDistance(bomchess::Square::kA1, bomchess::Square::kH8), 7);
  BOOST_CHECK_EQUAL(bomchess::ChebyshevDistance(bomchess::Square::kA1, bomchess::Square::kB8), 7);
  BOOST_CHECK_EQUAL(bomchess::ChebyshevDistance(bomchess::Square::kC4, bomchess::Square::kC4), 0);
  BOOST_CHECK_EQUAL(bomchess::ChebyshevDistance(bomchess::Square::kC4, bomchess::Square::kD4), 1);
}

BOOST_AUTO_TEST_CASE(ManhattanDistance) {
  BOOST_CHECK_EQUAL(bomchess::ManhattanDistance(bomchess::Square::kA1, bomchess::Square::kH8), 14);
  BOOST_CHECK_EQUAL(bomchess::ManhattanDistance(bomchess::Square::kA1, bomchess::Square::kB8), 8);
  BOOST_CHECK_EQUAL(bomchess::ManhattanDistance(bomchess::Square::kC4, bomchess::Square::kC4), 0);
  BOOST_CHECK_EQUAL(bomchess::ManhattanDistance(bomchess::Square::kC4, bomchess::Square::kD4), 1);
}

BOOST_AUTO_TEST_CASE(KnightDistance) {
  BOOST_CHECK_EQUAL(bomchess::KnightDistance(bomchess::Square::kG1, bomchess::Square::kF1), 3);
  BOOST_CHECK_EQUAL(bomchess::KnightDistance(bomchess::Square::kG1, bomchess::Square::kA8), 5);
  BOOST_CHECK_EQUAL(bomchess::KnightDistance(bomchess::Square::kG1, bomchess::Square::kE2), 1);
}