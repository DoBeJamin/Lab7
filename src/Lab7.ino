
#include <env.h>


#include <blynk.h>
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#define TEMPERATURE A5

int timer = 0;

void setup()
{


  pinMode(TEMPERATURE, INPUT);

  //setup
  Blynk.begin(BLYNK_AUTH_TOKEN);
  display.setup();
  Serial.begin(9600);

}

void loop()
{

  // update display and blynk
  display.loop();
  Blynk.run();



  if (display.pressedA()) {
    //notify blynk
    Blynk.logEvent("buttona", "panic button A has been pressed"); 
    Serial.print("alert"); //temporary alery because I ran out of events 

    //displays "push sent" message and sets timer
    format_display();
    display.println("Push Sent");
    display.display();
    timer = 20000;

  } else if (!timer) {

    //calculate temperatures
    uint64_t reading = analogRead(A5);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature_celcius = (voltage - 0.5) * 100;
    double temperature_fahrenheit = (temperature_celcius * 9.0 / 5.0) + 32.0;

    //format screen and text
    format_display();
    display.println("TEMPERATURE");
    display.print(temperature_celcius);
    display.print("C : ");
    display.print(temperature_fahrenheit);
    display.print("F");

    //display screen
    display.display();

    //Blynk.run();
    Blynk.virtualWrite(V0, temperature_fahrenheit);
    Blynk.virtualWrite(V1, temperature_celcius);
  }
  //countdown before switching back to temperature displaying
  if (timer > 0) {
    timer--;
  }
}

void format_display () {
  //sets up basic formatting for when using the display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.setCursor(0,0);
}



