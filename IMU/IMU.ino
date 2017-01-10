//Will not receive all packet unless  you increase serial buffer size from 64 to 256
//WORKAROUND is: arduino-1.5.5\hardware\arduino\sam\cores\arduino\RingBuffer.h Change the value of "#define SERIAL_BUFFER_SIZE 64",  to 256 

//GY-951_SERIAL_ONLY_MEGA , uses GY-951 serial out, offers "DATA ON REQUEST"  and "FREE RUN" mode for comparison
//Demo code with useful parsing example. To use this code, other progs should have been used to store mpu with cal figs
//CONNECT MODULE to Serial3 on Mega
//SHOULD be run on a 3.3v board, eg Sainsmart UNO w/5/3.3. Mega New Freaduino MEGA2560 5/3.3, or DUE.
//BUT everything has survived running on 5v without level shift!


// NOTE NOTE NOTE
//Specs are min 20ms update, but in "packet on request" mode without 35ms delay we get scrambled packets!!!. To do with "#f" echo time.
// In "free run" mode, we can get to a 25ms delay without data corruption
//Timings and packet sizes are changed at your peril. Generally from here, trying to speed things up comes to grief.
//Other modes tested, "#osrt" and "#osct," are a FAIL unless serial buffer is increased, and it appears the GY-951 internal processor cannot kep up with the serial out
//Othermodes will give a PACKET FAULT message, although will display the incoming stream correctly
//THIS IS BECAUSE the PARSER is only set to parse the normal X Y X packets, not packets from the #osct command
/*
These following notes re serial commands are extracted entirely from "Razor AHRS Firmware v1.4.1"
Serial commands that the firmware responds to    (P.W REM,these are documented commands, there may be others)
  
  "#o<params>" - Set OUTPUT mode and parameters. The available options are:
  
      // Streaming output
      "#o0" - DISABLE continuous streaming output. Also see #f below.
      "#o1" - ENABLE continuous streaming output.
      
      // Angles output
      "#ob" - Output angles in BINARY format (yaw/pitch/roll as binary float, so one output frame
              is 3x4 = 12 bytes long).
      "#ot" - Output angles in TEXT format (Output frames have form like "#YPR=-142.28,-5.38,33.52",
              followed by carriage return and line feed [\r\n]).
      
      // Sensor calibration
      "#oc" - Go to CALIBRATION output mode.
      "#on" - When in calibration mode, go on to calibrate NEXT sensor.
      
      // Sensor data output
      "#osct" - Output CALIBRATED SENSOR data of all 9 axes in TEXT format.
                One frame consist of three lines - one for each sensor: acc, mag, gyr.
      "#osrt" - Output RAW SENSOR data of all 9 axes in TEXT format.
                One frame consist of three lines - one for each sensor: acc, mag, gyr.
      "#osbt" - Output BOTH raw and calibrated SENSOR data of all 9 axes in TEXT format.
                One frame consist of six lines - like #osrt and #osct combined (first RAW, then CALIBRATED).
                NOTE: This is a lot of number-to-text conversion work for the little 8MHz chip on the Razor boards.
                In fact it's too much and an output frame rate of 50Hz can not be maintained. #osbb.
      "#oscb" - Output CALIBRATED SENSOR data of all 9 axes in BINARY format.
                One frame consist of three 3x3 float values = 36 bytes. Order is: acc x/y/z, mag x/y/z, gyr x/y/z.
      "#osrb" - Output RAW SENSOR data of all 9 axes in BINARY format.
                One frame consist of three 3x3 float values = 36 bytes. Order is: acc x/y/z, mag x/y/z, gyr x/y/z.
      "#osbb" - Output BOTH raw and calibrated SENSOR data of all 9 axes in BINARY format.
                One frame consist of 2x36 = 72 bytes - like #osrb and #oscb combined (first RAW, then CALIBRATED).
      
      // Error message output        
      "#oe0" - Disable ERROR message output.
      "#oe1" - Enable ERROR message output.
    
    
  "#f" - Request one output frame - useful when continuous output is disabled and updates are
         required in larger intervals only. Though #f only requests one reply, replies are still
         bound to the internal 20ms (50Hz) time raster. So worst case delay that #f can add is 19.99ms.
         
         
  "#s<xy>" - Request synch token - useful to find out where the frame boundaries are in a continuous
         binary stream or to see if tracker is present and answering. The tracker will send
         "#SYNCH<xy>\r\n" in response (so it's possible to read using a readLine() function).
         x and y are two mandatory but arbitrary bytes that can be used to find out which request
         the answer belongs to.
          
          
  ("#C" and "#D" - Reserved for communication with optional Bluetooth module.)
  
  Newline characters are not required. So you could send "#ob#o1#s", which
  would set binary output mode, enable continuous streaming output and request
  a synch token all at once.
    
  Byte order of binary output is little-endian: least significant byte comes first.
*/

//Set true for "free run", else will use "data on request" mode
bool FreeRunMode = false;

bool PassStringTest = false;
const int DataSize = 100;
char inData[DataSize]; // Allocate some space for the string
char inChar ; // The character read
byte index = 0; // Index into array; where to store the character
long dT = 40; //wait millis. rem; oficially new read posible every 20ms with the atmega firmware on gy951, but < 35 delay gives corrupted packet
long StartMillis;
long EndMillis;
int  PacketMin = 20; //just for testing when checking for incomplete packets in "packet on request" mode
int  PacketMax = 100; //29;  //normally 29, but use 90 for calibration mode
float numYaw, numPitch, numRoll; //Strings from GY951 are parsed and changed to global numeric values

void setup() 
{
    Serial3.begin(57600); //no choice, that's what the GY951 runs at, ulness there is an undocumented command to change it.
    Serial.begin(57600);
    delay(200);
    Serial3.print( "#oe0"); // Disable ERROR message output.
    delay(20);
    Serial3.print("#ot"); // Request output angles in TEXT format (Output frames normally have form like "#YPR=-142.28,-5.38,33.52",  followed by carriage return and line feed [\r\n]).
    delay(20);
    if(FreeRunMode)
      Serial3.print("#o1"); //turn on continuous output, we will extract data from the stream
         else
          Serial3.print("#o0"); //turn off continuous output, we will request one packet ofdata when needed (#o1 enables continuous)
    delay(20);
    
}


void loop()
{
  delay(500);
 StartMillis = millis();
 if (FreeRunMode)
 {  // we need to capture at least  64 chars on the fly to guarantee we have one complete data string and uncorrupted data
  while ( Serial3.available() && index < 60 ) //data buffer was declared to be 100 chars, so we're safe with 60!
    {               
          inChar = Serial3.read(); // Read a character
          if(inChar == '=') inChar = ','; //change the "=" to a comma,easier parsing later, we only need to  find the  commas as delimiters
          if (inChar == '\n') inChar = ','; //keeps all data in one string, instead of three lines, easier parsing
                 inData[index] = inChar; // Store it           
          index++;        
    }
    
   inData[index] = '\,'; //add final comma for an easy parse
   Serial.println();      
   Serial.println( String(inData)); //reassuring debug  
   Serial.println();      
   parseMessage2(inData); //parses the incoming data stream, converts to float, and displays as a debug
   memset(inData,0,DataSize); //empty array,  DataSize declared prev, saves recalc
   index=0;       //reindex
   
 } //end FreeRunMode
 
 
  else //request one packet mode
 { 

  Serial3.print("#f"); //request one packet
 
  while ( Serial3.available()  ) 
    {               
            inChar = Serial3.read(); // Read a character 
            if(inChar == '=') inChar = ','; //change the "=" to a comma,easier parsing later, we only need to  find the  commas as delimiters
            if (inChar == '\n') inChar = ','; //keeps all data in one string, easier parsing
            inData[index] = inChar; // Store it           
            index++;
    }
    
 //  Serial.println( String(inData)); //reassuring debug  
   PassStringTest=PacketCheck(inData); //moved test outside of bracket during debug
   
  if(PassStringTest == true ) //only print complete packets
   {
       Serial.println(inData); //debug to console via Serial 0
       Serial.println(); //there will be an echo to terminal of the "#f" we sent. This makes sure the data reported  by debug lines is clean of the confusing #f
       parseMessage(inData); //parses the incoming data stream, converts to float, and displays as a debug
    }
    else
    {
      Serial.println("PACKET FAULT");
      Serial.println(inData); //debug to console via Serial 0
    }
   memset(inData,0,DataSize); //empty array,  DataSize declared prev, saves recalc
   index=0;       //reindex
   inChar = ' '; //clear last char recd
   
  
   
   
 } //end data on demand mode
   do
   {
     EndMillis = millis();
   }
   while( EndMillis - StartMillis < dT); //just wait, as native speed of free run reads is 20 millis
   
}


bool PacketCheck(char DataPacket[])
{ 
  //correct packet will be of form "#YPR=-142.28,-5.38,33.52" We get a few "mangled packets" if close to min inter read interval, so only deal with complete ones, do rough check. 
  //Min length, "#YPR,0.00,0.00,0.00," 20 char. Max length "#YPR,-180.00,-180.00,-180.00,"  29 char.
  //we can confirm 2 commas, 3 stops, presence of "#YPR=", or check against 'f'
 int dots = 0;
 int commas = 0;
 int effs = 0;
 int i;
 int len;
 
//reject out of range packet size
len= numberOfCharsInArray(DataPacket); 
if(len < PacketMin || len > PacketMax)
return false;

//check dots  
 dots = 0;
for(i=0;i< len;i++)
{
   if(DataPacket[i] == '.')
      dots +=1;
} 

//check coommas
 commas = 0;
for(i=0;i < len;i++)
{
   if(DataPacket[i] == ',')
     commas +=1;
} 
 

 effs = 0;
for(i=0;i< len;i++)
{
   if(DataPacket[i] == 'f')
      effs +=1;
}  

if(dots == 3 && commas == 4 && effs == 0 ) 
 {
   return true;
 }
   else
     {
      return false;
    }  
}
////////////////////////////////////////////////////////////////////////////////

int numberOfCharsInArray(char* array){
 int numberOfChars = 0;
   while (*array++){
       numberOfChars++;
   }
   return numberOfChars;
}




void parseMessage(String toDigest) //used when in "packet by request" mode
{
//Parse string of form "#f#YPR,174.05,2.38,-0.05," NOTE we have added commas toinput from the GY951 to make for easier parsing
//Globals are required to received strings parsed and converted to float:   float numYaw, numPitch, numRoll; 

String Header,Yaw, Pitch, Roll; //Raw extracted values
int firstComma, secondComma,thirdComma,fourthComma; //Locations of field-separator commas
char TempBuff[8]; //to hold data of form "-359.99", 7 chars plus a spare, just habit
if (toDigest.indexOf("YPR") > -1) //found the correct header, so proceed
{ 
  firstComma = toDigest.indexOf(','); //Index the first comma.
  secondComma = toDigest.indexOf(',', firstComma+1); //Index the comma following the first.
  Yaw = toDigest.substring(firstComma+1, secondComma); //Extract yaw  
  Yaw.toCharArray(TempBuff, 7); //string to char array needed for atof function
  numYaw = atof(TempBuff); //now stored globally as a float for other use
  Serial.println("YAW " + Yaw);  //reassuring debug only

  thirdComma = toDigest.indexOf(',', secondComma+1);
  Pitch = toDigest.substring(secondComma+1, thirdComma);
  Pitch.toCharArray(TempBuff, 7); 
  numPitch = atof(TempBuff); //now stored as a float for other use
  Serial.println("PITCH " + Pitch); //debug only

 fourthComma = toDigest.indexOf(',', thirdComma+1);
 Roll = toDigest.substring(thirdComma+1, fourthComma);
 Roll.toCharArray(TempBuff, 7); 
 numRoll = atof(TempBuff); //now stored as a float for other use
 Serial.println("ROLL " + Roll); //debug only
} //end if (toDigest.startsWith("#f#YPR") )

}


void parseMessage2(String toDigest) //used when free run mode chosen
{
//slight difference, as place to start my be anywhere, as we grabbed a random string
//Parse string of form "#f#YPR,174.05,2.38,-0.05," NOTE we have added commas to char string received from the GY951 to make for easier parsing
//Globals are required to receive strings parsed and converted to float:   float numYaw, numPitch, numRoll; 

String Header,Yaw, Pitch, Roll; //Raw extracted values
int placeToStart,firstComma, secondComma,thirdComma,fourthComma; //Locations of field-separator commas
char TempBuff[8]; //to hold data of form "-359.99", 7 chars plus a spare, just habit

//Serial.println(toDigest);  //reassuring debug only
if (toDigest.indexOf("YPR") > -1) //contains the correct header, so proceed
{ 
 placeToStart = toDigest.indexOf("YPR"); //first occurance
  firstComma = toDigest.indexOf(',',placeToStart); //Index the first comma after the "YPR".
  secondComma = toDigest.indexOf(',', firstComma+1); //Index the comma following the first.
  Yaw = toDigest.substring(firstComma+1, secondComma); //Extract yaw  
  Yaw.toCharArray(TempBuff, 7); //string to char array needed for atof function
  numYaw = atof(TempBuff); //now stored globally as a float for other use
  Serial.println("YAW " + Yaw);  //reassuring debug only

  thirdComma = toDigest.indexOf(',', secondComma+1);
  Pitch = toDigest.substring(secondComma+1, thirdComma);
  Pitch.toCharArray(TempBuff, 7); 
  numPitch = atof(TempBuff); //now stored as a float for other use
  Serial.println("PITCH " + Pitch); //debug only

 fourthComma = toDigest.indexOf(',', thirdComma+1);
 Roll = toDigest.substring(thirdComma+1, fourthComma);
 Roll.toCharArray(TempBuff, 7); 
 numRoll = atof(TempBuff); //now stored as a float for other use
 Serial.println("ROLL " + Roll); //debug only
} //end if (toDigest.startsWith("#f#YPR") )

}



//void setup() {
//  Serial3.begin(9600);
//  Serial.begin(9600);
//}
//
//int incomingByte = 0;
//int values[5];
//int loc = 0;
//
//void loop() {
//  if(Serial3.available() > 0) {
//    incomingByte = Serial3.read();
//    values[loc] = incomingByte;
//    loc++;
//    if(loc == 5) {
//      loc = 0;
//      for(int i=0;i<5;i++) {
//            if (values[i]<100) Serial.print('0');
//            if (values[i]<10) Serial.print('0');
//            Serial.print(values[i], DEC);
//            Serial.print(" ");
//      }
//      Serial.println();
//    }
//  }
//  delay(50);
//}

