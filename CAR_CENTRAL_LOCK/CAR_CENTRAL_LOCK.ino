/* car central lock system

    designed by Arun jyothish k
*/


/* transmitt codes://////
 *  car0_0alarm_command_jyothu            111222333444                3
 *  car0_00lock_command_jyothu            777888999000                1
 *  car0_unlock_command_jyothu            555444333222                2
 */

#include <RH_ASK.h>                 //Includes RadioHead Library
#include <string.h>
String str_receive1;                 //Strings to Store Value
char str_receive;
RH_ASK rf;                          //rf as object for RG_ASK

int i = 0;

int int_receive=0;
#define   _INDICATOR   5
#define   _ALARM       6
#define   _LOCK        7
#define   _UNLOCK      8
#define   _POS_LO      A0
#define   _DOOR        A1
#define   _POS_UL      A2
#define   _POW_ON      A3
#define   _DATA_REC    11
#define   _SHOCK_SEN   A5
#define   _SHOCK_THR   60

int ce = 12;
void indi_4(int);
int prev = 0;
int stateLO = true;
int stateUL = true;
int stateDR = true;
int ala=true;
int prev_door_state = HIGH;
int lock_dl = 500;
void setup() {
  // put your setup code here, to run once:

  rf.init();                     //Initialize rf Object
  pinMode(_INDICATOR, OUTPUT);
  pinMode(_ALARM, OUTPUT);
  pinMode(_LOCK, OUTPUT);
  pinMode(_UNLOCK, OUTPUT);
  pinMode(_POS_LO, INPUT_PULLUP);
  pinMode(_POS_UL, INPUT_PULLUP);
  pinMode(_DOOR, INPUT_PULLUP);
  pinMode(_DATA_REC, INPUT);
  Serial.begin(9600);
  pinMode (ce, INPUT);
}

void loop() {
  int power_on = digitalRead(_POW_ON);
  uint8_t buf[26];

  uint8_t buflen = sizeof(buf);

  if (rf.recv(buf, &buflen))

  {
    str_receive1 = String((char*)buf);                          // Receive String from the Transmitter
    i = 0;
  }
  else
    i++;

  if (i > 2) {
    i = 2;
    str_receive1 = "no value";
  }
  Serial.println(str_receive1);
  
//  char int_receive = Serial.read();
 //   Serial.println(int_receive);
  //  delay(1000);
  // wireless section above

  //local control section below

  for (int i = 5; i < 9; i++) {
    digitalWrite(i, HIGH);
  }
  // put your main code here, to run repeatedly:
  int shock_value = analogRead(_SHOCK_SEN);
 // Serial.println(shock_value);
  if (shock_value > prev) {
    prev = shock_value;
    Serial.println(shock_value);
  }
  if  ((_SHOCK_THR < shock_value)&& !power_on) {
    digitalWrite(_ALARM, LOW);
    indi_4(8);
    digitalWrite(_ALARM, HIGH);
  }

  int door_state = digitalRead(_DOOR);
  if (! door_state && prev_door_state) {

    indi_4(5);
  }
  prev_door_state = door_state;

  //lock_unlock

  int noteU = digitalRead (_POS_UL);
  ///////////////////////////
  /*
char  str2[26]="car0_unlock_command_jyothu";
  int k=strcmp(str2,str_receive);
  if (k==0)
    noteU = LOW;

    


  *//////////////////////////
  if((str_receive1 == "car0_unlock_command_jyothu")&& !power_on){
  noteU = LOW;
  Serial.println("UNLOCK CODE");
  }
  if (!noteU && stateUL) {
    digitalWrite(_UNLOCK, LOW);
    delay(lock_dl);
    digitalWrite(_UNLOCK, HIGH);
  }
  stateUL = noteU;
  int noteL = digitalRead (_POS_LO);
  ///////////////////////////
  /*
char  str1[26]="car0_00lock_command_jyothu";
 k =strcmp(str1,str_receive);
  if (k ==0){
    
     noteL = LOW;
  }
  
   

  *//////////////////////////
  if ((str_receive1 == "car0_00lock_command_jyothu")&& !power_on){
    noteL = LOW;
  }
  if (!noteL && stateLO) {
    digitalWrite(_LOCK, LOW);
    delay(lock_dl);
    digitalWrite(_LOCK, HIGH);
  }
  stateLO = noteL;
  /*
char  str3[26]="car0_0alarm_command_jyothu";
  k = strcmp(str3,str_receive);
  if (k == 0 ){
        
    */
    if((str_receive1 == "car0_0alarm_command_jyothu")&& !power_on)
    {
for(int y=0;y<3;y++){
    digitalWrite(_ALARM, LOW);
    delay(100);
    digitalWrite(_ALARM, HIGH);
    delay(300);}
  }
}


void indi_4(int loc) {
  for (int i = 0; i < loc; i++) {
    digitalWrite(_INDICATOR, LOW);
    delay(600);
    digitalWrite(_INDICATOR, HIGH);
    delay(600);
  }
}
