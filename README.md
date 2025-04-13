**Multi-Process Calculator with Pipes in C**  
Bu proje, C dilinde yazılmış ve terminal üzerinden çalışan bir hesap makinesidir. UNIX sistem çağrıları olan `fork()`, `pipe()` ve `execlp()` kullanılmıştır.

**Desteklenen İşlemler:**  
- Toplama  
- Çıkarma  
- Çarpma  
- Bölme  

Her bir işlem, kendine özel bir alt işlem (subprocess) tarafından gerçekleştirilir. İşlem sonuçları `results.txt` adlı dosyaya alt işlemler tarafından otomatik olarak kaydedilir. Ana işlem bu kaydı yapmaz.

---

**Nasıl Çalışır?**  

1. **Ana Program (`calculator.c`)**  
   - Kullanıcıya bir menü gösterir ve iki sayı girmesini ister.  
   - Bu sayılar, ilgili alt sürece pipe (boru) üzerinden gönderilir.  
   - Sonuç aynı pipe üzerinden alınır ve terminalde görüntülenir.  

2. **Alt Süreçler (`addition.c`, `subtraction.c`, vb.)**  
   - Pipe üzerinden sayıları okurlar.  
   - İşlemi yaparlar.  
   - Sonucu hem pipe ile ana sürece gönderir hem de `results.txt` dosyasına kaydederler.  

**Not:** `dup`, `dup2` ve `STDIN_FILENO` gibi komutlar kullanılmamıştır.

---

**Dosya Yapısı:**

- `calculator.c`  
- `addition.c`  
- `subtraction.c`  
- `multiplication.c`  
- `division.c`  
- `results.txt` (alt işlemler tarafından otomatik oluşturulur)  
- `Makefile` (İsteğe bağlı derleme aracı)  
- `README.md`

---

**Derleme Komutları:**

Her bir dosyayı ayrı ayrı aşağıdaki gibi derleyebilirsiniz:

```
gcc -o calculator calculator.c
gcc -o addition addition.c
gcc -o subtraction subtraction.c
gcc -o multiplication multiplication.c
gcc -o division division.c
```

---

**Çalıştırma:**

```
./calculator
```

---

**Örnek Çıktı:**

```
========================================
          Welcome to Calculator         
========================================
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Exit
========================================
Enter your choice: 1
Enter two numbers (e.g., 10 5): 12 7

========================================
             ***** RESULT *****         
Addition Result: 12 + 7 = 19
========================================
```

Aynı sonuç ayrıca `results.txt` dosyasına da kaydedilir.

---

**Sağlanan Gereksinimler:**

- `dup`, `dup2` veya `STDIN_FILENO` kullanılmamıştır.  
- Her işlem alt bir süreç tarafından gerçekleştirilir.  
- Sonuç kaydı alt süreçlerde yapılır.  
- Tüm veri iletimi pipe (boru) üzerinden sağlanır.  
- Modüler ve temiz bir mimari kullanılmıştır.

---

**Yazar:**  
https://github.com/Aliylmaz

---

**Lisans:**  
Bu proje açık kaynaklıdır ve MIT lisansı altında ücretsiz olarak kullanılabilir.
