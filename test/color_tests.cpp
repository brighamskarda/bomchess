#define BOOST_TEST_MODULE "bomchess"

#include <sstream>

#include "boost/test/unit_test.hpp"

#include "color.h"

BOOST_AUTO_TEST_CASE(ColorOstream) {
  std::stringstream string_stream;
  string_stream << bomchess::Color::kWhite;
  BOOST_CHECK_EQUAL(string_stream.str(), "WHITE");

  string_stream.str("");
  string_stream << bomchess::Color::kBlack;
  BOOST_CHECK_EQUAL(string_stream.str(), "BLACK");

  string_stream.str("");
  string_stream << bomchess::Color::kNone;
  BOOST_CHECK_EQUAL(string_stream.str(), "NONE");

  string_stream.str("");
  string_stream << static_cast<bomchess::Color>(99);
  BOOST_CHECK_EQUAL(string_stream.str(), "NONE");
}