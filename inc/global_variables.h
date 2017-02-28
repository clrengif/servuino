extern mutex m_pins;
extern mutex m_leds;

extern int x_pinValue[MAX_TOTAL_PINS];
extern int x_leds[25]; // for microbit simulator
extern bool fast_mode;
extern uint64_t micros_elapsed;
extern mutex elapsed;