#include <avr/pgmspace.h>

// The TV-B-Gone for Arduino can use
//   either the EU or the NA database of POWER CODES
// EU is for Europe, Middle East, Australia, New Zealand, and some countries in Africa and South America
// NA is for North America, Asia, and the rest of the world not covered by EU

// Two regions!
#define NA 1
#define EU 0

// What pins do what
#define DBG 12
#define LED 13
#define IRLED 3
#define TRIGGER 2
#define REGIONSWITCH 5

// Lets us calculate the size of the NA/EU databases
#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)));

// set define to 0 to turn off debug output
#define DEBUG 0
#define DEBUGP(x) if (DEBUG == 1) { x ; }

// Shortcut to insert single, non-optimized-out nop
#define NOP __asm__ __volatile__ ("nop")

// Tweak this if neccessary to change timing
#define DELAY_CNT 25

// Makes the codes more readable. the OCRA is actually
// programmed in terms of 'periods' not 'freqs' - that
// is, the inverse!
#define freq_to_timerval(x) (F_CPU / 8 / x - 1)

// The structure of compressed code entries
struct IrCode {
  uint8_t timer_val;
  uint8_t numpairs;
  uint8_t bitcompression;
  uint16_t const *times;
  uint8_t const*codes;
};

extern const struct IrCode * const NApowerCodes[] PROGMEM;
extern const struct IrCode * const EUpowerCodes[] PROGMEM;
extern uint8_t num_NAcodes, num_EUcodes;
