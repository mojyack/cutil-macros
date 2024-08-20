#pragma once
#ifndef CUTIL_MACROS_NO_AUTO_INCLUDE
#include "util/assert.hpp"
#endif

#define assert_v(cond, ret, ...)                                      \
    if(!(cond)) {                                                     \
        line_warn("assertion failed" __VA_OPT__(": ", ) __VA_ARGS__); \
        return ret;                                                   \
    }

#define assert_n(cond, ...) assert_v(cond, , __VA_ARGS__)
#define assert_o(cond, ...) assert_v(cond, std::nullopt, __VA_ARGS__)
#define assert_b(cond, ...) assert_v(cond, false, __VA_ARGS__)
#define assert_p(cond, ...) assert_v(cond, nullptr, __VA_ARGS__)
