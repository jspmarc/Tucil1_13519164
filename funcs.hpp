#include <vector>
#include <iostream>

// *** DEKLARASI FUNGSI-FUNGSI ***

/**
 * Fungsi untuk menghapuskan whitespaces ('', '\t', '\n') dari awal C string.
 *
 * @param *strToStrip pointer ke C string yang ingin di-strip
 * @returns std::string yang sudah dihapuskan whitespace-nya
 */
std::string stripAtBeginning(char* strToStrip);

/**
 * Fungsi untuk menuliskan isi vector.
 * Format: [el1, el2, el3, el4,]
 *
 * @tparam T elemen yang ditampung vector.
 * @param vec vector yang ingin dituliskan isinya
 */
template <class T>
void printVec(std::vector<T> vec);
/**
 * Fungsi untuk menuliskan isi vector multidimensi
 * Format:
 * [
 *		[el11, el12, el13, el14,],
 *		[el21, el22, el23, el24,],
 *		[el31, el32, el33, el34,],
 *		[el41, el42, el43, el44,],
 * ]
 *
 * @tparam T elemen yang ditampung vector.
 * @param vecOvec vector dari vector yang ingin dituliskan isinya
 *
 * @overload
 */
template <class T>
void printVec(std::vector<std::vector<T>> vecOvec);

/**
 * Fungsi untuk membaca file (sesuai format pada spek) lalu memisahkannya
 * berdasarkan soal
 *
 * @param *fileName string yang berisi nama file soal
 * @param *output vector dari vector yang menampung soal-soal (tiap elemen
 * adalah soal)
 */
void parseFile(char* fileName, std::vector<std::vector<std::string>>* output);

/**
 * Fungsi untuk mendekripsi Cryptarithmetic
 *
 * @param soal soal yang mau didekripsi
 */
void decryptCryparithm(std::vector<std::string> soal);

/**
 * Fungsi untuk mendapatkan huruf-huruf unik dari soal
 *
 * @param soal soal yang ingin dicari huruf-huruf uniknya
 */
std::vector<char> uniqueLetters(std::vector<std::string> soal);
// *** END ***
