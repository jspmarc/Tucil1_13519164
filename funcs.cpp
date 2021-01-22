/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#include "funcs.hpp"
#include <algorithm> // next_permutation
#include <iostream> // string, cout
#include <chrono> // itung waktu eksekusi
#include <fstream> // file operation
#include <utility> // pairs
#include <vector> // vector
#include <unordered_map> // unordered_map
#include <stdlib.h> // exit()
#include <sysexits.h> // exit codes

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
            /// vektor yang akan dipush ke newVec
            std::vector<T> toBePushed = slice_vector(0, i, *p);
            /// tail ke vektor yang akan dipush
            std::vector<T> tail = slice_vector(i, p->size(), *p);
            toBePushed.push_back(first);
            toBePushed.insert(toBePushed.end(), tail.begin(), tail.end());

            newVec.push_back(toBePushed);
        }
    }

    return newVec;
}

template <typename T>
std::vector<T> slice_vector(int n, int m, std::vector<T> vec)
{
    return std::vector<T> (vec.begin()+n, vec.begin()+m);
}

std::string strip_at_beginning(char* strToStrip)
{
    while ((*strToStrip == ' ' || *strToStrip == '\t' || *strToStrip == '\n')
            && (*strToStrip != '\0')) strToStrip++;

    return strToStrip;
}

template <typename T>
void print_vec(std::vector<T> vec)
{
    std::cout << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ',';
    std::cout << "]";
}

template <typename T>
void print_vec(std::vector<std::vector<T>> vec)
{
    std::cout << '[' << std::endl;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << '\t';
        print_vec(*it);
        std::cout << ',' << std::endl;
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
        std::cerr << "Gagal membuka file " << fileName << "." << std::endl;
        exit(EX_NOINPUT);
    }
}

std::pair<std::vector<int>, int> decrypt_cryparithm(std::vector<std::string> soal)
{
    // proses perisapan dan inisialisasi

    /// vektor untuk menyimpan huruf-huruf unik
    std::vector<char> letters = unique_letters(soal);
    /// vektor untuk menyimpan huruf pertama dari tiap operand
    std::vector<char> firstLetters(soal.size());
    /// vektor untuk menyimpan operand yang diubah ke angka (4 byte integer)
    std::vector<int> operandNumbers(soal.size());
    /// variabel untuk menghitung jumlah kasus yang diuji
    int cases = 0;

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

            operandNumbers[i] = curNum;
        }

        if (sum == realSum) break;
        else cases++;
    //} while (permutate_vec(&numbers));
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    print_vec(permutate_vec(numbers));

    return std::make_pair(operandNumbers, cases);
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

void print_answer(std::vector<std::string> soal, std::vector<int> answer)
{
    print_vec(soal);
    std::cout << std::endl;
    print_vec(answer);
}
