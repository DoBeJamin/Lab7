/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Lab7/src/Lab7.ino"

#include <env.h>


#include <blynk.h>
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 8 "c:/Users/benja/OneDrive/Desktop/visualStudioCode/summerIOT/Lab7/src/Lab7.ino"
SYSTEM_THREAD(ENABLED);


OledWingAdafruit display;

#define TEMPERATURE A5

void setup()
{

  pinMode(TEMPERATURE, INPUT);



  delay(5000); // Allow board to settle
  Blynk.begin(BLYNK_AUTH_TOKEN);


}

void loop()
{


  // prevents epilepsy
  //delay(5000);

  //format screen 
	display.loop();  
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
 
  //calculate temperatures
  uint64_t reading = analogRead(A5);
  double voltage = (reading * 3.3) / 4095.0;
  double temperature_celcius = (voltage - 0.5) * 100;
  double temperature_fahrenheit = (temperature_celcius * 9.0 / 5.0) + 32.0;

  //format Text
  display.println("TEMPERATURE");
  display.print(temperature_celcius);
  display.print("C : ");
  display.print(temperature_fahrenheit);
  display.print("F");

  //sends to display
  display.display();


  Blynk.run();
  Blynk.virtualWrite(V0, temperature_fahrenheit);
  Blynk.virtualWrite(V1, temperature_celcius);

  if (display.pressedA()) {
    Blynk.logEvent("buttona", "panic button A has been pressed");

  }
}










