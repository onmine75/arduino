/*********************************************************************
**  Device: TCS230                                                  **
**  File:   EF_TCS230.pde                                           **
**                    **
**  Created by ElecFreaks Robi.W /24 Augest 2011                    **
**                                                                  **
**  Description:                                                    **
**  This file is a sample code for your reference.It's the demo of  **
**  TCS230-PROGRAMMABLE COLOR LIGHT-TO-FREQUENCY CONVERTER MODULE.  **
**                                                                  **
**  This demo code is free software; you can redistribute it and/or **
**  modify it under the terms of the GNU Lesser General Public      **
**  License as published by the Free Software Foundation; either    **
**  version 2.1 of the License, or (at your option)           **
**  any later version.                **
**                                                                  **
**  Copyright (C) 2011 ElecFreaks Corp.                           **
**                                                                  **
**                                                                  **
**  http://www.elecfreaks.com                                       **
*********************************************************************/

#include "TimerOne.h"

#define OUT  8
#define S2   9
#define S3   10
#define S0   11
#define S1   12
#define OE   13

#define  Filters_R  0
#define  Filters_G  1
#define  Filters_B  2

int Count[3] = {0};
int G_flag = 1;

void setup()
{
  TCS230_init();
  Select_Filters(3);             //default, no fiter
  Timer1.initialize();          // default 1S
  Timer1.attachInterrupt(callback);
  Serial.begin(9600);
}

void TCS230_init()
{
  pinMode(OUT, INPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(OE, OUTPUT);

  digitalWrite(S0, LOW);    // 2% of Output Frequence
  digitalWrite(S1, HIGH);
  digitalWrite(OE, LOW);
}

void Select_Filters(int RGB)
{
  switch (RGB)
  {
    case Filters_R:          //Red
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      Serial.println("-----select Red color");
      break;

    case Filters_G:          //Green
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      Serial.println("-----select Green color");
      break;

    case Filters_B:          //Blue
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      Serial.println("-----select Blue color");
      break;

    default:                  //Clear(no filter)
      digitalWrite(S2, HIGH);
      digitalWrite(S3, LOW);
      Serial.println("-----no filter");
      break;
  }
}

void Measure_Count(int RGB )          //For white balance correction
{
  int tmp = 0;
  while (1)
  {
    if (digitalRead(OUT) == 1)
    {
      if (G_flag == 0)
      {
        Count[RGB] = tmp;
        Serial.print("tmp=");
        Serial.println(tmp);
        break;
      }
      tmp++;
    }
  }
}

void callback()
{
  G_flag = 0;
}

void loop()
{
  Timer1.restart();
  for (int i = 0; i < 3; i++)
  {
    Select_Filters(i);
    Timer1.setPeriod(10000);  //set 10ms
    Measure_Count(i);
    G_flag = 1;
    Serial.println(Count[i]);
  }
  delay(3000);
}
