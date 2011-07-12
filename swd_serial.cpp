#include <string.h>
#include "wirish.h"

#define SWD_TIMEOUT 3000

typedef struct _SWDSERDATA {
    uint32       SendLen;
    uint32       ReceiveLen;
    uint8        SendBuf[32];
    uint8        ReceiveBuf[32];
} SWDSERDATA, *PSWDSERDATA;

SWDSERDATA SWDData;

volatile uint32 *DCRDR = (uint32 *)0xe000edf8;

class SWDSerial : public Print {
public:
    SWDSerial(void);

    uint32 available(void);

    uint32 read(void *buf, uint32 len);
    uint8  read(void);

    void write(uint8);
    void write(const char *str);
    void write(const void*, uint32);
};

extern SWDSerial SerialSWD;


uint32 SWDSendBytes(uint8 *buf, uint32 len)
{
    if (!buf || SWDData.SendLen)
        return 0;
    if (len > 31)
        len = 31;
    memcpy(SWDData.SendBuf, buf, len); 
    SWDData.SendLen = len;
    return len;
}

uint32 SWDReceiveBytes( uint8 *buf, uint32 len)
{
    if (!buf || !SWDData.ReceiveLen)
        return 0;
    if (len > 31)
        len = 31;
    if (len > SWDData.ReceiveLen)
        len = SWDData.ReceiveLen;

    memcpy(buf,SWDData.ReceiveBuf, len); 
    SWDData.ReceiveLen -= len;
    return len;
}

SWDSerial::SWDSerial(void) {
    SWDData.SendLen = 0;
    SWDData.ReceiveLen = 0;
    *DCRDR = (uint32)&SWDData;
}

void SWDSerial::write(uint8 ch) {
    const uint8 buf[] = {ch};
    this->write(buf, 1);
}

void SWDSerial::write(const char *str) {
    this->write(str, strlen(str));
}

void SWDSerial::write(const void *buf, uint32 len) {
    if (!buf) {
        return;
    }

    uint32 txed = 0;
    uint32 old_txed = 0;
    uint32 start = millis();

    while (txed < len && (millis() - start < SWD_TIMEOUT)) {
        txed += SWDSendBytes((uint8*)buf + txed, len - txed);
        if (old_txed != txed) {
            start = millis();
        }
        old_txed = txed;
    }
}

uint32 SWDSerial::available(void) {
    return SWDData.ReceiveLen;
}

uint32 SWDSerial::read(void *buf, uint32 len) {
    if (!buf) {
        return 0;
    }

    uint32 rxed = 0;
    while (rxed < len) {
        rxed += SWDReceiveBytes((uint8*)buf + rxed, len - rxed);
    }

    return rxed;
}

/* Blocks forever until 1 byte is received */
uint8 SWDSerial::read(void) {
    uint8 buf[1];
    this->read(buf, 1);
    return buf[0];
}

SWDSerial SerialSWD;



void setup() {

    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);


    SerialSWD.print("Hello!\n");
}

int i=0;

void loop() {
    toggleLED();
    SerialSWD.print(" Hello! Hello!\n");
    SerialSWD.print(i);
    i++;
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
