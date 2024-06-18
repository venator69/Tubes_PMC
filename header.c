#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_LINE_LENGTH 100
#define MAX 50

// Struktur untuk menyimpan data biaya tindakan
typedef struct Biaya {
    int no;
    char aktivitas[MAX];
    int biaya;
    struct Biaya* next;
} Biaya;

// Struktur untuk menyimpan data pasien
typedef struct Pasien {
    int no;
    char nama[MAX];
    char alamat[MAX];
    char kota[MAX];
    char tempatLahir[MAX];
    char tanggalLahir[MAX];
    int umur;
    char noBPJS[MAX];
    char idPasien[MAX];
    struct Pasien* next;
} Pasien;

// Struktur untuk menyimpan data riwayat pasien
typedef struct Riwayat {
    int no;
    char tanggal[MAX];
    char id_pasien[MAX];
    char diagnosis[MAX];
    char tindakan[MAX];
    char kontrol[MAX];
    int biaya;
    struct Riwayat* next;
} Riwayat;

// Fungsi untuk membaca file biaya tindakan dan mengisi linked list
Biaya* bacaBiayaFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    Biaya* head = NULL;
    Biaya* current = NULL;

    // Lewati header
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        Biaya* newNode = (Biaya*)malloc(sizeof(Biaya));
        sscanf(line, "%d,%49[^,],\"%d", &newNode->no, newNode->aktivitas, &newNode->biaya);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }

    fclose(file);
    return head;
}

// Fungsi untuk membaca file data pasien dan mengisi linked list
Pasien* bacaPasienFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    Pasien* head = NULL;
    Pasien* current = NULL;

    // Lewati header
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        Pasien* newNode = (Pasien*)malloc(sizeof(Pasien));
        sscanf(line, "%d,\"%49[^\"]\",\"%99[^\"]\",\"%49[^\"]\",\"%49[^\"]\",\"%49[^\"]\",%d,\"%19[^\"]\",\"%19[^\"]",
               &newNode->no, newNode->nama, newNode->alamat, newNode->kota, newNode->tempatLahir, newNode->tanggalLahir, &newNode->umur, newNode->noBPJS, newNode->idPasien);
        // convertDateFormat(newNode->tanggalLahir);  // Konversi tanggal lahir
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }

    fclose(file);
    return head;
}

// Fungsi untuk membaca file riwayat pasien dan mengisi linked list
Riwayat* bacaRiwayatPasienFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    Riwayat* head = NULL;
    Riwayat* current = NULL;

    // Lewati header
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        Riwayat* newNode = (Riwayat*)malloc(sizeof(Riwayat));
        sscanf(line, "%d,%49[^,],%19[^,],%49[^,],%49[^,],%49[^,],%d",
               &newNode->no, newNode->tanggal, newNode->id_pasien, newNode->diagnosis, newNode->tindakan, newNode->kontrol, &newNode->biaya);
        
        
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }

    fclose(file);
    return head;
}

// // Fungsi untuk mencetak linked list biaya tindakan
// void cetakBiaya(Biaya* head) {
//     Biaya* current = head;
//     while (current) {
//         printf("No: %d, Aktivitas: %s, Biaya: %d\n", current->no, current->aktivitas, current->biaya);
//         current = current->next;
//     }
// }

// // Fungsi untuk mencetak linked list pasien
// void cetakPasien(Pasien* head) {
//     Pasien* current = head;
//     while (current) {
//         printf("No: %d, Nama: %s, Alamat: %s, Kota: %s, Tempat Lahir: %s, Tanggal Lahir: %s, Umur: %d, No BPJS: %s, ID Pasien: %s\n",
//                current->no, current->nama, current->alamat, current->kota, current->tempatLahir, current->tanggalLahir, current->umur, current->noBPJS, current->idPasien);
//         current = current->next;
//     }
// }

