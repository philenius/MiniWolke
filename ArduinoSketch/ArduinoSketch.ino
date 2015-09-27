#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// pin on which the LED ring is connected to the Arduino
#define PIN            5

// amount of LEDs that the ring has
#define NUMPIXELS      12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize the NeoPixel library
  pixels.begin();
}

void loop() {

  int r = random(0,3);
  switch (r) {
    case 0:  pulsateRed(); break;
    case 1:  pulsateGreen(); break;
    case 2:  pulsateBlue(); break;
  }

  for(int i = 0; i < random(1,10); i++) {
    pulsate();
  }
 
  delay(2000);

  for(int i = 0; i < random(0,10); i++) {
    fullSpectrumWipe();
  }

  delay(2000);
  
  randomBlueFlash();
  
  delay(2000);
  
  for(int i = 0; i < random(0,10); i++) {
    pulsateRandomBlue();
  }
  
  for(int i = 0; i < random(0,10); i++) {
    pulsatePink();
  }
  
  delay(2000);
}

void randomBlueFlash()
{
  for(int i = 0; i < 50; i++) {
    int blue = random(0,256);
    int red = random(0,100);
    
    setColorForAll(pixels.Color(red,0,blue));
    delay(random(50,150));
    setColorForAll(pixels.Color(0,0,0));
    delay(random(50,700));
  }
}

// pulsation in pink
void pulsatePink() {
  delay(1000);
  colorWipe(pixels.Color(255,0,154), 25);
  delay(500);
  colorWipe(pixels.Color(0,0,0), 55);
  delay(200);
}

// pulsation in random color
void pulsate() {
  int r = random(0,256);
  int g = random(0,256);
  int b = random(0,256);
  delay(1000);
  colorWipe(pixels.Color(r,g,b), 50);
  delay(100);
  colorWipe(pixels.Color(0,0,0), 55);
  delay(100);
}

// pulsation in random blue with random delay
void pulsateRandomBlue() {
  int wait = random(100,1000);
  int tempo = random(45,55);
  int r = random(0,207);
  int g = random(120,204);
  delay(wait);
  colorWipe(pixels.Color(r,g,224), tempo);
  delay(wait*2);
  colorWipe(pixels.Color(0,0,0), tempo);
  delay(wait);
}

// ##########################################################################################################
// Methods which let the lamp pulsate in ether red(255,0,0), green(0,255,0) or blue(0,0,255) fading to black.
// pulsation in red
void pulsateRed() {
  int wait = random(1,20); 
  for(int i = 0; i < 255; i++) {
    setColorForAll(pixels.Color(i,0,0));
    delay(wait);
  }
  for(int i = 255; i > 0; i--) {
    setColorForAll(pixels.Color(i,0,0));
    delay(wait);
  }
}

// pulsation in blue
void pulsateBlue() {
  int wait = random(1,20); 
  for(int i = 0; i < 255; i++) {
    setColorForAll(pixels.Color(0,0,i));
    delay(wait);
  }
  for(int i = 255; i > 0; i--) {
    setColorForAll(pixels.Color(0,0,i));
    delay(wait);
  }
}

// pulsation in green
void pulsateGreen() {
  int wait = random(1,20); 
  for(int i = 0; i < 255; i++) {
    setColorForAll(pixels.Color(0,i,0));
    delay(wait);
  }
  for(int i = 255; i > 0; i--) {
    setColorForAll(pixels.Color(0,i,0));
    delay(wait);
  }
}
// ##########################################################################################################

// full wipe using the complete spectrum
void fullSpectrumWipe() {
  for(int i = 0; i < 255; i++) {
    setColorForAll(pixels.Color(i,0,0));
    delay(20);
  }
  for(int g = 0; g < 255; g++) {
    colorWipe(pixels.Color(255,g,0),1);
  }
  for(int r = 255; r > 0; r--) {
    colorWipe(pixels.Color(r,255,0),1);  
  }
  for(int b = 0; b < 255; b++) {
    colorWipe(pixels.Color(0,255,b),1);
  }
  for(int g = 255; g > 0; g--) {
    colorWipe(pixels.Color(0,g,255),1);   
  }
  for(int r = 0; r < 255; r++) {
    colorWipe(pixels.Color(r,0,255),1);  
  }
  for(int b = 255; b > 0; b--) {
    colorWipe(pixels.Color(255,0,b),1);
  }
  for(int i = 255; i > 0; i--) {
    setColorForAll(pixels.Color(i,0,0));
    delay(20);
  }
}

// Method which sets the colors of the ring with a given delay between each LED.
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i,c);
    pixels.show();
    delay(wait);
  }
}

// Method which sets all LEDs at the same time to the same color.
void setColorForAll(uint32_t color) {
  for(uint16_t i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i,color);
  }
  pixels.show();  
}
