# Panel de Pon · C Terminal Game

**Türkçe** | [English](README.en.md)

Panel de Pon mekaniklerinden esinlenen, C ile geliştirilmiş terminal tabanlı bir bulmaca oyunu. Oyuncu hücrelerin yerini değiştirir, aynı sembollerden oluşan dizileri temizler ve tahta üst sınıra ulaşmadan alan açmaya çalışır.

Oyun arayüzü Türkçedir; harici kütüphane gerektirmez.

## Oyun mekanikleri

- **Ayarlanabilir tahta:** Her boyutu 1–20 arasında seçilebilen oyun alanı.
- **Beş sembol:** `*`, `/`, `+`, `%` ve `O`. Nokta (`.`) boş hücreyi gösterir.
- **İki başlangıç modu:** Rastgele yerleşim veya elle girilen hücrelerle kontrol modu.
- **Eşleşme temizleme:** Seçilen hücreden sağa veya aşağı uzanan en az üç aynı sembolü patlatma.
- **Yerçekimi:** Hamle sonrasında boşlukların üzerindeki semboller aşağı düşer.
- **Yükselen tahta:** Geçerli yer değiştirme hamlesinin ardından alta rastgele bir satır eklenir.
- **Sayaçlar:** Yer değiştirme sayısı ve toplam patlatılan sembol sayısı ekranda gösterilir.

## Derleme ve çalıştırma

GCC veya Clang bulunan bir **macOS / Linux** terminalinde proje klasörüne geçip çalıştırın:

```sh
cc -std=c11 -Wall -Wextra panel_de_pon.c -o panel-de-pon
./panel-de-pon
```

Windows üzerinde WSL kullanılabilir. Kaynak kod `unistd.h` ve `sleep()` kullandığı için doğrudan yerel Windows derlemesi ek uyarlama gerektirir.

## Nasıl oynanır?

1. Başlangıçta `1` ile oyun modunu, `2` ile kontrol modunu seçin.
2. Tahta boyutunu aralarında boşluk bırakarak girin: örneğin `8 6`.
3. Menüden hamlenizi seçin ve istenen koordinatları girin.

| Menü | İşlem | Örnek giriş |
| --- | --- | --- |
| `1` | Hücrelerin yerini değiştir | `7,2 7,3` |
| `2` | Eşleşen sembolleri patlat | `7,1` |
| `0` | Oyundan çık | Ek koordinat gerekmez |

**Koordinatlar `satır,sütun` biçimindedir ve 1’den başlar.** Girişte parantez kullanmayın; iki hücre için araya boşluk koyun. Satırlar yukarıdan aşağıya, sütunlar soldan sağa numaralandırılır. Amaç, dolu ve yatay ya da dikey komşu iki hücrenin yerini değiştirmektir.

Patlama otomatik gerçekleşmez: menüden `2` seçilmelidir. Örneğin bir satırda şu dizi varsa:

```text
    1 2 3 4 5 6
7   * * * + O %
```

`7,1` koordinatı ilk üç sembolü temizler. Tarama yalnızca **sağa ve aşağı** yapıldığı için dizinin sol veya üst ucunu seçin. Her iki yönde de en az üçlü eşleşme varsa uzun olan temizlenir; eşitlikte yatay dizi seçilir.

Yer değiştirme sonrasında yeni satır tahtayı yukarı iter. Üst satırda bir sembol kaldığında oyun sona erer. Hamle gösterimleri arasında yaklaşık üç saniye bekleme vardır.

### Kontrol modu

Kontrol modunda tahtanın başlangıçta doldurulan alt bölümünü elle girerek belirli eşleşmeleri deneyebilirsiniz. Hücreler en alt satırdan yukarı doğru, her satırda soldan sağa istenir. Bu giriş istemlerindeki indeksler **0 tabanlıdır**; oyun sırasında kullanılan koordinatlar ise **1 tabanlıdır**. Kontrol modunda ara ekranlar temizlenmez; yer değiştirme sonrası eklenen satırlar yine rastgeledir.

## Proje yapısı

```text
.
├── panel_de_pon.c  # Oyun döngüsü, tahta ve hamle işlemleri
├── screenshots/   # Oyun ekran görüntüleri
├── .gitignore     # Yerel dosyalar ve derleme çıktıları
├── README.md      # Türkçe dokümantasyon
└── README.en.md   # İngilizce dokümantasyon
```

## Teknik notlar ve mevcut sınırlamalar

Tahta iki boyutlu bir karakter dizisinde tutulur. Başlangıç yerleşimi ve yeni satırlar `rand()` ile üretilir; rastgelelik başlangıcı `time(NULL)` ile belirlenir. Oyun akışı `main()`, tahta gösterimi `printBoard()`, satır ekleme `addRandomRow()` ve ekran temizleme `clearScreen()` içinde bulunur.

Bu sürüm temel bir ders projesidir. Kullanırken aşağıdaki sınırlamaları dikkate alın:

- Sayısal olmayan veya eksik girişler için sağlam bir giriş doğrulaması bulunmaz.
- Yer değiştirmede komşuluk veya boş hücre kontrolü hata verse bile takas kodu çalışabilir. Aynı hücrenin iki kez seçilmesi de engellenmez.
- Patlama işleminde sınır dışı koordinat girilmesi geçersiz bellek erişimine yol açabilir; tahta sınırları içinde kalın.
- Eşleşmeler tüm tahtada otomatik aranmaz; zincirleme patlama sistemi bulunmaz.

Kaynak kodun mevcut davranışı korunmuştur. Bu depo, terminal üzerinde dizi işlemleri, kullanıcı girdisi ve temel oyun mantığı çalışmalarını sunar.
