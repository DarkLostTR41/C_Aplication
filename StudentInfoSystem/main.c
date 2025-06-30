#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main() {
    int n;
    char arr[MAX][7][50]; // [öğrenci][alan][karakter]
    FILE *fp;

    printf("Kac ogrenci kaydedilecek? ");
    scanf("%d", &n);
    getchar(); // tampon temizle

    // Öğrenci bilgilerini al
    for (int i = 0; i < n; i++) {
        printf("\n%d. ogrenci bilgileri:\n", i + 1);
        printf("ID: "); fgets(arr[i][0], 50, stdin); arr[i][0][strcspn(arr[i][0], "\n")] = 0;
        printf("Ad: "); fgets(arr[i][1], 50, stdin); arr[i][1][strcspn(arr[i][1], "\n")] = 0;
        printf("Soyad: "); fgets(arr[i][2], 50, stdin); arr[i][2][strcspn(arr[i][2], "\n")] = 0;
        printf("Sinif: "); fgets(arr[i][3], 50, stdin); arr[i][3][strcspn(arr[i][3], "\n")] = 0;
        printf("Numara: "); fgets(arr[i][4], 50, stdin); arr[i][4][strcspn(arr[i][4], "\n")] = 0;
        printf("Bolum: "); fgets(arr[i][5], 50, stdin); arr[i][5][strcspn(arr[i][5], "\n")] = 0;
        printf("Not Ortalamasi: "); fgets(arr[i][6], 50, stdin); arr[i][6][strcspn(arr[i][6], "\n")] = 0;
    }

    // Dosyaya yaz
    fp = fopen("ogrenciler.txt", "w");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s;%s;%s;%s;%s;%s;%s\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
    }
    fclose(fp);
    printf("\nOgrenciler dosyaya kaydedildi.\n");

    // Sorgulama
    char arananNumara[50];
    printf("\nSorgulamak istediginiz ogrencinin numarasini girin: ");
    fgets(arananNumara, 50, stdin);
    arananNumara[strcspn(arananNumara, "\n")] = 0;

    fp = fopen("ogrenciler.txt", "r");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }
    char satir[400];
    int bulundu = 0;
    while (fgets(satir, sizeof(satir), fp)) {
        char *token;
        char temp[7][50];
        int idx = 0;
        token = strtok(satir, ";");
        while (token != NULL && idx < 7) {
            strcpy(temp[idx++], token);
            token = strtok(NULL, ";");
        }
        if (strcmp(temp[4], arananNumara) == 0) {
            printf("\nOgrenci Bilgileri:\n");
            printf("ID: %s\nAd: %s\nSoyad: %s\nSinif: %s\nNumara: %s\nBolum: %s\nNot Ortalamasi: %s\n",
                   temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6]);
            bulundu = 1;
            break;
        }
    }
    fclose(fp);
    if (!bulundu) {
        printf("Ogrenci bulunamadi.\n");
    }
    printf("\nCikmak icin Enter'a basin...");
    getchar();
    return 0;
}