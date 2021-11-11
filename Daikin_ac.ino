#include "HomeSpan.h" 
#include "DEV_LED.h"        
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Daikin.h>
int pinin1 = 32; //for analog read
int pinin2 = 35; //for analog read
int value1 = 0;
int value2 =0;
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRDaikinESP ac(kIrLed);  // Set the GPIO to be used to sending the message

void setup() {


ac.begin();
 
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LEDs");
  
  new SpanAccessory(); 
  
    new Service::AccessoryInformation(); 
      new Characteristic::Name("LED #1"); 
      new Characteristic::Manufacturer("HomeSpan"); 
      new Characteristic::SerialNumber("123-ABC"); 
      new Characteristic::Model("20mA LED"); 
      new Characteristic::FirmwareRevision("0.9"); 
      new Characteristic::Identify();            
      
    new Service::HAPProtocolInformation();      
      new Characteristic::Version("1.1.0");     
      
    new DEV_LED(5);        // this instantiates a new LED Service.  Where is this defined?  What happpened to Characteristic::On?  Keep 
  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Name("LED #2");    
      new Characteristic::Manufacturer("HomeSpan"); 
      new Characteristic::SerialNumber("123-ABC");  
      new Characteristic::Model("20mA LED");   
      new Characteristic::FirmwareRevision("0.9");  
      new Characteristic::Identify();               
      
    new Service::HAPProtocolInformation();          
      new Characteristic::Version("1.1.0");         

  //  new Service::LightBulb();                    
  //    new Characteristic::On();              
  
    new DEV_LED(18);                                

} // end of setup()

//////////////////////////////////////

void loop(){

 
  if (value1 > 4090)
  {
    Serial.println("Sending...");
  ac.on();
  ac.setPowerful(true);
  ac.setFan(3);
  ac.setMode(kDaikinCool);
  ac.setTemp(23);
  ac.setSwingVertical(true);
  ac.setSwingHorizontal(false);
  
  // Display what we are going to send.
  Serial.println(ac.toString());

  // Now send the IR signal.
#if SEND_DAIKIN
  ac.send();
#endif  // SEND_DAIKIN

  delay(500);
  }
  if (value2 > 4090)
  {
    Serial.println("Sending...");
  ac.off();
  ac.setFan(1);
  ac.setMode(kDaikinCool);
  ac.setTemp(25);
  ac.setSwingVertical(false);
  ac.setSwingHorizontal(false);
  
  // Display what we are going to send.
  Serial.println(ac.toString());

  // Now send the IR signal.
#if SEND_DAIKIN
  ac.send();
#endif  // SEND_DAIKIN

  delay(500);
  }
  homeSpan.poll();
  value1 = analogRead(pinin1);
  Serial.println(value1);
  value2 = analogRead(pinin2);
  Serial.println(value2);
} // end of loop()
