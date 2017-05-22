#include "EEPROM.h"
#include "cc1101.h"

#define LEDOUTPUT 13

CC1101 cc1101;

void blinker(){
  digitalWrite(LEDOUTPUT, HIGH);
  delay(100);
  digitalWrite(LEDOUTPUT, LOW);
  delay(100);
}

void setup(){
  Serial.begin(9600);
  Serial.println("Started");

  //BLINKER SETUP
  pinMode(LEDOUTPUT, OUTPUT);
  digitalWrite(LEDOUTPUT, LOW);
  blinker();

  cc1101.init();

  //FROM SIMPLICITI SETTINGS
  cc1101.writeReg(CC1101_IOCFG0, 0x06);
  cc1101.writeReg(CC1101_FIFOTHR, 0x47);
  cc1101.writeReg(CC1101_PKTCTRL0, 0x05);
  cc1101.writeReg(CC1101_FSCTRL1, 0x06);
  cc1101.writeReg(CC1101_FREQ2, 0x10);
  cc1101.writeReg(CC1101_FREQ1, 0xB0);
  cc1101.writeReg(CC1101_FREQ0, 0x5A);
  cc1101.writeReg(CC1101_MDMCFG4, 0x87);
  cc1101.writeReg(CC1101_MDMCFG3, 0x50);
  cc1101.writeReg(CC1101_MDMCFG2, 0x03);
  cc1101.writeReg(CC1101_DEVIATN, 0x44);
  cc1101.writeReg(CC1101_MCSM0, 0x18);
  cc1101.writeReg(CC1101_FOCCFG, 0x16);
  cc1101.writeReg(CC1101_WORCTRL, 0xFB);
  cc1101.writeReg(CC1101_FSCAL3, 0xE9);
  cc1101.writeReg(CC1101_FSCAL2, 0x2A);
  cc1101.writeReg(CC1101_FSCAL1, 0x00);
  cc1101.writeReg(CC1101_TEST2, 0x81);
  cc1101.writeReg(CC1101_TEST1, 0x35);
  cc1101.writeReg(CC1101_TEST0, 0x09);

  cc1101.writeReg(CC1101_PATABLE, 0xC0); //SUPPOSED TO BE MAX OUTPUT
  
  cc1101.setTxPowerAmp(PA_LongDistance);
  
  byte PA_TABLE[]= {0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0};
  cc1101.writeBurstReg(CC1101_PATABLE,PA_TABLE,8);

  delay(1000);

  //PRINT DIAGOSTIC STUFF
  Serial.print("CC1101_PARTNUM "); //cc1101=0
  Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_VERSION "); //cc1101=4
  Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  Serial.println("ALL REGISTERS SET");
}

void send_data(){
  CCPACKET data;
  data.length = 57;
  data.data[0] = 0b00000000;

  for (int i = 1; i < 40; i++){
    data.data[i] = data.data[0];
  }

  data.data[40] = 0b11110000;
  data.data[41] = 0b00001010;
  data.data[42] = 0b10101001;
  data.data[43] = 0b10110111;
  data.data[44] = 0b00100110;
  data.data[45] = 0b00011011;
  data.data[46] = 0b00010000;
  data.data[47] = 0b01010000;
  data.data[48] = 0b00000000;
  data.data[49] = 0b00001111;
  data.data[50] = 0b00000000;
  data.data[51] = 0b10101010;
  data.data[52] = 0b10011011;
  data.data[53] = 0b01110010;
  data.data[54] = 0b01100001;
  data.data[55] = 0b10110001;
  data.data[56] = 0b00000101;

  Serial.print("CC1101_MARCSTATE ");
  Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  if (cc1101.sendData(data)) {
    Serial.println(" sent ok :)");
    blinker();
  } else {
    Serial.println("sent failed :(");
    blinker();
    blinker();
  }
}

void loop(){
  send_data();
  delay(2000);
}
