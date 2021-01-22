/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#include <chrono> // itung waktu eksekusi
#include <utility> // pairs
#include <vector> // vector
#include <stdlib.h> // exit()
#include <sysexits.h> // exit codes
#include <stdio.h> // printf(), puts()
#include <iostream> // string, cout
#include <unordered_map> // unordered_map
#include "helpers.hpp"

#define MAX_UNIQUE_LETTERS 10
#define debug1() puts("males belajar tapi...")
#define debug2() puts("pengen kaya")
#define debug3() puts("haha lucu lo badut")
#define cel() puts("")

// *** DEKLARASI FUNGSI-FUNGSI ***

/**
 * Fungsi untuk membuat semua kemungkinan permutasi dari suatu vektor
 *
 * @tparam T tipe data yang disimpan pada vektor
 * @param vec vektor yang ingin dibuat permutasinya
 * @returns vektor yg berisi vektor-vektor hasil permutasi
 */
template <typename T>
std::vector<std::vector<T>> permutate_vec(std::vector<T> vec);

/**
 * Fungsi untuk menghasilkan list dari permutasi-permutasi mungkin dari
 * angka-angka dalam range [0..lim]
 *
 * @param lim batas atas angka
 */
std::vector<std::vector<int>> generate_permutated_numbers(int lim);

// *** END ***

int main(int argc, char *argv[])
{
    /// Vektor untuk nyimpen semua soal
    std::vector<std::vector<std::string>> semuaSoal;

    if (argc != 2)
    {
        /*
        fscanf(stderr, "Penggunaan: %s [nama file soal]\n", argv[0]);
        exit(EX_USAGE);
        */

        /// string berisi nama file soal
        char* namaFile;
        namaFile = (char *) malloc(128 * sizeof(char));

        printf("Masukkan nama file: ");
        scanf("%s", namaFile);
        getchar();
        parse_file(namaFile, &semuaSoal);
        free(namaFile);
    }
    else parse_file(argv[1], &semuaSoal);

    std::chrono::steady_clock sc;

    /// Vektor untuk menyimpan semua jawaban
    std::vector<std::unordered_map<char, int>> answers(semuaSoal.size());
    /// Vektor untuk menyimpan semua kemungkinan permutasi dari [0..9]
    std::vector<std::vector<int>> permutatedNumbers = generate_permutated_numbers(MAX_UNIQUE_LETTERS);

    /// awal perhitungan waktu semua soal
    auto start = sc.now();
    for (std::vector<std::vector<std::string>>::iterator it =
            semuaSoal.begin(); it != semuaSoal.end(); ++it)
    {
        /// awal hitungan waktu
        auto partialStart = sc.now();

        /// counter iterasi
        int i = it - semuaSoal.begin();
        /// jumlah kasus yg diuji
        int cases;

        std::pair<std::unordered_map<char, int>, int> result;

        // dekripsi dan tuliskan hasil
        result = decrypt_cryparithm(*it, permutatedNumbers);
        answers[i] = result.first;
        cases = result.second;

        print_answer(*it, answers[i]);
        printf("\n");

        /// akhir hitungan waktu
        auto partialEnd = sc.now();
        auto partialTimeSpend = static_cast<std::chrono::duration<double>>(partialEnd-partialStart);
        printf("Soal ke-%d membutuhkan: %lf detik.\n", i+1, partialTimeSpend.count());
        printf("Jumlah kasus yang diuji adalah %d.\n\n", cases);
    }

    // akhir perhitungan waktu semua soal
    auto end = sc.now();
    auto timeSpend = static_cast<std::chrono::duration<double>>(end-start);

    printf("Total waktu permutasi, eksekusi dekripsi %lu soal, dan menuliskan output membutuhkan %lf detik.\n",
            semuaSoal.size(), timeSpend.count());
}

template <typename T>
std::vector<std::vector<T>> permutate_vec(std::vector<T> vec)
{
    if (vec.size() == 0) return {{}};
    else if (vec.size() == 1) return {vec};
    else if (vec.size() == 2) return {vec, {vec[1], vec[0]}};

    /// vektor yang menampung hasil semua permutasi
    std::vector<std::vector<T>> newVec;
    /// elemen pertama vektor
    T first = vec[0];
    /// sisa elemen vektor
    std::vector<T> rest(vec.size()-1);
    std::copy(vec.begin()+1, vec.end(), rest.begin());
    /// tail yang sudha dipermutasi
    std::vector<std::vector<T>> permutated = permutate_vec(rest);

    // p harusnya std::vector<std::vector<T>>::iterator
    for (auto p = permutated.begin(); p != permutated.end(); ++p)
    {
        for (size_t i = 0; i < p->size() + 1; ++i)
        {
            // kode python:
            // toBePushed[:i] + [first] + toBePushed[i:]

            /// vektor yang akan dipush ke newVec
            std::vector<T> toBePushed(p->begin(), p->begin()+i); // toBePushed[:i]
            toBePushed.push_back(first); // + [first]
            toBePushed.insert(toBePushed.end(), p->begin()+i, p->end()); // + toBePushed[i:]

            newVec.push_back(toBePushed);
        }
    }

    return newVec;
}

std::vector<std::vector<int>> generate_permutated_numbers(int lim)
{

    /// vektor untuk menyimpan angka-angka pada vektor
    std::vector<int> numbers(10);
    for (int i = 0; i < 10; ++i)
        numbers[i] = i;

    std::vector<std::vector<int>> hasil = permutate_vec(numbers);

    return hasil;
}
