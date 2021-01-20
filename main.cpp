/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#include <fstream>
#include <unordered_map>
#include <sysexits.h>
#include <stdlib.h>
#include <stdio.h>
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

    parseFile(argv[1], &semuaSoal);

    for (std::vector<std::vector<std::string>>::iterator it =
            semuaSoal.begin(); it != semuaSoal.end(); ++it)
    {
        decryptCryparithm(*it);
    }
}

// *** INISIALISASI FUNGSI-FUNGSI ***

std::string stripAtBeginning(char* strToStrip)
{
    while ((*strToStrip == ' ' || *strToStrip == '\t' || *strToStrip == '\n')
            && (*strToStrip != '\0')) strToStrip++;

    return strToStrip;
}

template <class T>
void printVec(std::vector<T> vec)
{
    printf("[");
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << ',';
    printf("]");
}

void parseFile(char* fileName, std::vector<std::vector<std::string>>* output)
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
                std::string operand = stripAtBeginning(&(line[0])).c_str();

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

template <class T>
void printVec(std::vector<std::vector<T>> vecOvec)
{
    puts("[");
    for (auto it = vecOvec.begin(); it != vecOvec.end(); ++it)
    {
        printf("\t");
        printVec(*it);
        puts(",");
    }
    printf("]");
}

void decryptCryparithm(std::vector<std::string> soal)
{
    std::vector<char> letters = uniqueLetters(soal);

    // probably not needed, but wut teh hecc
    if (letters.size() > MAX_UNIQUE_LETTERS)
    {
        fprintf(stderr, "Banyak huruf berbeda (unik) maksimum adalah %d.",
                MAX_UNIQUE_LETTERS);
        exit(EX_DATAERR);
    }

    // https://stackoverflow.com/questions/37759513/cryptarithmetic-puzzle
}

std::vector<char> uniqueLetters(std::vector<std::string> soal)
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
