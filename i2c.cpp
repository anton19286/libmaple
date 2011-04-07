#include "wirish.h"
#include "i2c.h"

void init_Wii() {
i2c_msg msgs[1];
uint8 buf[2] = {0xFE, 0x05};  

    i2c_master_enable(I2C2, 0);
    delay(100);
    msgs[0].addr = 0x53;
    msgs[0].flags = 0;
    msgs[0].length = 2;
    msgs[0].data = buf;
    i2c_master_xfer(I2C2, msgs, 1);
    delay(100);
    buf[0] = 0xF0; buf[1] = 0x55;
    msgs[0].addr = 0x53;
    msgs[0].flags = 0;
    msgs[0].length = 2;
    msgs[0].data = buf;
//    i2c_master_xfer(I2C2, msgs, 1);
    delay(100);
}

void read_Wii(uint8 *buf) {
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
    i2c_master_xfer(I2C2, msgs, 2);
}

void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);
//      Serial2.begin(115200);
//      init_Wii();
}

void loop() {
uint8 buffer[6];  

//      read_Wii(buffer);
//      if (buffer[5] & 0x02) //If WiiMP
//          Serial2.print("G");
//      else //If Nunchuk
//        Serial2.print("A");

      toggleLED();
      delay(30);
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}
