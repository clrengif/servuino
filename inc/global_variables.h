// pin states of the arduino
extern mutex m_pins;
extern int x_pinValue[MAX_TOTAL_PINS];

// led states for microbit simulator
extern mutex m_leds;
extern int x_leds[25]; 

// shutdown the simulator
extern atomic<bool> shutdown;

// stop the arduino code running
extern atomic<bool> running;

// run the simulator in fast_mode
extern bool fast_mode;


// how many microseconds have elapsed
extern uint64_t micros_elapsed;
extern mutex elapsed;

// suspend the arduino code
extern atomic<bool> suspend;
extern mutex m_suspend;
extern condition_variable cv_suspend;