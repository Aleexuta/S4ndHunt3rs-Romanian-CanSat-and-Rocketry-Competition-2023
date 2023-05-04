#define DEBUG true

static uint64_t debugCount = 0;

#if DEBUG
#define debug_println(message) \
Serial.println(" No." + String(debugCount++) + ". Msg: " + message);
#else
#define debug_println(message)
#endif

#if DEBUG
#define debug_print(message) \
Serial.print(" No." + String(debugCount++) + ". Msg: " + message);
#else
#define debug_print(message)
#endif

//static const int RXPin = 17, TXPin = 16;
