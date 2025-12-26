#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GECMIS 20
#define URL_BOYUT 50

// Stack yapisi
typedef struct {
  char linkler[MAX_GECMIS][URL_BOYUT];
  int tepe; // en ustteki elemanin indisi
} Yigin;

// Fonksiyonlar

void yiginOlustur(Yigin *y) { y->tepe = -1; }

int bosMu(Yigin *y) { return y->tepe == -1; }

void ekle(Yigin *y, char *url) {
  if (y->tepe < MAX_GECMIS - 1) {
    y->tepe++;
    strcpy(y->linkler[y->tepe], url);
  }
}

char *cikar(Yigin *y) {
  if (bosMu(y))
    return NULL;
  return y->linkler[y->tepe--];
}

// ekrandaki tabloyu cizdiren fonksiyon
void durumYazdir(char *aktif, Yigin *geri, Yigin *ileri) {
  printf("\n=====================================\n");
  printf(" SU ANKI SAYFA: [ %s ]\n", aktif);
  printf("=====================================\n");

  printf(" GERI (Back) Yigini:\n");
  if (bosMu(geri))
    printf("  (Bos)\n");
  for (int i = geri->tepe; i >= 0; i--) {
    printf("  | %s |\n", geri->linkler[i]);
  }
  printf("  +----------------+\n");

  printf(" ILERI (Forward) Yigini:\n");
  if (bosMu(ileri))
    printf("  (Bos)\n");
  for (int i = ileri->tepe; i >= 0; i--) {
    printf("  | %s |\n", ileri->linkler[i]);
  }
  printf("  +----------------+\n");
  printf("=====================================\n");
}

int main() {
  Yigin geriYigini, ileriYigini;
  yiginOlustur(&geriYigini);
  yiginOlustur(&ileriYigini);

  char aktifSayfa[URL_BOYUT] = "duckduckgo.com"; // acilis sayfasi
  int secim;
  char yeniUrl[URL_BOYUT];

  durumYazdir(aktifSayfa, &geriYigini, &ileriYigini);

  while (1) {
    printf("\n1. Siteye Git (Visit)\n");
    printf("2. Geri Git (Back)\n");
    printf("3. Ileri Git (Forward)\n");
    printf("0. Cikis\n");
    printf("Islem seciniz: ");
    scanf("%d", &secim);

    if (secim == 0)
      break;

    switch (secim) {
    case 1: // yeni siteye git
      printf("URL girin (orn: youtube.com): ");
      scanf("%s", yeniUrl);

      // mantik: eskiyi geri yiginina at, ileriyi temizle
      ekle(&geriYigini, aktifSayfa);
      strcpy(aktifSayfa, yeniUrl);
      yiginOlustur(&ileriYigini); // ileri yigini sifirlanir
      break;

    case 2: // Geri git
      if (!bosMu(&geriYigini)) {
        ekle(&ileriYigini, aktifSayfa);         // suankini ileriye at
        strcpy(aktifSayfa, cikar(&geriYigini)); // geriden al
      } else {
        printf("\nUYARI: Geri gidilecek sayfa yok!\n");
      }
      break;

    case 3: // ileri git
      if (!bosMu(&ileriYigini)) {
        ekle(&geriYigini, aktifSayfa);           // suankini geriye at
        strcpy(aktifSayfa, cikar(&ileriYigini)); // ileriden al
      } else {
        printf("\nUYARI: Ileri gidilecek sayfa yok!\n");
      }
      break;
    }
    durumYazdir(aktifSayfa, &geriYigini, &ileriYigini);
  }

  return 0;
}
