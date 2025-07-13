# ARDUINO ARAÇ PARK SİSTEMİ
<img src="arduino_uno_sensör.png" width="1000px"><br>

## ## 📋 Proje Tanımı

Bu proje, araçların park ederken yakın çevredeki nesneleri algılamasına yardımcı olan bir **park destek sistemi (PAEK sistemi)**dir. Arduino UNO, **HC-SR04 ultrasonik sensör** ve **pasif buzzer** kullanılarak geliştirilmiştir. Sistem, yakındaki bir nesneyi algıladığında buzzer ile sesli uyarı verir. Nesneye yaklaşıldıkça uyarı sesi daha hızlı hale gelir.

Proje, **Arduino ile elektronik temellerini öğrenmek isteyen herkes için uygundur.** Basit bağlantılarla gerçek dünyada işlevsel bir sistem inşa etmek hedeflenmiştir.

---

## ✨ Demo & Proje Kodları Anlatımı

Aşağıda, sistemin nasıl çalıştığını gösteren açıklamalı Arduino kodları yer almaktadır.

```cpp
// Ultrasonik sensör ve buzzer pinlerini belirliyoruz
#define echoPin 6        // Sensörden gelen yankı sinyali (Echo)
#define trigPin 7        // Sensöre gönderilecek tetik sinyali (Trigger)
#define buzzerPin 8      // Pasif buzzer'ı bağladığımız pin

void setup() {
  // Pinlerin giriş/çıkış yönlerini belirliyoruz
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Seri port ekranını başlatıyoruz, mesafeyi görmek için
  Serial.begin(9600);
}

void loop() {
  // Mesafe ölçümünü yapıyoruz
  int distance = getDistance();

  // Ölçülen mesafeyi seri ekranda gösteriyoruz
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Eğer nesne çok uzakta veya ölçüm hatalıysa ses vermiyoruz
  if (distance == 0 || distance > 50) {
    noTone(buzzerPin);     // Buzzer susturulur
    delay(300);            // Küçük bir gecikme
  } else {
    // Nesneye yaklaştıkça buzzer'ın bip sesi hızlanır
    int delayTime = map(distance, 5, 50, 50, 1000); // Mesafeye göre gecikme süresi
    tone(buzzerPin, 1000);     // 1000 Hz frekansla ses çıkar (pasif buzzer için)
    delay(delayTime);          // Sesin süresi
    noTone(buzzerPin);         // Ses kapatılır
    delay(delayTime);          // Sessizlik süresi
  }
}

// Mesafeyi hesaplayan fonksiyon
int getDistance() {
  long duration;

  // Trig pinine kısa bir sinyal gönderiyoruz (ölçüm için)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pininden gelen sinyal süresini ölçüyoruz
  duration = pulseIn(echoPin, HIGH);

  // Süreyi cm cinsine çeviriyoruz (HC-SR04 için formül)
  int distance = duration / 58.2;

  // Geçersiz ölçümse 0 döndür (örneğin sensör boşlukta kaldıysa)
  if (distance <= 0 || distance > 200) return 0;

  return distance;
}


