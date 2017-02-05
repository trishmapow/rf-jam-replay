#include "EEPROM.h"
#include "cc1101.h"

CC1101 cc1101;

#define LEDOUTPUT 7

byte counter;
byte b;
//byte syncWord = 1;

byte syncWord[] = {0x55, 0x55};


void blinker() {
  digitalWrite(LEDOUTPUT, HIGH);
  delay(100);
  digitalWrite(LEDOUTPUT, LOW);
  delay(100);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting CC1101...");


  pinMode(LEDOUTPUT, OUTPUT);
  digitalWrite(LEDOUTPUT, LOW);

  // blink once to signal the setup
  blinker();

  // reset the counter
  counter = 0;
  Serial.println("Initialize and set registers.");


  cc1101.init();

  Serial.println("Setting PA_TABLE.");
  config2();

  cc1101.setSyncWord(syncWord, false);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck();

  //I ADDED THIS
  cc1101.setChannel(0x05);

  cc1101.setTxPowerAmp(PA_LongDistance);

  delay(1000);

  Serial.print("CC1101_PARTNUM ");
  Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_VERSION ");
  Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  Serial.println("device initialized");
}


void send_data() {

  CCPACKET data;
  byte blinkCount = counter++;

  /*
    data.length = 8;
    data.data[0] = B00001110;
    data.data[1] = B01100011;
    data.data[2] = B10011100;
    data.data[3] = B11000111;
    data.data[4] = B00110001;
    data.data[5] = B10001110;
    data.data[6] = B01110011;
    data.data[7] = B00011000;
  */


  data.length = 13;
  data.data[0] = 0b10001110;
  data.data[1] = 0b10001110;
  data.data[2] = 0b10001110;
  data.data[3] = 0b10001110;
  data.data[4] = 0b10001110;
  data.data[5] = 0b10001110;
  data.data[6] = 0b10001110;
  data.data[7] = 0b10001110;
  data.data[8] = 0b11101110;
  data.data[9] = 0b10001000;
  data.data[10] = 0b10001000;
  data.data[11] = 0b10001000;
  data.data[12] = 0b10000000;

  if (cc1101.sendData(data)) {
    Serial.print(blinkCount, HEX);
    Serial.println(" sent ok :)");
    //blinker();
  } else {
    Serial.println("sent failed :(");
  }
}

void loop()
{
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();
  send_data();

  delay(2000);
}


void config2()
{
  byte PA_TABLE[] = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0};
  cc1101.writeBurstReg(CC1101_PATABLE, PA_TABLE, 8);
}
