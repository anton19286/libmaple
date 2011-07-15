#include <string.h>
#include "wirish.h"

/**
 * The buffer is empty when head == tail.
 * The buffer is full when the head is one byte in front of the tail,
 * modulo buffer length.
 * One byte is left free to distinguish empty from full. */

#define SWD_TX_BUF_SIZE               64
#define SWD_RX_BUF_SIZE               16

/** SWD device data structure */
typedef struct swd_dev {
    uint32 tx_head;         /**< Index of the next item to remove */
    uint32 tx_tail;         /**< Index where the next item will get inserted */
    uint32 tx_size;         /**< Buffer capacity minus one */
    uint32 rx_head;         /**< Index of the next item to remove */
    uint32 rx_tail;         /**< Index where the next item will get inserted */
    uint32 rx_size;         /**< Buffer capacity minus one */
    uint8  tx_buf[SWD_TX_BUF_SIZE];   /**< Actual TX buffer used by rb */
    uint32  rx_buf[SWD_RX_BUF_SIZE];   /**< Actual RX buffer used by rb */
} swd_dev;


static inline void swd_rb_init(swd_dev *swd, uint16 tx_size, uint16 rx_size) {
    swd->tx_head = 0;
    swd->tx_tail = 0;
    swd->tx_size = tx_size - 1;
    swd->rx_head = 0;
    swd->rx_tail = 0;
    swd->rx_size = rx_size - 1;
}

static inline int swd_rb_is_full(swd_dev *swd) {
    return (swd->tx_tail + 1 == swd->tx_head) ||
        (swd->tx_tail == swd->tx_size && swd->tx_head == 0);
}

static inline void swd_rb_insert(swd_dev *swd, uint8 element) {
    swd->tx_buf[swd->tx_tail] = element;
    swd->tx_tail = (swd->tx_tail == swd->tx_size) ? 0 : swd->tx_tail + 1;
}

static inline int swd_rb_safe_insert(swd_dev *swd, uint8 element) {
    if (swd_rb_is_full(swd)) {
        return 0;
    }
    swd_rb_insert(swd, element);
    return 1;
}

static inline int swd_rb_is_empty(swd_dev *swd) {
    return swd->rx_head == swd->rx_tail;
}

static inline uint8 swd_rb_remove(swd_dev *swd) {
    uint8 ch = (uint8)swd->rx_buf[swd->rx_head];
    swd->rx_head = (swd->rx_head == swd->rx_size) ? 0 : swd->rx_head + 1;
    return ch;
}

/**
 * Attempt to remove the first item from a ring buffer.
 * If the ring buffer is nonempty, removes and returns its first item.
 * If it is empty, does nothing and returns a negative value.
 */
static inline int16 swd_rb_safe_remove(swd_dev *swd) {
    return swd_rb_is_empty(swd) ? -1 : swd_rb_remove(swd);
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
    if (len > swd.tx_size)
        len = swd.tx_size;
    for(i=0;i<len;i++)
	if(!swd_rb_safe_insert(&swd, buf[i])) 
	    break;
    return i;
}

uint32 SWDReceiveBytes( uint8 *buf, uint32 len)
{
uint16 i;
int16 ch;
    if (!buf)
        return 0;
    if (len > 31)
        len = 31;
    for(i=0;i<len;i++) {
        if((ch = swd_rb_safe_remove(&swd)) < 0) 
           break;
        else
           buf[i] = (uint8)ch;
    }
    return i;
}

SWDSerial::SWDSerial(void) {
    swd_rb_init(&swd, SWD_TX_BUF_SIZE, SWD_RX_BUF_SIZE);
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


int n,start, i=0;
void setup() {

    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);


    SerialSWD.print("Hello!\n");
    start = millis();
}

void loop() {
char ch;
    toggleLED();
    n = millis();
    ch = char(1 + SerialSWD.read());
    SerialSWD.print(ch);
//    SerialSWD.print(" ");
//    if(n-start < 10000)
//       SerialSWD.println(i);
//    i++;
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
