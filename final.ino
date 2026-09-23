#include <ESP8266WiFi.h> 
#include <WiFiUdp.h> 
#include <WiFiManager.h> 
#include <MD_Parola.h> 
#include <MD_MAX72xx.h> 
#include <SPI.h> 
#include <TimeLib.h> 
#include <Adafruit_GFX.h> 
#include <Max72xxPanel.h> 

//const char* ssid = "uhuuu";
//const char* password = "shahriyer";
const char* ssid = "iPhone";
const char* password = "samia1491";
const int dateScrollDelay = 80;  // For date scrolling


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CS_PIN_TIME D3  //4   // D3 - for time display
#define CS_PIN_DATE D8  // D8 - for date/weekday
#define CS_PIN D6  // for notice
#define CLK_PIN D5      // D5
#define DATA_PIN D7     // D7

// Web server
ESP8266WebServer server(80);

byte boishakh1_1[8] = {0x60,0x10,0xFF,0x27,0x49,0x4D,0x23,0x00};
byte boishakh1_2[8] = {0x00,0x05,0xDD,0x27,0x55,0x05,0x05,0x00};
byte boishakh1_3[8] = {0x00,0x02,0xEB,0x7A,0x0A,0x32,0x0E,0x00};
byte joishtho1_1[8] = {0x30,0x08,0x7F,0x11,0x25,0x24,0x13,0x00};
byte joishtho1_2[8] = {0x00,0x00,0xFF,0xC5,0x28,0xA4,0xA8,0x00};
byte joishtho1_3[8] = {0x1C,0x20,0xFE,0x38,0xE4,0xA4,0x78,0x00};
byte ashar1_1[8] = {0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00};
byte ashar1_2[8] = {0x00,0x81,0xFD,0xA7,0x95,0xAD,0x9D,0x00};
byte ashar1_3[8] = {0x00,0x00,0xFE,0x40,0x4C,0x44,0x38,0x10};
byte srabon1_1[8] = {0x00,0x01,0x37,0x09,0x15,0x01,0x23,0x1D};
byte srabon1_2[8] = {0x00,0x40,0x7F,0xCE,0x52,0x5A,0x46,0x00};
byte srabon1_3[8] = {0x00,0x08,0x6C,0x98,0xC8,0x08,0x08,0x00};
byte bhadro1_1[8] = {0x00,0x00,0x0F,0x00,0x04,0x02,0x01,0x00};
byte bhadro1_2[8] = {0x00,0x08,0xEF,0x59,0x89,0x69,0xCA,0x01};
byte bhadro1_3[8] = {0x00,0x00,0xF0,0x00,0x20,0xD0,0x90,0x60};
byte ashin1_1[8] = {0x00,0x00,0xFE,0x1B,0x56,0x46,0x3A,0x00};
byte ashin1_2[8] = {0x1E,0xA1,0xFB,0xA4,0xAA,0xA1,0xA2,0x01};
byte ashin1_3[8] = {0x00,0x80,0xFF,0x82,0xBA,0xA6,0xB2,0x80};
byte kartik1_1[8] = {0x00,0x00,0xFE,0x3D,0x4A,0x6A,0x18,0x00};
byte kartik1_2[8] = {0x1C,0xA3,0xFF,0xA3,0xAA,0xA8,0xA7,0x00};
byte kartik1_3[8] = {0x80,0x00,0xFF,0x1E,0xA5,0xB5,0x0C,0x00};
byte ogrohayon1_1[8] = {0x00,0x00,0x1F,0x03,0x0A,0x08,0x07,0x00};
byte ogrohayon1_2[8] = {0x00,0x00,0xF6,0x49,0xC4,0xCC,0x51,0x0E};
byte ogrohayon1_3[8] = {0x00,0x80,0xD8,0x98,0x80,0x98,0x98,0x00};
byte poush1_1[8] = {0x00,0x00,0x0E,0x05,0x08,0x08,0x04,0x00};
byte poush1_2[8] = {0xB8,0x54,0xDF,0x35,0xD4,0x95,0x14,0x00};
byte poush1_3[8] = {0x00,0x00,0xF0,0x20,0xA0,0x60,0xE0,0x00};
byte magh1_1[8] = {0x00,0x00,0x07,0x02,0x01,0x03,0x03,0x00};
byte magh1_2[8] = {0x00,0x10,0xDF,0x74,0x55,0xD2,0x53,0x00};
byte magh1_3[8] = {0x00,0x00,0xE0,0x40,0x40,0x40,0xC0,0x00};
byte falgun1_1[8] = {0x00,0x00,0xFE,0x4D,0x2A,0x4A,0x38,0x00};
byte falgun1_2[8] = {0x00,0x80,0xF8,0x86,0xA9,0xD4,0x8D,0x01};
byte falgun1_3[8] = {0x00,0x80,0xFF,0x81,0x9D,0x93,0x59,0xA0};
byte choitro1_1[8] = {0x06,0x01,0x0F,0x02,0x04,0x04,0x02,0x00};
byte choitro1_2[8] = {0x00,0x00,0xFF,0x81,0xF1,0x94,0xE3,0x00};
byte choitro1_3[8] = {0x00,0x00,0xF0,0xC0,0x20,0x60,0xA0,0x00};
byte shonibar[2][8] = {{0x00,0x05,0xDF,0x25,0x55,0x05,0x05,0x00},
                      {0xF0,0x08,0xFE,0x08,0x68,0x58,0x08,0x00}};


byte robibar[2][8] = {{0x01,0x02,0xFF,0x3A,0x4A,0x2A,0x5A,0x00},
                      {0xE0,0x10,0xFC,0x70,0x90,0x90,0x70,0x00}};


byte shombar[2][8] = {{0x00,0x00,0xFF,0x29,0x45,0x47,0x2D,0x00},
                  {0x00,0x40,0x7F,0xD2,0x4A,0x5E,0x5A,0x00}};


byte mongol[2][8] = {{0x04,0x03,0xFA,0x99,0x56,0xF1,0xD3,0x00},
                    {0x00,0x40,0x7F,0xC1,0x4B,0x55,0x51,0x00}};

byte budhbar[2][8] = {{0x01,0x02,0xFE,0x39,0x4A,0x39,0x14,0x0A},
                     {0x00,0x00,0xF0,0x40,0x40,0xC0,0x40,0x00}};

byte briho[2][8] = {{0x00,0x00,0xFF,0x3B,0x48,0x3B,0x11,0x1C},
                   {0x00,0x00,0xD8,0x18,0x80,0x18,0xD8,0x00}};

byte shukro[2][8] = {{0x00,0x02,0xDB,0x26,0x52,0x06,0x0A,0x05},
                    {0x00,0x00,0xFF,0x3C,0x4A,0x3A,0x98,0x68}};

byte shunno_small_1[8] = {0x18, 0x24, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18};
byte ek_small_1[8] = {0x60, 0x70, 0x1c, 0x06, 0x02, 0x62, 0x76, 0x3c};
byte dui_small_1[8] = {0x60, 0x7c, 0x06, 0x06, 0x7c, 0x60, 0x30, 0x1e};
byte tin_small_1[8] = {0x0c, 0x5a, 0x5a, 0x42, 0x42, 0x42, 0x42, 0x3c};
byte char_small_1[8] = {0x3c, 0x66, 0x66, 0x3c, 0x3c, 0x66, 0x66, 0x3c};
byte pach_small_1[8] = {0x30, 0x38, 0x46, 0x48, 0x4a, 0x46, 0x62, 0x3c};
byte chhoy_small_1[8] = {0x18, 0x58, 0x48, 0x4a, 0x4e, 0x42, 0x62, 0x3e};
byte shaat_small_1[8] = {0x38, 0x44, 0x44, 0x3c, 0x04, 0x04, 0x06, 0x06};
byte aat_small_1[8] = {0x60, 0x60, 0x26, 0x22, 0x3e, 0x24, 0x24, 0x38};
byte noy_small_1[8] = {0x60, 0x78, 0x0c, 0x06, 0x72, 0x4a, 0x6a, 0x0e};
//int pinCS = 4;  // D2 for Max72xxPanel
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel DateMatrix(CS_PIN_DATE, numberOfHorizontalDisplays, numberOfVerticalDisplays);  // D8
Max72xxPanel TimeMatrix(CS_PIN_TIME, numberOfHorizontalDisplays, numberOfVerticalDisplays);  // D3
Max72xxPanel matrix = Max72xxPanel(CS_PIN,numberOfHorizontalDisplays, numberOfVerticalDisplays);//D6

// Sentence 1: line mene cholun
const uint64_t IMAGES_1[] = {
  0x3f203f2428242926, 0x20212d73b3aba020, 0x203f242828262020,
  0x0000000000000000, 0x3f22242e36312926, 0x3f24282826312926,
  0x0000000000000000, 0x2020242a293f2020, 0x21223f2b3328322c,
  0x203f242828262020
};
const int LEN_1 = sizeof(IMAGES_1) / 8;

// Sentence 2: aage namte din
const uint64_t IMAGES_2[] = {
  0x3f3f222c3229212e, 0x3f10262a1a21322c, 0x0000000000000000,
  0x3f203f2428282620, 0x203f24242e362020, 0x2e31352922342926,
  0x0000000000000000, 0x2020afa8a4bea07f, 0x20203f2428282620
};
const int LEN_2 = sizeof(IMAGES_2) / 8;

// Sentence 3: jatra shuvo hok
const uint64_t IMAGES_3[] = {
  0x7f407f424a566240, 0x7f405f626252424c, 0x0000000000000000,
  0x4142ff453b384030, 0x5c7249697979425c, 0x0000000000000000,
  0x7f5865635360514e, 0x4c52507f514a4642
};
const int LEN_3 = sizeof(IMAGES_3) / 8;

// Sentence 4: nirapod durotto bojay rakhun
const uint64_t IMAGES_4[] = {
  0x20bfa4a8a8a6603f, 0x3f203f322b262220, 0x20203f1828241808,
  0x20202f28243c2020, 0x0000000000000000, 0x21222f2b243e2020,
  0x20203f322b262220, 0x202b353129222c20, 0x0000000000000000,
  0x20203f322a262220, 0x3f2728373539222c, 0x20203f222b362220,
  0x0000000000000000, 0x3f203f322b262220, 0x2e223f011d232d14,
  0x203f242828262020
};
const int LEN_4 = sizeof(IMAGES_4) / 8;

// Sentence 5: gari thambe
const uint64_t IMAGES_5[] = {
  0x3f203f10202c3414, 0x2caaaabba2bc603f, 0x0000000000000000,
  0x3f203f02122a261a, 0x203f24242e362020, 0x3f29262231292620
};
const int LEN_5 = sizeof(IMAGES_5) / 8;

// Global scroll state
const uint64_t* currentMessage = nullptr;
int currentMessageLen = 0;
int scrollSpeed = 80;
volatile bool shouldScroll = false;
unsigned long lastScrollTime = 0;
const int scrollStep = 2;       // Smaller = smoother
const int scrollInterval = 140;  // Time between scroll updates (ms)
int shift = -numberOfHorizontalDisplays * 8; // Initial offset
unsigned long lastDateUpdate = 0;
const unsigned long dateUpdateInterval = 5000;  // 3 seconds

// Web root
void handleRoot() {
  server.send(200, "text/plain", "ESP8266 is running");
}

// Web message trigger
void handleIndex() {
  if (server.hasArg("value")) {
    String value = server.arg("value");
    Serial.print("Received Index: ");
    Serial.println(value);

    shouldScroll = false;  // Stop previous scroll

    if (value == "135") {
      matrix.fillScreen(LOW);
      matrix.write();
      currentMessage = nullptr;
      currentMessageLen = 0;
      server.send(200, "text/plain", "Display Cleared");
      return;
    } else if (value == "136") {
      currentMessage = IMAGES_1;
      currentMessageLen = LEN_1;
    } else if (value == "137") {
      currentMessage = IMAGES_2;
      currentMessageLen = LEN_2;
    } else if (value == "138") {
      currentMessage = IMAGES_3;
      currentMessageLen = LEN_3;
    } else if (value == "139") {
      currentMessage = IMAGES_4;
      currentMessageLen = LEN_4;
    } else if (value == "140") {
      currentMessage = IMAGES_5;
      currentMessageLen = LEN_5;
    } else {
      server.send(400, "text/plain", "Invalid value!");
      return;
    }

    shouldScroll = true;
    scrollSpeed = 80;
    server.send(200, "text/plain", "OK: " + value);
  } else {
    server.send(400, "text/plain", "Missing 'value' parameter");
  }
}

// Scroll one frame across full 32x8 display
void scrollOneFrame(const uint64_t *images, int len, int shift) {
  const int charWidth = 8;
  const int totalWidth = len * charWidth;

  static uint8_t buffer[256];  // up to 32 characters
  for (int i = 0; i < len; i++) {
    uint64_t img = images[i];
    for (int col = 0; col < charWidth; col++) {
      buffer[i * charWidth + col] = (img >> (col * 8)) & 0xFF;
    }
  }

  matrix.fillScreen(LOW);
  for (int x = 0; x < numberOfHorizontalDisplays * 8; x++) {
    int sourceCol = shift + x;
    if (sourceCol >= 0 && sourceCol < totalWidth) {
      for (int y = 0; y < 8; y++) {
        bool pixelOn = bitRead(buffer[sourceCol], y);
        matrix.drawPixel(numberOfHorizontalDisplays * 8 - 1 - x, y, pixelOn);
      }
    }
  }
  matrix.write();
}
//Max72xxPanel GD(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
//const char* ssid = "iPhone";
//const char* password = "samia1491";
//const char* ssid = "Sami's realme 8";
//const char* password = "sami2006139";

const char* ntpServerName = "pool.ntp.org";
const long timezoneOffset = 6 * 3600;  // +6 hours


// === MAPPING FUNCTIONS ===
byte* getBanglaDigit(int digit) {
  switch (digit) {
    case 0: return shunno_small_1;
    case 1: return ek_small_1;
    case 2: return dui_small_1;
    case 3: return tin_small_1;
    case 4: return char_small_1;
    case 5: return pach_small_1;
    case 6: return chhoy_small_1;
    case 7: return shaat_small_1;
    case 8: return aat_small_1;
    case 9: return noy_small_1;
    default: return shunno_small_1;
  }
}

byte** getBanglaMonth(int bMonth) {
  static byte* months[][3] = {
    {},
    {boishakh1_1, boishakh1_2, boishakh1_3},
    {joishtho1_1, joishtho1_2, joishtho1_3},
    {ashar1_1, ashar1_2, ashar1_3},
    {srabon1_1, srabon1_2, srabon1_3},
    {bhadro1_1, bhadro1_2, bhadro1_3},
    {ashin1_1, ashin1_2, ashin1_3},
    {kartik1_1, kartik1_2, kartik1_3},
    {ogrohayon1_1, ogrohayon1_2, ogrohayon1_3},
    {poush1_1, poush1_2, poush1_3},
    {magh1_1, magh1_2, magh1_3},
    {falgun1_1, falgun1_2, falgun1_3},
    {choitro1_1, choitro1_2, choitro1_3},
  };
  return months[bMonth];
}

byte** getBanglaWeekday(int weekDay) {
  static byte* weekdays[][2] = {
    {},
    {shombar[0], shombar[1]},
    {mongol[0], mongol[1]},
    {budhbar[0], budhbar[1]},
    {briho[0], briho[1]},
    {shukro[0], shukro[1]},
    {shonibar[0], shonibar[1]},
    {robibar[0], robibar[1]}
  };
  return weekdays[weekDay];
}

// === SETUP ===
void setup() {
  Serial.begin(115200);

  // Init both matrices
  DateMatrix.setIntensity(5);
  TimeMatrix.setIntensity(5);
   matrix.setIntensity(5);
    // adjust if text appears flipped or rotated
  matrix.fillScreen(LOW);
  matrix.write();

  for (int i = 0; i < numberOfHorizontalDisplays; i++) {
   // DateMatrix.setRotation(i, 1);
    TimeMatrix.setRotation(i, 1);
     DateMatrix.setRotation(i, 1); // Rotate each panel clockwise
     matrix.setRotation(i, 1);
  }

  WiFi.begin(ssid, password);
   Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(5);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/index", handleIndex);
  server.begin();
  Serial.println("HTTP server started");

  configTime(0, 0, ntpServerName);  // Use UTC
  while (!time(nullptr)) {
    delay(10);
    Serial.print(".");
  }
  Serial.println("Time set");
}

void slideBitmapRightToLeft(byte** bitmaps, int count, int totalWidth) {
  for (int shift = 0; shift <= totalWidth; shift++) {
    DateMatrix.fillScreen(LOW);
    int x = 32 - shift;
    for (int i = 0; i < count; i++) {
      DateMatrix.drawBitmap(x + i * 8, 0, bitmaps[i], 8, 8, HIGH);
    }
    DateMatrix.write();
    delay(dateScrollDelay);  // Instead of delay(35)
  }
}

void showBanglaDate() {
  time_t now = time(nullptr);
  now += timezoneOffset;
  struct tm *timeinfo = gmtime(&now);

  int gDay = timeinfo->tm_mday;
  int gMonth = timeinfo->tm_mon + 1;
  int gYear = timeinfo->tm_year + 1900;
  int weekDay = timeinfo->tm_wday;
  if (weekDay == 0) weekDay = 7;

  int bDay = gDay, bMonth = gMonth, bYear = gYear;
  if (gMonth >= 4 && gMonth <= 12) bYear = gYear - 593;
  else bYear = gYear - 594;

  if (gMonth == 4) { if (gDay < 14) { bMonth = 12; bDay = gDay + 17; } else { bMonth = 1; bDay = gDay - 13; } }
  else if (gMonth == 5) { if (gDay < 15) { bMonth = 1; bDay = gDay + 17; } else { bMonth = 2; bDay = gDay - 14; } }
  else if (gMonth == 6) { if (gDay < 15) { bMonth = 2; bDay = gDay + 17; } else { bMonth = 3; bDay = gDay - 14; } }
  else if (gMonth == 7) { if (gDay < 16) { bMonth = 3; bDay = gDay + 16; } else { bMonth = 4; bDay = gDay - 15; } }
  else if (gMonth == 8) { if (gDay < 16) { bMonth = 4; bDay = gDay + 16; } else { bMonth = 5; bDay = gDay - 15; } }
  else if (gMonth == 9) { if (gDay < 16) { bMonth = 5; bDay = gDay + 16; } else { bMonth = 6; bDay = gDay - 15; } }
  else if (gMonth == 10) { if (gDay < 16) { bMonth = 6; bDay = gDay + 15; } else { bMonth = 7; bDay = gDay - 15; } }
  else if (gMonth == 11) { if (gDay < 15) { bMonth = 7; bDay = gDay + 16; } else { bMonth = 8; bDay = gDay - 14; } }
  else if (gMonth == 12) { if (gDay < 15) { bMonth = 8; bDay = gDay + 16; } else { bMonth = 9; bDay = gDay - 14; } }
  else if (gMonth == 1) { if (gDay < 14) { bMonth = 9; bDay = gDay + 17; } else { bMonth = 10; bDay = gDay - 13; } }
  else if (gMonth == 2) { if (gDay < 13) { bMonth = 10; bDay = gDay + 18; } else { bMonth = 11; bDay = gDay - 12; } }
  else if (gMonth == 3) { if (gDay < 15) { bMonth = 11; bDay = gDay + 17; } else { bMonth = 12; bDay = gDay - 14; } }
   // ========== DAY AND MONTH SLIDE ==========
  byte* dateBitmaps[5];
  int count = 0;

  if (bDay >= 10) {
    dateBitmaps[count++] = getBanglaDigit(bDay / 10);
    dateBitmaps[count++] = getBanglaDigit(bDay % 10);
  } else {
    dateBitmaps[count++] = getBanglaDigit(bDay);
  }

  byte** monthBitmap = getBanglaMonth(bMonth);
  for (int i = 0; i < 3; i++) {
    dateBitmaps[count++] = monthBitmap[i];
  }

  slideBitmapRightToLeft(dateBitmaps, count, count * 8);
  //delay(1);

  // ========== WEEKDAY SLIDE ==========
  byte** weekdayBitmap = getBanglaWeekday(weekDay);
  byte* weekSlide[2] = { weekdayBitmap[0], weekdayBitmap[1] };
  slideBitmapRightToLeft(weekSlide, 2, 2 * 8);
  //delay(2000);
}

void showTime() {
  time_t now = time(nullptr);
  now += timezoneOffset;  // Convert to BD time
  struct tm *timeinfo = gmtime(&now);

  int h = timeinfo->tm_hour;
  int m = timeinfo->tm_min;

  TimeMatrix.fillScreen(LOW);
  TimeMatrix.drawBitmap(0, 0, getBanglaDigit(h / 10), 8, 8, HIGH);
  TimeMatrix.drawBitmap(8, 0, getBanglaDigit(h % 10), 8, 8, HIGH);
  // Draw colon manually at center
  TimeMatrix.drawPixel(16, 2, HIGH);
  TimeMatrix.drawPixel(16, 5, HIGH);
  //
  TimeMatrix.drawBitmap(16, 0, getBanglaDigit(m / 10), 8, 8, HIGH);
  TimeMatrix.drawBitmap(24, 0, getBanglaDigit(m % 10), 8, 8, HIGH);
  TimeMatrix.write();
}
void loop() {
  server.handleClient();

  // Smooth notice scroll using millis()
  if (shouldScroll && currentMessage != nullptr) {
    unsigned long currentTime = millis();
    if (currentTime - lastScrollTime >= scrollInterval) {
      lastScrollTime = currentTime;

      scrollOneFrame(currentMessage, currentMessageLen, shift);
      shift += scrollStep;

      int totalWidth = currentMessageLen * 8;
      if (shift > totalWidth) {
        shift = -numberOfHorizontalDisplays * 8;
      }
    }
  }

  showTime();  // still every loop

// Only update date every 3 seconds
if (millis() - lastDateUpdate >= dateUpdateInterval) {
  showBanglaDate();
  lastDateUpdate = millis();
}
}


