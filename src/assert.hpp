#include <optional>
#include <source_location>

#pragma once
#ifndef CUTIL_MACROS_NO_AUTO_INCLUDE
#include "util/assert.hpp"
#endif

template <bool is_void, bool is_bool, bool is_int, bool is_opt, bool is_ptr>
auto return_error() -> auto {
    if constexpr(is_void) {
        return;
    } else if constexpr(is_bool) {
        return false;
    } else if constexpr(is_int) {
        return -1;
    } else if constexpr(is_opt) {
        return std::nullopt;
    } else if constexpr(is_ptr) {
        return nullptr;
    } else {
        static_assert(false);
    }
}

#define bail(...)                                                                                              \
    {                                                                                                          \
        line_warn(__VA_ARGS__);                                                                                \
        constexpr auto fn      = std::source_location::current().function_name();                              \
        constexpr auto str     = std::string_view(fn);                                                         \
        constexpr auto type    = str.substr(str.starts_with("static ") * 7 + str.starts_with("virtual ") * 8); \
        constexpr auto is_void = type.starts_with("void ") && str[5] != '*';                                   \
        constexpr auto is_bool = type.starts_with("bool ") && str[5] != '*';                                   \
        constexpr auto is_int  = type.starts_with("int ") && str[4] != '*';                                    \
        constexpr auto is_opt  = type.starts_with("std::optional<");                                           \
        constexpr auto is_ptr  = true; /* TODO: handle template return type */                                 \
        return return_error<is_void, is_bool, is_int, is_opt, is_ptr>();                                       \
    }

#define ensure(cond, ...)                                        \
    if(!(cond)) {                                                \
        bail("assertion failed" __VA_OPT__(": ", ) __VA_ARGS__); \
    }

struct VoidErrorType {};

template <class T>
consteval auto return_error_v(T error_value) -> auto {
    if constexpr(std::is_same_v<decltype(error_value), VoidErrorType>) {
        return;
    } else {
        return error_value;
    }
}

constexpr auto error_value = VoidErrorType{};

// constexpr auto error_value = (-1, std::nullopt, nullptr, ...)
#define bail_v(...)                         \
    {                                       \
        line_warn(__VA_ARGS__);             \
        return return_error_v(error_value); \
    }

#define ensure_v(cond, ...)                                        \
    if(!(cond)) {                                                  \
        bail_v("assertion failed" __VA_OPT__(": ", ) __VA_ARGS__); \
    }
