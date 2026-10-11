#define DATA_PIN  6   // SER / DS
#define CLOCK_PIN 7   // SRCLK / SHCP
#define LATCH_PIN 8   // RCLK / STCP

// Common-cathode 7-segment patterns
// Bit order: Q0=A, Q1=B, Q2=C, Q3=D,
//            Q4=E, Q5=F, Q6=G
const byte digitSegments[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void send595(byte digits, byte segments) {
  digitalWrite(LATCH_PIN, LOW);

  // First byte goes to the far register (digit selection)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digits);

  // Second byte goes to the near register (segments)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, segments);

  digitalWrite(LATCH_PIN, HIGH);
}

void showDigit(byte position, byte number) {
  // Common-cathode digit selection: LOW enables a digit
  byte digits = 0b11111111;
  digits &= ~(1 << position);

  send595(digits, digitSegments[number]);

  // Short multiplexing interval
  delayMicroseconds(1000);
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // All digits off at startup
  send595(0b11111111, 0);
}

void loop() {
  showDigit(0, 1);
  showDigit(1, 2);
  showDigit(2, 3);
  showDigit(3, 4);
}
