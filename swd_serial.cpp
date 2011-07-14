#include <string.h>
#include "wirish.h"

/**
 * The buffer is empty when head == tail.
 * The buffer is full when the head is one byte in front of the tail,
 * modulo buffer length.
 * One byte is left free to distinguish empty from full. */

#define SWD_TX_BUF_SIZE               64

/** SWD device data structure */
typedef struct swd_dev {
    uint32 head;         /**< Index of the next item to remove */
    uint32 tail;         /**< Index where the next item will get inserted */
    uint32 size;         /**< Buffer capacity minus one */
    uint8  buf[SWD_TX_BUF_SIZE];   /**< Actual TX buffer used by rb */
} swd_dev;


static inline void swd_rb_init(swd_dev *swd, uint16 size) {
    swd->head = 0;
    swd->tail = 0;
    swd->size = size - 1;
}

static inline int swd_rb_is_full(swd_dev *swd) {
    return (swd->tail + 1 == swd->head) ||
        (swd->tail == swd->size && swd->head == 0);
}

static inline void swd_rb_insert(swd_dev *swd, uint8 element) {
    swd->buf[swd->tail] = element;
    swd->tail = (swd->tail == swd->size) ? 0 : swd->tail + 1;
}

static inline int swd_rb_safe_insert(swd_dev *swd, uint8 element) {
    if (swd_rb_is_full(swd)) {
        return 0;
    }
    swd_rb_insert(swd, element);
    return 1;
}


#define SWD_TIMEOUT 3000


swd_dev swd;

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
uint16 i;
    if (!buf)
        return 0;
    if (len > swd.size)
        len = swd.size;
    for(i=0;i<len;i++)
	if(!swd_rb_safe_insert(&swd, buf[i])) 
	    break;
    return i;
}

uint32 SWDReceiveBytes( uint8 *buf, uint32 len)
{
    if (!buf)
        return 0;
    if (len > 31)
        len = 31;

    return len;
}

SWDSerial::SWDSerial(void) {
    swd_rb_init(&swd, SWD_TX_BUF_SIZE);
    *DCRDR = (uint32)&swd;
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
    return 0;
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
    i = millis();
//    SerialSWD.print(" Hello! Hello!\n");
    SerialSWD.println(i);

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
