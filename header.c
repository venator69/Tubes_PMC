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

void bacaDataPasien(FILE* file, Pasien** head) {
    char line[MAX_LINE];

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

        Pasien* newPasien = createPasien(no, nama_lengkap, alamat, kota, tempat_lahir, tanggal_lahir, umur, no_bpjs, id_pasien);
        insertPasien(head, newPasien);
    }
}
