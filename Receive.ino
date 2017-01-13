#include "EEPROM.h"
#include "cc1101.h"

// The connection to the hardware chip CC1101 the RF Chip
CC1101 cc1101;

byte b;
byte i;
byte syncWord = 199;
long counter = 0;
byte chan = 0;

// a flag that a wireless packet has been received
boolean packetAvailable = false;

/* Handle interrupt from CC1101 (INT0) gdo0 on pin2 */
void cc1101signalsInterrupt(void) {
  // set the flag that a package is available
  packetAvailable = true;
}

void setup()
{
  Serial.begin(38400);
  Serial.println("start");
  
  // initialize the RF Chip
  cc1101.init();

  //cc1101.setSyncWord(&syncWord, false);
  cc1101.setCarrierFreq(CFREQ_433);
  cc1101.disableAddressCheck(); //if not specified, will only display "packet received"
  //cc1101.setTxPowerAmp(PA_LowPower);

  Serial.print("CC1101_PARTNUM "); //cc1101=0
  Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_VERSION "); //cc1101=4
  Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  cc1101.setRxState(); //ADDED BY ME

  attachInterrupt(0, cc1101signalsInterrupt, FALLING);

  Serial.println("device initialized");
}

void ReadLQI()
{
  byte lqi = 0;
  byte value = 0;
  lqi = (cc1101.readReg(CC1101_LQI, CC1101_STATUS_REGISTER));
  value = 0x3F - (lqi & 0x3F);
  Serial.print("CC1101_LQI ");
  Serial.println(value);
}

void ReadRSSI()
{
  byte rssi = 0;
  byte value = 0;

  rssi = (cc1101.readReg(CC1101_RSSI, CC1101_STATUS_REGISTER));

  if (rssi >= 128)
  {
    value = 255 - rssi;
    value /= 2;
    value += 74;
  }
  else
  {
    value = rssi / 2;
    value += 74;
  }
  Serial.print("CC1101_RSSI ");
  Serial.println(value);
}

void loop()
{
  if (packetAvailable) {
    Serial.println("packet received");
    // Disable wireless reception interrupt
    detachInterrupt(0);

    ReadRSSI();
    ReadLQI();
    // clear the flag
    packetAvailable = false;

    CCPACKET packet;

    if (cc1101.receiveData(&packet) > 0) { 
      if (!packet.crc_ok) {
        Serial.println("crc not ok");
      }

      if (packet.length > 0) {
        Serial.print("packet: len ");
        Serial.print(packet.length);
        Serial.print(" data: ");
        for (int j = 0; j < packet.length; j++) {
          Serial.print(packet.data[j], HEX);
          Serial.print(" ");
        }
        Serial.println(".");
      }
    }
    // Enable wireless reception interrupt
    attachInterrupt(0, cc1101signalsInterrupt, FALLING);
  }
}
