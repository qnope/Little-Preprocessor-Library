#pragma once

#define LPL_PROBE UNUSED, 1
#define LPL_CHECK_IMPL(unused, n, ...) n
#define LPL_CHECK(expressionToTest) LPL_CHECK_IMPL(expressionToTest, 0, 0)

#define LPL_IS_PARENTHESIS_IMPL(...) LPL_PROBE
#define LPL_IS_PARENTHESIS(x) LPL_CHECK(LPL_IS_PARENTHESIS_IMPL x)

#define LPL_IS_NOT_PARENTHESIS(x) LPL_COMPL(LPL_IS_PARENTHESIS(x))

#define LPL_IS_0_0 LPL_PROBE
#define LPL_IS_0(...) LPL_CHECK(LPL_CAT(LPL_IS_0_, LPL_HEAD(__VA_ARGS__, ())))

#define LPL_IS_NOT_0(...) LPL_COMPL(LPL_IS_0(LPL_HEAD(__VA_ARGS__, ())))
