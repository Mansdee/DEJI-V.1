/*
===========================================================
  PROJECT   : DEJI - Expressive Wearable
  VERSION   : v.1 (Stable Build)
  DEVELOPER : MANS_DEE (@MANS_DEE)
  HARDWARE  : ESP32-C3 | SSD1306 OLED
===========================================================
*/

#define FW_VERSION "DEJI-v.1"

#include <ChronosESP32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "eye_emot.h"
#include "deji_loading.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define BUTTON_PIN 4
#define BUZZER_PIN 5

// Timing/Tuning
#define ANIMATION_FRAME_DELAY_MS 42
#define ANIMATION_LOOP_DELAY_MS 500
#define LONG_PRESS_TIME_MS 600
#define DOUBLE_TAP_WINDOW_MS 500
#define TAP_MAX_MS 400
#define DEBOUNCE_DELAY_MS 20
#define MAX_NOTIFICATIONS 5

// Objek
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ChronosESP32 watch;

// Icon Cuaca
const unsigned char cuacaCerah_Berawan[] PROGMEM = {
  0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x21, 0x00, 0x00, 0x00, 0x06, 0x23, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x38, 0x30,
  0x00, 0x00, 0x00, 0x00, 0xf1, 0xfc, 0x00, 0x00, 0x01, 0xe3, 0xfe, 0x00, 0x00, 0x01, 0xe7, 0xff,
  0x00, 0x00, 0xf3, 0xcf, 0xff, 0xfc, 0x00, 0x01, 0xcf, 0xff, 0xfe, 0x00, 0x01, 0x0f, 0xff, 0xff,
  0x00, 0x08, 0x1f, 0xff, 0xff, 0x00, 0x38, 0x7f, 0xff, 0xff, 0x80, 0x20, 0xff, 0xff, 0xff, 0xc0,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x03,
  0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xc0
};

// Ikon Petir Kecil (8x10 pixel) buat Charging
const unsigned char iconPetir[] PROGMEM = {
  0x1c, 0x38, 0x30, 0x7e, 0xfc, 0x0c, 0x1c, 0x18
};

// LOGIKA ANIMASI
struct Animation {
  uint16_t startFrame;
  uint16_t endFrame;
};

// 1. Tambahkan ke array animations[]
const Animation animations[] = {
  { EYE1_START_INDEX, EYE1_START_INDEX + EYE1_FRAME_COUNT - 1 },         // 0
  { EYE2_START_INDEX, EYE2_START_INDEX + EYE2_FRAME_COUNT - 1 },         // 1
  
  // INDEX 2-6 ADALAH KOLAM IDLE
  { TIDUR_START_INDEX, TIDUR_START_INDEX + TIDUR_FRAME_COUNT - 1 },      // 2
  { SPIDO_START_INDEX, SPIDO_START_INDEX + SPIDO_COUNT - 1 },            // 3
  { GAME_START_INDEX, GAME_START_INDEX + GAME_COUNT - 1 },               // 4
  { RISING_START_INDEX, RISING_START_INDEX + RISING_COUNT - 1 },         // 5
  { MAKAN_START_INDEX, MAKAN_START_INDEX + MAKAN_COUNT - 1 },            // 6
  
  // INDEX 7-10 ADALAH ANIMASI TAP
  { MENGEJEK_START_INDEX, MENGEJEK_START_INDEX + MENGEJEK_COUNT - 1 },   // 7
  { EVIL_LAUGH_START_INDEX, EVIL_LAUGH_START_INDEX + EVIL_COUNT - 1 },   // 8
  { KISS_V2_START_INDEX, KISS_V2_START_INDEX + KISS_COUNT - 1 },         // 9
  { TANJIRO_START_INDEX, TANJIRO_START_INDEX + TANJIRO_COUNT - 1 },      // 10
  { NAVIGATION_START_INDEX, NAVIGATION_START_INDEX + NAVIGATION_ICON_COUNT - 1 } // 11
};

// 2. Setting Kolam Idle & Index Baru
int idlePool[] = {2, 3, 4, 5, 6}; // Tidur, Spido, Game, Rising, Makan
int totalIdlePool = 5;

// Pastikan Index Navigasi di-update juga
const int NAV_ANIMATION_INDEX = 11;

// Update Index Callbacks biar pas sama tombol
const int KISS_ANIMATION_INDEX = 1;
const int TIDUR_ANIMATION_INDEX = 2; // Ganti ngiler jadi tidur biar keren

// Animasi yang muter otomatis pas standby (Eye1 & Eye2 gantian)
const int loopingAnimationIndices[] = { 0, 1 }; 
const int TOTAL_LOOPING_ANIMATIONS = sizeof(loopingAnimationIndices) / sizeof(loopingAnimationIndices[0]);

enum DisplayMode {
  MODE_ANIMATION,
  MODE_CLOCK_DATE,
  MODE_WEATHER,
  MODE_NOTIFICATION_LIST,
  MODE_NAVIGATION,
  MODE_SURPRISE
};

DisplayMode currentMode = MODE_ANIMATION;
DisplayMode modeBeforeNavigation = MODE_ANIMATION;
static DisplayMode lastDisplayedMode = (DisplayMode)-1; // Variabel "Penyembuh Macet"

// --- TAMBAHAN UNTUK LOGIKA TIDUR ---
unsigned long lastInteractionTime = 0;
const unsigned long IDLE_TIMEOUT_MS = 10000; // 10000 ms = 10 detik
int activeAwakeIndex = 0; // 0 = EYE1 (Normal), 1 = EYE2 (Kiss)
bool isSleeping = false;
// -----------------------------------

uint16_t currentFrame;
int currentAnimationIndex = -1;
// int currentLoopIndex = 0; // <--- INI BOLEH DIHAPUS KARENA UDAH GA DIPAKE
bool isPlayingAnimation = false;

Notification notificationHistory[MAX_NOTIFICATIONS];
int notificationCount = 0;
int latestNotificationIndex = -1;
volatile bool newNotificationAvailable = false;

bool navActiveFlag = false;

const char *monthNames[] = { "Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Ags", "Sep", "Okt", "Nov", "Des" };
const char *dayNames[] = { "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu" };


int surprisePage = 0; 
int globalTapCount = 0; // Tambahkan ini biar bisa dibaca di displaySurpriseMode

// =================== Callbacks & Helpers ==================
void displayModernNavigation();

void onNotification(Notification notif) {
  if (navActiveFlag) return;
  latestNotificationIndex = (latestNotificationIndex + 1) % MAX_NOTIFICATIONS;
  notificationHistory[latestNotificationIndex] = notif;
  if (notificationCount < MAX_NOTIFICATIONS) notificationCount++;
  newNotificationAvailable = true;
}

void configCallback(Config config, uint32_t a, uint32_t b) {
  if (config == CF_NAV_ICON && currentMode == MODE_NAVIGATION) {
    displayModernNavigation();
  }
}

// =================== Helpers UI =========================
void drawCenteredText(const String &text, int y, int size) {
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - (int)w) / 2, y);
  display.println(text);
}

void drawCenteredTextInRect(const String &text, int rectX, int rectW, int y, int size, bool isBold = false) {
  display.setTextSize(size);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int cursorX = rectX + (rectW - w) / 2;
  display.setCursor(cursorX, y);
  display.print(text);
  if (isBold) {
    display.setCursor(cursorX + 1, y);
    display.print(text);
  }
}

void drawScrollingText(const String &text, int16_t x, int16_t y, int16_t areaWidth) {
  static int16_t scrollOffset = 0;
  static unsigned long lastScrollTime = 0;
  static String lastText = "";
  const int SCROLL_SPEED_MS = 150;
  const int PADDING = 20;

  if (text != lastText) {
    scrollOffset = 0;
    lastText = text;
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.fillRect(x, y, areaWidth, h, SSD1306_BLACK);

  if (w <= areaWidth) {
    int16_t centeredX = x + (areaWidth - w) / 2;
    display.setCursor(centeredX, y);
    display.print(text);
    return;
  }

  if (millis() - lastScrollTime > SCROLL_SPEED_MS) {
    lastScrollTime = millis();
    scrollOffset++;
    if (scrollOffset >= w + PADDING) scrollOffset = 0;
  }

  for (int i = 0; i < 2; i++) {
    int16_t textX = x - scrollOffset + (i * (w + PADDING));
    if (textX > x + areaWidth || textX + w < x) continue;
    
    int startChar = 0;
    int16_t drawX = textX;
    
    if (textX < x) {
      startChar = (x - textX) / 6;
      drawX = x;
    }
    
    int numChars = text.length() - startChar;
    if (textX + w > x + areaWidth) numChars -= ((textX + w) - (x + areaWidth)) / 6;
    
    display.setCursor(drawX, y);
    display.print(text.substring(startChar, startChar + numChars));
  }
}

// =================== Logika Animasi =====================
void startAnimation(int animIndex, bool isOneShot) {
  currentAnimationIndex = animIndex;
  currentFrame = animations[animIndex].startFrame;
  isPlayingAnimation = true;

  // Bunyi tiap ganti animasi
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
}

void playNextLoopingAnimation() {
  if (!isPlayingAnimation) {
    // Bakal ngeloop animasi yang lagi aktif aja (ga gonta-ganti otomatis lagi)
    startAnimation(currentAnimationIndex, false); 
  }
}

void handleAnimation() {
  static unsigned long lastFrameTime = 0;
  static unsigned long animationEndTime = 0;
  unsigned long now = millis();

  // 1. Logika Tidur (Idle)
  if (!isSleeping && (now - lastInteractionTime > IDLE_TIMEOUT_MS)) {
    isSleeping = true; 
    int randomIndex = random(0, totalIdlePool); 
    startAnimation(idlePool[randomIndex], true); 
  }

  if (isPlayingAnimation) {
    if (now - lastFrameTime >= ANIMATION_FRAME_DELAY_MS) {
      lastFrameTime = now;
      
      display.clearDisplay(); 
      
      // --- GAMBAR WAJAH DEJI ---
      display.drawBitmap(0, 0, frames[currentFrame], 128, 64, SSD1306_WHITE);
      
      // --- HEADER KIRI (JAM) ---
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      char timeStr[6]; 
      sprintf(timeStr, "%02d:%02d", watch.getHourC(), watch.getMinute());
      display.setCursor(2, 2);
      display.print(timeStr);
      
      // --- HEADER KANAN (NAMA BARU) ---
      // Pakai MANS_DEE tanpa garis bawah (underline)
      // Koordinat X digeser ke 78 biar muat karena teksnya lebih panjang
      display.setCursor(75, 2); 
      display.print("Mans_Dee");
      
      display.display(); // Tampilkan ke OLED
      
      currentFrame++;

      if (currentFrame > animations[currentAnimationIndex].endFrame) {
        isPlayingAnimation = false;
        animationEndTime = now;
        
        if (isSleeping) {
          isSleeping = false; 
          lastInteractionTime = now;
          startAnimation(activeAwakeIndex, false); 
        } else if (currentAnimationIndex >= 7 && currentAnimationIndex <= 10) {
          startAnimation(activeAwakeIndex, false); 
        }
      } 
    } 
  } else {
    if (now - animationEndTime >= ANIMATION_LOOP_DELAY_MS) {
      startAnimation(activeAwakeIndex, false);
    }
  } 
}


// =================== Display Modes ======================
void displayClockDate() {
  display.clearDisplay();

  // Header kiri label
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print("Mans_Dee");

  // Garis header
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  // Jam HH:MM
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", watch.getHourC(), watch.getMinute());
  drawCenteredText(String(timeStr), 28, 2);

  // Tanggal (ID)
  String dateStr = String(dayNames[watch.getDayofWeek()]) + ", " + String(watch.getDay()) + " " + String(monthNames[watch.getMonth()]);
  drawCenteredText(dateStr, 54, 1);

  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

void displayWeather() {
  display.clearDisplay();

  // Header
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print("Mans_Dee");
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  // Ikon cuaca (cerah berawan) di kiri
  display.drawBitmap(8, 18, cuacaCerah_Berawan, 35, 22, SSD1306_WHITE);

  // Suhu & kota di kanan
  Weather w_now = watch.getWeatherAt(0);
  String city = watch.getWeatherCity();

  display.setTextSize(2);
  String t = String(w_now.temp);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(t, 0, 0, &x1, &y1, &w, &h);
  int cursorX = 64 + (64 - w) / 2 - 8;
  display.setCursor(cursorX, 18);
  display.print(t);
  
  int tempCursorX = display.getCursorX();
  display.drawCircle(tempCursorX + 4, 20, 2, SSD1306_WHITE);
  display.setCursor(tempCursorX + 8, 18);
  display.print("C");

  display.setTextSize(1);
  drawCenteredTextInRect(city.substring(0, 12), 64, 64, 42, 1);
  drawCenteredTextInRect("Cerah Berawan", 64, 64, 54, 1);

  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

int parseDistanceToMeters(String distStr) {
  distStr.trim();
  distStr.replace(',', '.');
  float val = distStr.toFloat();
  if (distStr.indexOf("km") != -1) return (int)(val * 1000);
  else if (distStr.indexOf("m") != -1) return (int)val;
  return (int)val;
}

void displayModernNavigation() {
  Navigation nav = watch.getNavigation();
  display.clearDisplay();

  const int ICON_WIDTH = 48;
  const int ICON_HEIGHT = 48;
  const int FOCUS_AREA_X_START = ICON_WIDTH + 6;

  // gambar ikon nav 48x48 di kiri
  for (int y = 0; y < ICON_HEIGHT; y++) {
    for (int x = 0; x < ICON_WIDTH; x++) {
      int byte_index = (y * ICON_WIDTH + x) / 8;  // per-baris, 1-bit packed
      int bit_pos = 7 - (x % 8);
      bool px_on = (nav.icon[byte_index] >> bit_pos) & 0x01;
      if (px_on) display.drawPixel(x + 2, y + 1, SSD1306_WHITE);
    }
  }

  // judul manuver & step (marquee)
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(FOCUS_AREA_X_START, 8);
  display.print(nav.title);

  drawScrollingText(nav.directions, FOCUS_AREA_X_START, 28, SCREEN_WIDTH - FOCUS_AREA_X_START - 2);

  // garis info bawah + jarak & ETA
  display.drawLine(0, 50, SCREEN_WIDTH - 1, 50, SSD1306_WHITE);
  const int colWidth = SCREEN_WIDTH / 2;
  drawCenteredTextInRect(nav.distance, 0, colWidth, 54, 1, false);

  String etaTime = nav.eta;
  int bracketPos = etaTime.indexOf('(');
  if (bracketPos != -1) {
    etaTime = etaTime.substring(0, bracketPos);
    etaTime.trim();
  }
  drawCenteredTextInRect(etaTime, colWidth, colWidth, 54, 1, false);

  // border statis
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

void displayNotificationList() {
  display.clearDisplay();
  String header = "Pesan Masuk (" + String(notificationCount) + "/" + String(MAX_NOTIFICATIONS) + ")";
  drawCenteredText(header, 2, 1);
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  if (notificationCount == 0) {
    drawCenteredText("Tidak Ada Pesan", 32, 1);
  } else {
    int yPos = 16;
    for (int i = 0; i < notificationCount; i++) {
      int index = (latestNotificationIndex - i + MAX_NOTIFICATIONS) % MAX_NOTIFICATIONS;
      Notification notif = notificationHistory[index];

      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setTextWrap(false);

      String titleStr = "[" + String(i + 1) + "] " + notif.title;
      display.setCursor(2, yPos);
      display.print(titleStr.substring(0, 20));
      yPos += 10;

      display.setCursor(8, yPos);
      display.print(notif.message.substring(0, 18));
      yPos += 10;

      if (i < notificationCount - 1 && yPos < 58) {
        for (int j = 4; j < SCREEN_WIDTH - 4; j += 4) display.drawPixel(j, yPos, SSD1306_WHITE);
        yPos += 4;
      }
      if (yPos > 60) break;
    }
  }
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}

void displaySurpriseMode() {
  static int charIndex = 0;
  static unsigned long lastCharTime = 0;
  static bool isDone = false;
  
  // Kita tambahin dua \n (enter) sebelum love biar beneran di bawah banget
  // Dan spasi yang pas buat layar 128px
  String fullMsg = "Mans, makasih ya\nudah berjuang\nsejauh ini. Jangan\nlupa istirahat,\nkarya besarmu\nbutuh energi dari\ndirimu yang sehat.\n\n                <3";
  
  display.clearDisplay();
  
  // 1. LOGIKA NGETIK (Speed 50ms biar lebih sat-set)
  if (!isDone && millis() - lastCharTime > 50) {
    charIndex++;
    lastCharTime = millis();
    
    if (charIndex % 3 == 0 && charIndex > 0) {
      char c = fullMsg[charIndex - 1];
      if (c != ' ' && c != '\n') tone(BUZZER_PIN, 2200, 5); 
    }
    if (charIndex >= fullMsg.length()) isDone = true;
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false); 

  // 2. LOGIKA SCROLL OTOMATIS (SINKRON TIAP BARIS)
  // Kita hitung jumlah '\n' yang udah diketik buat nentuin kapan harus naik
  int lineBreaks = 0;
  for (int i = 0; i < charIndex; i++) {
    if (fullMsg[i] == '\n') lineBreaks++;
  }

  // Kalau baris udah lebih dari 4, kita angkat teksnya 10 pixel tiap baris baru
  int scrollOffset = 0;
  if (lineBreaks >= 4) {
    scrollOffset = (lineBreaks - 3) * 10; 
  }

  int currentY = 22 - scrollOffset;
  display.setCursor(8, currentY);
  
  // 3. CETAK TEKS
  for (int i = 0; i < charIndex; i++) {
    if (fullMsg[i] == '\n') {
      currentY += 10; 
      display.setCursor(8, currentY); 
    } else {
      display.print(fullMsg[i]);
    }
  }

  // 4. HEADER MASKING
  display.fillRect(0, 0, 128, 16, SSD1306_BLACK); 
  display.drawRect(0, 0, 128, 64, SSD1306_WHITE); 
  display.drawLine(0, 15, 128, 15, SSD1306_WHITE); 
  drawCenteredText("DEJI'S MESSAGE", 4, 1);

  display.display();

  // Reset Tap
  if (globalTapCount > 0) {
    charIndex = 0;
    isDone = false;
    globalTapCount = 0;
    tone(BUZZER_PIN, 1500, 30); 
  }
}

// =================== Input (tombol) ======================
void handleButton() {
  static int lastButtonState = LOW;        
  static unsigned long lastDebounceTime = 0;
  static unsigned long buttonDownTime = 0;
  static bool longPressDone = false;
  
  // Gamy hapus 'static' di sini karena kita pakai 'globalTapCount' di paling atas tadi
  static unsigned long lastTapTime = 0;
  const unsigned long MULTI_TAP_TIMEOUT = 400; 

  int reading = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  if (reading != lastButtonState) lastDebounceTime = now;
  lastButtonState = reading;

  if ((now - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
    bool isPressed = (reading == HIGH); 

    if (isPressed && buttonDownTime == 0) {
      buttonDownTime = now;
      longPressDone = false;
    } 
    else if (!isPressed && buttonDownTime != 0) {
      unsigned long pressDuration = now - buttonDownTime;
      
      if (!longPressDone && pressDuration < LONG_PRESS_TIME_MS) {
        // Pakai variabel global biar bisa dibaca mode surprise
        globalTapCount++; 
        lastTapTime = now;
        lastInteractionTime = now; 
        tone(BUZZER_PIN, 2000, 30); 
      }
      buttonDownTime = 0;
    }

    if (isPressed && !longPressDone && (now - buttonDownTime >= LONG_PRESS_TIME_MS)) {
      longPressDone = true;
      globalTapCount = 0; // Reset tap pas ganti mode
      lastInteractionTime = now; 
      
      tone(BUZZER_PIN, 1000, 200); 
      delay(200); 
      noTone(BUZZER_PIN); 

      // GANTI MODE
      if (currentMode == MODE_ANIMATION) currentMode = MODE_CLOCK_DATE;
      else if (currentMode == MODE_CLOCK_DATE) currentMode = MODE_WEATHER;
      else if (currentMode == MODE_WEATHER) currentMode = MODE_NOTIFICATION_LIST;
      else if (currentMode == MODE_NOTIFICATION_LIST) currentMode = MODE_SURPRISE;
      else if (currentMode == MODE_SURPRISE) currentMode = MODE_ANIMATION; 

      lastDisplayedMode = (DisplayMode)-1; 
      isPlayingAnimation = false; 

      display.clearDisplay();
      display.drawRect(10, 20, 108, 24, SSD1306_WHITE); 
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      drawCenteredText("LOADING MODE...", 28, 1);
      display.display();
      
      delay(500); 
      noTone(BUZZER_PIN); 
      globalTapCount = 0;          
      buttonDownTime = 0;    
    }
  }

  // --- EKSEKUSI TAP ---
  if (globalTapCount > 0 && (now - lastTapTime > MULTI_TAP_TIMEOUT)) {
    // Kalau di mode surprise, biarkan displaySurpriseMode yang me-reset globalTapCount
    if (currentMode == MODE_SURPRISE) {
        // Jangan reset di sini, biar dibaca fungsi sebelah
    } 
    else if (currentMode == MODE_ANIMATION) {
      if (isSleeping) {
        isSleeping = false;
        startAnimation(activeAwakeIndex, false);
      } else {
        switch (globalTapCount) {
          case 1:
            activeAwakeIndex = (activeAwakeIndex == 0) ? 1 : 0;
            startAnimation(activeAwakeIndex, false);
            break;
          case 2: startAnimation(7, true); break;
          case 3: startAnimation(8, true); break;
          case 4: startAnimation(9, true); break;
          case 5: startAnimation(10, true); break;
        }
      }
      globalTapCount = 0; // Reset setelah dipake di mode animasi
    } else {
      globalTapCount = 0; // Reset buat mode lain
    }
  }
}


// --- TARUH DI ATAS SEBELUM SETUP ---
void drawBattery(int x, int y, int percentage) {
  display.drawRect(x, y, 20, 10, SSD1306_WHITE);
  display.fillRect(x + 20, y + 3, 2, 4, SSD1306_WHITE);
  int fillWidth = map(percentage, 0, 100, 0, 16);
  if (fillWidth > 0) display.fillRect(x + 2, y + 2, fillWidth, 6, SSD1306_WHITE);
  display.setCursor(x - 25, y + 1);
  display.print(String(percentage) + "%");
}

void drawChargingAnimation(int x, int y) {
  static int chargeLevel = 0;
  static uint32_t lastAnimTime = 0;
  
  if (millis() - lastAnimTime > 200) {
    chargeLevel += 20; 
    if (chargeLevel > 100) chargeLevel = 0;
    lastAnimTime = millis();
  }

  // Gambar rangka baterai
  display.drawRect(x, y, 20, 10, SSD1306_WHITE);
  display.fillRect(x + 20, y + 3, 2, 4, SSD1306_WHITE);
  
  // Gambar isi yang bergerak
  int fillWidth = map(chargeLevel, 0, 100, 0, 16);
  if (fillWidth > 0) display.fillRect(x + 2, y + 2, fillWidth, 6, SSD1306_WHITE);
  
  // ICON PETIR
  display.drawBitmap(x - 12, y, iconPetir, 8, 8, SSD1306_WHITE);
}

void playBootAnimation() {
  // Masukin semua 21 nama variabel dari file .h kamu ke sini
  const unsigned char* frames_deji[] = {
    deji_loadingezgif_frame_001, deji_loadingezgif_frame_002, deji_loadingezgif_frame_003, 
    deji_loadingezgif_frame_004, deji_loadingezgif_frame_005, deji_loadingezgif_frame_006,
    deji_loadingezgif_frame_007, deji_loadingezgif_frame_008, deji_loadingezgif_frame_009,
    deji_loadingezgif_frame_010, deji_loadingezgif_frame_011, deji_loadingezgif_frame_012,
    deji_loadingezgif_frame_013, deji_loadingezgif_frame_014, deji_loadingezgif_frame_015,
    deji_loadingezgif_frame_016, deji_loadingezgif_frame_017, deji_loadingezgif_frame_018,
    deji_loadingezgif_frame_019, deji_loadingezgif_frame_020, deji_loadingezgif_frame_021
  };

  int totalFrames = 21;

  // --- SOUND AWAL: "Brip-brip!" ---
  // Bunyi dua nada cepat pas layar pertama kali nyala
  tone(BUZZER_PIN, 1500, 40);
  delay(60);
  tone(BUZZER_PIN, 2500, 40);

  for (int i = 0; i < totalFrames; i++) {
    display.clearDisplay();
    display.drawBitmap(0, 0, frames_deji[i], 128, 64, SSD1306_WHITE);
    display.display();
    
    // Suara ketukan tipis (clicky) pas loading tengah-tengah
    if (i == 10) tone(BUZZER_PIN, 1800, 20); 
    
    delay(60);
  }

  // --- SOUND FINAL: NADA STEADY ---
  // Nada lembut tapi panjang pas logo DEJI & Kanji lagi freeze
  tone(BUZZER_PIN, 1200, 500); 

  // --- BAGIAN 2: EFEK FREEZE ---
  delay(1500);

  // --- BAGIAN 3: EFEK KEDIP/BLINK ---
  display.invertDisplay(true);
  delay(100);
  display.invertDisplay(false);
  delay(200);
}

// =================== Setup & Loop ========================
void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9); // I2C untuk OLED

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {}
  }

  // 1. Set Clock dulu biar animasinya smooth (nggak patah-patah)
  Wire.setClock(400000);

  // 2. JALANKAN ANIMASI DEJI DI SINI! 
  // Biar user (Mans) langsung liat logo grafiti pas baru nyala
  playBootAnimation();

  // 3. BARU URUS HARDWARE LAINNYA
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); 
  pinMode(BUTTON_PIN, INPUT);

  // 4. KASI SOUND EFFECT SEDIKIT PAS ANIMASI SELESAI
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  // 5. INISIALISASI BERAT (Bluetooth/Watch) Taruh belakangan
  watch.setName("Kazumi27");
  watch.setNotificationCallback(onNotification);
  watch.setConfigurationCallback(configCallback);
  watch.begin();
  
  Serial.println(watch.getAddress());

  // 6. MASUK KE MODE NORMAL (Mata/Eye)
  activeAwakeIndex = 0;
  isSleeping = false;
  lastInteractionTime = millis();
  startAnimation(activeAwakeIndex, false);
}


void loop() {
  watch.loop();
  navActiveFlag = watch.getNavigation().active;

  handleButton();

  // Logika Navigasi Otomatis
  if (navActiveFlag) {
    if (currentMode != MODE_NAVIGATION) {
      modeBeforeNavigation = currentMode;
      currentMode = MODE_NAVIGATION;
    }
  } else if (currentMode == MODE_NAVIGATION) {
    currentMode = modeBeforeNavigation;
  }

  // Cek mana mode yang butuh update terus-menerus
  // Cek mana mode yang butuh update terus-menerus
  bool isDynamicMode = (currentMode == MODE_ANIMATION || 
                        currentMode == MODE_CLOCK_DATE || 
                        currentMode == MODE_WEATHER || 
                        currentMode == MODE_NAVIGATION ||
                        currentMode == MODE_NOTIFICATION_LIST ||
                        currentMode == MODE_SURPRISE); 

  // Gambar ke layar cuma kalau mode ganti atau emang lagi mode dinamis
  if (currentMode != lastDisplayedMode || isDynamicMode) {
    switch (currentMode) {
      case MODE_ANIMATION:         handleAnimation(); break;
      case MODE_CLOCK_DATE:        displayClockDate(); break;
      case MODE_WEATHER:           displayWeather(); break;
      case MODE_NOTIFICATION_LIST: displayNotificationList(); break;
      case MODE_NAVIGATION:        displayModernNavigation(); break;
      case MODE_SURPRISE:          displaySurpriseMode(); break;
    }
    lastDisplayedMode = currentMode; 
  }

  delay(25); 
}