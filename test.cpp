#include "funcs.hpp"
#include <chrono>

int main()
{
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    std::vector<std::vector<int>> b;
    b.push_back(a);
    print_vec(slice_vector(1, 3, a));
    cel();
    print_vec(b);
    cel();
    //print_vec(permutate_vec(std::vector<int> {}));
    //cel();
    //print_vec(permutate_vec(std::vector<int> {1}));
    //cel();
    //print_vec(permutate_vec(std::vector<int> {1,2}));
    //cel();
    std::chrono::steady_clock sc;
    auto start = sc.now();
    b = permutate_vec(a);
    auto end = sc.now();
    printf("%lf detik.\n", static_cast<std::chrono::duration<double>>(end-start).count());
    printf("%ld\n", b.size());
    //print_vec(b);
}
