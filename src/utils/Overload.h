#pragma once

namespace utils {

// Helper to overload multiple lambdas
template<class... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;

} // namespace utils
