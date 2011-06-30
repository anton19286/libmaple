/******************************************************************************
DiscoveryFlyer001 for the STM32VLDISCOVERY evaluation board.  (USD $11.85)
Modified by anton for quad with WiiMP

No safety features like arming/disarming in this revision!
No bounds checking either!
Flyable, but more lines of code are needed...
Yaw servo could use a low pass filter for higher gains without twitching.
Stick reversing set in transmitter.
No coffee grinder (jitter on the esc outputs) sounds from this setup!

Created April 14, 2011    By ridgebackred

This code is released with no strings attached.
******************************************************************************/

#include "wirish.h"
#include "i2c.h"
#include "exti.h"

#define PRINT_TELEMETRY

// Declare the interrupt handler routine
void measurePulseWidthISR();

 // Declare called routines
void InitWii(void);
void ReadWii(uint8 *buf);
void CalibrateGyros(void);

#define ROLL 0
#define PITCH 1
#define YAW 2
#define THROTTLE 3
#define LASTCHANNEL 4

#define RISING_EDGE 1
#define FALLING_EDGE 0
#define MINONWIDTH 950
#define MAXONWIDTH 2075
#define MINOFFWIDTH 12000
#define MAXOFFWIDTH 24000

// Channel data
typedef struct {
  byte edge;
  unsigned long riseTime;
  unsigned long fallTime;
  unsigned int  lastGoodWidth;
} tPinTimingData;
 
// Global variables for use in interrupt routines
volatile static tPinTimingData pinData[LASTCHANNEL];

 // I/O pin assignments

// 5V tolerant pins from different EXTI channels used for ROLL, PITCH, YAW, THROTTLE 
static byte receiverPin[4] = {PA8, PA9, PC6, PD2}; 

// ESC PWM pins
const int Esc1Pin         = PA6; // 12 Timer3,1 Front motor, ESC #1
const int Esc2Pin         = PA7; // 11 Timer3,2 Left motor, ESC #2
const int Esc3Pin         = PB0; // 27 Timer3,3 Right motor, ESC #3
const int Esc4Pin         = PB1; // 28 Timer3,4 Rear motor, ESC #4

// Global variables

// This group is adjusted according to flying style and taste.
int PitchGyroScale    = 8;    // sensitivity multiplier value for gyro
int RollGyroScale     = 9;    // sensitivity multiplier value for gyro
int YawGyroScale      = 5;    // sensitivity multiplier value for gyro
int PitchStickScale   = 3;    // sensitivity multiplier value for stick
int RollStickScale    = 3;    // sensitivity multiplier value for stick
int YawStickScale     = 3;    // sensitivity multiplier value for stick

// No adjustment needed here for these.
int PitchStickZero    = 0;    // center position stick reading
int RollStickZero     = 0;    // center position stick reading
int YawStickZero      = 0;    // center position stick reading
int ThrottleStickZero = 0;    // off position stick reading
int PitchGyroValue    = 0;    // value from from gyro sensor
int RollGyroValue     = 0;    // value from from gyro sensor
int YawGyroValue      = 0;    // value from from gyro sensor
int PitchGyroZero     = 0;    // no motion zero offset value for gyro
int RollGyroZero      = 0;    // no motion zero offset value for gyro
int YawGyroZero       = 0;    // no motion zero offset value for gyro
int MotorOut1         = 0;    // value sent to front ESC
int MotorOut2         = 0;    // value sent to left ESC
int MotorOut3         = 0;    // value sent to right ESC
int MotorOut4         = 0;    // value sent to rear ESC
int RxInPitchHold     = 0;
int RxInRollHold      = 0;
int RxInYawHold       = 0;
int RxInThrottleHold  = 0;

 // Do housekeeping activities once at power-up********************************
void setup()
{
    pinMode(BOARD_LED_PIN,  OUTPUT);

    // Set up the RC receiver pins as inputs
    // Attach the RC receiver pins to their interrupt handlers
    for (int channel = ROLL; channel < LASTCHANNEL; channel++) {
      pinMode(receiverPin[channel], INPUT);
      pinData[receiverPin[channel]].edge = FALLING_EDGE;
      attachInterrupt(receiverPin[channel], measurePulseWidthISR, CHANGE);           
    }

    // Set up the ESC pins as PWM outputs on Timer4
    pinMode(Esc1Pin, PWM);
    pinMode(Esc2Pin, PWM);
    pinMode(Esc3Pin, PWM);
    pinMode(Esc4Pin, PWM);

    delay(1500);                      // Time to accumulate a few interrupts.

    // Setup pwm Timers for the ESC's
    timer_set_mode(TIMER3, TIMER_CH1, TIMER_PWM);
    timer_set_mode(TIMER3, TIMER_CH2, TIMER_PWM);
    timer_set_mode(TIMER3, TIMER_CH3, TIMER_PWM);
    timer_set_mode(TIMER3, TIMER_CH4, TIMER_PWM);
    timer_pause(TIMER3);
    timer_set_count(TIMER3, 0);
    timer_set_reload(TIMER3, 60000);   //Sets the period of the PWM signal
    timer_resume(TIMER3);              // if LCD delay, spin up afterwards

#ifdef PRINT_TELEMETRY
    Serial2.begin(115200);
#endif    
    InitWii();

    // Accurate reading if gyros are motionless here... :-)
    CalibrateGyros();

     // Accurate reading if sticks are not being moved here... :-)
    PitchStickZero     = pinData[PITCH].lastGoodWidth;        // center position stick read
    RollStickZero       = pinData[ROLL].lastGoodWidth;          // center position stick read
    YawStickZero      = pinData[YAW].lastGoodWidth;          // center position stick read
    ThrottleStickZero = pinData[THROTTLE].lastGoodWidth;  // center position stick read
}

 // Run continuously after running setup()*************************************
void loop() {
uint8 buffer[6];
#ifdef PRINT_TELEMETRY
int startTag=0xDEAD;
#endif  


    ReadWii(buffer);
//  delay(4);
    // General idea for mixer adapted from KKmulticopter derivatives

    // Read the stick and gyro inputs...

    RxInPitchHold    = pinData[PITCH].lastGoodWidth;      // Temporary store of rx stick values
    RxInRollHold     = pinData[ROLL].lastGoodWidth;       // since an interrupted update of
    RxInThrottleHold = pinData[THROTTLE].lastGoodWidth;   // the value may cause glitch.
    RxInYawHold      = pinData[YAW].lastGoodWidth;

    YawGyroValue  = ((buffer[3] >> 2) << 8) + buffer[0];
    PitchGyroValue = ((buffer[4] >> 2) << 8) + buffer[1];
    RollGyroValue   = ((buffer[5] >> 2) << 8) + buffer[2];
	
#ifdef PRINT_TELEMETRY
    Serial2.write((unsigned byte*)&startTag, 2);            //processing code in the end of this file
    Serial2.write((unsigned byte*)&PitchGyroValue, 2);   
    Serial2.write((unsigned byte*)&YawGyroValue, 2);
    Serial2.write((unsigned byte*)&RollGyroValue, 2);
    Serial2.write((unsigned byte*)&RxInPitchHold, 2);    
    Serial2.write((unsigned byte*)&RxInYawHold, 2);
    Serial2.write((unsigned byte*)&RxInRollHold, 2);
    Serial2.write((unsigned byte*)&RxInThrottleHold, 2);
#endif

    RxInPitchHold -= PitchStickZero;   // Offset the Pitch, Roll and Yaw
    RxInRollHold  -= RollStickZero;    // stick values to a +- value
    RxInYawHold   -= YawStickZero;     // with stick center = 0

    RxInPitchHold *= PitchStickScale;  // Scale the Pitch, Roll and Yaw
    RxInRollHold  *= RollStickScale;   // stick values to increase/decrease
    RxInYawHold   *= YawStickScale;    // stick sensitivity

    // Offset Pitch, Roll and Yaw gyro values to no motion state = 0
    PitchGyroValue -= PitchGyroZero;
    PitchGyroValue  = -PitchGyroValue; // Uncomment to reverse gyro output
    RollGyroValue  -= RollGyroZero;
    RollGyroValue   = -RollGyroValue;  // Uncomment to reverse gyro output
    YawGyroValue   -= YawGyroZero;
    //YawGyroValue = -YawGyroValue;    // Uncomment to reverse gyro output

    PitchGyroValue *= PitchGyroScale;  // Scale the Pitch, Roll and Yaw
    RollGyroValue  *= RollGyroScale;   // gyro values to increase/decrease
    YawGyroValue   *= YawGyroScale;    // gyro sensitivity


     // Prime the motor speeds...
     // Hand tuned multiplier for throttle,
     // tweak for your prop, esc characteristics.
    MotorOut1 = (RxInThrottleHold*12); // Front initial motor speed
    MotorOut2 = (RxInThrottleHold*12); // Left initial motor speed
    MotorOut3 = (RxInThrottleHold*12); // Right initial motor speed
    MotorOut4 = (RxInThrottleHold*12); // Rear initial motor speed

     // Apply mixer calculations...
    RxInRollHold += RollGyroValue;
    MotorOut2 += RxInRollHold;
    MotorOut3 -= RxInRollHold;

    RxInPitchHold += PitchGyroValue;
    MotorOut1 += RxInPitchHold;
    MotorOut4 -= RxInPitchHold;

    RxInYawHold += YawGyroValue;
    MotorOut1 -= RxInYawHold;
    MotorOut2 += RxInYawHold;
    MotorOut3 += RxInYawHold;
    MotorOut4 -= RxInYawHold;


	 // Write speed/position values...
    pwmWrite(Esc1Pin,MotorOut1);       // Update front motor speed
    pwmWrite(Esc2Pin,MotorOut2);       // Update left motor speed
    pwmWrite(Esc3Pin,MotorOut3);       // Update right motor speed
    pwmWrite(Esc4Pin,MotorOut4);       // Update rear motor speed

    toggleLED();
     // Do it again...
}
//*****************************************************************************

void InitWii() {
i2c_msg msgs[1];
uint8 buf[2] = {0xFE, 0x04};

 i2c_master_enable(I2C2, 0);
 delay(100);
 msgs[0].addr = 0x53;
 msgs[0].flags = 0;
 msgs[0].length = 2;
 msgs[0].data = buf;
 i2c_master_xfer(I2C2, msgs, 1, 0);
 delay(100);
 buf[0] = 0xF0; buf[1] = 0x55;
 msgs[0].addr = 0x53;
 msgs[0].flags = 0;
 msgs[0].length = 2;
 msgs[0].data = buf;
 // i2c_master_xfer(I2C2, msgs, 1, 0);
 delay(100);
}

void ReadWii(uint8 *buf) {
i2c_msg msgs[2];

 buf[0] = 0x00;
 msgs[0].addr = 0x52;
 msgs[0].flags = 0;
 msgs[0].length = 1;
 msgs[0].data = buf;

 /* Repeated start condition, then read 6 byte back */
 msgs[1].addr = 0x52;
 msgs[1].flags = I2C_MSG_READ;
 msgs[1].length = 6;
 msgs[1].data = buf;
 i2c_master_xfer(I2C2, msgs, 2, 0);
}

void CalibrateGyros(){
unsigned int i;
uint8 buffer[6];

    for (i=0;i<32;i++){  // Average of 32 readings of gyros
        ReadWii(buffer);
        delay(4);
        YawGyroValue =   ((buffer[3] >> 2) << 8) + buffer[0];
        PitchGyroValue = ((buffer[4] >> 2) << 8) + buffer[1];
        RollGyroValue =  ((buffer[5] >> 2) << 8) + buffer[2];
        PitchGyroZero  += PitchGyroValue;
		RollGyroZero   += RollGyroValue;
        YawGyroZero    += YawGyroValue;
        toggleLED();
        delay(30);
   }
   PitchGyroZero = (PitchGyroZero / 32);
   RollGyroZero  = (RollGyroZero  / 32);
   YawGyroZero   = (YawGyroZero   / 32);
}

void measurePulseWidthISR(){
    uint32 currentTime;
    uint32 time;
    uint8 pin, bit;
    uint32 mask, pending;

    pending = GET_BITS(EXTI_BASE->PR, 0, 15);	
    currentTime = micros();

    for (byte channel = ROLL; channel < LASTCHANNEL; channel++) {      
        pin = receiverPin[channel];
        bit = PIN_MAP[pin].gpio_bit;
        mask = BIT(bit);
        if (mask & pending){
            *bb_perip(&EXTI_BASE->PR, bit) = 1; // clear_pending(bit); 
            if (digitalRead(pin)){
                time = currentTime - pinData[channel].fallTime;
                pinData[channel].riseTime = currentTime;
                if ((time >= MINOFFWIDTH) && (time <= MAXOFFWIDTH))
                    pinData[channel].edge = RISING_EDGE;
                else
                    pinData[channel].edge = FALLING_EDGE; // invalid rising edge detected
            } else {
                time = currentTime - pinData[channel].riseTime;
                pinData[channel].fallTime = currentTime;
                if ((time >= MINONWIDTH) && (time <= MAXONWIDTH) && (pinData[channel].edge == RISING_EDGE)) {
                    pinData[channel].lastGoodWidth = time;
                    pinData[channel].edge = FALLING_EDGE;
                }
            }
        }  
    }
}  


// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__(( constructor )) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}






/*****************************************************************************
Processing code by knuckles904 from arduino.cc forum
// 6-30-2009
// Original code at http://www.glacialwanderer.com/hobbyrobotics

// This takes data off the serial port and graphs it.
// There is an option to log this data to a file.

import processing.serial.*;

// Globals
int g_winW             = 820;   // Window Width
int g_winH             = 600;   // Window Height
boolean g_dumpToFile   = false;  // Dumps data to c:\\output.txt in a comma seperated format (easy to import into Excel)
boolean g_enableFilter = false;  // Enables simple filter to help smooth out data.

cDataArray pitch_g    = new cDataArray(200);
cDataArray yaw_g    = new cDataArray(200);
cDataArray roll_g    = new cDataArray(200);
cDataArray pitch_t      = new cDataArray(200);
cDataArray yaw_t     = new cDataArray(200);
cDataArray roll_t     = new cDataArray(200);
cDataArray throttle_t     = new cDataArray(200);

cGraph g_graph         = new cGraph(10, 190, 800, 400);
Serial g_serial;
PFont  g_font;

void setup()
{
  size(g_winW, g_winH, P2D);

  println(Serial.list());
  g_serial = new Serial(this, "COM9", 115200, 'N', 8, 1.0);  //enter COM port of
  g_font = loadFont("AndaleMono-24.vlw");                       //of arduino here
  textFont(g_font, 20);
  
  // This draws the graph key info
  strokeWeight(1.5);
  stroke(255, 0, 0);     line(20, 440, 35, 440);
  stroke(0, 255, 0);     line(20, 460, 35, 460);
  stroke(0, 0, 255);     line(20, 480, 35, 480);
  stroke(255, 255, 0);   line(20, 500, 35, 500);
  stroke(0, 255, 255);   line(20, 520, 35, 520);
  stroke(255, 0, 255);   line(20, 540, 35, 540);
  stroke(0, 0, 0);       line(20, 560, 35, 560);
  fill(0, 0, 0);
  text("pitch_g", 40, 450);
  text("yaw_g", 40, 470);
  text("roll_g", 40, 490);
  text("pitch_t", 40, 510);
  text("yaw_t", 40, 530);
  text("roll_t", 40, 550);
  text("throttle_t", 40, 570);
  //text("current raw", 180, 430);
  //text("current deg/s", 320, 430);
  
  if (g_dumpToFile)
  {
    // This clears deletes the old file each time the app restarts
    byte[] tmpChars = {'\r', '\n'};
    saveBytes("c:\\output.txt", tmpChars);
  }
}

void draw()
{
  // We need to read in all the avilable data so graphing doesn't lag behind
  while (g_serial.available() >= 2*6+2)
  {
    processSerialData();
  }

  strokeWeight(1);
  fill(255, 255, 255);
  g_graph.drawGraphBox();
  
  strokeWeight(1.5);
  stroke(255, 0, 0);
  g_graph.drawLine(pitch_g, 0, 16384);
  stroke(0, 255, 0);
  g_graph.drawLine(yaw_g, 0, 16384);
  stroke(0, 0, 255);
  g_graph.drawLine(roll_g, 0, 16384);
  stroke(255, 255, 0);
  g_graph.drawLine(pitch_t, 0, 16384);
  stroke(0, 255, 255);
  g_graph.drawLine(yaw_t, 0, 16384);
  stroke(255, 0, 255);
  g_graph.drawLine(roll_t, 0, 16384);
    stroke(0, 0, 0);
  g_graph.drawLine(throttle_t, 0, 16384);

}

// This reads in one set of the data from the serial port
void processSerialData()
{
  int inByte = 0;
  int curMatchPos = 0;
  int[] intBuf = new int[2];

  intBuf[0] = 0xAD;
  intBuf[1] = 0xDE;
  
  while (g_serial.available() < 2); // Loop until we have enough bytes
  inByte = g_serial.read();
  
  // This while look looks for two bytes sent by the client 0xDEAD
  // This allows us to resync the server and client if they ever
  // loose sync.  In my testing I haven't seen them loose sync so
  // this could be removed if you need to, but it is a good way to
  // prevent catastrophic failure.
  while(curMatchPos < 2)
  {
    if (inByte == intBuf[curMatchPos])
    {
      ++curMatchPos;
      
      if (curMatchPos == 2)
        break;
    
      while (g_serial.available() < 2); // Loop until we have enough bytes
      inByte = g_serial.read();
    }
    else
    {
      if (curMatchPos == 0)
      {
        while (g_serial.available() < 2); // Loop until we have enough bytes
        inByte = g_serial.read();
      }
      else
      {
        curMatchPos = 0;
      }
    }
  }
  
  while (g_serial.available() < 2*6);  // Loop until we have a full set of data

  // This reads in one set of data
  {
    byte[] inBuf = new byte[2];
    int pitch0_cur, yaw0_cur, roll0_cur, pitch_cur, yaw_cur, roll_cur, throttle_cur;
  
    g_serial.readBytes(inBuf);
    // Had to do some type conversion since Java doesn't support unsigned bytes
    pitch0_cur = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    yaw0_cur = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    roll0_cur = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    pitch_cur   = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    yaw_cur  = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    roll_cur  = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    g_serial.readBytes(inBuf);
    throttle_cur  = ((int)(inBuf[1]&0xFF) << 8) + ((int)(inBuf[0]&0xFF) << 0);
    
    pitch_g.addVal(pitch0_cur);
    yaw_g.addVal(yaw0_cur);
    roll_g.addVal(roll0_cur);
    pitch_t.addVal(pitch_cur+300);
    yaw_t.addVal(yaw_cur+200);
    roll_t.addVal(roll_cur+100);
    throttle_t.addVal(throttle_cur);

    if (g_dumpToFile)  // Dump data to a file if needed
    {
      String tempStr;
      tempStr = pitch0_cur + "," + yaw0_cur + "," + roll0_cur + "," + pitch_cur + "," + yaw_cur + "," + roll_cur + "\r\n";
      FileWriter file;

      try  
      {  
        file = new FileWriter("c:\\output.txt", true); //bool tells to append
        file.write(tempStr, 0, tempStr.length()); //(string, start char, end char)
        file.close();
      }  
      catch(Exception e)  
      {  
        println("Error: Can't open file!");
      }
    }

    
//    print(pitch0_cur);  print(" ");   print(yaw0_cur);   print(" ");    print(roll0_cur);     print(" ");
//    print(pitch_cur);    print(" ");   print(yaw_cur);    print(" ");    println(roll_cur);
    
  }
}

// This class helps mangage the arrays of data I need to keep around for graphing.
class cDataArray
{
  float[] m_data;
  int m_maxSize;
  int m_startIndex = 0;
  int m_endIndex = 0;
  int m_curSize;
  
  cDataArray(int maxSize)
  {
    m_maxSize = maxSize;
    m_data = new float[maxSize];
  }
  
  void addVal(float val)
  {
    
    if (g_enableFilter && (m_curSize != 0))
    {
      int indx;
      
      if (m_endIndex == 0)
        indx = m_maxSize-1;
      else
        indx = m_endIndex - 1;
      
      m_data[m_endIndex] = getVal(indx)*.5 + val*.5;
    }
    else
    {
      m_data[m_endIndex] = val;
    }
    
    m_endIndex = (m_endIndex+1)%m_maxSize;
    if (m_curSize == m_maxSize)
    {
      m_startIndex = (m_startIndex+1)%m_maxSize;
    }
    else
    {
      m_curSize++;
    }
  }
  
  float getVal(int index)
  {
    return m_data[(m_startIndex+index)%m_maxSize];
  }
  
  int getCurSize()
  {
    return m_curSize;
  }
  
  int getMaxSize()
  {
    return m_maxSize;
  }
}

// This class takes the data and helps graph it
class cGraph
{
  float m_gWidth, m_gHeight;
  float m_gLeft, m_gBottom, m_gRight, m_gTop;
  
  cGraph(float x, float y, float w, float h)
  {
    m_gWidth     = w;
    m_gHeight    = h;
    m_gLeft      = x;
    m_gBottom    = g_winH - y;
    m_gRight     = x + w;
    m_gTop       = g_winH - y - h;
  }
  
  void drawGraphBox()
  {
    stroke(0, 0, 0);
    rectMode(CORNERS);
    rect(m_gLeft, m_gBottom, m_gRight, m_gTop);
  }
  
  void drawLine(cDataArray data, float minRange, float maxRange)
  {
    float graphMultX = m_gWidth/data.getMaxSize();
    float graphMultY = m_gHeight/(maxRange-minRange);
    
    for(int i=0; i<data.getCurSize()-1; ++i)
    {
      float x0 = i*graphMultX+m_gLeft;
      float y0 = m_gBottom-((data.getVal(i)-minRange)*graphMultY);
      float x1 = (i+1)*graphMultX+m_gLeft;
      float y1 = m_gBottom-((data.getVal(i+1)-minRange)*graphMultY);
      line(x0, y0, x1, y1);
    }
  }
} 
*/