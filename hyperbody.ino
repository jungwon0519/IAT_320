#include <Adafruit_CircuitPlayground.h>

float value;
uint8_t pixeln = 0;

int preset =0;
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

}

void loop() {
  value = CircuitPlayground.mic.soundPressureLevel(100);
  Serial.print("Sound Sensor SPL: ");
  Serial.println(value);
  int presets[3][2][3]={
 {{random(256),random(256),random(256)},{random(256),random(256),random(256)}},
  {{random(256),random(256),random(256)},{random(256),random(256),random(256)}},
   {{random(256),random(256),random(256)},{random(256),random(256),random(256)}}
  };
  
  if (value > 80){
  float acc =abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
  if (acc > 10){
  preset = rand() % 3;
}

  for (int i=0; i<10;i++){
    CircuitPlayground.setPixelColor(
    i,presets[preset][i%2][0],presets[preset][i%2][1],presets[preset][i%2][2]);
  }
  CircuitPlayground.clearPixels();
  delay(100);
    }

 else{
     CircuitPlayground.setPixelColor(pixeln++, CircuitPlayground.colorWheel(25 * pixeln));
       delay(2000);
       if (pixeln == 10) {
       pixeln = 0;
       CircuitPlayground.clearPixels();
  }
    }
delay(100);
}
