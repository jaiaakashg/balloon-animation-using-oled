#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int numBalloons = 5;
int balloonX[numBalloons];
int balloonY[numBalloons];
int balloonSpeed[numBalloons];
int balloonSize[numBalloons];

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  randomSeed(analogRead(0));
  for (int i = 0; i < numBalloons; i++) {
    balloonX[i] = random(0, SCREEN_WIDTH);
    balloonY[i] = random(SCREEN_HEIGHT, SCREEN_HEIGHT + 20);
    balloonSpeed[i] = random(1, 4);
    balloonSize[i] = random(5, 11);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  for (int i = 0; i < numBalloons; i++) {
    display.fillCircle(balloonX[i], balloonY[i], balloonSize[i], SSD1306_WHITE);
    display.drawLine(balloonX[i], balloonY[i] + balloonSize[i], balloonX[i], balloonY[i] + balloonSize[i] + 10, SSD1306_WHITE);

    balloonY[i] -= balloonSpeed[i];
    if (balloonY[i] < -balloonSize[i]) {
      balloonX[i] = random(0, SCREEN_WIDTH);
      balloonY[i] = SCREEN_HEIGHT + balloonSize[i];
      balloonSpeed[i] = random(1, 4);
      balloonSize[i] = random(5, 11);
    }
  }

  display.display();
  delay(100);
}

