// #include "header.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 100
#define MAX_LINE 500

typedef struct Pasien {
    char nama_lengkap[MAX];
    char alamat[MAX];
    char kota[MAX];
    char tempat_lahir[MAX];
    char tanggal_lahir[MAX];
    int umur;
    char no_bpjs[MAX];
    char id_pasien[MAX];
    struct Pasien* next;
}Pasien;

typedef struct Riwayat
{
    char tanggal[MAX];
    char id_pasien[MAX];
    char diagnosis[MAX];
    char tindakan[MAX];
    char kontrol[MAX];
    int biaya;
}Riwayat;

void readCSV(const char* filename, Riwayat* riwayatArray, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // Skip the first line

    *count = 0;
    while (fgets(line, MAX_LINE, file) != NULL) {

        char* token = strtok(line, ",");
        token = strtok(NULL, ","); // Skip the first column

        strcpy(riwayatArray[*count].tanggal, token);

        token = strtok(NULL, ",");
        strcpy(riwayatArray[*count].id_pasien, token);

        token = strtok(NULL, ",");
        strcpy(riwayatArray[*count].diagnosis, token);

        token = strtok(NULL, ",");
        strcpy(riwayatArray[*count].tindakan, token);

        token = strtok(NULL, ",");
        strcpy(riwayatArray[*count].kontrol, token);

        token = strtok(NULL, ",");
        riwayatArray[*count].biaya = atoi(token);

        (*count)++;
    }

    fclose(file);
}

// Fungsi untuk membuat node baru untuk pasien
Pasien* createPasien(char* nama_lengkap, char* alamat, char* kota, char* tempat_lahir, char* tanggal_lahir, int umur, char* no_bpjs, char* id_pasien) {
    Pasien* newPasien = (Pasien*)malloc(sizeof(Pasien));
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
    //
    Pasien* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void bacaDataPasien(FILE* file, Pasien** head) {
    char line[MAX_LINE];
    fgets(line,sizeof(line), file); //Gw nambah ini biar skip first line -Adit
    while (fgets(line, sizeof(line), file)) {
        int no, umur;
        char nama_lengkap[MAX], alamat[MAX], kota[MAX], tempat_lahir[MAX], tanggal_lahir[MAX], no_bpjs[MAX], id_pasien[MAX];

        char* pos;
        if ((pos = strchr(line, '\n')) != NULL) {
            *pos = '\0';
        }
        if ((pos = strchr(line, '\r')) != NULL) {
            *pos = '\0';
        }

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

        Pasien* newPasien = createPasien(nama_lengkap, alamat, kota, tempat_lahir, tanggal_lahir, umur, no_bpjs, id_pasien);
        insertPasien(head, newPasien);
    }
}

// create a function to print pasien linked list
void printPasienList(Pasien* head) {
    Pasien* temp = head;
    while (temp != NULL) {
        printf("Nama Lengkap: %s\n", temp->nama_lengkap);
        printf("Alamat: %s\n", temp->alamat);
        printf("Kota: %s\n", temp->kota);
        printf("Tempat Lahir: %s\n", temp->tempat_lahir);
        printf("Tanggal Lahir: %s\n", temp->tanggal_lahir);
        printf("Umur: %d\n", temp->umur);
        printf("No BPJS: %s\n", temp->no_bpjs);
        printf("ID Pasien: %s\n", temp->id_pasien);
        printf("\n");
        temp = temp->next;
    }
}

// create a function to print riwayatArray
void printRiwayatArray(Riwayat* riwayatArray, int count) {
    for (int i = 0; i < count; i++) {
        printf("Tanggal: %s\n", riwayatArray[i].tanggal);
        printf("ID Pasien: %s\n", riwayatArray[i].id_pasien);
        printf("Diagnosis: %s\n", riwayatArray[i].diagnosis);
        printf("Tindakan: %s\n", riwayatArray[i].tindakan);
        printf("Kontrol: %s\n", riwayatArray[i].kontrol);
        printf("Biaya: %d\n", riwayatArray[i].biaya);
        printf("\n");
    }
}

// function to replace any '-' substring with ' ' in riwayatArray.tanggal
void replaceHyphenWithSpace(Riwayat* riwayatArray, int count) {
    for (int i = 0; i < count; i++) {
        char* pos = strchr(riwayatArray[i].tanggal, '-');
        while (pos != NULL) {
            *pos = ' ';
            pos = strchr(pos, '-');
        }
        
        char* pos2 = strchr(riwayatArray[i].kontrol, '-');
        while (pos2 != NULL) {
            *pos2 = ' ';
            pos2 = strchr(pos2, '-');
        }
    }
}



void searchRiwayat(Riwayat* riwayatArray, int count, const char* idPasien) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(riwayatArray[i].id_pasien, idPasien) == 0) {
            printf("Tanggal: %s\n", riwayatArray[i].tanggal);
            printf("Diagnosis: %s\n", riwayatArray[i].diagnosis);
            printf("Tindakan: %s\n", riwayatArray[i].tindakan);
            printf("Kontrol: %s\n", riwayatArray[i].kontrol);
            printf("Biaya: %d\n", riwayatArray[i].biaya);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ditemukan riwayat untuk ID Pasien: %s\n", idPasien);
    }
}

void searchDataPasien(Pasien* head, const char* idPasien) {
    Pasien* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->id_pasien, idPasien) == 0) {
            printf("Data Pasien dengan ID Pasien: %s\n", idPasien);
            printf("\n");
            printf("Nama Lengkap: %s\n", temp->nama_lengkap);
            printf("Alamat: %s\n", temp->alamat);
            printf("Kota: %s\n", temp->kota);
            printf("Tempat Lahir: %s\n", temp->tempat_lahir);
            printf("Tanggal Lahir: %s\n", temp->tanggal_lahir);
            printf("Umur: %d\n", temp->umur);
            printf("No BPJS: %s\n", temp->no_bpjs);
            printf("ID Pasien: %s\n", temp->id_pasien);
            printf("\n");
            printf("Riwayat Pasien: \n");
            printf("\n");
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Tidak ditemukan data untuk ID Pasien: %s\n", idPasien);
        printf("\n");
    }
}
