#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definisi
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C default biasanya 0x27

void setup() {
  // Setup komunikasi serial
  Serial.begin(9600);
  
  // Inisialisasi pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo ke pin
  myServo.attach(servoPin);
  myServo.write(0);  // Servo mulai dari posisi 0 derajat

  // Inisialisasi LCD
  lcd.begin();
  lcd.backlight();  // Menyalakan lampu latar LCD
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
}

void loop() {
  long duration, distance;

  // Trigger sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Membaca durasi dari sinyal echo
  duration = pulseIn(echoPin, HIGH);
  
  // Menghitung jarak (dalam cm)
  distance = duration * 0.034 / 2;

  // Menampilkan jarak ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Menampilkan jarak ke LCD
  lcd.setCursor(0, 1);  // Pindah ke baris kedua
  lcd.print("           ");  // Membersihkan baris kedua
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Jika objek lebih dekat dari 20 cm, gerakkan servo ke 90 derajat
  if (distance < 20) {
    myServo.write(90);
  } else {
    myServo.write(0);  // Kembali ke posisi awal (0 derajat)
  }

  delay(500);  // Delay untuk memperlambat pembacaan
}