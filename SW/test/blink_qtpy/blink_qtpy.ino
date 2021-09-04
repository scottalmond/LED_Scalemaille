#include <Adafruit_NeoPixel.h>

// create a pixel strand with 1 pixel on PIN_NEOPIXEL
Adafruit_NeoPixel strip(13*5*3*3, A0);
Adafruit_NeoPixel pixels2(1, PIN_NEOPIXEL);
int frameCount=0;

void setup() {
    strip.begin();  // initialize the pixel
    pixels2.begin();  // initialize the pixel
}

void loop() {
    // set the first pixel #0 to red
    
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    //strip.setPixelColor(0, pixels.Color(0, 255, 0));
    // and write the data
    //strip.show();
    frameCount++;
    rainbow(firstPixelHue);
    pixels2.show();


    if(millis()%500<250)
    {
      pixels2.clear();
      pixels2.show();
    }else{
      pixels2.setPixelColor(0, pixels2.Color(255, 0, 0));
      pixels2.show();
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(long firstPixelHue) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
    //strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    strip.setPixelColor(i, frameCount%11==i%11?strip.gamma32(strip.ColorHSV(pixelHue)):0);
  }
  strip.show(); // Update strip with new contents
}
