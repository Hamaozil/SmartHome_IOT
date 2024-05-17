#include <Servo.h>
#include <SoftwareSerial.h>
//leds
#define bedRoomLed 2 //N4 relay1
#define officeLed 3 //N1 relay2
#define livingRoomLed 4 //N2 relay2
//fans
#define bedRoomFan 5 //N1 relay1
#define officeFan 6 //N2 relay1
#define livingRoomFan 7 //N3 relay1
//-------------------------------------
#define gas_sensor A0
#define buzzer 8
#define servo_pin 9
#define temperature_sensor A1

#define gas_threshold 900

Servo myservo;
SoftwareSerial gas(12, 13);
void setup() {
  // leds
  pinMode(bedRoomLed, OUTPUT);
  pinMode(officeLed, OUTPUT);
  pinMode(livingRoomLed, OUTPUT);
  // fans
  pinMode(bedRoomFan, OUTPUT);
  pinMode(officeFan, OUTPUT);
  pinMode(livingRoomFan, OUTPUT);

  // defualt is  off
  digitalWrite(bedRoomLed, HIGH);
  digitalWrite(officeLed, HIGH);
  digitalWrite(livingRoomLed, HIGH);

  digitalWrite(bedRoomFan, HIGH);
  digitalWrite(officeFan, HIGH);
  digitalWrite(livingRoomFan, HIGH);
  //----------------------------------------------
  pinMode(gas_sensor, INPUT);
  pinMode(temperature_sensor, INPUT);
  pinMode(ir, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  myservo.attach(servo_pin);
  //Serial.println("Sounds good lets do it....");
  delay(100);
}
// topic --->home/bedRoomLed/  ---->message ---->on (0) /  off (1)
// topic --->home/officeLed/ ---->message ---->on (0) / off (1)
// topic --->home/livingRoomLed/  ---->message ---->on (0) / off (1)

// topic --->home/bedRoomFan/  ---->message ---->on (0) / off (1)
// topic --->home/officeFan/  ---->message ---->on (0) / off (1)
// topic --->home/livingRoomFan/  ---->message ---->on (0) / off (1)

unsigned long previous = 0;
byte ir_read ;
int gas_read , sensorValue;
float voltage , temperature;
void loop() {

  ir_read = digitalRead(ir);
  gas_read = analogRead(gas_sensor);

  sensorValue = analogRead(temperature_sensor);  // Read the analog value from the LM35
  voltage = sensorValue * (5.0 / 1023.0);  // Convert the analog value to voltage
  temperature = (voltage - 0.5) * 100;  // Convert the voltage to temperature (in Celsius)

  if (Serial.available() > 0)
  {
    String topic_msg = Serial.readStringUntil('\n');
    //state = topicName/message      home/bedRoomLed/on
    if (topic_msg == "home/bedRoomLed/on")
      digitalWrite(bedRoomLed, LOW);
    else if (topic_msg == "home/bedRoomLed/off")
      digitalWrite(bedRoomLed, HIGH);

    //home/officeLed/on
    else if (topic_msg == "home/officeLed/on")
      digitalWrite(officeLed, LOW);
    else if (topic_msg == "home/officeLed/off")
      digitalWrite(officeLed, HIGH);

    //home/livingRoomLed/on
    else if (topic_msg == "home/livingRoomLed/on")
      digitalWrite(livingRoomLed, LOW);
    else if (topic_msg == "home/livingRoomLed/off")
      digitalWrite(livingRoomLed, HIGH);
    //--------------------------------------------------------------------------

    //home/bedRoomFan/on
    else if (topic_msg == "home/bedRoomFan/on")
      digitalWrite(bedRoomFan, LOW);
    else if (topic_msg == "home/bedRoomFan/off")
      digitalWrite(bedRoomFan, HIGH);

    //home/officeFan/on
    else if (topic_msg == "home/officeFan/on")
      digitalWrite(officeFan, LOW);
    else if (topic_msg == "home/officeFan/off")
      digitalWrite(officeFan, HIGH);

    //home/livingRoomFan/on
    else if (topic_msg == "home/livingRoomFan/on")
      digitalWrite(livingRoomFan, LOW);
    else if (topic_msg == "home/livingRoomFan/off")
      digitalWrite(livingRoomFan, HIGH);
    //--------------------------------------------------------------------------
    else if (topic_msg == "home/door/open")
      myservo.write(0);
    else if (topic_msg == "home/door/close")
      myservo.write(90);
  }
  if (millis() - previous > 5000)
  {
    String dataString = "T:" + String(temperature) + ",G:" + String(gas_read);
    Serial.print(dataString);
    previous = millis();
  }//gas.print( gas_read);

  if (gas_read > gas_threshold)
    digitalWrite(buzzer, HIGH);
  else
    digitalWrite(buzzer, LOW);

}
