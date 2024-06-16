#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100
#define MAX_LINE 500

typedef struct Disease {
    char Nama[MAX];
    int Jumlah;
    struct Disease *next;
} Disease;


typedef struct Year {
    struct Disease *Bulan[12];
    int JumlahPasien[12];
    int Tahun;
    struct Year *next;
} Year;

const char* NumberToMonth(int month) {
    switch (month) {
        case 1: return "Januari";
        case 2: return "Februari";
        case 3: return "Maret";
        case 4: return "April";
        case 5: return "Mei";
        case 6: return "Juni";
        case 7: return "Juli";
        case 8: return "Agustus";
        case 9: return "September";
        case 10: return "Oktober";
        case 11: return "November";
        case 12: return "Desember";
        default: return "Invalid month"; // Error case
    }
}


Year* createYear(int tahun) {
    Year *newYear = (Year*) malloc(sizeof(Year));
    if (newYear == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newYear->Tahun = tahun;
    newYear->next = NULL;
    for (int i = 0; i < 12; i++) {
        newYear->JumlahPasien[i]=0;
        newYear->Bulan[i] = NULL;
    }
    return newYear;
}

Disease* createDisease(const char *nama) {
    Disease *newDisease = (Disease*) malloc(sizeof(Disease));
    if (newDisease == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(newDisease->Nama, nama, MAX);
    newDisease->Nama[MAX-1] = '\0'; // Ensure null-termination
    newDisease->Jumlah = 1;
    newDisease->next = NULL;
    return newDisease;
}

// Tanggal pada file ada 2 jenis, yaitu yang dipisahkan menggunakan "-" dan spasi
int TipeTanggal (char a[]){
    for (int i=0; i<8; i++){
        if (a[i]=='-') return 0;
    }
    return 1;
}

// Memasukkan penyakit, atau membuat node baru
void insertOrUpdateDisease(Disease **head, const char *nama) {
    Disease *current = *head;
    Disease *prev = NULL;
    Disease *newDisease;

    // Mencari penyakit
    while (current != NULL && strcmp(current->Nama, nama) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Penyakit tidak ditemukan. Membuat node baru
        newDisease = createDisease(nama);

        // Masukkan sesuai urutan
        if (prev == NULL) {
            // Urutan pertama 
            newDisease->next = *head;
            *head = newDisease;
        } 
        else {
            // Lainnya
            newDisease->next = prev->next;
            prev->next = newDisease;
        }
    } else {
        // Penyakit ditemukan
        current->Jumlah++;

        // Pengurutan
        if (prev != NULL && current->Jumlah > prev->Jumlah) {
            // Melepaskan node dari list
            prev->next = current->next;

            // Menentukan posisi baru
            Disease *temp = *head;
            Disease *tempPrev = NULL;
            while (temp != NULL && current->Jumlah <= temp->Jumlah) {
                tempPrev = temp;
                temp = temp->next;
            }

            // Penyisipan node
            if (tempPrev == NULL) {
                current->next = *head;
                *head = current;
            } else {
                current->next = tempPrev->next;
                tempPrev->next = current;
            }
        }
    }
}

Year* insertYear(Year **head, int tahun) {
    Year *current = *head;
    Year *prev = NULL;

    // Menentukan posisi yang tepat
    while (current != NULL && current->Tahun <= tahun) {
        // Kasus node sudah ada
        if (current->Tahun==tahun) return current;

        prev = current;
        current = current->next;
    }

    // Membuat node baru
    Year *newYear = createYear(tahun);
    if (newYear == NULL) {
        return NULL;
    }

    // Menyisipkan node baru
    if (prev == NULL) {
        newYear->next = *head;
        *head = newYear;
    } else {
        newYear->next = prev->next;
        prev->next = newYear;
    }

    return newYear;
}

void PasienTiapWaktu (FILE *file){
    Year *Head = NULL;
    char token[MAX_LINE], *token2, *tanggal, *penyakit;
    int bulan, tahun;

    //lewati baris pertama
    fgets(token, sizeof(token), file);

    while (fgets(token, sizeof(token), file)){
        //skip nomor
        token2=strtok(token, ",");

        //ambil tanggal
        tanggal=strtok(NULL, ",");

        //skip id pasien
        token2=strtok(NULL, ",");

        //ambil nama penyakit
        penyakit=strtok(NULL, ",");

        //YYYY-MM-DD
        tahun = atoi(strtok(tanggal, "-"));
        bulan =atoi(strtok(NULL, "-"));
        
        //Menyusun data terurut per tahun dan bulan
        Year *currentYear = insertYear(&Head, tahun);
        currentYear->JumlahPasien[bulan-1]+=1;
        insertOrUpdateDisease(&(currentYear->Bulan[bulan - 1]), penyakit);
    }

    // Mencetak hasil
    Year *currentYear = Head;
    while (currentYear != NULL) {
        printf("\n-------TAHUN %d-------\n", currentYear->Tahun);
        for (int i = 0; i < 12; i++) {
            Disease *currentDisease = currentYear->Bulan[i];
            printf("%s  (%d pasien)\n", NumberToMonth(i+1), currentYear->JumlahPasien[i]);
            while (currentDisease != NULL) {
                printf("   %s : %d\n", currentDisease->Nama, currentDisease->Jumlah);
                currentDisease = currentDisease->next;
            }
        }
        currentYear = currentYear->next;
    }    

    // Pembebasan memori
    currentYear = Head;
    while (currentYear != NULL) {
        for (int i = 0; i < 12; i++) {
            Disease *currentDisease = currentYear->Bulan[i];
            while (currentDisease != NULL) {
                Disease *tempDisease = currentDisease;
                currentDisease = currentDisease->next;
                free(tempDisease);
            }
        }
        Year *tempYear = currentYear;
        currentYear = currentYear->next;
        free(tempYear);
    }
}

int Fungsi13(){
    FILE *file = fopen("riwayatpasien.csv", "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    PasienTiapWaktu(file);
}
