#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu1;
MPU6050 mpu2;

#define set1 2
#define set2 3

String data;
unsigned long timer = 0;
float timeStep = 0.01;
float yaw1 = 90;
float yaw2 = 90;

void setup() {
  Serial.begin(9600);
  pinMode(set1, OUTPUT);
  pinMode(set2, OUTPUT);
  digitalWrite(set1, HIGH);
  digitalWrite(set2, HIGH);
  
  // Inisialisasi MPU6050
  while(!mpu1.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor 1, check wiring!");
    delay(200);
  }
  mpu1.calibrateGyro();
  mpu1.setThreshold(1);
  
  while(!mpu2.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor 2, check wiring!");
    delay(200);
  }
  mpu2.calibrateGyro();
  mpu2.setThreshold(1);
}

void loop() {
  timer = millis();
  
  // Membaca data gyro dari MPU6050
  Vector norm1 = mpu1.readNormalizeGyro();
  Vector norm2 = mpu2.readNormalizeGyro();

  // Menghitung data yaw dari masing-masing sensor
  if(norm1.ZAxis > 0) {
    yaw1 = yaw1 - (norm1.ZAxis * timeStep) - (norm1.ZAxis * timeStep * 0.19); // CW  kurang+ lebih -
  }
  if(norm1.ZAxis < 0) {
    yaw1 = yaw1 - (norm1.ZAxis * timeStep) - (norm1.ZAxis * timeStep * 0.193); // CCW kurang+ lebih -
  }
  
  if(norm2.ZAxis > 0) {
    yaw2 = yaw2 - (norm2.ZAxis * timeStep) - (norm2.ZAxis * timeStep * 0.19); // CW  kurang+ lebih -
  }
  if(norm2.ZAxis < 0) {
    yaw2 = yaw2 - (norm2.ZAxis * timeStep) - (norm2.ZAxis * timeStep * 0.193); // CCW kurang+ lebih -
  }
  
  // Mengirimkan data yaw ke serial monitor
  Serial.print("Yaw 1: ");
  Serial.println(yaw1);
  Serial.print("Yaw 2: ");
  Serial.println(yaw2);
  
  delay((timeStep*1000) - (millis() - timer));
}
