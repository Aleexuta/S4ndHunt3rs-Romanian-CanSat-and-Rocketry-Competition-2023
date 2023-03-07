#define DEBUG true

static uint64_t debugCount = 0;

#if DEBUG
#define debug_print(message) \
Serial.println("Debug print no. " + String(debugCount++) + ". Message: " + message);
#else
#define debug_print(message)
#endif


//static const int RXPin = 17, TXPin = 16;
