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
#include <iostream>
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
    free(namaFile);

    /// Vektor untuk menyimpan semua jawaban
    std::vector<std::vector<int>> answers(semuaSoal.size());

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

        std::pair<std::vector<int>, int> result;

        // dekripsi dan tuliskan hasil
        result = decrypt_cryparithm(*it);
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

    printf("Total waktu eksekusi dekripsi %lu soal dan menuliskan output membutuhkan %lf detik.\n",
            semuaSoal.size(), timeSpend.count());
}
