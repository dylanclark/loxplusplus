#pragma once

// explicit deduction guide - useful for helping implement pattern-matching like
// pattern with variant types
template <class... Ts> struct overloaded : Ts... {
    using Ts::operator()...;
};                                                             // (1)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // (2)
