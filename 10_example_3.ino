#include <Servo.h> 
#include <math.h> 

#define PIN_SERVO 10

Servo myServo;
unsigned long MOVING_TIME = 3000; // 이동 시간 3초
unsigned long moveStartTime;
int startAngle = 30; 
int stopAngle  = 90; 

void setup() {
  myServo.attach(PIN_SERVO);
  moveStartTime = millis(); // 움직임 시작 시간 기록

  myServo.write(startAngle); // 초기 위치 설정
  delay(500);
}

void loop() {
  unsigned long progress = millis() - moveStartTime;

  if (progress <= MOVING_TIME) {
    // 진행도를 0에서 1로 정규화
    float normalProgress = (float)progress / (float)MOVING_TIME;
    
    // Sigmoid 함수 계산
    float z = 20 * (normalProgress - 0.5); // Sigmoid 함수 범위를 -10에서 10으로 조정
    float sigmoidValue = 1.0 / (1.0 + exp(-z)); // Sigmoid 함수 계산
    
    // Sigmoid 값을 0~1 사이에서 startAngle과 stopAngle 사이로 변환
    float angle = startAngle + (stopAngle - startAngle) * sigmoidValue;
    
    myServo.write(angle); // 서보 모터를 해당 각도로 이동
  } 
}
