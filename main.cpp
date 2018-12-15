#include "lpl/lpl.h"
#include <cassert>
#include <iostream>

#include <string_view>

#define WRITE(id) id LPL_DEFER(WRITE_I)()(id)
#define WRITE_I() WRITE

#define A() 125
int main() {
  static_assert(LPL_DEC(8) == 7);
  static_assert(LPL_INC(5) == 6);

  static_assert(LPL_CHECK(LPL_PROBE) == 1);
  static_assert(LPL_CHECK(blah) == 0); // 0
  static_assert(LPL_IS_PARENTHESES((char)) == 1);

  static_assert(LPL_IS_PARENTHESES(()) == 1);
  static_assert(LPL_IS_PARENTHESES(blah) == 0);

  static_assert(LPL_IS_NOT_PARENTHESES(()) == 0);
  static_assert(LPL_IS_NOT_PARENTHESES(blah) == 1);

  static_assert(A() == 125);
  static_assert(LPL_EVAL(LPL_DEFER_TWICE(A)()) == 125);

  static_assert(LPL_IS_0(5) == 0);
  static_assert(LPL_IS_0(0) == 1);

  static_assert(LPL_IS_NOT_0(5) == 1);
  static_assert(LPL_IS_NOT_0(0) == 0);

  static_assert(LPL_IF(0)(1, 0) == 0);
  static_assert(LPL_IF(1)(1, 0) == 1);
  static_assert(LPL_IF(5)(1, 0) == 1);

  static_assert(LPL_WHEN(1)(1) == 1);

  static_assert(LPL_AND(LPL_IS_PARENTHESES(())) == 1);
  static_assert(LPL_AND(LPL_IS_PARENTHESES(x)) == 0);
  static_assert(LPL_AND(1, 3, 1, 4, 5, 1) == 1);
  static_assert(LPL_AND(1, 0) == 0);
  static_assert(LPL_AND(0, 1, 3, 1, 4, 5, 1) == 0);
  static_assert(LPL_AND(1, 3, 1, 4, 5, 0, 1) == 0);

  static_assert(LPL_OR(0, 1) == 1);
  static_assert(LPL_OR(0, 0) == 0);
  static_assert(LPL_OR(1, 1) == 1);
  static_assert(LPL_OR(1, 1) == 1);

  std::cout << "AND : ";
  std::cout << LPL_STRINGIFY(LPL_AND(1, 0)) << ";";
  std::cout << LPL_STRINGIFY(LPL_AND(1, 1)) << std::endl;
  std::cout << "OR : ";
  std::cout << LPL_STRINGIFY(LPL_OR(1, 0)) << ";";
  std::cout << LPL_STRINGIFY(LPL_OR(0, 0)) << std::endl;

  std::cout << LPL_STRINGIFY(LPL_EVAL(WRITE(blah)))
            << std::endl; // Lot of blah wrote

#define F(x) x,

  std::cout << LPL_STRINGIFY(LPL_MAP(F, 0, 1, 2, 3, 4, 5)) << std::endl;
  return 0;
}
