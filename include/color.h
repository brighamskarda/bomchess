#ifndef COLOR_H
#define COLOR_H

#include <ostream>

namespace bomchess {
enum class Color { kWhite, kBlack, kNone };

constexpr std::ostream& operator<<(std::ostream& os, const Color color) noexcept {
  switch (color) {
    case Color::kWhite:
      os << "WHITE";
      break;
    case Color::kBlack:
      os << "BLACK";
      break;
    default:
      os << "NONE";
      break;
  }
  return os;
}
}  // namespace bomchess

#endif  // COLOR_H
