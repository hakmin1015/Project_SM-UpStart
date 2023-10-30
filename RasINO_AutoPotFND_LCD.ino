/* Auto Water Pot - 자동 물공급 화분 with FND & LCD */
/* Rasino.tistory.com 제작도면과 자료 제공합니다 */

#define humiditySensor  A0
#define pump  9

#include <LiquidCrystal_I2C.h> //i2c LCD 사용위한 선언
LiquidCrystal_I2C lcd (0x27, 16,2); //(고유ID, 16칸2줄LCD)
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(pump, OUTPUT);
}
void loop() {

  int sensorData = analogRead(humiditySensor);
  sensorData = map(sensorData, 0, 1023, 9, 0);
  
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Dry---------Wet");  // 첫 줄에 적힐 내용
  lcd.setCursor(7, 0);
  lcd.print(sensorData, 1);
  lcd.setCursor(2, 1);

  lcd.write("        ");
  for(int i = 0; i < sensorData; i++) lcd.write(0xFF);

  if(sensorData <= 2) {
    Serial.println("Very Dry !");
    Serial.println("Pumping for 1 Second");
    digitalWrite(pump, HIGH);
    delay(1000);
  } else {
    Serial.println("Very Wet !");
    digitalWrite(pump, LOW);
  }
  delay(3000);
}
