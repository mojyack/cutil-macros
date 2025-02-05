#include <memory>
#include <optional>

#include "unwrap.hpp"

auto fail_n() -> void {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_o() -> std::optional<int> {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_b() -> bool {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_i() -> int {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_p() -> int* {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_up() -> std::unique_ptr<int> {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_sp() -> std::shared_ptr<int> {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

auto fail_cp() -> const int* {
    unwrap(a, (int*)nullptr);
    ensure(false, "ok");
    (void)a;
}

struct S {
    static auto fail_n() -> void {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
        (void)a;
    }

    virtual auto fail_o() -> std::optional<int> {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
        (void)a;
    }

    auto fail_b() -> bool {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
        (void)a;
    }

    auto fail_i() -> int {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
        (void)a;
    }

    auto fail_p() -> int* {
        unwrap(a, (int*)nullptr);
        ensure(false, "ok");
        (void)a;
    }
};

auto main() -> int {
    fail_n();
    if(fail_o() != std::nullopt) return 1;
    if(fail_b() != false) return 1;
    if(fail_i() != -1) return 1;
    if(fail_p() != nullptr) return 1;
    if(fail_up() != nullptr) return 1;
    if(fail_sp() != nullptr) return 1;
    if(fail_cp() != nullptr) return 1;

    auto s = S();
    s.fail_n();
    if(s.fail_o() != std::nullopt) return 1;
    if(s.fail_b() != false) return 1;
    if(s.fail_i() != -1) return 1;
    if(s.fail_p() != nullptr) return 1;

    std::println("pass");
    ASSERT(false, "with {}", "message");
    PANIC();
    return 0;
}
