#pragma once
#include <optional>
#include <source_location>

#include "print.hpp"

#ifndef CUTIL_MACROS_NO_AUTO_INCLUDE
#include "util/assert.hpp"
#endif

#ifndef CUTIL_MACROS_PRINT_FUNC
#define CUTIL_MACROS_PRINT_FUNC WARN
#endif

#define PANIC(...)                                                       \
    CUTIL_MACROS_PRINT_FUNC("fatal error" __VA_OPT__(": ") __VA_ARGS__); \
    panic("");

#define ASSERT(cond, ...)   \
    if(!(cond)) {           \
        PANIC(__VA_ARGS__); \
    }

template <comptime::String str>
constexpr auto type_string_to_type() -> auto {
    if constexpr(comptime::starts_with<str, "std::unique_ptr<"> ||
                 comptime::starts_with<str, "std::shared_ptr<">) {
        return nullptr;
    } else if constexpr(str.str() == "void") {
        return;
    } else if constexpr(str.str() == "bool") {
        return false;
    } else if constexpr(str.str() == "int") {
        return -1;
    } else if constexpr(comptime::starts_with<str, "std::optional<">) {
        return std::nullopt;
    } else {
        return;
    }
}

template <comptime::String func>
constexpr auto detect_error_value() -> auto {
    constexpr auto str000 = func;
    constexpr auto str010 = comptime::remove_prefix<str000, "static ">;
    constexpr auto str020 = comptime::remove_prefix<str010, "virtual ">;
    constexpr auto str030 = comptime::remove_prefix<str020, "const ">;
    constexpr auto space  = comptime::find<str030, " ">;
    if constexpr(space == std::string_view::npos) {
        return;
    } else {
        constexpr auto ret  = comptime::substr<str030, 0, space>;
        constexpr auto name = comptime::substr<str030, space + 1>;
        if constexpr(ret[-1] == '*' || name[0] == '*') {
            return nullptr;
        } else {
            return type_string_to_type<ret>();
        }
    }
}

#define bail(...)                         \
    CUTIL_MACROS_PRINT_FUNC(__VA_ARGS__); \
    return detect_error_value<CUTIL_COMPSTR(std::source_location::current().function_name())>();

#define ensure(cond, ...)                                      \
    if(!(cond)) {                                              \
        bail("assertion failed" __VA_OPT__(": ") __VA_ARGS__); \
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
#define bail_v(...)                           \
    {                                         \
        CUTIL_MACROS_PRINT_FUNC(__VA_ARGS__); \
        return return_error_v(error_value);   \
    }

#define ensure_v(cond, ...)                                      \
    if(!(cond)) {                                                \
        bail_v("assertion failed" __VA_OPT__(": ") __VA_ARGS__); \
    }

#define co_bail_v(...)                         \
    {                                          \
        CUTIL_MACROS_PRINT_FUNC(__VA_ARGS__);  \
        co_return return_error_v(error_value); \
    }

#define co_ensure_v(cond, ...)                                      \
    if(!(cond)) {                                                   \
        co_bail_v("assertion failed" __VA_OPT__(": ") __VA_ARGS__); \
    }
