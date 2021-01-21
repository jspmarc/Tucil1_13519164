/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#include <iostream> // string, cout
#include <chrono> // itung waktu eksekusi
#include <algorithm> // next_permutation()
#include <fstream> // file operation
#include <vector> // vector
#include <unordered_map> // unordered_map
#include <stdlib.h> // exit()
#include <sysexits.h> // exit codes
#include <stdio.h> // printf(), puts()
#include "funcs.hpp"

#define debug1() puts("males belajar tapi...")
#define debug2() puts("pengen kaya")
#define debug3() puts("haha lucu lo badut")
#define MAX_UNIQUE_LETTERS 10

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Penggunaan: %s [nama file soal]\n", argv[0]);
        exit(EX_USAGE);
    }

    /// Vektor untuk nyimpen semua soal
    std::vector<std::vector<std::string>> semuaSoal;

    std::chrono::steady_clock sc;

    parse_file(argv[1], &semuaSoal);

    /// Vektor untuk menyimpan semua jawaban
    std::vector<std::vector<int>> answers(semuaSoal.size());

    auto start = sc.now();
    for (std::vector<std::vector<std::string>>::iterator it =
            semuaSoal.begin(); it != semuaSoal.end(); ++it)
    {
        int i = it - semuaSoal.begin();
        auto partialStart = sc.now();

        answers[i] = decrypt_cryparithm(*it);
        auto partialEnd = sc.now();
        auto partialTimeSpend = static_cast<std::chrono::duration<double>>(partialEnd-partialStart);
        printf("Soal ke-%d membutuhkan: %lf detik.\n", i+1, partialTimeSpend.count());
    }
    auto end = sc.now();
    auto timeSpend = static_cast<std::chrono::duration<double>>(end-start);

    print_vec(answers);
    puts("");

    printf("Operasi dekripsi %lu soal membutuhkan %lf detik.\n",
            semuaSoal.size(), timeSpend.count());
}

// *** INISIALISASI FUNGSI-FUNGSI ***

std::string strip_at_beginning(char* strToStrip)
{
    while ((*strToStrip == ' ' || *strToStrip == '\t' || *strToStrip == '\n')
            && (*strToStrip != '\0')) strToStrip++;

    return strToStrip;
}

template <class T>
void print_vec(std::vector<T> vec)
{
    printf("[");
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ',';
    printf("]");
}

template <class T>
void print_vec(std::vector<std::vector<T>> vec)
{
    puts("[");
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        printf("\t");
        print_vec(*it);
        puts(",");
    }
    printf("]");
}

template <class K, class V>
void print_map(std::unordered_map<K, V> umap)
{
    printf("[");
    for (auto it = umap.begin(); it != umap.end(); ++it)
        std::cout << '<' << it->first << ',' << it->second << ">,";
    printf("]");
}

void parse_file(char* fileName, std::vector<std::vector<std::string>>* output)
{
    /// variabel untuk menyimmpan file
    std::fstream input;
    input.open(fileName, std::ios::in);

    if (input.is_open())
    {
        /// menyimpan baris dari file yang lagi mau diparse
        std::string line;

        while(getline(input, line))
        {
            /// vektor buat nyimpen operand-operand yang dibaca
            std::vector<std::string> operands;
            /// buat ngecek masih ngerjain ngeparse soal atau bukan
            bool isMasihParseSoal = true;
            /// buat ngecek udah operand terakhir atau belum
            bool isReadingLastOperand = false;

            do
            {
                /// operand yang lagi dibaca, sesudah di-strip di depan
                std::string operand = strip_at_beginning(&(line[0])).c_str();

                if (isReadingLastOperand)
                {
                    isMasihParseSoal = false;
                    operands.push_back(operand);
                }
                else if (operand.empty() || operand[0] == '-')
                {
                    isReadingLastOperand = operand[0] == '-';
                    continue;
                }
                else if (*(operand.end()-1) == '+')
                {
                    operand.resize(operand.size()-1);
                    operands.push_back(operand);
                }
                else
                    operands.push_back(operand);
            } while(isMasihParseSoal && getline(input, line));

            output->push_back(operands);
        }

        input.close();
    }
    else
    {
        fprintf(stderr, "Gagal membuka file %s.\n", fileName);
        exit(EX_NOINPUT);
    }
}

std::vector<int> decrypt_cryparithm(std::vector<std::string> soal)
{
    // proses perisapan dan inisialisasi

    /// vektor untuk menyimpan huruf-huruf unik
    std::vector<char> letters = unique_letters(soal);
    /// vektor untuk menyimpan huruf pertama dari tiap operand
    std::vector<char> firstLetters(soal.size());
    /// vektor untuk menyimpan operand yang diubah ke angka (4 byte integer)
    std::vector<int> operandNumbers(soal.size());

    for (std::vector<std::string>::iterator it = soal.begin();
            it != soal.end();
            ++it)
        firstLetters[it - soal.begin()] = ((*it)[0]);

    // probably not needed, but wut teh hecc
    if (letters.size() > MAX_UNIQUE_LETTERS)
    {
        fprintf(stderr, "Banyak huruf berbeda (unik) maksimum adalah %d.",
                MAX_UNIQUE_LETTERS);
        exit(EX_DATAERR);
    }

    /// vektor untuk menyimpan angka-angka pada vektor
    std::vector<int> numbers(10);
    for (int i = 0; i < 10; ++i)
        numbers[i] = i;

    // proses dekripsi
    do
    {
        /// unordered_map yang memetakan huruf ke angka
        std::unordered_map<char, int> numberFromLetter;
        /// unordered_map yan memetakan angka ke huruf (kebalikan numberFromLetter)
        std::unordered_map<int, char> letterFromNumber;

        // map huruf ke angka
        // dan angka ke huruf
        for (size_t i = 0; i < letters.size(); ++i)
        {
            numberFromLetter[letters[i]] = numbers[i];
            letterFromNumber[numbers[i]] = letters[i];
        }

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

            operandNumbers[i] = curNum;
        }

        if (sum == realSum) break;
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    return operandNumbers;
}

std::vector<char> unique_letters(std::vector<std::string> soal)
{
    /// vector untuk nyimpen huruf-huruf unik
    std::vector<char> letters;

    /// array untuk nandain huruf apa aja yg udah dipake
    bool areLettersUsed[] = {
        false, false, false, false, false, false,
        false, false, false, false, false, false,
        false, false, false, false, false, false,
        false, false, false, false, false, false,
        false, false, false, false, false, false
    };

    for (std::vector<std::string>::iterator it = soal.begin(); it != soal.end(); ++it)
    {
        for (std::string::iterator it_c = it->begin(); it_c != it->end(); ++it_c)
        {
            if (!areLettersUsed[*it_c - 'A'])
            {
                letters.push_back(*it_c);
                areLettersUsed[*it_c - 'A'] = true;
            }
        }
    }

    return letters;
}

// *** END ***
