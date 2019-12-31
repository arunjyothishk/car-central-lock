#include <Wire.h>
#include <SPI.h>
#include <RH_ASK.h>

#include <Adafruit_SSD1306.h>
RH_ASK driver(2000, 9, 8);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define left 6
#define right 4
#define up 5
#define down 3

String transmit;
String UNLOCK = "car0_unlock_command_jyothu";

String LOCK = "car0_00lock_command_jyothu";

String ALARM = "car0_0alarm_command_jyothu";
int vibrate_motor = 10;
int i;
void RF_transmit(int);
void setup() {
  digitalWrite(vibrate_motor, HIGH);
  delay(1000);
  digitalWrite(vibrate_motor, LOW);
  delay(1000);
  //rf_driver.init();

  int i;
  // put your setup code here, to run once:
  for (i = 3; i <= 7; i++)
    pinMode(i, INPUT_PULLUP);
  for (i = 0; i < 3; i++)
    pinMode(i, OUTPUT);
  digitalWrite(i, LOW);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

}

void loop() {
  // put your main code hRH_ASK driver(2000,9,8);ere, to run repeatedly:
  for (i = 3; i < 8; i++) {
    if (!digitalRead(i))
      Serial.println(i);
    delay(13);
  }
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner

  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;

    // Message with a good checksum received, dump it.
    driver.printBuffer("Got:", buf, buflen);
  }

  display.println(F("hello"));
  display.display();
}

void RF_transmit(int k)

{
  switch (k) {
    case (3):
      transmit = ALARM;
    case (4):
      transmit = UNLOCK;
    case (5):
      transmit = LOCK;
    default:
      transmit = "no";
  }
  const char *msg = transmit.c_str();

  //    rf_driver.send((uint8_t *)msg, strlen(msg));          //Sends the String

  //  rf_driver.waitPacketSent();

  Serial.println(msg);                                  //Serial Print value for debug

  delay(100);

}
