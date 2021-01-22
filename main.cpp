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
#include "funcs.hpp"

int main(int argc, char *argv[])
{
    char* namaFile;
    namaFile = (char *) malloc(128 * sizeof(char));

    if (argc != 2)
    {
        /*
        fprintf(stderr, "Penggunaan: %s [nama file soal]\n", argv[0]);
        exit(EX_USAGE);
        */

        printf("Masukan nama file: ");
        scanf("%s", namaFile);
        getchar();
    }
    else
    {
        free(namaFile);
        namaFile = argv[1];
    }

    /// Vektor untuk nyimpen semua soal
    std::vector<std::vector<std::string>> semuaSoal;

    std::chrono::steady_clock sc;

    parse_file(namaFile, &semuaSoal);

    /// Vektor untuk menyimpan semua jawaban
    std::vector<std::unordered_map<char, int>> answers(semuaSoal.size());

    /// awal perhitungan waktu semua soal
    auto start = sc.now();
    /// vektor untuk menyimpan hasil permutasi dari 0 sampai 10
    std::vector<std::vector<int>> permutatedNumbers = generatePermutatedNumbers(MAX_UNIQUE_LETTERS);
    /// akhir waktu perhitungan waktu membuat permutasi angka-angka
    auto endPermutation = sc.now();
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
    auto permutationTimeSpend = static_cast<std::chrono::duration<double>>(endPermutation - start);

    printf("Waktu untuk membuat permutasi adalah %lf.\n", permutationTimeSpend.count());
    printf("Total waktu permutasi, eksekusi dekripsi %lu soal, dan menuliskan output membutuhkan %lf detik.\n",
            semuaSoal.size(), timeSpend.count());
}
