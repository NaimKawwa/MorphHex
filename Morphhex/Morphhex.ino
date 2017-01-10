#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>
 
const long CODE_0          = 0xFF6897;
const long CODE_1          = 0xFF30CF;
const long CODE_2          = 0xFF18E7;
const long CODE_3          = 0xFF7A85;
const long CODE_4          = 0xFF10EF;
const long CODE_5          = 0xFF38C7;
const long CODE_6          = 0xFF5AA5;
const long CODE_7          = 0xFF42BD;
const long CODE_8          = 0xFF4AB5;
const long CODE_9          = 0xFF52AD;
const long CODE_EQ         = 0xFF906F;
const long CODE_VOL_UP     = 0xFFA857;
const long CODE_VOL_DOWN   = 0xFFE01F;
const long CODE_PLAY_PAUSE = 0xFFC23D;
const long CODE_NEXT       = 0xFF02FD;
const long CODE_PREV       = 0xFF22DD;
const long CODE_CH         = 0xFF629D;
const long CODE_CH_PLUS    = 0xFFE21D;
const long CODE_CH_MINUS   = 0xFFA25D;
void _state_readytomove();
int RECV_PIN = 50;
IRrecv irrecv(RECV_PIN);
decode_results results;

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

// Flag to determine if initial functions have been run
int started = 0;

// Definitions for determining total number of servos.
#define NUM_SERVO 32

// Servo configuration array
ServoDef servoDefs[32];

void setup_servos() {
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
  servoDefs[6].servo_dir = DIR_REVERSE;
   
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
  servoDefs[8].servo_dir = DIR_REVERSE;
  
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
  servoDefs[11].servo_dir = DIR_REVERSE;
  
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
  servoDefs[15].servo_dir = DIR_REVERSE;
  
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
  servoDefs[31].servo_dir = DIR_REVERSE;
 
  driver1.begin();
  
  driver1.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  
  driver2.begin();
  
  driver2.setPWMFreq(50);  // Analog servos run at ~60 Hz updates

  for(servonum = 0; servonum < NUM_SERVO; servonum++){
    ServoDef* servoDef = &(servoDefs[servonum]);
    uint8_t lservonum = (servonum%16); 
    Adafruit_PWMServoDriver driver = getDriver(servonum);

    if(servonum != 15 && servonum != 31) {
      driver.setPWM(lservonum, 0, servoDef->init_pulse-20);
      
      delay(50);
      
      driver.setPWM(lservonum, 0, servoDef->init_pulse);
  
      delay(50);

      driver.setPWM(lservonum, 0, servoDef->init_pulse+20);
  
      delay(50);
    }
    
    driver.setPWM(lservonum, 0, servoDef->init_pulse);
    
  }
}

void setup_IR() {
  Serial.println("Setting up IR...");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  Serial.println("IR setup complete.");
}

void setup() {
  Serial.begin(9600);  
  
  setup_IR();
  setup_servos();
  
  Serial.println("Setup Complete");

  standing();
  delay(500);
  _state_readytomove ();
  delay(500);
    
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

//  Serial.print("servonum: "); 
//  Serial.println(servonum);
//  Serial.print("angle: "); 
//  Serial.println(angle);
//  Serial.println("");
  
  driver.setPWM(lservonum,0,pulselen);
}

void standing() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 45);


  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9,45);

  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 45);

  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 45);

  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 45);

  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}

void evenLegstanding_liftedfoot() {
  setServoAngle(2, 90);
  setServoAngle(3, 90);
  setServoAngle(4, 45);

  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 45);

  setServoAngle(12, 90);
  setServoAngle(13, 90);
  setServoAngle(14, 45);

  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 45);

  setServoAngle(23, 90);
  setServoAngle(24, 90);
  setServoAngle(25, 45);

  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}

void evenLegstanding_liftedleg() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 45);

  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 45);

  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 45);

  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 45);

  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 45);

  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}

void evenLegstanding_rotating() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 45);

  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 45);

  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}

void evenLegstanding_airfoot() {
  setServoAngle(2, 45);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 45);

  setServoAngle(12, 45);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 45);

  setServoAngle(23, 45);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}


void evenLegCenteredstanding_landingleg() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 45);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20,45);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 45);
}

void oddLegstanding_liftedfoot() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 90);
  setServoAngle(9, 45);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 90);
  setServoAngle(20, 45);

  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 90);
  setServoAngle(30, 45);
}

void oddLegstanding_liftedleg() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 45);

  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 45);

  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 45);
}

void oddLegstanding_rotating() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 23);
}

void oddLegstanding_airfoot() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void oddLegCenteredstanding_landingleg() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

//forward movement code

void EvenMovingforward_0() {
  setServoAngle(2, 90);
  setServoAngle(3, 90);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 90);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 90);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void EvenMovingforward_1() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void EvenMovingforward_2() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 40);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 40);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 5);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void EvenMovingforward_3() {
  setServoAngle(2, 45);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 45);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 45);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void EvenMovingforward_4() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void oddMovingforward_0() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 90);
  setServoAngle(8, 90);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 90);
  setServoAngle(19, 90);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 90);
  setServoAngle(29, 90);
  setServoAngle(30, 23);
}

void oddMovingforward_1() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 23);
}

void oddMovingforward_2() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 40);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 40);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 5);
}

void oddMovingforward_3() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 45);
  setServoAngle(8, 0);
  setServoAngle(9, 40);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 45);
  setServoAngle(19, 0);
  setServoAngle(20, 40);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 45);
  setServoAngle(29, 0);
  setServoAngle(30, 5);
}

void oddMovingforward_4() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 40);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 40);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 40);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 40);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 5);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 5);
}

void push_forward0() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 5);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 5);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 40);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward1() {
  setServoAngle(2, 90);
  setServoAngle(3, 90);
  setServoAngle(4, 5);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 90);
  setServoAngle(13, 90);
  setServoAngle(14, 5);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 90);
  setServoAngle(24, 90);
  setServoAngle(25, 40);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward2() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 5);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 5);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 40);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward3() {
  setServoAngle(2, 45);
  setServoAngle(3, 90);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 45);
  setServoAngle(13, 90);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 45);
  setServoAngle(24, 90);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward4() {
  setServoAngle(2, 45);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 45);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 45);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward5() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 5);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 0);
  setServoAngle(20, 5);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 40);
}

void push_forward6() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 90);
  setServoAngle(9, 5);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19, 90);
  setServoAngle(20, 5);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 90);
  setServoAngle(30, 40);
}


void push_forward7() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 5);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 5);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 40);
}


void push_forward8() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 90);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19, 90);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 90);
  setServoAngle(30, 23);
}


void push_forward9() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 45);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 45);
  setServoAngle(19,  0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 45);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void push_forward10() {
  setServoAngle(2, 90);
  setServoAngle(3, 0);
  setServoAngle(4, 23);
  
  setServoAngle(7, 90);
  setServoAngle(8, 0);
  setServoAngle(9, 23);
  
  setServoAngle(12, 90);
  setServoAngle(13, 0);
  setServoAngle(14, 23);
  
  setServoAngle(18, 90);
  setServoAngle(19,  0);
  setServoAngle(20, 23);
  
  setServoAngle(23, 90);
  setServoAngle(24, 0);
  setServoAngle(25, 23);
  
  setServoAngle(28, 90);
  setServoAngle(29, 0);
  setServoAngle(30, 23);
}

void ArmsAndLeg_dance0() {
  setServoAngle(0, 90);
  setServoAngle(1, 90);
  setServoAngle(4, 23);
  
  setServoAngle(5, 90);
  setServoAngle(6, 90);
  setServoAngle(9, 23);
  
  setServoAngle(10, 90);
  setServoAngle(11, 90);
  setServoAngle(14, 23);
  
  setServoAngle(16, 90);
  setServoAngle(17, 90);
  setServoAngle(20, 23);
  
  setServoAngle(21, 90);
  setServoAngle(22, 90);
  setServoAngle(25, 23);
  
  setServoAngle(26, 90);
  setServoAngle(27, 90);
  setServoAngle(30, 23);
}


void ArmsAndLeg_dance1() {
  setServoAngle(0, 90);
  setServoAngle(1,  0);
  setServoAngle(4, 23);
  
  setServoAngle(5, 90);
  setServoAngle(6,  0);
  setServoAngle(9, 23);
  
  setServoAngle(10, 90);
  setServoAngle(11,  0);
  setServoAngle(14, 23);
  
  setServoAngle(16, 90);
  setServoAngle(17,  0);
  setServoAngle(20, 23);
  
  setServoAngle(21, 90);
  setServoAngle(22,  0);
  setServoAngle(25, 23);
  
  setServoAngle(26, 90);
  setServoAngle(27,  0);
  setServoAngle(30, 23);
}

void ArmsAndLeg_dance2() {
  setServoAngle(0, 90);
  setServoAngle(1, 90);
  setServoAngle(4, 23);
  
  setServoAngle(5, 90);
  setServoAngle(6, 90);
  setServoAngle(9, 23);
  
  setServoAngle(10, 90);
  setServoAngle(11, 90);
  setServoAngle(14, 23);
  
  setServoAngle(16, 90);
  setServoAngle(17, 90);
  setServoAngle(20, 23);
  
  setServoAngle(21, 90);
  setServoAngle(22, 90);
  setServoAngle(25, 23);
  
  setServoAngle(26, 90);
  setServoAngle(27, 90);
  setServoAngle(30, 23);
}

void evenleglift () {
    setServoAngle (2, 0);
    setServoAngle (12,0);
    setServoAngle (23,0);
  
  }

  void evenhorizontalservos () {
    setServoAngle (4,  40);
    setServoAngle (14, 40);
    setServoAngle (25, 40);
  
  }

  void evenlegland () {
    setServoAngle (2,  90);
    setServoAngle (12, 90);
    setServoAngle (23, 90);
  
  }
   void evenhorizontaldrag () {
    setServoAngle (4,  10);
    setServoAngle (14, 10);
    setServoAngle (25, 10);
  }

     void oddleglift () {
    setServoAngle (7,  0);
    setServoAngle (18, 0);
    setServoAngle (28, 0);
  }

     void oddhorizontalservos () {
    setServoAngle (9,  40);
    setServoAngle (20, 40);
    setServoAngle (30, 40);
  }
     void oddlegland () {
     setServoAngle (7,  90);
     setServoAngle (18, 90);
     setServoAngle (28, 90);
  }
     void oddhorizontaldrag () {
        setServoAngle (9,  10);
        setServoAngle (20, 10);
        setServoAngle (30, 10);
  }
  void evenrecenter () {
        setServoAngle (2,  0);
        setServoAngle (12, 0);
        setServoAngle (23, 0);
  }
  void evenrecenter_1 () {
       setServoAngle (4,  23);
       setServoAngle (14, 23);
       setServoAngle (25, 23);
  }
  void evenrecenter_2 () {
        setServoAngle (2,  90);
        setServoAngle (12, 90);
        setServoAngle (23, 90);
        }

  void oddrecenter() {
      setServoAngle (7,  0);
      setServoAngle (18, 0);
      setServoAngle (28, 0);
        }
          void oddrecenter_1() {
          setServoAngle (9,  23);
          setServoAngle (20, 23);
          setServoAngle (30, 23);
        }

  void oddrecenter_2 () {
      setServoAngle (7,  90);
      setServoAngle (18, 90);
      setServoAngle (28, 90);
        }


        
          void leg_onepush0 () {
         setServoAngle( 1,  90);
         setServoAngle( 2,   90 );
    
    }


void leg_onepush()

{
  setServoAngle( 1,   45);
  setServoAngle( 2,   45 );
  
  }
  void leg_onepush1 () {
      setServoAngle( 1,   90);
  setServoAngle( 2,   90 );
    
    }
  void leg_twopush0() {
      setServoAngle( 6,    90);
      setServoAngle( 7,   90 );
    

  }
  void leg_twopush() {
      setServoAngle( 6,   45);
      setServoAngle( 7,   45 );
    
    }

 
  void leg_twopush1() {
      setServoAngle( 6,   90);
      setServoAngle( 7,   90 );
    
    }

  
  void leg_threepush0() {
      setServoAngle( 11,   90);
      setServoAngle( 12,   90);
    }
  
  void leg_threepush() {
      setServoAngle( 11,   45);
      setServoAngle( 12,   45 );
    
    }

  
  void leg_threepush1() {
      setServoAngle( 11,   90);
      setServoAngle( 12,  90);
    
    }
  
  void leg_fourpush0() {
      setServoAngle( 17,   90);
      setServoAngle( 18,   90);
    
    }

  
  void leg_fourpush() {
      setServoAngle( 17,   45);
      setServoAngle( 18,   45 );
    
    }

  
  void leg_fourpush1() {
      setServoAngle( 17,   90);
      setServoAngle( 18,   90 );
    
    }

  
  void leg_fivepush0() {
      setServoAngle( 22,   90);
      setServoAngle( 23,   90 );
    
    }
          void leg_fivepush() {
      setServoAngle( 22,   45);
      setServoAngle( 23,   45 );
    
    }

            void leg_fivepush1() {
      setServoAngle( 22,   90);
      setServoAngle( 23,   90 );
    
    }
  
     void leg_sixpush0() {
      setServoAngle( 27,   90);
      setServoAngle( 28,   90);
    
    }
  
  void leg_sixpush() {
      setServoAngle( 27,   45);
      setServoAngle( 28,   45 );
    
    }
  
             void leg_sixpush1() {
      setServoAngle( 27,   90);
      setServoAngle( 28,   90 );
    
    }

    void servo_test () 
    {
    setServoAngle(2,90);
 
    }
      void servo_test1 () 
    {
    setServoAngle(2,45);
 
    }
      void servo_test2 () 
    {
   
  setServoAngle(2, 90) ;
    }

  void servo_testing () {
servo_test ();
servo_test1 ();
servo_test2 ();

    
    }
    void roll () {
   
      leg_onepush0 ();
      delay(150);
      leg_onepush ();
      delay(150);
     leg_onepush1 ();
 delay (1000);
      leg_twopush0 ();
      delay(150);
      leg_twopush ();
      delay(150);
      leg_twopush1 ();
     
  delay (1000);
      leg_threepush0 ();
      delay(150);
      leg_threepush ();
      delay(150);
     leg_threepush1 ();
  delay (1000);
      leg_fourpush0();
      delay(150);
      leg_fourpush();
      delay(150);
    leg_fourpush1();
 delay (1000);

      leg_fivepush0();
      delay(150);
      leg_fivepush ();
      delay(150);
    leg_fivepush1();
 delay (1000);
      leg_sixpush();
      delay(150);
      leg_sixpush ();
      delay(150);
      leg_sixpush1 ();
 delay (1000);
   
     
    }
  
void rotate () {
  evenleglift();
  delay (500);
  evenhorizontalservos();
    delay (500);
  evenlegland();
    delay (500);
  evenhorizontaldrag();
    delay (500);
  oddleglift();
    delay (500);
  oddhorizontalservos();
    delay (500);
  oddlegland();
    delay (500);
  oddhorizontaldrag();
    delay (500);
  evenrecenter();
    delay (500);
  evenrecenter_1();
    delay (500);
  evenrecenter_2();
    delay (500);
  oddrecenter();  
  delay (500);
  oddrecenter_1();
    delay (500);
  oddrecenter_2();
    delay (500);
 
  }
  

void Upper_Body_dance() {
    int j = 0;
  for (j = 0; j <5; j++){
   {
 Serial.println(")Dance...");
    ArmsAndLeg_dance0();
    delay(500);

    Serial.println(")Dance...");
    ArmsAndLeg_dance1();
    delay(500);

    Serial.println(")Dance...");
    ArmsAndLeg_dance2();
    delay(500);
   }
    
  }
}

void Forward_Movement() {
       Serial.println("Ef1..");
    EvenMovingforward_0();
   
    delay(100);
     Serial.println("Ef2...");
    EvenMovingforward_1();
    delay(100);
    Serial.println("Ef3...");
    EvenMovingforward_2();
    delay(100);
    Serial.println("Ef4...");
    EvenMovingforward_3();
    delay(100);
    Serial.println("Ef5...");
    EvenMovingforward_4();
    delay(100);


   Serial.println("Of1..");
    oddMovingforward_0();
  
    delay(100);
     Serial.println("Of2...");
    oddMovingforward_1();
    delay(100);
    Serial.println("Of3...");
    oddMovingforward_2();
    delay(100);
    Serial.println(")f4...");
    oddMovingforward_3();
    delay(100);
    Serial.println("Of5...");
    oddMovingforward_4();
    delay(100);

    Serial.println("Of6...");
    push_forward0();
    delay(100);


     Serial.println("Of7...");
    push_forward1();
    delay(100);
    Serial.println("Of8...");
    push_forward2();
    delay(100);
    Serial.println(")f9...");
    push_forward3();
    delay(100);
    Serial.println("Of10...");
    push_forward4();
    delay(100);

    Serial.println("Of11...");
    push_forward5();
    delay(100);

    Serial.println("Of12..");
    push_forward6();
   
    delay(100);
     Serial.println("Of13...");
    push_forward7();
    delay(100);
    Serial.println("Of14...");
    push_forward8();
    delay(100);
    Serial.println(")f15...");
    push_forward9();
    delay(100);

     Serial.println(")f16...");
    push_forward10();
    delay(100);

 
  }

void _state_readytomove() {
  //Even leggs centered
    Serial.println("evenLegstanding_liftedleg...");
    evenLegstanding_liftedfoot();
    
    delay(100);
    Serial.println("evenLegstanding_liftedleg...");
    evenLegstanding_liftedleg();
    delay(100);
    Serial.println("evenLegstanding_rotating...");
    evenLegstanding_rotating();
    delay(100);
    Serial.println("evenLegstanding_airfoot...");
    evenLegstanding_airfoot();
    delay(100);
    Serial.println("evenLegCenteredstanding_landingleg...");
    evenLegCenteredstanding_landingleg();
    delay(100);

    //odd leggs centered
     Serial.println("oddLegstanding_liftedleg...");
    oddLegstanding_liftedfoot();
    started = 1;
    delay(100);
     Serial.println("oddLegstanding_liftedleg...");
    oddLegstanding_liftedleg();
    delay(100);
    Serial.println("oddLegstanding_erotating...");
    oddLegstanding_rotating();
    delay(100);
    Serial.println("oddLegstanding_airfoot...");
    oddLegstanding_airfoot();
    delay(100);
    Serial.println("oddLegCenteredstanding_landingleg...");
    oddLegCenteredstanding_landingleg();
    delay(100);
}

void close_sphere() {
  setServoAngle(15,0);
}

void open_sphere() {
  setServoAngle(15,70);
}

void loop() {

  
   if (irrecv.decode(&results))
   {
     //Serial.println(results.value, HEX);
     //Serial.println(CODE_0, HEX);
    
     if(results.value == CODE_2) {
       Serial.println("Code 2 received. Moving forward...");
       _state_readytomove();
       Forward_Movement();
       Serial.println("Done.");
     } else if(results.value == CODE_0) {
       Serial.println("Code 0 received. Dancing...");
       Upper_Body_dance();
       Serial.println("Done.");
     } else if(results.value == CODE_1) {
       Serial.println("Code 1 received. Standing...");
       standing();
       Serial.println("Done.");
     } else if(results.value == CODE_NEXT) {
       Serial.println("Code NEXT received. Closing Sphere...");
       close_sphere();
       Serial.println("Done.");
     } else if(results.value == CODE_PREV) {
       Serial.println("Code PREV received. Opening Sphere...");
       open_sphere();
       Serial.println("Done.");
     } else if (results.value == CODE_EQ) {
      Serial.println("Code rotate received. rotating...");
      _state_readytomove();
       rotate();
       Serial.println("Done.");
      
      }else if (results.value == CODE_9) {
      Serial.println("Code roll received. rolling...");
      
      roll();
       
       Serial.println("Done.");
      
      } 
     irrecv.resume(); // Receive the next value
   }
   
}

 
//void loop() {
//  if(started == 0) {
//    Serial.println("Standing...");
//    standing();
//    delay(3000);
//    started = 1;
//
//    _readytomove();
//    
//    // upper body dance
//
//    Upper_Body_dance();
//
//    //Forward movement
//
//    Forward_Movement();
//  }
//}
