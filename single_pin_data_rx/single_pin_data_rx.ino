
#include <RH_ASK.h>                 //Includes RadioHead Library
RH_ASK rf_driver(2000, 11, 10);              //Sets Pin PA9 as receiver and PA10 as transmitterand 2000 as Speed

String str_receive;                 //Strings to Store Value

RH_ASK rf;                          //rf as object for RG_ASK

int i = 0;
/*
int buzz_on = 200;
int buzz_off = 50;
int buzz_pin = 12;
//indi_delay = 500;
*/
void setup()

{

  rf.init();                     //Initialize rf Object
  Serial.begin(9600);

}

void loop()

{

  uint8_t buf[26];

  uint8_t buflen = sizeof(buf);

  if (rf.recv(buf, &buflen))

  {
    str_receive = String((char*)buf);                          // Receive String from the Transmitter
    i = 0;
  }
  else
    i++;

  if (i > 4) {
    i = 4;
    str_receive = "no value";
  }
  Serial.println(str_receive);
  delay(100);


/*
  switch (str_receive) {

    case ("car_remote_controller_0010") {
        digitalWrite(10, HIGH);
        delay(2);
        digitalWrite(10, LOW);
        break;
      }

    case ("car_remote_controller_0011") {
        digitalWrite(11, HIGH);
        delay(2);
        digitalWrite(11, LOW);

        break;
      }

    case ("car_remote_controller_1001") {

      }
      digitalWrite(buzz_pin, HIGH);
      delay(buzz_on);
      digitalWrite(buzz_pin, LOW);
      delay(buzz_off);
      digitalWrite(buzz_pin, HIGH);
      delay(buzz_on);
      digitalWrite(buzz_pin, LOW);

      break;
  }

case ("car_remote_controller_1010") {

    digitalWrite(indicator, HIGH);
    delay(indi_delay);
    digitalWrite(indicator, LOW);
    delay(indi_delay);
    break;
  }
  */
}
