#pragma once
#include <source_location>

#include "assert.hpp"

template <comptime::String func>
constexpr auto coop_detect_error_value() -> auto {
    constexpr auto str000 = func;
    constexpr auto str010 = comptime::remove_prefix<str000, "static ">;
    constexpr auto str020 = comptime::remove_prefix<str010, "virtual ">;
    constexpr auto str030 = comptime::remove_prefix<str020, "const ">;
    constexpr auto marker = comptime::String("coop::Async<");
    constexpr auto open   = comptime::find<str030, marker>;
    if constexpr(open == std::string_view::npos) {
        return;
    } else {
        constexpr auto region = comptime::find_region<str030, '<', '>'>;
        if constexpr(region.first == std::string_view::npos) {
            return;
        } else {
            constexpr auto ret = comptime::substr<str030, region.first + 1, region.second - 2>;
            if constexpr(ret[-1] == '*') {
                return nullptr;
            } else {
                return type_string_to_type<comptime::remove_region<ret, '<', '>'>>();
            }
        }
    }
}

#define coop_bail(...)                    \
    CUTIL_MACROS_PRINT_FUNC(__VA_ARGS__); \
    co_return coop_detect_error_value<CUTIL_COMPSTR(std::source_location::current().function_name())>();

#define coop_ensure(cond, ...)                                      \
    if(!(cond)) {                                                   \
        coop_bail("assertion failed" __VA_OPT__(": ") __VA_ARGS__); \
    }
