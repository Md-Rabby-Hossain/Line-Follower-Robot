#include <U8x8lib.h>

// OLED Display
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

// MUX control pins
#define MUX_S0  PB3
#define MUX_S1  PA15
#define MUX_S2  PA9
#define MUX_S3  PA10
#define MUX_SIG PB0

// Sensor arrays
int analog_read[14];
//int limit[14] = {700, 496, 419, 500, 565, 560, 950, 662, 395, 398, 1205, 550, 360, 570};
//int limit[14] = {180, 170, 160, 180, 180, 180, 190, 170, 170, 180, 220, 190, 180, 170};
int limit[14] = {200, 200, 220, 240, 240, 220, 250, 230, 220, 220, 300, 230, 210, 210};
int digital_read[14];

void setup() {
  Serial.begin(115200);

  // OLED Init
  u8x8.begin();
  u8x8.setFont(u8x8_font_5x7_f);

  // MUX control pins as output
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  pinMode(MUX_SIG, INPUT);

  delay(500); // Startup delay
}

void loop() {
  readSensors();        // Read analog values
  convertToDigital();   // Convert to digital values based on individual limits
  displayOnOLED();      // Show digital values on OLED
  printSerial();        // Show both analog & digital values in Serial Monitor

  delay(500);
}

// Select MUX channel (0-15)
void selectMuxChannel(int channel) {
  digitalWrite(MUX_S0, channel & 0x01);
  digitalWrite(MUX_S1, (channel >> 1) & 0x01);
  digitalWrite(MUX_S2, (channel >> 2) & 0x01);
  digitalWrite(MUX_S3, (channel >> 3) & 0x01);
  delayMicroseconds(5);
}

// Read analog sensors from channel 1 to 14
void readSensors() {
  for (int i = 0; i < 14; i++) {
    selectMuxChannel(i + 1);  // Channel 1 to 14
    analog_read[i] = analogRead(MUX_SIG);
  }
}

// Convert analog values to digital values using individual limits
void convertToDigital() {
  for (int i = 0; i < 14; i++) {
    digital_read[i] = (analog_read[i] > limit[i]) ? 1 : 0;
  }
}

// Display digital readings on OLED (2 rows, 7 columns)
void displayOnOLED() {
  u8x8.clearDisplay();
  char buffer[20];

  // 1st row (0-6)
  sprintf(buffer, "%d %d %d %d %d %d %d", 
          digital_read[0], digital_read[1], digital_read[2], digital_read[3],
          digital_read[4], digital_read[5], digital_read[6]);
  u8x8.drawString(0, 0, buffer);

  // 2nd row (7-13)
  sprintf(buffer, "%d %d %d %d %d %d %d", 
          digital_read[7], digital_read[8], digital_read[9], digital_read[10],
          digital_read[11], digital_read[12], digital_read[13]);
  u8x8.drawString(0, 1, buffer);
}

// Print analog and digital values in Serial Monitor
void printSerial() {
  Serial.print(" ");
  for (int i = 0; i < 14; i++) {
    Serial.print(analog_read[i]);
    Serial.print("  ");
  }
  Serial.println();

  Serial.print(" ");
  for (int i = 0; i < 14; i++) {
    Serial.print(digital_read[i]);
    Serial.print("  ");
  }
  Serial.println();
  Serial.println();
}
