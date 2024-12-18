#include <optional>

#include "unwrap.hpp"
#include "util/print.hpp"

auto fail_n() -> void {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

auto fail_o() -> std::optional<int> {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

auto fail_b() -> bool {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

auto fail_i() -> int {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

auto fail_p() -> int* {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

auto fail_cp() -> const int* {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
}

struct S {
    static auto fail_n() -> void {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
    }

    virtual auto fail_o() -> std::optional<int> {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
    }

    auto fail_b() -> bool {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
    }

    auto fail_i() -> int {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
    }

    auto fail_p() -> int* {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
    }
};

auto main() -> int {
    fail_n();
    if(fail_o() != std::nullopt) return 1;
    if(fail_b() != false) return 1;
    if(fail_i() != -1) return 1;
    if(fail_p() != nullptr) return 1;
    if(fail_cp() != nullptr) return 1;

    auto s = S();
    s.fail_n();
    if(s.fail_o() != std::nullopt) return 1;
    if(s.fail_b() != false) return 1;
    if(s.fail_i() != -1) return 1;
    if(s.fail_p() != nullptr) return 1;

    print("pass");
    ASSERT(false);
    PANIC();
    return 0;
}
