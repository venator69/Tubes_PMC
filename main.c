#include "header.c"
#include "functions/Adam.c"
#include "functions/Hubert.c"
#include "functions/Fitraka.c"
#include "functions/Raditya.c"
#include "functions/Requint.c"


int main() {
    int ch;
    FILE* file = fopen("DataPMC20232024.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    Pasien* head = NULL;
    bacaDataPasien(file, &head);
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