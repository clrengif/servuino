extern mutex m_pins;
extern mutex m_leds;

extern int x_pinValue[MAX_TOTAL_PINS];
extern int x_leds[25]; // for microbit simulator

extern atomic<bool> shutdown;
extern bool fast_mode;
extern atomic<bool> running;

extern atomic<bool> suspend;

extern uint64_t micros_elapsed;
extern mutex elapsed;


extern mutex m_suspend;
extern condition_variable cv_suspend;