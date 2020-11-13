#include <Adafruit_CircuitPlayground.h>
//it detects if u r slouching or not by measuring angle

#define SLOUCH_ANGLE  10.0
#define SLOUCH_TIME   3000  //this is 3 sec
#define GRAVITY       9.80665
#define RAD2DEG       57.29579
//180/3.1415

float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
uint8_t pixeln = 0;


void setup() {
   Serial.begin(9600);
    CircuitPlayground.begin();
    targetAngle = 0; 
}

void loop() {
  currentAngle = RAD2DEG *asin(-CircuitPlayground.motionZ()/GRAVITY);
  //asin is arcsine. this will give angle in radiance, we have to change it to degrees.

  //Serial.println(currentAngle);


  
  if ( ( CircuitPlayground.leftButton()) || ( CircuitPlayground.rightButton())) {
    // if either is pressed 
    targetAngle = currentAngle;
    
    CircuitPlayground.playTone(900,100);
    delay(100);
    CircuitPlayground.playTone(900,100);
    delay(100);

    }

   if(currentAngle - targetAngle > SLOUCH_ANGLE) {
     if (!slouching){
      CircuitPlayground.clearPixels();
      slouchStartTime = millis();
      slouching = true;
      
      }
    }
   else {
    slouching = false;
    }
  
  if (slouching){
     if (millis()-slouchStartTime > SLOUCH_TIME)
      CircuitPlayground.playTone(800,500);
      CircuitPlayground.setPixelColor(pixeln++, CircuitPlayground.colorWheel(25 * pixeln));

  if (pixeln == 11) {
    pixeln = 0;
    CircuitPlayground.clearPixels();
  }
  delay(10);
    } 
}
