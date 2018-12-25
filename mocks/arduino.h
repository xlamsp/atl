/*
 * Excerpt from Arduino.h for mocking purposes
 */

#ifndef Arduino_h
#define Arduino_h

#include <stdbool.h>
#include <stdint.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

typedef bool boolean;
typedef uint8_t byte;

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int16_t digitalRead(uint8_t);

uint32_t millis(void);

#endif /* Arduino_h */

