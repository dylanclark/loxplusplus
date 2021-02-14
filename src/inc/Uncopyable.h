#pragma once

namespace Loxpp {
struct Uncopyable {
    explicit Uncopyable() = default;
    virtual ~Uncopyable() = default;
    // Delete copy and move constrs
    Uncopyable(const Uncopyable&) = delete;
    auto operator=(const Uncopyable&) -> Uncopyable& = delete;
    Uncopyable(Uncopyable&&) = delete;
    auto operator=(Uncopyable&&) -> Uncopyable& = delete;
};

} // namespace Loxpp