#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUGUM 12 // Cizdigim diyagramda bulunan bina sayisi (Yurt dahil)

// Yapi tanimlari

typedef struct Dugum { // basit dugum yapisi
  int id;
  struct Dugum *sonraki;
} Dugum;

typedef struct Graf {
  int dugumSayisi;
  char *isimler[MAX_DUGUM];
  Dugum *komsulukListesi[MAX_DUGUM];         // liste yapisi
  int komsulukMatrisi[MAX_DUGUM][MAX_DUGUM]; // matris yapisi
  int ziyaret[MAX_DUGUM];                    // DFS ve BFS takibi icin
} Graf;

// Yardimci fonksiyonlar

// liste icin yeni dugum olusturma
Dugum *dugumOlustur(int id) {
  Dugum *yeni = malloc(sizeof(Dugum));
  yeni->id = id;
  yeni->sonraki = NULL;
  return yeni;
}

// grafi baslatma
Graf *grafOlustur(int n) {
  Graf *g = malloc(sizeof(Graf));
  g->dugumSayisi = n;

  for (int i = 0; i < n; i++) {
    g->komsulukListesi[i] = NULL;
    g->ziyaret[i] = 0;
    for (int j = 0; j < n; j++) {
      g->komsulukMatrisi[i][j] = 0;
    }
  }
  return g;
}

// binaya isim ver
void isimVer(Graf *g, int id, char *isim) { g->isimler[id] = isim; }

// yol ekle (cift yonlu)
void kenarEkle(Graf *g, int kaynak, int hedef) {
  // listeye ekle (kaynak -> hedef)
  Dugum *yeni = dugumOlustur(hedef);
  yeni->sonraki = g->komsulukListesi[kaynak];
  g->komsulukListesi[kaynak] = yeni;

  // listeye ekle (hedef -> kaynak)
  yeni = dugumOlustur(kaynak);
  yeni->sonraki = g->komsulukListesi[hedef];
  g->komsulukListesi[hedef] = yeni;

  // matrise isle
  g->komsulukMatrisi[kaynak][hedef] = 1;
  g->komsulukMatrisi[hedef][kaynak] = 1;
}

// BFS (en kisa yol)
void bfsYolBul(Graf *g, int baslangic, int bitis) {
  int mesafe[MAX_DUGUM];
  int ebeveyn[MAX_DUGUM]; // yolu geri takip etmek icin
  int kuyruk[MAX_DUGUM];
  int bas = 0, son = 0;

  // sifirlama
  for (int i = 0; i < g->dugumSayisi; i++) {
    g->ziyaret[i] = 0;
    mesafe[i] = -1;
    ebeveyn[i] = -1;
  }

  // baslangic ayarlari
  g->ziyaret[baslangic] = 1;
  mesafe[baslangic] = 0;
  kuyruk[son++] = baslangic;

  while (bas < son) {
    int suanki = kuyruk[bas++];

    if (suanki == bitis)
      break;

    Dugum *temp = g->komsulukListesi[suanki];
    while (temp) {
      int komsusu = temp->id;
      if (!g->ziyaret[komsusu]) {
        g->ziyaret[komsusu] = 1;
        mesafe[komsusu] = mesafe[suanki] + 1;
        ebeveyn[komsusu] = suanki;
        kuyruk[son++] = komsusu;
      }
      temp = temp->sonraki;
    }
  }

  if (mesafe[bitis] == -1) {
    printf(">>> HATA: %s ile %s arasinda yol YOK!\n", g->isimler[baslangic],
           g->isimler[bitis]);
  } else {
    // yolu ekrana yazdirma
    int yol[MAX_DUGUM];
    int sayac = 0;
    int gezen = bitis;

    yol[sayac++] = gezen;
    while (ebeveyn[gezen] != -1) {
      gezen = ebeveyn[gezen];
      yol[sayac++] = gezen;
    }

    printf("\n>>> En Kisa Yol (%d Durak): ", mesafe[bitis]);
    for (int i = sayac - 1; i >= 0; i--) {
      printf("%s", g->isimler[yol[i]]);
      if (i > 0)
        printf(" -> ");
    }
    printf("\n");
  }
}

// DFS (kopuk alan analizi)
void dfsGez(Graf *g, int id) {
  g->ziyaret[id] = 1;
  printf("[%s] ", g->isimler[id]);

  Dugum *temp = g->komsulukListesi[id];
  while (temp) {
    if (!g->ziyaret[temp->id]) {
      dfsGez(g, temp->id);
    }
    temp = temp->sonraki;
  }
}

void baglantiKontrol(Graf *g) {
  for (int i = 0; i < g->dugumSayisi; i++)
    g->ziyaret[i] = 0; // temizle

  int grupSayisi = 0;
  printf("\n>>> Kampus Baglanti Analizi:\n");

  for (int i = 0; i < g->dugumSayisi; i++) {
    if (g->ziyaret[i] == 0) {
      grupSayisi++;
      printf("Bolge %d: ", grupSayisi);
      dfsGez(g, i);
      printf("\n");
    }
  }

  if (grupSayisi > 1)
    printf("SONUC: Kampuste kopuk alanlar var! (Yurt binasi)\n");
  else
    printf("SONUC: Her yere yuruyerek gidilebilir.\n");
}

int main() {
  // binalara id veriyorum
  Graf *kampus = grafOlustur(12);

  isimVer(kampus, 0, "Giris");
  isimVer(kampus, 1, "Denizcilik");
  isimVer(kampus, 2, "Yemekhane");
  isimVer(kampus, 3, "A_Blok");
  isimVer(kampus, 4, "B_Blok");
  isimVer(kampus, 5, "C_Blok");
  isimVer(kampus, 6, "Isletme");
  isimVer(kampus, 7, "Mimarlik");
  isimVer(kampus, 8, "Kutuphane");
  isimVer(kampus, 9, "D_Blok");
  isimVer(kampus, 10, "Dekanlik");
  isimVer(kampus, 11, "Yurt"); // bunu kopuk yaptim DFS icin

  // haritandaki cizgilere gore yollar:
  kenarEkle(kampus, 0, 1);  // giris - denizcilik
  kenarEkle(kampus, 0, 3);  // giris - a blok
  kenarEkle(kampus, 0, 10); // giris - dekanlik

  kenarEkle(kampus, 1, 3); // denizcilik - a blok
  kenarEkle(kampus, 1, 2); // denizcilik - yemekhane

  kenarEkle(kampus, 2, 4); // yemekhane - b blok
  kenarEkle(kampus, 2, 6); // yemekhane - isletme

  kenarEkle(kampus, 3, 4); // a blok - b blok
  kenarEkle(kampus, 4, 5); // b Blok - c blok

  kenarEkle(kampus, 5, 9); // c Blok - d blok
  kenarEkle(kampus, 5, 7); // c Blok - mimarlik

  kenarEkle(kampus, 6, 7); // isletme - mimarlik
  kenarEkle(kampus, 7, 8); // mimarlik - kutuphane

  kenarEkle(kampus, 8, 9);  // Kutuphane - x blok
  kenarEkle(kampus, 9, 10); // d blok - dekanlik

  // NOT: 11 (Yurt) hicbir yere baglanmadi, gorseldeki gibi tek basina.

  int secim;
  while (1) {
    printf("\n--- KAMPUS NAVIGASYON ---\n");
    printf("1. Yol Tarifi Al (BFS)\n");
    printf("2. Kopuk Alanlari Bul (DFS)\n");
    printf("0. Cikis\n");
    printf("Secim: ");
    scanf("%d", &secim);

    if (secim == 0)
      break;

    if (secim == 1) {
      printf("\nBinalar:\n0:Giris, 1:Deniz, 2:Yemek, 3:A, 4:B, 5:C\n6:Isletme, "
             "7:Mimar, 8:Kutup, 9:D, 10:Dekan, 11:Yurt\n");
      int s, e;
      printf("Baslangic No: ");
      scanf("%d", &s);
      printf("Hedef No: ");
      scanf("%d", &e);
      if (s >= 0 && s < 12 && e >= 0 && e < 12)
        bfsYolBul(kampus, s, e);
      else
        printf("Hatali numara!\n");
    } else if (secim == 2) {
      baglantiKontrol(kampus);
    }
  }
  return 0;
}
