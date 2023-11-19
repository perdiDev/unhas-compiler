# unhas-compiler
Tugas mata kuliah TBO semester 3

## ALUR KERJA

Spesifikasi
- harus punya compiler c atau c++, disarankan MingW64

Langkah-langkah menggunakan unhas-compiler:
1. Masuk ke directory ./unhas di terminal dengan cara `cd ./unhas`
2. Compile file UHCompiler dengan cara `g++ .\UHCompiler.cpp -o ../src/unhasc`, setelah itu akan muncul file baru pada ./src dengan nama unhasc.exe
3. Masuk ke direcctory ./src pada terminal dengan cara `cd ../src`
4. Kemudian buat file baru pada ./src dengan ekstensi .uh, kemudian masukkan kodingan sesuai aturan unhas-compiler
5. Setelah itu jalankan compiler untuk mengkompile <your file>.uh ke bahasa C, dengan cara jalankan perintah berikut pada terminal `./unhasc.exe <nama_file>.uh`
6. Compiler akan bekerja dan menghasilkan file baru pada ./out, file tersebut adalah hasil compile dari file yang ada pada src, file yang terbentuk adalah file C dan .exe
7. Compiler Done!
