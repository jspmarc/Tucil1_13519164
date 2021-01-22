#include "funcs.hpp"
#include <chrono>

int main()
{
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<std::vector<int>> b;
    std::chrono::steady_clock sc;
    auto start = sc.now();
    b = permutate_vec(a);
    auto end = sc.now();
    printf("%lf detik.\n", static_cast<std::chrono::duration<double>>(end-start).count());
    printf("%ld\n", b.size());
    print_vec(b);
}
