/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#ifndef _TUCIL_1_STIMA_
#define _TUCIL_1_STIMA_

#include <utility>
#include <vector> // vector
#include <iostream> // string, cout
#include <unordered_map> // unordered_map

#define MAX_UNIQUE_LETTERS 80
#define debug1() puts("males belajar tapi...")
#define debug2() puts("pengen kaya")
#define debug3() puts("haha lucu lo badut")
#define cel() std::cout << std::endl


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
 * Fungsi untuk memotong vektor ( membuat vektor baru dengan elemen [n..m) )
 *
 * @param n indeks elemen pertama yg ingin diambil (inklusif)
 * @param m satu indeks setelah elemen terakhir yg ingin diambil (ekslusif)
 * @param vec vektor yang ingin dipotong
 * @returns potongan vektor vec di indeks [n..m)
 */
template <typename T>
std::vector<T> slice_vector(int n, int m, std::vector<T> vec);

/**
 * Fungsi untuk menghapuskan whitespaces ('', '\t', '\n') dari awal C string
 *
 * @param *strToStrip pointer ke C string yang ingin di-strip
 * @returns std::string yang sudah dihapuskan whitespace-nya
 */
std::string strip_at_beginning(char* strToStrip);

/**
 * Fungsi untuk menuliskan isi vector
 * Format: [el1,el2,el3,el4,]
 *
 * @tparam T tipe data elemen yang ditampung vector
 * @param vec vector yang ingin dituliskan isinya
 */
template <typename T>
void print_vec(std::vector<T> vec);

/**
 * Fungsi untuk menuliskan isi vector multidimensi
 * Format:
 * [
 *		[el11,el12,el13,el14,],
 *		[el21,el22,el23,el24,],
 *		[el31,el32,el33,el34,],
 *		[el41,el42,el43,el44,],
 * ]
 *
 * @tparam T tipe data elemen yang ditampung vector multidimensi
 * @param vec vector dari vector yang ingin dituliskan isinya
 *
 * @overload
 */
template <typename T>
void print_vec(std::vector<std::vector<T>> vec);

/**
 * Fungsi untuk menuliskan isi suatu unordered_map
 * Format:
 * [<K1, V1>,<K2, V2>,]
 *
 * @tparam K tipe data untuk key pada unordered_map
 * @tparam V tipe data untuk value pada unordered_map
 * @param umap unordered_map yang ingin dituliskan isinya
 */
template <typename K, typename V>
void print_map(std::unordered_map<K, V> umap);

/**
 * Fungsi untuk membaca file (sesuai format pada spek) lalu memisahkannya
 * berdasarkan soal
 *
 * @param *fileName string yang berisi nama file soal
 * @param *output vector dari vector yang menampung soal-soal (tiap elemen
 * adalah soal)
 */
void parse_file(char* fileName, std::vector<std::vector<std::string>>* output);

/**
 * Fungsi untuk mendekripsi Cryptarithmetic
 *
 * @param soal soal yang mau didekripsi
 * @param permutatedNumbers vektor berisi vektor-vektor kumpulan
 * permutasi-permutasi yang mungkin dari vektor angka [0..MAX_UNIQUE_LETTERS]
 * @returns sebuah pair berisi solusi benar dan jumlah kasus yang dikerjakan
 */
std::pair<std::unordered_map<char, int>, int> decrypt_cryparithm(std::vector<std::string> soal, std::vector<std::vector<int>> permutatedNumbers);

/**
 * Fungsi untuk mendapatkan huruf-huruf unik dari soal
 *
 * @param soal soal yang ingin dicari huruf-huruf uniknya
 */
std::vector<char> unique_letters(std::vector<std::string> soal);

/**
 * Fungsi untuk menuliskan jawaban sesuai dengan spek
 *
 * @param soal vektor yang berisi soal yang ingin diprint, hasil parse parse_file()
 * @param answer jawaban dari soal yang ingin diprint, hasil decrypt_cryparithm()
 */
void print_answer(std::vector<std::string> soal, std::unordered_map<char, int> answer);

/**
 * Fungsi untuk menghasilkan list dari permutasi-permutasi mungkin dari
 * angka-angka dalam range [0..lim]
 *
 * @param lim batas atas angka
 */
std::vector<std::vector<int>> generatePermutatedNumbers(int lim);

// *** END ***

#endif
