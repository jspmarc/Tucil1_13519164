# Cryptarithm Decryptor

Sebuah dekriptor untuk enkripsi cryptarithmetic dengan menggunakan algoritma
*brute force*.

# Dependencies
untuk *compile*:
* g++ dengan standar C++11
* C++11 STL dan library lain:
    * utility
    * vector
    * unordered_map
    * fstream
    * iostream
    * chrono
* C standard library:
    * stdio.h
    * stdlib.h
* sysexits.h

# Compiling
Untuk mengkompilasi program, pada root folder proyek jalankan `make compile`
atau `make`

# Running
Ada 2 cara untuk menjalankan program dekriptor ini:

1. Jika program sudah dikompilasi, jalankan *executable* `bin/main
   [path/ke/file]` atau bisa juga tanpa argumen (`bin/main`).
1. Jika belum dikompilasi atau mau mengkompilasi lalu langsung menjalankan
program, jalankan `make run`.

# Input

Bentuk input adalah path ke file yang berisi masalah enkripsi cryptarithmetic.

Contoh file dengan 2 masalah cryptarithmetic:
```
NUMBER
NUMBER+
-------
PUZZLE

  TILES
PUZZLES+
--------
PICTURE
```

# Author

* Nama: Josep Marcello
* NIM: 13519164
* Email: jspmarcello@live.com / josep1403@students.itb.ac.id
