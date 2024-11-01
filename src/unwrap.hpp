#pragma once
#include "assert.hpp"

#define generic_unwrap(const, var, opt, ...) \
    const auto var##_o = opt;                \
    ensure(var##_o, __VA_ARGS__);            \
    const auto& var = *var##_o;

#define unwrap(var, opt, ...)     generic_unwrap(const, var, opt, __VA_ARGS__)
#define unwrap_mut(var, opt, ...) generic_unwrap(/*const*/, var, opt, __VA_ARGS__)

#define generic_unwrap_v(const, var, opt, ...) \
    const auto var##_o = opt;                  \
    ensure_v(var##_o, __VA_ARGS__);            \
    const auto& var = *var##_o;

#define unwrap_v(var, opt, ...)     generic_unwrap_v(const, var, opt, __VA_ARGS__)
#define unwrap_v_mut(var, opt, ...) generic_unwrap_v(/*const*/, var, opt, __VA_ARGS__)

#define co_generic_unwrap_v(const, var, opt, ...) \
    const auto var##_o = opt;                  \
    co_ensure_v(var##_o, __VA_ARGS__);            \
    const auto& var = *var##_o;

#define co_unwrap_v(var, opt, ...)     co_generic_unwrap_v(const, var, opt, __VA_ARGS__)
#define co_unwrap_v_mut(var, opt, ...) co_generic_unwrap_v(/*const*/, var, opt, __VA_ARGS__)
