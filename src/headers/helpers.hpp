/* Nama     : Josep Marcello
 * NIM      : 13519164
 * Tanggal  : 20 Januari 2021
 */

#ifndef _TUCIL_1_STIMA_
#define _TUCIL_1_STIMA_

#include <iostream> // string
#include <vector> // vector
#include <unordered_map> // unordered_map
#include <stdio.h> // puts()

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

#endif
