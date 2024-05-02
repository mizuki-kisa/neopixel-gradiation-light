#include <Adafruit_NeoPixel.h>

#define PIN        8  // NeoPixelリングに接続したGPIOピン番号
#define NUMPIXELS 8  // NeoPixelリングのLEDの数
#define DELAYVAL 3000 // グラデーションの更新間隔（ミリ秒）

// NeoPixelのインスタンスを作成
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // NeoPixelの初期化
}

void loop() {
  // 色 #008b8b から #ff1493 へのグラデーション
  colorWipe(pixels.Color(0, 139, 139), pixels.Color(255, 20, 147), DELAYVAL); // シアンからピンクへ
  // 色 #ff1493 から #008b8b へのグラデーション
  colorWipe(pixels.Color(255, 20, 147), pixels.Color(0, 139, 139), DELAYVAL); // ピンクからシアンへ
}

// 指定された2色間でグラデーションを行う関数
void colorWipe(uint32_t color1, uint32_t color2, int wait) {
  for (int j = 0; j < 256; j++) { // グラデーションのステップ数
    for(int i = 0; i < NUMPIXELS; i++) {
      uint8_t r = (((color1 >> 16) & 255) * (255 - j) + ((color2 >> 16) & 255) * j) / 255;
      uint8_t g = (((color1 >> 8) & 255) * (255 - j) + ((color2 >> 8) & 255) * j) / 255;
      uint8_t b = ((color1 & 255) * (255 - j) + (color2 & 255) * j) / 255;
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    pixels.show();
    delay(wait / 256); // 総待ち時間を256ステップに分割
  }
}

