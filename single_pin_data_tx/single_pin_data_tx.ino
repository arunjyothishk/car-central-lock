
#include <RH_ASK.h>                             //RadioHead library

RH_ASK rf_driver(2000,9,8);              //Sets Pin PA9 as receiver and PA10 as transmitterand 2000 as Speed






/* transmitt codes://////
 *  car0_0alarm_command_jyothu            111222333444                3
 *  car0_00lock_command_jyothu            777888999000                1
 *  car0_unlock_command_jyothu            555444333222                2
 */
    int vibrate_motor = 10;
String transmit;
String UNLOCK = "car0_unlock_command_jyothu";

String LOCK = "car0_00lock_command_jyothu";

String ALARM = "car0_0alarm_command_jyothu";

void setup()

{

    // Initialize ASK Object


    rf_driver.init();

    Serial.begin(9600);
    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(vibrate_motor,OUTPUT);
}

 

void loop()

{
    if(!digitalRead(3))
    transmit=ALARM;
    else if(!digitalRead(4))
    transmit=UNLOCK;
    else if(!digitalRead(5))
    transmit=LOCK;
    else 
    transmit="no";
    const char *msg = transmit.c_str();

    rf_driver.send((uint8_t *)msg, strlen(msg));          //Sends the String

    rf_driver.waitPacketSent();         

    Serial.println(msg);                                  //Serial Print value for debug

    delay(100);

}

 
