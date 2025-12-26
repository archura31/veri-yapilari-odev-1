# Veri Yapıları Projesi - Algoritma Analiz Raporu

Bu proje kapsamında geliştirilen **Kampüs Navigasyon Sistemi** için kullanılan graf (graph) algoritmalarının zaman karmaşıklığı analizleri aşağıdadır.

## 1. Kullanılan Veri Yapısı ve Tanımlar

Algoritmalarımızın performansını analiz ederken aşağıdaki değişkenler temel alınmıştır:
- **V (Vertex / Düğüm):** Kampüsteki toplam bina sayısı.
- **E (Edge / Kenar):** Binaları birbirine bağlayan toplam yol sayısı.

Projede graf yapısı hem **Komşuluk Matrisi (Adjacency Matrix)** hem de **Komşuluk Listesi (Adjacency List)** olarak modellenmiştir. Ancak arama algoritmaları (BFS ve DFS), performans verimliliği açısından **Komşuluk Listesi** üzerinde çalıştırılmıştır.

---

## 2. BFS Algoritması (En Kısa Yol)

Genişlik Öncelikli Arama (Breadth-First Search - BFS), kampüs içindeki iki bina arasındaki en az duraklı yolu bulmak için kullanılmıştır.

* **Zaman Karmaşıklığı:** $O(V + E)$
* **Analiz:**
    * En kötü durumda (worst-case), algoritma başlangıç düğümünden ulaşılabilen tüm düğümleri ($V$) ziyaret eder.
    * Ziyaret edilen her düğümün komşularını kontrol ederken, graf üzerindeki tüm kenarlar ($E$) üzerinden en fazla birer kez geçilir.
    * Komşuluk listesi kullanıldığı için boş bağlantıları kontrol etmekle zaman kaybedilmez. (Matris kullanılsaydı karmaşıklık $O(V^2)$ olurdu).

---

## 3. DFS Algoritması (Bağlı Bileşen Analizi)

Derinlik Öncelikli Arama (Depth-First Search - DFS), kampüsteki kopuk alanların (bağlı olmayan bileşenlerin) tespiti için kullanılmıştır.

* **Zaman Karmaşıklığı:** $O(V + E)$
* **Analiz:**
    * DFS algoritması, özyinelemeli (recursive) bir yapıya sahiptir.
    * Algoritma, ziyaret edilmemiş her düğüm ($V$) için bir kez çağrılır.
    * Her düğümün komşuluk listesindeki kenarlar ($E$) taranır.
    * Toplam işlem süresi, düğüm sayısı ve kenar sayısının toplamı ile doğru orantılıdır.

---

## 4. Sonuç

Her iki algoritma da **Lineer Zaman Karmaşıklığına (O(V+E))** sahiptir. Bu durum, kampüs haritası büyüse (bina ve yol sayısı artsa) bile sistemin performansının kabul edilebilir seviyelerde kalacağını ve verimli çalışacağını gösterir.
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
