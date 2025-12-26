---

## Soru 2: Tarayıcı Geçmişi Simülasyonu (Browser History)

Bu modülde, modern web tarayıcılarının "Geri" ve "İleri" butonlarının çalışma mantığı **Yığın (Stack)** veri yapısı kullanılarak simüle edilmiştir.

### 1. Kullanılan Veri Yapısı Tasarımı

Sistemde 3 temel bileşen bulunur:
1.  **Back Stack (Geri Yığını):** Ziyaret edilen önceki sayfaları tutar.
2.  **Forward Stack (İleri Yığını):** Geri gelindiğinde, tekrar ileri gidilebilecek sayfaları tutar.
3.  **Current Page (Aktif Sayfa):** Kullanıcının o an görüntülediği URL.

### 2. Algoritma Mantığı ve İşlemler

* **Visit (Yeni Sayfa):** Yeni bir adrese gidildiğinde;
    * Mevcut sayfa *Back Stack*'e atılır (Push).
    * *Forward Stack* tamamen temizlenir (Çünkü yeni bir tarihçe dalı oluşur).
* **Back (Geri Git):**
    * Mevcut sayfa *Forward Stack*'e atılır.
    * *Back Stack*'ten bir önceki sayfa çekilir (Pop) ve aktif yapılır.
* **Forward (İleri Git):**
    * Mevcut sayfa *Back Stack*'e atılır.
    * *Forward Stack*'ten bir sonraki sayfa çekilir (Pop) ve aktif yapılır.

### 3. Zaman Karmaşıklığı Analizi

Yığın (Stack) veri yapısının doğası gereği, ekleme ve çıkarma işlemleri sadece "en üstteki" elemanla yapılır. Herhangi bir döngü veya arama işlemi gerekmez.

* **Push (Ekleme):** $O(1)$
* **Pop (Çıkarma):** $O(1)$
* **Clear (Forward Stack Temizleme):** $O(N)$ (Sadece yeni sayfa ziyaretinde, yığın boyutu kadar).

**Neden Stack Seçildi?**
Tarayıcı geçmişinde gezinme işlemi **LIFO (Last-In, First-Out / Son Giren İlk Çıkar)** mantığına dayanır. En son ziyaret ettiğimiz sayfa, geri tuşuna bastığımızda ilk karşımıza çıkması gereken sayfadır. Bu nedenle Stack, bu problem için en optimize veri yapısıdır.
