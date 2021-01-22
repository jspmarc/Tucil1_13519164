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

// *** DEKLARASI FUNGSI-FUNGSI ***

/**
 * Fungsi untuk membuat permutasi semua permutasi yang mungkin dari suatu
 * vektor dengan panjang length dengan nilai elemen di dalam vektor
 * [batasBawah..batasAtas)
 *
 * @param length panjang vektor yang diinginkan
 * @param batasBawah nilai batas bawah elemen vektor (inklusif)
 * @param batasAtas nilai batas atas elemen vektor (ekslusif)
 * @returns vektor dari vektor-vektor dengan panjang length yang berisi semua
 * kemungkinan permutasi dari angka-angka pada [batasBawah..batasAtas)
 */
std::vector<std::vector<int>> new_perm(int length, int batasBawah, int batasAtas);

/**
 * fungsi untuk mencari angka duplikat di dalam vektor,
 * dibatasi sampai 10 angka [0..9]
 *
 * @param vec vektor yang ingin dicari duplikat
 * @param dup angka yang ingin dicari duplikatnya
 * @returns true jika dup merupakan angka duplikat di vec
 */
bool is_duplicate_number(std::vector<int> vec, int dup);

/**
 * Fungsi untuk mendekripsi Cryptarithmetic
 *
 * @param soal soal yang mau didekripsi
 * @returns sebuah pair berisi solusi benar dan jumlah kasus yang dikerjakan
 */
std::pair<std::vector<int>, int> decrypt_cryparithm(std::vector<std::string> soal);

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

    printf("Total waktu eksekusi dekripsi %lu soal dan menuliskan output adalah %lf detik.\n",
            semuaSoal.size(), timeSpend.count());
}

std::vector<std::vector<int>> new_perm(int length, int batasBawah, int batasAtas)
{
    /*
     * Kode Python:
     * ```py
        def newPerm(length: int, batas_bawah: int, batas_atas:int) -> list[list]:
            if (length == 0):
                return []
            elif (length == 1):
                l = [i for i in range(batas_bawah, batas_atas)]
                return [l]
            elif (length == 2):
                l = [[i, j] for i in range(batas_bawah, batas_atas) for j in range(batas_bawah, batas_atas) if i != j]
                return l

            # else
            perm = newPerm(length-1, batas_bawah, batas_atas)
            l = []
            for p in perm:
                for i in range(batas_bawah, batas_atas):
                    if not (i in p):
                        l.append(p + [i])
            return l
     * ```
     */
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
        {
            for (int j = batasBawah; j < batasAtas; ++j)
            {
                if (i != j)
                    numbers.push_back({i, j});
            }
        }

        return numbers;
    }

    std::vector<std::vector<int>> perm = new_perm(length-1, batasBawah, batasAtas);
    std::vector<std::vector<int>> l;
    for (std::vector<int> p: perm)
    {
        for (int i = batasBawah; i < batasAtas; ++i)
        {
            if (!is_duplicate_number(p, i))
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

bool is_duplicate_number(std::vector<int> vec, int dup)
{
    bool usedNumbers[] = {
        false, false, false, false, false,
        false, false, false, false, false
    };

    for (int i: vec) usedNumbers[i] = true;

    return usedNumbers[dup];
}

std::pair<std::vector<int>, int> decrypt_cryparithm(std::vector<std::string> soal)
{
    // proses perisapan dan inisialisasi

    /// vektor u/ nampung operands yg udh diubah ke dalam bentuk bilangan
    std::vector<int> operandInNumbers(soal.size());
    /// vektor untuk menyimpan huruf-huruf unik
    std::vector<char> letters = unique_letters(soal);
    /// vektor untuk menyimpan huruf pertama dari tiap operand
    std::vector<char> firstLetters(soal.size());
    /// unordered_map yang memetakan huruf ke angka
    std::unordered_map<char, int> numberFromLetter;
    /// unordered_map yan memetakan angka ke huruf (kebalikan numberFromLetter)
    int cases = 0;

    // bikin vektor huruf pertama
    for (std::vector<std::string>::iterator it = soal.begin();
            it != soal.end();
            ++it)
        firstLetters[it - soal.begin()] = ((*it)[0]);

    // probably not needed, but wut teh hecc
    if (letters.size() > MAX_UNIQUE_LETTERS)
    {
        std::cerr << "Banyak huruf berbeda (unik) maksimum adalah "
                << MAX_UNIQUE_LETTERS << '.';
        exit(EX_DATAERR);
    }

    std::vector<std::vector<int>> permutatedNumbers =
        new_perm(letters.size(), 0, MAX_UNIQUE_LETTERS);

    // proses dekripsi
    for (std::vector<int> numbers: permutatedNumbers)
    {
        operandInNumbers.clear();
        // map huruf ke angka
        // dan angka ke huruf
        for (size_t i = 0; i < letters.size(); ++i)
            numberFromLetter[letters[i]] = numbers[i];

        // periksa huruf pertama ada yg bernilai 0 atau ngga

        /// Penanda apakah loop perlu dilanjutkan atau tidak
        bool stopThyLoop = false;
        for (std::vector<char>::iterator it = firstLetters.begin();
                it != firstLetters.end() && !stopThyLoop;
                ++it)
            if (numberFromLetter[*it] == 0)
                stopThyLoop = true;

        if (stopThyLoop) continue;

        /// variabel untuk menyimpan sum dari semua operand
        int sum = 0,
        /// variabel untuk menyimmpan sum 'yang seharusnya'
            realSum = 0;

        // ubah operand-operand menjadi angka
        for (size_t i = 0; i < soal.size(); ++i)
        {
            int curNum = 0;
            for (size_t j = 0; j < soal[i].size(); ++j)
                curNum = curNum*10 + numberFromLetter[soal[i][j]];

            if (i != soal.size()-1)
                sum += curNum;
            else
                realSum = curNum;

            operandInNumbers.push_back(curNum);
        }

        if (sum == realSum) break;
        else cases++;
    }

    return std::make_pair(operandInNumbers, cases);
}
