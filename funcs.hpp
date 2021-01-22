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

// *** DEKLARASI FUNGSI-FUNGSI ***

/**
 * Fungsi untuk membuat permutasi dari suatu vektor
 *
 * @tparam T tipe data yang disimpan pada vektor
 * @param *vec pointer ke vektor yang ingin dibuat permutasinya
 * @returns true jika merupakan permutasi baru, false jika sudah kembali ke bentuk vektor awal
 */
template <class T>
bool permutate_vec(std::vector<T>* vec);

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
template <class T>
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
template <class T>
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
template <class K, class V>
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
 */
std::pair<std::vector<int>, int> decrypt_cryparithm(std::vector<std::string> soal);

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
void print_answer(std::vector<std::string> soal, std::vector<int> answer);

// *** END ***

#endif
