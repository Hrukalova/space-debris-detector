// -------------------------
// HC-SR04
// -------------------------
const int trigPin = 10;
const int echoPin = 11;

// -------------------------
// Пищалка
// -------------------------
const int buzzerPin = 8;

// -------------------------
// RGB светодиод
// -------------------------
const int redPin = 4;
const int greenPin = 5;
const int bluePin = 6;

// Опасное расстояние
const int dangerDistance = 20;


void setup() {

  Serial.begin(9600);

  // Дальномер
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Пищалка
  pinMode(buzzerPin, OUTPUT);

  // RGB
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // При запуске пищалка выключена
  digitalWrite(buzzerPin, LOW);
}


void loop() {

  // ==================================
  // 1. ИЗМЕРЯЕМ РАССТОЯНИЕ
  // ==================================

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  float distance;

  // Если датчик ничего не увидел
  if (duration == 0) {
    distance = 999;
  } else {
    distance = duration * 0.0343 / 2.0;
  }


  // ==================================
  // 2. ВЫВОДИМ РАССТОЯНИЕ
  // ==================================

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // ==================================
  // 3. ПРОВЕРЯЕМ ОПАСНОСТЬ
  // ==================================

  if (distance <= dangerDistance) {

    // 🚨 ОПАСНОСТЬ

    // Красный включить
    digitalWrite(redPin, HIGH);

    // Зеленый выключить
    digitalWrite(greenPin, LOW);

    // Синий выключить
    digitalWrite(bluePin, LOW);

    // Пищалка ВКЛЮЧЕНА ПОСТОЯННО
    digitalWrite(buzzerPin, HIGH);

    Serial.println("!!! DANGER - SPACE DEBRIS !!!");

  }

  else {

    // ✅ ВСЁ БЕЗОПАСНО

    // Красный выключить
    digitalWrite(redPin, LOW);

    // Зеленый включить
    digitalWrite(greenPin, HIGH);

    // Синий выключить
    digitalWrite(bluePin, LOW);

    // Пищалка выключена
    digitalWrite(buzzerPin, LOW);

    Serial.println("SAFE");

  }

  delay(100);
}
