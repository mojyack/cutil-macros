#include <memory>
#include <optional>

auto fail_n() -> Ret(void) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_o() -> Ret(std::optional<int>) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_o2() -> Ret(std::optional<int*>) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_b() -> Ret(bool) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_i() -> Ret(int) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_p() -> Ret(int*) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_up() -> Ret(std::unique_ptr<int>) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_sp() -> Ret(std::shared_ptr<int>) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

auto fail_cp() -> Ret(const int*) {
    _unwrap(a, (int*)nullptr);
    _ensure(false, "ok");
    (void)a;
}

struct S {
    static auto fail_n() -> Ret(void) {
        _unwrap(a, (int*)nullptr);
        _ensure(false, "ok");
        (void)a;
    }

    virtual auto fail_o() -> Ret(std::optional<int>) {
        _unwrap(a, (int*)nullptr);
        _ensure(false, "ok");
        (void)a;
    }

    auto fail_b() -> Ret(bool) {
        _unwrap(a, (int*)nullptr);
        _ensure(false, "ok");
        (void)a;
    }

    auto fail_i() -> Ret(int) {
        _unwrap(a, (int*)nullptr);
        _ensure(false, "ok");
        (void)a;
    }

    auto fail_p() -> Ret(int*) {
        _unwrap(a, (int*)nullptr);
        _ensure(false, "ok");
        (void)a;
    }
};

auto pass = false;

auto test() -> Ret(void) {
    _await fail_n();
    if(_await fail_o() != std::nullopt) _return;
    if(_await fail_o2() != std::nullopt) _return;
    if(_await fail_b() != false) _return;
    if(_await fail_i() != -1) _return;
    if(_await fail_p() != nullptr) _return;
    if(_await fail_up() != nullptr) _return;
    if(_await fail_sp() != nullptr) _return;
    if(_await fail_cp() != nullptr) _return;

    auto   s = S();
    _await s.fail_n();
    if(_await s.fail_o() != std::nullopt) _return;
    if(_await s.fail_b() != false) _return;
    if(_await s.fail_i() != -1) _return;
    if(_await s.fail_p() != nullptr) _return;

    pass = true;
}
