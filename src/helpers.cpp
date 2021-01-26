/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#include "headers/helpers.hpp"
#include <utility> // pairs
#include <vector> // vector
#include <stdlib.h> // exit()
#include <sysexits.h> // exit codes
#include <iostream> // string, cout, cerr
#include <unordered_map> // unordered_map
#include <fstream> // file operation

template <typename T>
void print_vec(std::vector<T> vec)
{
    std::cout << '[';
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ',';
    std::cout << ']';
}

template <typename T>
void print_vec(std::vector<std::vector<T>> vec)
{
    std::cout << "[\n";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << '\t';
        print_vec(*it);
        std::cout << ",\n";
    }
    std::cout << ']';
}

template <typename K, typename V>
void print_map(std::unordered_map<K, V> umap)
{
    std::cout << "[";
    for (auto it = umap.begin(); it != umap.end(); ++it)
        std::cout << '<' << it->first << ',' << it->second << ">,";
    std::cout << "]";
}
