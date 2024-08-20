#include <source_location>

#pragma once
#ifndef CUTIL_MACROS_NO_AUTO_INCLUDE
#include "util/assert.hpp"
#endif

template <bool is_void, bool is_bool, bool is_int, bool is_opt, bool is_ptr>
auto return_error() -> auto {
    if constexpr(is_void) {
        print("void");
        return;
    } else if constexpr(is_bool) {
        print("bool");
        return false;
    } else if constexpr(is_int) {
        print("int");
        return -1;
    } else if constexpr(is_opt) {
        print("opt");
        return std::nullopt;
    } else if constexpr(is_ptr) {
        print("ptr");
        return nullptr;
    } else {
        static_assert(false);
    }
}

#define bail(...)                                                                 \
    {                                                                             \
        line_warn(__VA_ARGS__);                                                   \
        constexpr auto fn      = std::source_location::current().function_name(); \
        constexpr auto str     = std::string_view(fn);                            \
        constexpr auto is_void = str.starts_with("void ") && str[5] != '*';       \
        constexpr auto is_bool = str.starts_with("bool ") && str[5] != '*';       \
        constexpr auto is_int  = str.starts_with("int ") && str[4] != '*';        \
        constexpr auto is_opt  = str.starts_with("std::optional<");               \
        constexpr auto is_ptr  = true; /* TODO: handle template return type */    \
        return return_error<is_void, is_bool, is_int, is_opt, is_ptr>();          \
    }

#define assert(cond, ...)                                        \
    if(!(cond)) {                                                \
        bail("assertion failed" __VA_OPT__(": ", ) __VA_ARGS__); \
    }

// constexpr auto error_value = (-1, std::nullopt, nullptr, ...)
#define bail_v(...)             \
    {                           \
        line_warn(__VA_ARGS__); \
        return error_value;     \
    }

#define assert_v(cond, ...)                                        \
    if(!(cond)) {                                                  \
        bail_v("assertion failed" __VA_OPT__(": ", ) __VA_ARGS__); \
    }
