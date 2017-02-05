#include "EEPROM.h"
#include "cc1101.h"

CC1101 cc1101;

// The LED is wired to the Arduino Output 4 (physical panStamp pin 19)
#define LEDOUTPUT 7

// counter to get increment in each loop
byte counter;
byte b;
//byte syncWord = 199;
byte syncWord[2] = {199, 0};

void blinker() {
  digitalWrite(LEDOUTPUT, HIGH);
  delay(100);
  digitalWrite(LEDOUTPUT, LOW);
  delay(100);
}

void setup()
{
  Serial.begin(38400);
  Serial.println("start");

  // setup the blinker output
  pinMode(LEDOUTPUT, OUTPUT);
  digitalWrite(LEDOUTPUT, LOW);

  // blink once to signal the setup
  blinker();

  // reset the counter
  counter = 0;
  Serial.println("initializing...");
  // initialize the RF Chip
  cc1101.init();

  //cc1101.setSyncWord(&syncWord, false);
  cc1101.setSyncWord(syncWord, false);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck();
  //cc1101.setTxPowerAmp(PA_LowPower);

  delay(1000);

  Serial.print("CC1101_PARTNUM "); //cc1101=0
  Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_VERSION "); //cc1101=4
  Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  Serial.println("device initialized");
  //Serial.println("done");
}

void send_data() {
  CCPACKET data;
  data.length = 10;
  byte blinkCount = counter++;
  data.data[0] = 5;
  data.data[1] = blinkCount; data.data[2] = 0;
  data.data[3] = 1; data.data[4] = 0;
  //cc1101.flushTxFifo ();
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);
  if (cc1101.sendData(data)) {
    Serial.print(blinkCount, HEX);
    Serial.println(" sent ok :)");
    blinker();
  } else {
    Serial.println("sent failed :(");
    blinker();
    blinker();
  }
}

void loop()
{
  send_data();
  delay(4000);
}

