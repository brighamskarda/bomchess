#define BOOST_TEST_MODULE "bomchess"

#include <ostream>
#include <stdexcept>

#include "boost/test/unit_test.hpp"

#include "move.h"
#include "piece.h"

BOOST_AUTO_TEST_CASE(MoveFromUCI) {
  BOOST_CHECK_EQUAL(bomchess::FromUCI("a2a4"),
                    bomchess::Move(bomchess::Square::kA2, bomchess::Square::kA4, bomchess::PieceType::kNone));
  BOOST_CHECK_EQUAL(bomchess::FromUCI("h2h1K"),
                    bomchess::Move(bomchess::Square::kH2, bomchess::Square::kH1, bomchess::PieceType::kKing));
  BOOST_CHECK_EQUAL(bomchess::FromUCI("h2h1k"),
                    bomchess::Move(bomchess::Square::kH2, bomchess::Square::kH1, bomchess::PieceType::kKing));
  BOOST_CHECK_EQUAL(bomchess::FromUCI("E5D5"),
                    bomchess::Move(bomchess::Square::kE5, bomchess::Square::kD5, bomchess::PieceType::kNone));
}

BOOST_AUTO_TEST_CASE(MoveFromUCIThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::FromUCI("a2z4"), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::FromUCI("h2h1o"), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::FromUCI("h2h1pp"), std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::FromUCI("h2h"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(MoveToUCI) {
  BOOST_CHECK_EQUAL(
      bomchess::ToUCI(bomchess::Move(bomchess::Square::kA2, bomchess::Square::kA4, bomchess::PieceType::kNone)),
      "a2a4");
  BOOST_CHECK_EQUAL(
      bomchess::ToUCI(bomchess::Move(bomchess::Square::kH2, bomchess::Square::kH1, bomchess::PieceType::kKing)),
      "h2h1K");
  BOOST_CHECK_EQUAL(
      bomchess::ToUCI(bomchess::Move(bomchess::Square::kE5, bomchess::Square::kD5, bomchess::PieceType::kNone)),
      "e5d5");
}

BOOST_AUTO_TEST_CASE(MoveToUCIThrows) {
  BOOST_CHECK_THROW(std::ignore = bomchess::ToUCI(
                        bomchess::Move(bomchess::Square::kA2, bomchess::Square::kNone, bomchess::PieceType::kNone)),
                    std::invalid_argument);
  BOOST_CHECK_THROW(std::ignore = bomchess::ToUCI(bomchess::Move(bomchess::Square::kA2, bomchess::Square::kA4,
                                                                 static_cast<bomchess::PieceType>(99))),
                    std::invalid_argument);
}
