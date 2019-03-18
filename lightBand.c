#include "lightband.h"

int lightBandInit()
{
	pinMode(G1, OUTPUT);
	pinMode(G2, OUTPUT);
	pinMode(G3, OUTPUT);
	pinMode(G4, OUTPUT);
	pinMode(Y1, OUTPUT);
	pinMode(Y2, OUTPUT);
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);

	digitalWrite(G1, LOW);
        digitalWrite(G2, LOW);
        digitalWrite(G3, LOW);
        digitalWrite(G4, LOW);
        digitalWrite(Y1, LOW);
        digitalWrite(Y2, LOW);
        digitalWrite(R1, LOW);
        digitalWrite(R2, LOW);	
}

int lightBandUpdate(int rpm)
{
  switch (rpmTest(rpm))
  {
   case 0:
   				digitalWrite(G1, LOW);
				digitalWrite(G2, LOW);
				digitalWrite(G3, LOW);
				digitalWrite(G4, LOW);
				digitalWrite(Y1, LOW);
				digitalWrite(Y2, LOW);
				digitalWrite(R1, LOW);
				digitalWrite(R2, LOW);
   case 1:
                                digitalWrite(G1, HIGH);
                                digitalWrite(G2, LOW);
                                digitalWrite(G3, LOW);
                                digitalWrite(G4, LOW);
                                digitalWrite(Y1, LOW);
                                digitalWrite(Y2, LOW);
                                digitalWrite(R1, LOW);
                                digitalWrite(R2, LOW);
    break;
   case 2:
                                digitalWrite(G1, HIGH);
                                digitalWrite(G2, HIGH);
                                digitalWrite(G3, LOW);
                                digitalWrite(G4, LOW);
                                digitalWrite(Y1, LOW);
                                digitalWrite(Y2, LOW);
                                digitalWrite(R1, LOW);
                                digitalWrite(R2, LOW);
    break;
   case 3:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, LOW);
    digitalWrite(Y1, LOW);
    digitalWrite(Y2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    break;
   case 4:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, HIGH);
    digitalWrite(Y1, LOW);
    digitalWrite(Y2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    break;
   case 5:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, HIGH);
    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R1, LOW);
    break;
   case 6:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, HIGH);
    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, HIGH);
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    break;
   case 7:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, HIGH);
    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    break;
   case 8:
    digitalWrite(G1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G3, HIGH);
    digitalWrite(G4, HIGH);
    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    break;
  }
 return 0;
}

int rpmTest(unsigned int input) 
{
  if(input <RPM_1)
  {
   return 0;
  }
  if(input >= RPM_1 && input<=RPM_2)
  {
   return 1;
  }
  else if(input >RPM_2 && input <= RPM_3)
  {
   return 2;
  }
  else if(input >RPM_3 && input <= RPM_4)
  {
   return 3;
  }
  else if(input >RPM_4 && input <= RPM_5)
  {
   return 4;
  }
  else if(input >RPM_5 && input <= RPM_6)
  {
   return 5;
  }
  else if(input >RPM_6 && input <= RPM_7)
  {
   return 6;
  }
  else if(input >RPM_7 && input <= RPM_8)
  {
   return 7;
  }
  else if(input >RPM_8)   
  {
   return 8;
  }
 return -1;
}
