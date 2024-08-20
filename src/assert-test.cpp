#include "unwrap.hpp"

auto fail_n() -> void {
    unwrap(a, (int*)nullptr);
    assert(false, "ok");
}

auto fail_o() -> std::optional<int> {
    unwrap(a, (int*)nullptr);
    assert(false, "ok");
}

auto fail_b() -> bool {
    unwrap(a, (int*)nullptr);
    assert(false, "ok");
}

auto fail_i() -> int {
    unwrap(a, (int*)nullptr);
    assert(false, "ok");
}

auto fail_p() -> int* {
    unwrap(a, (int*)nullptr);
    assert(false, "ok");
}

struct S {
    auto fail_n() -> void {
        unwrap(a, (int*)nullptr);
        assert(false, "ok");
    }

    auto fail_o() -> std::optional<int> {
        unwrap(a, (int*)nullptr);
        assert(false, "ok");
    }

    auto fail_b() -> bool {
        unwrap(a, (int*)nullptr);
        assert(false, "ok");
    }

    auto fail_i() -> int {
        unwrap(a, (int*)nullptr);
        assert(false, "ok");
    }

    auto fail_p() -> int* {
        unwrap(a, (int*)nullptr);
        assert(false, "ok");
    }
};

auto main() -> int {
    fail_n();
    if(fail_o() != std::nullopt) return 1;
    if(fail_b() != false) return 1;
    if(fail_i() != -1) return 1;
    if(fail_p() != nullptr) return 1;

    auto s = S();
    s.fail_n();
    if(s.fail_o() != std::nullopt) return 1;
    if(s.fail_b() != false) return 1;
    if(s.fail_i() != -1) return 1;
    if(s.fail_p() != nullptr) return 1;

    print("pass");
    line_assert(false);
    line_panic();
    return 0;
}
