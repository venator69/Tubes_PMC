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

typedef struct riwayatwithtanggal
{
    char tanggal[MAX];
    char tanggalnum[MAX];
    char bulan[MAX];
    char tahun[MAX];
    char id_pasien[MAX];
    char diagnosis[MAX];
    char tindakan[MAX];
    char kontrol[MAX];
    int biaya;
}riwayatwithtanggal;

void getriwayatwithtanggal(riwayatwithtanggal* riwayatWithTanggalArray, Riwayat* riwayatArray, int count) {
    for (int i = 0; i < count; i++) {
        strcpy(riwayatWithTanggalArray[i].tanggal, riwayatArray[i].tanggal);

        char* token = strtok(riwayatWithTanggalArray[i].tanggal, " ");
        strcpy(riwayatWithTanggalArray[i].tanggalnum, token);

        token = strtok(NULL, " ");
        strcpy(riwayatWithTanggalArray[i].bulan, token);

        token = strtok(NULL, " ");
        strcpy(riwayatWithTanggalArray[i].tahun, token);

        strcpy(riwayatWithTanggalArray[i].id_pasien, riwayatArray[i].id_pasien);
        strcpy(riwayatWithTanggalArray[i].diagnosis, riwayatArray[i].diagnosis);
        strcpy(riwayatWithTanggalArray[i].tindakan, riwayatArray[i].tindakan);
        strcpy(riwayatWithTanggalArray[i].kontrol, riwayatArray[i].kontrol);
        riwayatWithTanggalArray[i].biaya = riwayatArray[i].biaya;
    }
}

void add2000ToTahun(riwayatwithtanggal* riwayatWithTanggalArray, int count) {
    for (int i = 0; i < count; i++) {
        int tahun = atoi(riwayatWithTanggalArray[i].tahun);
        if (tahun < 2000){
            tahun += 2000;
        }
        sprintf(riwayatWithTanggalArray[i].tahun, "%d", tahun);
    }
}

typedef struct penghasilan{
    int bulan;
    int tahun;
    int biaya;
}penghasilan;

void convertformat(riwayatwithtanggal* riwayatWithTanggalArray, int count, penghasilan* penghasilanArray) {
    for (int i = 0; i < count; i++) {
        penghasilanArray[i].bulan = MonthToNumber(riwayatWithTanggalArray[i].bulan);
        penghasilanArray[i].tahun = atoi(riwayatWithTanggalArray[i].tahun);
        penghasilanArray[i].biaya = riwayatWithTanggalArray[i].biaya;
    }
}

void mergePenghasilan(penghasilan* penghasilanArray, int count, penghasilan* mergedArray, int* mergedCount) {
    *mergedCount = 0;
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < *mergedCount; j++) {
            if (penghasilanArray[i].bulan == mergedArray[j].bulan && penghasilanArray[i].tahun == mergedArray[j].tahun) {
                mergedArray[j].biaya += penghasilanArray[i].biaya;
                found = 1;
                break;
            }
        }
        if (!found) {
            mergedArray[*mergedCount] = penghasilanArray[i];
            (*mergedCount)++;
        }
    }
}

// fungsi untuk sorting array penghasilan berdasarkan bulan dan tahun
void sortPenghasilan(penghasilan* mergedArray, int mergedCount) {
    for (int i = 0; i < mergedCount; i++) {
        for (int j = i + 1; j < mergedCount; j++) {
            if (mergedArray[i].tahun > mergedArray[j].tahun) {
                penghasilan temp = mergedArray[i];
                mergedArray[i] = mergedArray[j];
                mergedArray[j] = temp;
            } else if (mergedArray[i].tahun == mergedArray[j].tahun) {
                if (mergedArray[i].bulan > mergedArray[j].bulan) {
                    penghasilan temp = mergedArray[i];
                    mergedArray[i] = mergedArray[j];
                    mergedArray[j] = temp;
                }
            }
        }
    }
}

typedef struct penghasilantahun{
    int tahun;
    int biaya;
}penghasilantahun;

void fillPenghasilanTahunArray(penghasilan* mergedArray, int mergedCount, penghasilantahun* penghasilanTahunArray, int* mergedTahunCount) {
    *mergedTahunCount = 0;
    for (int i = 0; i < mergedCount; i++) {
        int found = 0;
        for (int j = 0; j < *mergedTahunCount; j++) {
            if (mergedArray[i].tahun == penghasilanTahunArray[j].tahun) {
                penghasilanTahunArray[j].biaya += mergedArray[i].biaya;
                found = 1;
            }
        }
        if (!found) {
            penghasilanTahunArray[*mergedTahunCount].tahun = mergedArray[i].tahun;
            penghasilanTahunArray[*mergedTahunCount].biaya = mergedArray[i].biaya;
            (*mergedTahunCount)++;
        }
    }
}

// print penghasilan per tahun
void printTotalBiayaPerTahun(penghasilantahun* penghasilanTahunArray, int mergedTahunCount) {
    printf("Penghasilan klinik per tahun: \n");
    printf("\n");
    for (int i = 0; i < mergedTahunCount; i++) {
        printf("Penghasilan klinik tahun %d adalah %d\n", penghasilanTahunArray[i].tahun, penghasilanTahunArray[i].biaya);
    }
}

float findAverageBiayaPerTahun(penghasilantahun* penghasilanTahunArray, int mergedTahunCount) {
    int totalBiaya = 0;
    for (int i = 0; i < mergedTahunCount; i++) {
        totalBiaya += penghasilanTahunArray[i].biaya;
    }
    float averageBiaya = (float)totalBiaya / mergedTahunCount;
    return averageBiaya;
}

// Fungsi untuk mencetak total biaya per bulan dan tahun dari array penghasilan
void printTotalBiayaPerBulanTahun(penghasilan* mergedArray, int mergedCount) {
    printf("Penghasilan klinik per bulan: \n");
    printf("\n");
    for (int i = 0; i < mergedCount; i++) {
        if (mergedArray[i].bulan == 1){
            printf("Penghasilan klinik bulan Januari %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 2){
            printf("Penghasilan klinik bulan Februari %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 3){
            printf("Penghasilan klinik bulan Maret %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 4){
            printf("Penghasilan klinik bulan April %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 5){
            printf("Penghasilan klinik bulan Mei %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 6){
            printf("Penghasilan klinik bulan Juni %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 7){
            printf("Penghasilan klinik bulan Juli %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 8){
            printf("Penghasilan klinik bulan Agustus %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 9){
            printf("Penghasilan klinik bulan September %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 10){
            printf("Penghasilan klinik bulan Oktober %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 11){
            printf("Penghasilan klinik bulan November %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }
        else if (mergedArray[i].bulan == 12){
            printf("Penghasilan klinik bulan Desember %d adalah %d\n", mergedArray[i].tahun, mergedArray[i].biaya); 
        }

    }
}



int MonthToNumber (char a []){

    if (strcmp(a, "Januari")==0||strcmp(a, "Jan")==0) return 1;
    else if (strcmp(a, "Februari")==0||strcmp(a, "Feb")==0) return 2;
    else if (strcmp(a, "Maret")==0||strcmp(a, "Mar")==0) return 3;
    else if (strcmp(a, "April")==0||strcmp(a, "Apr")==0) return 4;
    else if (strcmp(a, "Mei")==0) return 5;
    else if (strcmp(a, "Juni")==0||strcmp(a, "Jun")==0) return 6;
    else if (strcmp(a, "Juli")==0||strcmp(a, "Jul")==0) return 7;
    else if (strcmp(a, "Agustus")==0||strcmp(a, "Agu")==0) return 8;
    else if (strcmp(a, "September")==0||strcmp(a, "Sep")==0) return 9;
    else if (strcmp(a, "Oktober")==0||strcmp(a, "Okt")==0) return 10;
    else if (strcmp(a, "November")==0||strcmp(a, "Nov")==0) return 11;
    else if (strcmp(a, "Desember")==0||strcmp(a, "Des")==0) return 12;
    else return -1; // Error case
}




/*
int main() {
    Riwayat riwayatArray[MAX];
    int count;
    char idpasiensearch[MAX];

    int ch;
    FILE* file = fopen("DataPMC20232024.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    Pasien* head = NULL;
    bacaDataPasien(file, &head);
    fclose(file);

    readCSV("riwayatpasien.csv", riwayatArray, &count);
    replaceHyphenWithSpace(riwayatArray, count);
    // printPasienList(head);

    // printRiwayatArray(riwayatArray, count);

    //get idpasiensearch from user using fgets

    printf("Masukkan ID Pasien yang ingin dicari: ");
    scanf("%[^\n]%*c", idpasiensearch);
    printf("\n");

    searchDataPasien(head, idpasiensearch);
    searchRiwayat(riwayatArray, count, idpasiensearch);
    

    // primnting sum by bulan tahun
    riwayatwithtanggal riwayatWithTanggalArray[MAX];
    penghasilan penghasilanArray[MAX];
    penghasilan mergedArray[MAX];
    penghasilantahun penghasilanTahunArray[MAX];
    penghasilantahun mergedTahunArray[MAX];
    int mergedCount, mergedTahunCount;
    getriwayatwithtanggal(riwayatWithTanggalArray, riwayatArray, count);
    add2000ToTahun(riwayatWithTanggalArray, count);
    convertformat(riwayatWithTanggalArray, count, penghasilanArray);
    mergePenghasilan(penghasilanArray, count, mergedArray, &mergedCount);
    sortPenghasilan(mergedArray, mergedCount);
    printTotalBiayaPerBulanTahun(mergedArray, mergedCount);
    fillPenghasilanTahunArray(mergedArray, mergedCount, penghasilanTahunArray, &mergedTahunCount);
    printTotalBiayaPerTahun(penghasilanTahunArray, mergedTahunCount);
    int avgyear = findAverageBiayaPerTahun(penghasilanTahunArray, mergedTahunCount);
    printf("\n");
    printf("Rata-rata pendapatan per tahun adalah %d\n", avgyear);

    return 0;
}
*/
