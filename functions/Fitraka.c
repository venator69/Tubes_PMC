void tambahRiwayatPasien(RiwayatPasienNode** head) {
    RiwayatPasienNode* newNode = (RiwayatPasienNode*)malloc(sizeof(RiwayatPasienNode));
    printf("Masukkan nomor riwayat: ");
    scanf("%d", &newNode->no);
    getchar(); // Consumes the newline character left in the input buffer by scanf

    printf("Masukkan tanggal (format DD MMM YYYY): ");
    fgets(newNode->tanggal, sizeof(newNode->tanggal), stdin);
    newNode->tanggal[strcspn(newNode->tanggal, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan ID Pasien: ");
    fgets(newNode->idPasien, sizeof(newNode->idPasien), stdin);
    newNode->idPasien[strcspn(newNode->idPasien, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan diagnosis: ");
    fgets(newNode->diagnosis, sizeof(newNode->diagnosis), stdin);
    newNode->diagnosis[strcspn(newNode->diagnosis, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan tindakan: ");
    fgets(newNode->tindakan, sizeof(newNode->tindakan), stdin);
    newNode->tindakan[strcspn(newNode->tindakan, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan tanggal kontrol (format DD MMM YYYY): ");
    fgets(newNode->kontrol, sizeof(newNode->kontrol), stdin);
    newNode->kontrol[strcspn(newNode->kontrol, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan biaya: ");
    scanf("%d", &newNode->biaya);
    getchar(); // Consumes the newline character left in the input buffer by scanf

    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        RiwayatPasienNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Fungsi untuk mencari riwayat pasien berdasarkan ID Pasien dan tanggal
void cariRiwayatPasien(RiwayatPasienNode* head) {
    char idPasien[20];
    char tanggal[50];

    printf("Masukkan ID Pasien: ");
    fgets(idPasien, sizeof(idPasien), stdin);
    fgets(idPasien, sizeof(idPasien), stdin);
    idPasien[strcspn(idPasien, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan tanggal (format DD MMM YYYY): ");
    fgets(tanggal, sizeof(tanggal), stdin);
    tanggal[strcspn(tanggal, "\n")] = '\0'; // Remove newline character if present

    RiwayatPasienNode* current = head;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->idPasien, idPasien) == 0 && strcmp(current->tanggal, tanggal) == 0) {
            found = true;
            printf("No: %d, Tanggal: %s, ID Pasien: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya: %d\n",
                   current->no, current->tanggal, current->idPasien, current->diagnosis, current->tindakan, current->kontrol, current->biaya);
        }
        current = current->next;
    }

    if (!found) {
        printf("Riwayat pasien dengan ID Pasien %s pada tanggal %s tidak ditemukan.\n", idPasien, tanggal);
    }
}

void hapusRiwayatPasien(RiwayatPasienNode** head) {
    char idPasien[20];

    printf("Masukkan ID Pasien untuk menghapus riwayat: ");
    fgets(idPasien, sizeof(idPasien), stdin);
    fgets(idPasien, sizeof(idPasien), stdin);
    idPasien[strcspn(idPasien, "\n")] = '\0'; // Remove newline character if present

    RiwayatPasienNode* current = *head;
    RiwayatPasienNode* prev = NULL;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->idPasien, idPasien) == 0) {
            found = true;
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Riwayat pasien dengan ID Pasien %s berhasil dihapus.\n", idPasien);
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        printf("Riwayat pasien dengan ID Pasien %s tidak ditemukan.\n", idPasien);
    }
}

void ubahRiwayatPasien(RiwayatPasienNode* head) {
    char idPasien[20];
    int no;

    printf("Masukkan ID Pasien yang ingin diubah: ");
    fgets(idPasien, sizeof(idPasien), stdin);
    fgets(idPasien, sizeof(idPasien), stdin);
    idPasien[strcspn(idPasien, "\n")] = '\0'; // Remove newline character if present

    printf("Masukkan nomor riwayat yang ingin diubah: ");
    scanf("%d", &no);

    RiwayatPasienNode* current = head;
    bool found = false;

    while (current != NULL) {
        if (strcmp(current->idPasien, idPasien) == 0 && current->no == no) {
            found = true;

            // Mengubah data riwayat pasien
            printf("Masukkan tanggal (format DD-MMM-YY): ");
            fgets(current->tanggal, sizeof(current->tanggal), stdin);
            fgets(current->tanggal, sizeof(current->tanggal), stdin);
            current->tanggal[strcspn(current->tanggal, "\n")] = '\0'; // Remove newline character if present
            
            printf("Masukkan diagnosis: ");
            fgets(current->diagnosis, sizeof(current->diagnosis), stdin);
            current->diagnosis[strcspn(current->diagnosis, "\n")] = '\0'; // Remove newline character if present
            
            printf("Masukkan tindakan: ");
            fgets(current->tindakan, sizeof(current->tindakan), stdin);
            current->tindakan[strcspn(current->tindakan, "\n")] = '\0'; // Remove newline character if present
            
            printf("Masukkan tanggal kontrol (format DD-MMM-YY): ");
            fgets(current->kontrol, sizeof(current->kontrol), stdin);
            current->kontrol[strcspn(current->kontrol, "\n")] = '\0'; // Remove newline character if present

            printf("Masukkan biaya: ");
            scanf("%d", &current->biaya);

            printf("Riwayat pasien dengan ID Pasien %s dan nomor %d telah diubah.\n", idPasien, no);
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Riwayat pasien dengan ID Pasien %s dan nomor %d tidak ditemukan.\n", idPasien, no);
    }
}

/*
 case 5:
    tambahRiwayatPasien(&riwayatPasienHead);
    break;
case 6:
    cariRiwayatPasien(riwayatPasienHead);
    break;
case 7:
    hapusRiwayatPasien(&riwayatPasienHead);
    break;
case 8:
    ubahRiwayatPasien(riwayatPasienHead);
    break;
*/
