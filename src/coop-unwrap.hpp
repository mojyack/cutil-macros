#pragma once
#include "coop-assert.hpp"
#include "unwrap.hpp"

#define coop_unwrap(var, opt, ...)     generic_unwrap(coop_ensure, const, var, opt, __VA_ARGS__)
#define coop_unwrap_mut(var, opt, ...) generic_unwrap(coop_ensure, /*const*/, var, opt, __VA_ARGS__)
