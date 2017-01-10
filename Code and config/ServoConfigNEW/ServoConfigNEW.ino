#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//ignore these
#define SERVOMIN  300 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  350 // this is the 'maximum' pulse length count (out of 4096)
#define SERVOMID  325

//constants to denote direction
#define DIR_FORWARD 1
#define DIR_REVERSE 2

// Initializes objects for the two servo drivers.
Adafruit_PWMServoDriver driver1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver driver2 = Adafruit_PWMServoDriver(0x41);

//Structure for storing servo configuration.
typedef struct servo_def {
  double  init_pulse;
  double  min_pulse;
  double  max_pulse;
  int     min_angle;
  int     max_angle;
  int     servo_dir;
} ServoDef;

// our servo # counter
uint8_t servonum = 0;

// Definitions for determining which servo to start with and total number of servos.
#define START_SERVO 0
#define NUM_SERVO 32

// Servo configuration array
ServoDef servoDefs[32];

void setup() {
  Serial.begin(9600);
  Serial.println("16 Channel");
  Serial.println("Servo Test");  
  
  //Servo Configuration

  //pwm1
  servoDefs[0].init_pulse = 270;
  servoDefs[0].min_pulse = 90;
  servoDefs[0].max_pulse = 450;
  servoDefs[0].min_angle = 0;
  servoDefs[0].max_angle = 180;
  servoDefs[0].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[1].init_pulse = 440;
  servoDefs[1].min_pulse = 360;
  servoDefs[1].max_pulse = 520;
  servoDefs[1].min_angle = 0;
  servoDefs[1].max_angle = 90;
  servoDefs[1].servo_dir = DIR_REVERSE;
   
  //pwm1
  servoDefs[2].init_pulse = 205;
  servoDefs[2].min_pulse = 130;
  servoDefs[2].max_pulse = 280;
  servoDefs[2].min_angle = 0;
  servoDefs[2].max_angle = 90;
  servoDefs[2].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[3].init_pulse = 270;
  servoDefs[3].min_pulse = 90;
  servoDefs[3].max_pulse = 450;
  servoDefs[3].min_angle = 0;
  servoDefs[3].max_angle = 180;
  servoDefs[3].servo_dir = DIR_REVERSE;
  
  //pwm1
  servoDefs[4].init_pulse = 405;
  servoDefs[4].min_pulse = 350;
  servoDefs[4].max_pulse = 460;
  servoDefs[4].min_angle = 0;
  servoDefs[4].max_angle = 45;
  servoDefs[4].servo_dir = DIR_FORWARD;

  //pwm1
  servoDefs[5].init_pulse = 285;
  servoDefs[5].min_pulse = 120;
  servoDefs[5].max_pulse = 450;
  servoDefs[5].min_angle = 0;
  servoDefs[5].max_angle = 180;
  servoDefs[5].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[6].init_pulse = 475;
  servoDefs[6].min_pulse = 390;
  servoDefs[6].max_pulse = 560;
  servoDefs[6].min_angle = 0;
  servoDefs[6].max_angle = 90;
  servoDefs[6].servo_dir = DIR_FORWARD;
   
  //pwm1
  servoDefs[7].init_pulse = 250;
  servoDefs[7].min_pulse = 180;
  servoDefs[7].max_pulse = 320;
  servoDefs[7].min_angle = 0;
  servoDefs[7].max_angle = 90;
  servoDefs[7].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[8].init_pulse = 275;
  servoDefs[8].min_pulse = 150;
  servoDefs[8].max_pulse = 400;
  servoDefs[8].min_angle = 0;
  servoDefs[8].max_angle = 180;
  servoDefs[8].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[9].init_pulse = 390;
  servoDefs[9].min_pulse = 330;
  servoDefs[9].max_pulse = 450;
  servoDefs[9].min_angle = 0;
  servoDefs[9].max_angle = 45;
  servoDefs[9].servo_dir = DIR_FORWARD;

  //pwm1
  servoDefs[10].init_pulse = 280;
  servoDefs[10].min_pulse = 90;
  servoDefs[10].max_pulse = 470;
  servoDefs[10].min_angle = 0;
  servoDefs[10].max_angle = 180;
  servoDefs[10].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[11].init_pulse = 335;
  servoDefs[11].min_pulse = 260;
  servoDefs[11].max_pulse = 410;
  servoDefs[11].min_angle = 0;
  servoDefs[11].max_angle = 90;
  servoDefs[11].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[12].init_pulse = 255;
  servoDefs[12].min_pulse = 180;
  servoDefs[12].max_pulse = 330;
  servoDefs[12].min_angle = 0;
  servoDefs[12].max_angle = 90;
  servoDefs[12].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[13].init_pulse = 270;
  servoDefs[13].min_pulse = 120;
  servoDefs[13].max_pulse = 420;
  servoDefs[13].min_angle = 0;
  servoDefs[13].max_angle = 180;
  servoDefs[13].servo_dir =DIR_REVERSE;

  //pwm1
  servoDefs[14].init_pulse = 235;
  servoDefs[14].min_pulse = 180;
  servoDefs[14].max_pulse = 290;
  servoDefs[14].min_angle = 0;
  servoDefs[14].max_angle = 45;
  servoDefs[14].servo_dir = DIR_FORWARD;
 
  //pwm1
  servoDefs[15].init_pulse = 295;
  servoDefs[15].min_pulse = 220;
  servoDefs[15].max_pulse = 370;
  servoDefs[15].min_angle = 0;
  servoDefs[15].max_angle = 90;
  servoDefs[15].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[16].init_pulse = 260;
  servoDefs[16].min_pulse = 180;
  servoDefs[16].max_pulse = 440;
  servoDefs[16].min_angle = 0;
  servoDefs[16].max_angle = 180;
  servoDefs[16].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[17].init_pulse = 375;
  servoDefs[17].min_pulse = 300;
  servoDefs[17].max_pulse = 450;
  servoDefs[17].min_angle = 0;
  servoDefs[17].max_angle = 90;
  servoDefs[17].servo_dir = DIR_REVERSE;
  
  //pwm1
  servoDefs[18].init_pulse = 150;
  servoDefs[18].min_pulse = 90;
  servoDefs[18].max_pulse = 210;
  servoDefs[18].min_angle = 0;
  servoDefs[18].max_angle = 90;
  servoDefs[18].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[19].init_pulse = 290;
  servoDefs[19].min_pulse = 130;
  servoDefs[19].max_pulse = 450;
  servoDefs[19].min_angle = 0;
  servoDefs[19].max_angle = 180;
  servoDefs[19].servo_dir = DIR_REVERSE;
   
  //pwm1
  servoDefs[20].init_pulse = 295;
  servoDefs[20].min_pulse = 240;
  servoDefs[20].max_pulse = 350;
  servoDefs[20].min_angle = 0;
  servoDefs[20].max_angle = 45;
  servoDefs[20].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[21].init_pulse = 300;
  servoDefs[21].min_pulse = 150;
  servoDefs[21].max_pulse = 450;
  servoDefs[21].min_angle = 0;
  servoDefs[21].max_angle = 180;
  servoDefs[21].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[22].init_pulse = 465;
  servoDefs[22].min_pulse = 380;
  servoDefs[22].max_pulse = 550;
  servoDefs[22].min_angle = 0;
  servoDefs[22].max_angle = 90;
  servoDefs[22].servo_dir = DIR_REVERSE;

  //pwm1
  servoDefs[23].init_pulse = 190;
  servoDefs[23].min_pulse = 130;
  servoDefs[23].max_pulse = 250;
  servoDefs[23].min_angle = 0;
  servoDefs[23].max_angle = 90;
  servoDefs[23].servo_dir = DIR_FORWARD;
  
  
  //pwm1
  servoDefs[24].init_pulse = 260;
  servoDefs[24].min_pulse = 120;
  servoDefs[24].max_pulse = 400;
  servoDefs[24].min_angle = 0;
  servoDefs[24].max_angle = 180;
  servoDefs[24].servo_dir = DIR_REVERSE;
   
  //pwm1
  servoDefs[25].init_pulse = 310;
  servoDefs[25].min_pulse = 270;
  servoDefs[25].max_pulse = 350;
  servoDefs[25].min_angle = 0;
  servoDefs[25].max_angle = 45;
  servoDefs[25].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[26].init_pulse = 305;
  servoDefs[26].min_pulse = 160;
  servoDefs[26].max_pulse = 450;
  servoDefs[26].min_angle = 0;
  servoDefs[26].max_angle = 180;
  servoDefs[26].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[27].init_pulse = 480;
  servoDefs[27].min_pulse = 400;
  servoDefs[27].max_pulse = 560;
  servoDefs[27].min_angle = 0;
  servoDefs[27].max_angle = 90;
  servoDefs[27].servo_dir = DIR_REVERSE;

  //pwm1
  servoDefs[28].init_pulse = 240;
  servoDefs[28].min_pulse = 160;
  servoDefs[28].max_pulse = 320;
  servoDefs[28].min_angle = 0;
  servoDefs[28].max_angle = 90;
  servoDefs[28].servo_dir = DIR_FORWARD;
  
  
  //pwm1
  servoDefs[29].init_pulse = 280;
  servoDefs[29].min_pulse = 100;
  servoDefs[29].max_pulse = 460;
  servoDefs[29].min_angle = 0;
  servoDefs[29].max_angle = 180;
  servoDefs[29].servo_dir = DIR_REVERSE;
   
  //pwm1
  servoDefs[30].init_pulse = 315;
  servoDefs[30].min_pulse = 270;
  servoDefs[30].max_pulse = 360;
  servoDefs[30].min_angle = 0;
  servoDefs[30].max_angle = 45;
  servoDefs[30].servo_dir = DIR_FORWARD;
  
  //pwm1
  servoDefs[31].init_pulse = 295;
  servoDefs[31].min_pulse = 220;
  servoDefs[31].max_pulse = 370;
  servoDefs[31].min_angle = 0;
  servoDefs[31].max_angle = 90;
  servoDefs[31].servo_dir = DIR_FORWARD;
 
  driver1.begin();
  
  driver1.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  
  driver2.begin();
  
  driver2.setPWMFreq(50);  // Analog servos run at ~60 Hz updates

  for(servonum = 0; servonum < NUM_SERVO; servonum++){
    ServoDef* servoDef = &(servoDefs[servonum]);
    uint8_t lservonum = (servonum%16); 
    Adafruit_PWMServoDriver driver = getDriver(servonum);

    delay(50);
    
    driver.setPWM(lservonum, 0, servoDef->init_pulse);
  }
  
  Serial.println("Setup Complete");
  
  delay(500);

  
//  for(servonum = 0; servonum <= NUM_SERVO; servonum++){
//    uint8_t lservonum = (servonum<=14)?servonum:servonum-1;  
//    if(lservonum%5 != 4) {
//      driver1.setPWM(servonum, 0, SERVOMID+1);
//      driver2.setPWM(servonum, 0, SERVOMID+1);
//
//    } else {
//      driver1.setPWM(servonum, 0, 599);
//      driver2.setPWM(servonum, 0, 599);
//    }
//  }
  
  servonum = START_SERVO;
  
  //yield();
}

//Gets the driver based on the servo number.
Adafruit_PWMServoDriver getDriver(uint8_t servonum) {
  return ((servonum/16)==0)?driver1:driver2;
}

void setServoAngle(uint8_t servonum, double angle) {
  ServoDef* servoDef = &(servoDefs[servonum]);
  uint8_t lservonum = (servonum%16); 
  Adafruit_PWMServoDriver driver = getDriver(servonum);

  //Caps angle at servo min/max as defined in servo configuration.
  if(angle < servoDef->min_angle) {
    angle = servoDef->min_angle;
  } else if(angle > servoDef->max_angle) {
    angle = servoDef->max_angle;
  }
  
  int pulselen;
  double pulsediff = (angle*(servoDef->max_pulse - servoDef->min_pulse))/(servoDef->max_angle-servoDef->min_angle);
  if(servoDef->servo_dir == DIR_FORWARD) {
    pulselen = servoDef->min_pulse+pulsediff;
  } else {
    pulselen = servoDef->max_pulse-pulsediff; 
  }
  
  driver.setPWM(lservonum,0,pulselen);
}

void loop() {
  // Drive each servo one at a time
  Serial.print("servonum: "); 
  Serial.println(servonum);

  //setServoAngle(2,15);
  //setServoAngle(4,45);
  //setServoAngle(6,90);

  setServoAngle(servonum, 0);
  Serial.println("angle: 0");
  delay(1000);
  setServoAngle(servonum, 15);
  Serial.println("angle: 15");
  delay(1000);
  setServoAngle(servonum, 30);
  Serial.println("angle: 30");
  delay(1000);
  setServoAngle(servonum, 45);
  Serial.println("angle: 45");
  delay(1000);

  /*ServoDef* servoDef = &(servoDefs[servonum]);
  uint8_t lservonum = (servonum%16); 
  Adafruit_PWMServoDriver driver = getDriver(servonum);

  Serial.print("lservonum: ");
  Serial.println(lservonum, DEC);
  Serial.print("driver: ");
  Serial.println((servonum<=15)?"driver1":"driver2");
  Serial.println();
      
  if(servoDef->servo_dir == DIR_FORWARD) {
    for (uint16_t pulselen = servoDef->min_pulse; pulselen < servoDef->max_pulse; pulselen+=1) {
      //if(lservonum%5 != 4 && lservonum != 15) {
        driver.setPWM(lservonum,0,pulselen);
        Serial.print("pulselen: ");
        Serial.println(pulselen, DEC);
        delay(50);
      //}
    }
  } else {
    for (uint16_t pulselen = servoDef->max_pulse; pulselen > servoDef->min_pulse; pulselen-=1) {
      //if(lservonum != 15) {
          driver.setPWM(lservonum,0,pulselen);
          Serial.print("pulselen: ");
          Serial.println(pulselen, DEC);
          delay(50);
        //}
    }
  }

  delay(500);*/

  servonum ++;
  if (servonum >= NUM_SERVO) servonum = START_SERVO;
}

// Debug Info
//      Serial.print("pulselen: ");
//      Serial.println(pulselen, DEC);
//      Serial.print("servonum: ");
//      Serial.println(servonum, DEC);
//      Serial.print("lservonum: ");
//      Serial.println(lservonum, DEC);
//      Serial.print("driver: ");
//      Serial.println((&driver==&driver1)?"driver1":"driver2");
//      Serial.println();


// Ignore this function
// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  driver1.setPWM(n, 0, pulse);
}

