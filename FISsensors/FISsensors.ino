#include "VAGFISWriter.h"
#include "bitmaps.h"
#include <NewPing.h>
//also define these in lib
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define ONE_PIN_ENABLED false
#define ROUNDING_ENABLED false

NewPing sonar[4] = {   // Sensor object array.
  NewPing(6, 7, MAX_DISTANCE), //trigger pin, echo pin, and max distance to ping
  NewPing(8, 9, MAX_DISTANCE),
  NewPing(10, 11, MAX_DISTANCE),
  NewPing(12, 13, MAX_DISTANCE)
};

#define MinRefresh 100


// FIS
#define FIS_CLK 3
#define FIS_DATA 4
#define FIS_ENA 2



#define SIZE_OF_CAR 46
#define START_CAR_ON_DISPLAY_POSITION 22
#define START_REAR_SENSORS 69 //SIZE_OF_CAR + START_CAR_ON_DISPLAY_POSITION +1
#define NUM_OF_LINES 20
#define _DELAY 0

VAGFISWriter fisWriter( FIS_CLK, FIS_DATA, FIS_ENA );
static char fisBuffer[10] = {'B', '5', ' ', 'F', 'A', 'M', 'I', 'L', 'I', 'A'} ;
int myInit = 2;
volatile uint8_t carType = 1; //0=sedan,1=avant
volatile uint8_t sensorsMode = 1; //0=front,1=rear
volatile uint8_t sensor1 = 8;
volatile uint8_t sensor2 = 8;
volatile uint8_t sensor3 = 8;
volatile uint8_t sensor4 = 8;


void write_car() {
  switch (carType) {
    case 0:
      fisWriter.GraphicFromArray(22, START_CAR_ON_DISPLAY_POSITION, 20, 46, sedan, 2);
      break;
    case 1:
      fisWriter.GraphicFromArray(22, START_CAR_ON_DISPLAY_POSITION, 20, 46, avant, 2);
      break;
  }
}

void write_sensors(uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4) {

  if ( s1 > NUM_OF_LINES) s1 = NUM_OF_LINES;
  if ( s2 > NUM_OF_LINES) s2 = NUM_OF_LINES;
  if ( s3 > NUM_OF_LINES) s3 = NUM_OF_LINES;
  if ( s4 > NUM_OF_LINES) s4 = NUM_OF_LINES;

  if (!sensorsMode) {//front
    for (int8_t y = 20; y >= 0 ; y -= 2) {

      if (s1 >= 20 - y) {
        if (sensorsFront[0 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(0, y, 16, 1, line, 1);
          sensorsFront[0 + (y * 4)] = 1;
        }
      } else {
        if (sensorsFront[0 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(0, y, 16, 1, line, 1);
          sensorsFront[0 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s2 >= 20 - y) {
        if (sensorsFront[2 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(16, y, 16, 1, line, 1);
          sensorsFront[2 + (y * 4)] = 1;
        }
      } else {
        if (sensorsFront[2 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(16, y, 16, 1, line, 1);
          sensorsFront[2 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s3 >= 20 - y) {
        if (sensorsFront[3 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(32, y, 16, 1, line, 1);
          sensorsFront[3 + (y * 4)] = 1;
        }
      } else {
        if (sensorsFront[3 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(32, y, 16, 1, line, 1);
          sensorsFront[3 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s4 >= 20 - y) {
        if (sensorsFront[4 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(48, y, 16, 1, line, 1);
          sensorsFront[4 + (y * 4)] = 1;
        }
      } else {
        if (sensorsFront[4 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(48, y, 16, 1, line, 1);
          sensorsFront[4 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
    }
  }



  if (sensorsMode) { //rear

    for (uint8_t y = 0; y <= 20; y += 2) {
      if (s1 >= y) {
        if (sensorsRear[0 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(0, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[0 + (y * 4)] = 1;
        }
      } else {
        if (sensorsRear[0 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(0, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[0 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s2 >= y) {
        if (sensorsRear[2 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(16, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[2 + (y * 4)] = 1;
        }
      } else {
        if (sensorsRear[2 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(16, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[2 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s3 >= y) {
        if (sensorsRear[3 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(32, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[3 + (y * 4)] = 1;
        }
      } else {
        if (sensorsRear[3 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(32, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[3 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
      if (s4 >= y) {
        if (sensorsRear[4 + (y * 4)] != 1) {
          fisWriter.GraphicFromArray(48, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[4 + (y * 4)] = 1;
        }
      } else {
        if (sensorsRear[4 + (y * 4)] != 0) {
          fisWriter.GraphicFromArray(48, y + START_REAR_SENSORS, 16, 1, line, 1);
          sensorsRear[4 + (y * 4)] = 0;
        }
      }
      delay(_DELAY);
    }
  }
}

uint8_t get_distance(uint8_t sensor) {
  delayMicroseconds(50);
  int ping = sonar[sensor].ping_cm(MAX_DISTANCE);
  delayMicroseconds(50);
  ping += sonar[sensor].ping_cm(MAX_DISTANCE);
  delayMicroseconds(50);
  ping += sonar[sensor].ping_cm(MAX_DISTANCE);
  delayMicroseconds(50);
  ping += sonar[sensor].ping_cm(MAX_DISTANCE);
  ping = ping/4;
 // delay(50);
  //Serial.print(sensor);Serial.print(": ");Serial.println(ping,DEC);
  if (ping == 0xFFFF )
     return NUM_OF_LINES;
  if (ping < 21)
    return 0;
  if (ping < 31)
    return 2;
  if (ping < 41)
    return 4;
  if (ping < 51)
    return 6;
  if (ping < 61)
    return 8;
  if (ping < 71)
    return 10;
  if (ping < 91)
    return 12;
  if (ping < 111)
    return 14;
  if (ping < 121)
    return 16;
  if (ping < 141)
    return 18;
  return NUM_OF_LINES;
}

void setup() {
  //  for (uint8_t grg = 0 ; grg < 168; grg++) {
  //    sensorsRear[grg] = 0;
  //    sensorsFront[grg] = 0;
  //  }
  fisWriter.begin();
  fisWriter.initScreen(0x82, 0, 0, 64, 88);
  delay(100);
  fisWriter.initScreen(0x82, 0, 0, 64, 88);
  delay(100);
  Serial.begin(115200);
}


void loop() {

  //write_car();
  //delay(100);
  //sensorsMode = !sensorsMode;
  //write_sensors(NUM_OF_LINES, NUM_OF_LINES, NUM_OF_LINES, NUM_OF_LINES);
  //sensorsMode = !sensorsMode;
  //write_sensors(NUM_OF_LINES, NUM_OF_LINES, NUM_OF_LINES, NUM_OF_LINES);
  uint8_t sensor0,sensor1,sensor2,sensor3 = 0 ;
  while (1) {
    sensor0=get_distance(0);
   Serial.print(sensor0);
   Serial.print(" ");

    sensor1=get_distance(1);
    Serial.print(sensor1);
    Serial.print(" ");

    sensor2=get_distance(2);
    Serial.print(sensor2);
    Serial.print(" ");

    sensor3=get_distance(3);
    Serial.println(sensor3);

    //write_sensors(sensor0,sensor1,sensor2,sensor3);
   // Serial.println(sensor0);
    //delay(100);
    //    delayMicroseconds(50);
    //    Serial.println(sonar[1].ping_cm()/20);
    //    delayMicroseconds(50);
    //    Serial.println(sonar[2].ping_cm()/20);
    //    delayMicroseconds(50);
    //    Serial.println(sonar[3].ping_cm()/20);
    //    delayMicroseconds(50);
  }

}


