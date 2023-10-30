/* TC74센서로 RGB LED를 이용 I2C LCD에 온도 표시하기  */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16,2);
const int RLED=9; //9번 핀을 사용하는 빨간색 BLED 상수 정의 
const int GLED=10; //10번 핀을 사용하는 초록색 GLED 상수 정의 
const int BLED=11; //11번 핀을 사용하는 파란색 RLED 상수 정의 
const int tempAdress=72; //TC74 센서의 고유 주소값(10진 값)
const int LOWER_BOUND=20;  //온도 하한값을 정의한 LOWER_BOUND 상수 정의
const int UPPER_BOUND=30;  //온도 상한값을 정의한 UPPER_BOUND 상수 정의

byte SpecialChar0[8] = {  
 B00010,
 B00101,
 B00101,
 B00010,
 B00000,
 B00000,
 B00000,
 B00000
};
void setup() {
  Wire.begin();     // I2C Wire 객체 시작
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.createChar(0,SpecialChar0);
  pinMode(RLED, OUTPUT);  // RLED를 출력으로 지정
  pinMode(GLED, OUTPUT);  // GLED를 출력으로 지정
  pinMode(BLED, OUTPUT);  // BLED를 출력으로 지정  
}

void loop() {
  Wire.beginTransmission(tempAdress); // I2C 센서와 통신 개시
  Wire.write(0);  // I2C 센서의 0번 레지스터를 읽겠다는 명령을 쓰기모드로 전송
  Wire.endTransmission();
  Wire.requestFrom(tempAdress, 1); // I2C센서에서 1바이트 값을 읽음
  while(Wire.available()==0);  // 응답이 올 때까지 대기
  int TempC = Wire.read();  // 온도(섭씨)를 읽어 변수에 저장
  int TempF = round(TempC * 9.0 / 5.0 + 32.0); // 섭씨 온도를 화씨로 변환(소수점 반올림)
  
  Serial.print(TempC);
  Serial.print("C  /  ");
  Serial.print(TempF);
  Serial.println("F");
  delay(500);
 
  lcd.setCursor(0,0);  
  lcd.print("temperature Sensor!");
  lcd.setCursor(0,1);
  lcd.print("C:");
  lcd.print(TempC);
  lcd.write(0);
  lcd.print("C /");

  lcd.print(" F:");
  lcd.print(TempF);
  lcd.write(0);
  lcd.print("F ");
  delay(500);
  if(TempC < LOWER_BOUND)    // 하위 경계선 값 이하이면 Blue LED ON
  {  // RGB LED 공통단자 '-' 사용  (켜려고 하는 LED에 HIGH 값 지정)
    digitalWrite(RLED,LOW);
    digitalWrite(GLED,LOW);
    digitalWrite(BLED,HIGH);
  }
  else if (TempC > UPPER_BOUND)  // 상위 경계선 값 이하이면 Red LED ON
  {  
    digitalWrite(RLED,HIGH);
    digitalWrite(GLED,LOW);
    digitalWrite(BLED,LOW);    
  }
  else {                     // 경계선 사이 값 이면 Green LED ON
    digitalWrite(RLED,LOW);
    digitalWrite(GLED,HIGH);
    digitalWrite(BLED,LOW);
  }  
}
