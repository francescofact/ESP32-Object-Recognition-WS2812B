/**
 * Object Recognition + WS2812B ringlight manager
 * For Object Recognition it uses Edge Impulse FOMO model.
 * 
 * BE SURE TO SET "TOOLS > CORE DEBUG LEVEL = INFO"
 * to turn on debug messages
 */

//#include <your-fomo-project_inferencing.h>
//#include <eloquent_esp32cam.h>
//#include <eloquent_esp32cam/edgeimpulse/fomo.h>
#include <Adafruit_NeoPixel.h>

#define PIN_WS2812B  2
#define NUM_PIXELS  45
Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

//using eloq::camera;
//using eloq::ei::fomo;

void setup() {
    delay(3000);
    Serial.begin(115200);

    /*
    // camera settings
    camera.pinout.aithinker();
    camera.brownout.disable();
    // NON-PSRAM FOMO only works on 96x96 (yolo) RGB565 images
    camera.resolution.yolo();
    camera.pixformat.rgb565();

    // init camera
    while (!camera.begin().isOk())
        Serial.println(camera.exception.toString());

    Serial.println("Camera OK");
    Serial.println("Put object in front of camera");
    */
    WS2812B.begin();
    Serial.println("WS Initialized");
    WS2812B.setBrightness(20);
}

void loop() {
  while(true){
    WS2812B.fill(WS2812B.Color(255,255,255), 0, 45);
    WS2812B.show();
    delay(5000);
    WS2812B.clear();
    for (int i=0;i<45;i++){
      float hue = i * 360.0 / 45;
      byte r, g, b;
      hsvToRgb(hue, 1.0, 1.0, &r, &g, &b);
      WS2812B.setPixelColor(i, WS2812B.Color(r,g,b));
      WS2812B.show();
      delay(800);
    }
  }
}

/*
void loop_object_recognition(){
    // capture picture
    if (!camera.capture().isOk()) {
        Serial.println(camera.exception.toString());
        return;
    }

    // run FOMO
    if (!fomo.run().isOk()) {
      Serial.println(fomo.exception.toString());
      return;
    }

    // how many objects were found?
    Serial.printf(
      "Found %d object(s) in %dms", 
      fomo.count(),
      fomo.benchmark.millis()
    );

    // if no object is detected, return
    if (!fomo.foundAnyObject())
      return;

    // if you expect to find a single object, use fomo.first
    Serial.printf(
      "Found %s at (x = %d, y = %d) (size %d x %d). "
      "Proba is %.2f",
      fomo.first.label,
      fomo.first.x,
      fomo.first.y,
      fomo.first.width,
      fomo.first.height,
      fomo.first.proba
    );

    // if you expect to find many objects, use fomo.forEach
    if (fomo.count() > 1) {
      fomo.forEach([](int i, bbox_t bbox) {
        Serial.printf(
          "#%d) Found %s at (x = %d, y = %d) (size %d x %d). "
          "Proba is %.2f",
          i + 1,
          bbox.label,
          bbox.x,
          bbox.y,
          bbox.width,
          bbox.height,
          bbox.proba
        );
      });
    }
}
*/

void hsvToRgb(float h, float s, float v, byte* r, byte* g, byte* b) {
  float c = v * s;
  float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
  float m = v - c;
  float r1, g1, b1;

  if (h < 60) {
    r1 = c; g1 = x; b1 = 0;
  } else if (h < 120) {
    r1 = x; g1 = c; b1 = 0;
  } else if (h < 180) {
    r1 = 0; g1 = c; b1 = x;
  } else if (h < 240) {
    r1 = 0; g1 = x; b1 = c;
  } else if (h < 300) {
    r1 = x; g1 = 0; b1 = c;
  } else {
    r1 = c; g1 = 0; b1 = x;
  }

  *r = (r1 + m) * 255;
  *g = (g1 + m) * 255;
  *b = (b1 + m) * 255;
}