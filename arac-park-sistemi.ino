#define echoPin 6
#define trigPin 7
#define buzzerPin 8

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);  // İstersen seri monitörden mesafeyi de görebilirsin
}

void loop() {
  int distance = getDistance();

  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance == 0 || distance > 50) {
    noTone(buzzerPin);  // Çok uzakta ya da ölçüm hatalıysa sessiz
    delay(300);
  } else {
    int delayTime = map(distance, 5, 50, 50, 1000); // Yaklaştıkça bip hızı artar
    tone(buzzerPin, 1000);       // 1000 Hz — PASİF BUZZER için zorunlu
    delay(delayTime);
    noTone(buzzerPin);
    delay(delayTime);
  }
}

int getDistance() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration / 58.2;

  if (distance <= 0 || distance > 200) return 0;  // Ölçüm hatalıysa 0 döndür
  return distance;
}
