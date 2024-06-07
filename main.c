#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "functions/Adam.c"
#include "functions/Hubert.c"
#include "functions/Fitraka.c"
#include "functions/Raditya.c"
#include "functions/Requint.c"

#define MAX 100
#define MAX_LINE 500

// Definisikan struktur Pasien untuk data pasien
typedef struct Pasien {
    int no;
    char nama_lengkap[MAX];
    char alamat[MAX];
    char kota[MAX];
    char tempat_lahir[MAX];
    char tanggal_lahir[MAX];
    int umur;
    char no_bpjs[MAX];
    char id_pasien[MAX];
    struct Pasien* next;
} Pasien;

// Fungsi untuk membuat node baru untuk pasien
Pasien* createPasien(int no, char* nama_lengkap, char* alamat, char* kota, char* tempat_lahir, char* tanggal_lahir, int umur, char* no_bpjs, char* id_pasien) {
    Pasien* newPasien = (Pasien*)malloc(sizeof(Pasien));
    newPasien->no = no;
    strcpy(newPasien->nama_lengkap, nama_lengkap);
    strcpy(newPasien->alamat, alamat);
    strcpy(newPasien->kota, kota);
    strcpy(newPasien->tempat_lahir, tempat_lahir);
    strcpy(newPasien->tanggal_lahir, tanggal_lahir);
    newPasien->umur = umur;
    strcpy(newPasien->no_bpjs, no_bpjs);
    strcpy(newPasien->id_pasien, id_pasien);
    newPasien->next = NULL;
    return newPasien;
}

// Fungsi untuk menyisipkan pasien baru ke dalam linked list
void insertPasien(Pasien** head, Pasien* newPasien) {
    if (*head == NULL) {
        *head = newPasien;
    } else {
        Pasien* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPasien;
    }
}

// Fungsi untuk membebaskan memori dari linked list
void freeList(Pasien* head) {
    Pasien* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


// Fungsi utama
int main() {
    // Buka file DataPMC20232024.csv
    FILE* file = fopen("DataPMC20232024.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Inisialisasi linked list untuk menyimpan data pasien
    Pasien* head = NULL;
    char line[MAX_LINE];
    int ch;

    // Baca data dari file CSV dan simpan ke dalam linked list
    while (fgets(line, sizeof(line), file)) {
        int no, umur;
        char nama_lengkap[MAX], alamat[MAX], kota[MAX], tempat_lahir[MAX], tanggal_lahir[MAX], no_bpjs[MAX], id_pasien[MAX];

        // Menghapus karakter newline dan double quotes dari baris
        char* pos;
        if ((pos = strchr(line, '\n')) != NULL) {
            *pos = '\0';
        }
        if ((pos = strchr(line, '\r')) != NULL) {
            *pos = '\0';
        }

        // Tokenisasi baris menggunakan delimiter koma
        char* token = strtok(line, "\",\"");
        no = atoi(token);

        token = strtok(NULL, "\",\"");
        strcpy(nama_lengkap, token);

        token = strtok(NULL, "\",\"");
        strcpy(alamat, token);

        token = strtok(NULL, "\",\"");
        strcpy(kota, token);

        token = strtok(NULL, "\",\"");
        strcpy(tempat_lahir, token);

        token = strtok(NULL, "\",\"");
        strcpy(tanggal_lahir, token);

        token = strtok(NULL, "\",\"");
        umur = atoi(token);

        token = strtok(NULL, "\",\"");
        strcpy(no_bpjs, token);

        token = strtok(NULL, "\",\"\n");
        strcpy(id_pasien, token);

        Pasien* newPasien = createPasien(no, nama_lengkap, alamat, kota, tempat_lahir, tanggal_lahir, umur, no_bpjs, id_pasien);
        insertPasien(&head, newPasien);
    }

    fclose(file);

    // Loop menu utama
    do {
        system("cls");  // Membersihkan layar konsol
        printf("1.  Menambah data pasien\n");
        printf("2.  Mengubah data pasien\n");
        printf("3.  Menghapus data pasien\n");
        printf("4.  Mencari data pasien\n");
        printf("5.  Menambah riwayat diagnosis dan penanganan\n");
        printf("6.  Mengubah riwayat diagnosis dan penanganan\n");
        printf("7.  Menghapus riwayat diagnosis dan penanganan\n");
        printf("8.  Mencari riwayat diagnosis dan penanganan\n");
        printf("9.  Info pasien dan riwayat medisnya\n");
        printf("10. Info pendapatan bulanan\n");
        printf("11. Info pendapatan tahunan\n");
        printf("12. Info rata-rata pendapatan per tahun\n");
        printf("13. Info jumlah pasien dan penyakitnya\n");
        printf("14. Info untuk kontrol\n");
        printf("\nMasukan pilihan (pilih 0 untuk keluar) : ");
        scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        // Menambah data pasien
        break;
    case 2:
        // Mengubah data pasien
        break;
    case 3:
        // Menghapus data pasien
        break;
    case 4:
        // Mencari data pasien
        break;
    case 5:
        // Menambah riwayat diagnosis dan penanganan
        break;
    case 6:
        // Mengubah riwayat diagnosis dan penanganan
        break;
    case 7:
        // Menghapus riwayat diagnosis dan penanganan
        break;
    case 8:
        // Mencari riwayat diagnosis dan penanganan
        break;
    case 9:
        // Memberikan info pasien dan riwayat medisnya kepada petugas medis
        break;
    case 10:
        // Mendapat info laporan pendapatan bulanan
        break;
    case 11:
        // Mendapat info laporan pendapatan tahunan
        break;
    case 12:
        // Mendapat informasi rata-rata pendapatan per tahun
        break;
    case 13:
        // Mendapat info jumlah pasien dan penyakit yang diderita (sorted)
        break;
    case 14:
        // Memberikan info untuk kontrol
        break;
    case 0:
        printf("Terima kasih telah menggunakan program ini. Program telah ditutup.\n");
        break;
    default:
        printf("Pilihan tidak valid.\n");
    }

    printf("\n");
    printf("Tekan tombol apapun untuk melanjutkan");
    _getch();  // Menunggu input dari user sebelum melanjutkan
    } while (ch != 0);  // Loop terus menerus hingga user memilih keluar (0)

    // Bebaskan memori dari linked list sebelum keluar dari program
    freeList(head);
  return 0;
}