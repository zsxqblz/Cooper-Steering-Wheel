#include <SPI.h>
#include <mcp2515.h>

#define RPM_ID 0x8CFFF048
#define SHIFT_L 2
#define SHIFT_R 3
#define DSR 4
#define VALVE_TIME 10000
#define VALVE_CONT_TIME 30000
#define COMM_PERIOD 100

#define GEAR_POT A5
#define POT_N1 146
#define POT_N2 292
#define POT_1 438
#define POT_2 584
#define POT_3 730
#define POT_4 876

struct can_frame canMsg;
MCP2515 mcp2515(10);
unsigned short shiftlStat = 0;
unsigned short shiftrStat = 0;
unsigned short dsrStat = 0;
unsigned short shiftlStatOld = 0;
unsigned short shiftrStatOld = 0;
unsigned short dsrStatOld = 0;
unsigned long shiftlTime = 0;
unsigned long shiftrTime = 0;
unsigned long dsrTime = 0;
unsigned long nextTime = 0;

char strbuffer[20];
unsigned short i = 0;

void setup() {
  pinMode(SHIFT_L, OUTPUT);
  pinMode(SHIFT_R, OUTPUT);
  pinMode(DSR, OUTPUT);
  pinMode(GEAR_POT, INPUT);
  digitalWrite(SHIFT_L, LOW);
  digitalWrite(SHIFT_R, LOW);
  digitalWrite(DSR, LOW);
  Serial.begin(57600);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();
  
  nextTime = millis() + COMM_PERIOD;
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      //send data
      if(canMsg.can_id == RPM_ID)
      {
        // send rpm
        Serial.print('r');
        Serial.print(canMsg.data[0]);
        Serial.print(canMsg.data[1]);
        // send tps
        Serial.print('t');
        Serial.print(canMsg.data[2]);
        Serial.print(canMsg.data[3]);
        //send gear num
        Serial.print('g');
        Serial.print(getGear());
        Serial.println();
      }
  }

  // send rpm
        Serial.print('r');
        Serial.print(0x20);
        Serial.print(0x00);
        // send tps
        Serial.print('t');
        Serial.print(0x01);
        Serial.print(0x01);
        //send gear num
        Serial.print('g');
        Serial.print(1);
        Serial.println();

  //read buttons
  while(Serial.available())
    {
      strbuffer[i++] = Serial.read();
      if(strbuffer[i-1] == '\n' && strbuffer[i-5] == 'b')
      {
        shiftlStat = strbuffer[i-4]=='1'?1:0;
        shiftrStat = strbuffer[i-3]=='1'?1:0;
        shiftrStat = strbuffer[i-2]=='1'?1:0;
        i = 0;
      }
    }

    valveUpdate(SHIFT_L, shiftlStat, shiftlStatOld, shiftlTime);
    valveUpdate(SHIFT_R, shiftrStat, shiftrStatOld, shiftrTime);
    valveUpdate(DSR, dsrStat, dsrStatOld, dsrTime);


}

unsigned short getGear() {
  int potval = analogRead(GEAR_POT);
  if(potval < POT_N1)
    return 1;
  else if(potval < POT_N2)
    return 2;
  else if(potval < POT_1)
    return 3;
  else if(potval < POT_2)
    return 4;
  else if(potval < POT_3)
    return 5;
  else if(potval < POT_4)
    return 6;
  else
    return 7;
}

void valveUpdate(int pin, unsigned short stat, unsigned short statOld, unsigned long timeOld) {
  //activate the value
  if(stat == 1 && statOld == 0)
  {
    statOld == 1;
    digitalWrite(pin, HIGH);
    timeOld = millis();
  }
  else
  {
    //valve holds for VALVE_TIME
    if(millis() - timeOld > VALVE_TIME)
    {
      digitalWrite(pin, LOW);
      //not kept activated, resume oldstat to 0
      if(stat == 0)
        statOld = 0;
    }

    //kept activated, trigger once again per VALVE_CONT_TIME
    if(stat == 1 && millis() - timeOld > VALVE_CONT_TIME)
    {
      statOld == 1;
      digitalWrite(pin, HIGH);
      timeOld = millis();
    }
  }
}

