#define A0Pin 0
int sensorVal = 0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  sensorVal = analogRead(A0Pin);  // 토양센서 센서값 읽어 저장
  delay(1000);
  Serial.print("Asensor = ");
  Serial.println(sensorVal);  // 0(습함) ~ 1023(건조)값 출력 
  // 습도 값에 따라 출력 처리 다르게 해줌
  if ( sensorVal <= 450) {    
    Serial.println(" Very Wet ! ");        
  }
  if (sensorVal > 500 && sensorVal <= 1000) {
    Serial.println(" It's OK ! ");    
  }
  else if ( sensorVal > 1000){
    Serial.println(" Very Dry ! ");    
  }    
}
