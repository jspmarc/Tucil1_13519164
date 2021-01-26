#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::vector<int>> new_perm(int length, int batasBawah, int batasAtas)
{
    if (length == 0) return {{}};
    if (length == 1)
    {
        std::vector<int> numbers(batasAtas-batasBawah);
        for (int i = batasBawah; i < batasAtas; ++i)
            numbers[i-batasBawah] = i;
        return {numbers};
    }
    if (length == 2)
    {
        std::vector<std::vector<int>> numbers;
        for (int i = batasBawah; i < batasAtas; ++i)
            for (int j = batasBawah; j < batasAtas; ++j)
                if (i != j)
                    numbers.push_back({i, j});

        return numbers;
    }

    std::vector<std::vector<int>> perm = new_perm(length-1, batasBawah, batasAtas);
    std::vector<std::vector<int>> l;
    for (std::vector<int> p: perm)
    {
        bool numbersInVec[] = {
            false, false, false, false, false,
            false, false, false, false, false
        };
        for (int i: p) numbersInVec[i] = true;

        for (int i = batasBawah; i < batasAtas; ++i)
        {
            if (!numbersInVec[i])
            {
                std::vector<int> temp(p.size());
                std::copy(p.begin(), p.end(), temp.begin());
                temp.push_back(i);
                l.push_back(temp);
            }
        }
    }

    return l;
}

template <typename T>
std::vector<std::vector<T>> perm1(std::vector<T> vec)
{
    if (vec.size() == 0) return {{}};
    else if (vec.size() == 1) return {vec};
    else if (vec.size() == 2) return {vec, {vec[1], vec[0]}};

    /// vektor yang menampung hasil semua permutasi
    std::vector<std::vector<T>> newVec;
    /// elemen pertama vektor
    T first = vec[0];
    /// sisa elemen vektor
    //std::vector<T> rest(vec.begin()+1, vec.end());
    /// tail yang sudah dipermutasi
    std::vector<std::vector<T>> permutated = perm1(std::vector<T>(vec.begin()+1, vec.end()));

    // tambahin first ke setiap hasil permutasi tail

    /// elemen dari permutated (tail yang sudah dipermutasi)
    for (std::vector<T> p: permutated)
    {
        for (size_t i = 0; i < p.size() + 1; ++i)
        {
            /// vektor yang akan dipush ke newVec
            std::vector<T> toBePushed(p.begin(), p.begin()+i);
            toBePushed.push_back(first);
            toBePushed.insert(toBePushed.end(), p.begin()+i, p.end());

            newVec.push_back(toBePushed);
        }
    }

    return newVec;
}

int main()
{
    std::chrono::steady_clock sc;
    std::vector<std::vector<int>> a, b;
    auto start = sc.now();
    a = perm1(std::vector<int>({0,1,2,3,4,5,6,7,8,9}));
    auto end = sc.now();
    auto timeSpend = static_cast<std::chrono::duration<double>> (end-start);
    std::cout << "Old permutation took: " << timeSpend.count() << " seconds.\n";

    start = sc.now();
    b = new_perm(10, 0, 10);
    end = sc.now();
    timeSpend = static_cast<std::chrono::duration<double>> (end-start);
    std::cout << "New permutation took: " << timeSpend.count() << " seconds.\n";
}
