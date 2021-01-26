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

std::string strip_at_beginning(char* strToStrip)
{
    while ((*strToStrip == ' ' || *strToStrip == '\t' || *strToStrip == '\n')
            && (*strToStrip != '\0')) strToStrip++;

    return strToStrip;
}

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

void parse_file(char* fileName, std::vector<std::vector<std::string>>* output)
{
    /// variabel untuk menyimpan file
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
                else operands.push_back(operand);
            } while(isMasihParseSoal && getline(input, line));

            output->push_back(operands);
        }

        input.close();
    }
    else
    {
        std::cerr << "Gagal membuka file " << fileName << ".\n";
        exit(EX_NOINPUT);
    }
}
