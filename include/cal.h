//  #include <time.h>
#include <Arduino.h>
#include <OneWire.h>
#include <DS18B20.h>
#include "ThingSpeak.h"
#include <TridentTD_LineNotify.h>
#include <BlynkSimpleEsp8266.h>   // BLYNK
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>


// char auth[] = "JX0m0y_m5FomW9eEFnhhZK7pTfNlA8L9";
//thingspeak
// unsigned long myChannelNumber = 914246;
// const char *myWriteAPIKey = "H9JOOZ14XZR40QEG";
// const char *server = "api.thingspeak.com";

//line
#define LINE_TOKEN "xnirEr9FSMfvD2QO6D1oNU7ZibGFkc9GphXjq4Kyeza"
// #define LINE_TOKEN "wLMNKSY3Vvkv8AbIE6K6bKm7Yx2y2KfRA3JdJUPqzwp"

WidgetLED led(V3);
WidgetLED ledlink(V7);
BlynkTimer timer;

//firebase//

/*สายไฟ*/
#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

float sensorTemp();
String timenows();
String daynows();




// oxygen//
const float SaturationValueTab[41] PROGMEM = {
    //saturation dissolved oxygen concentrations at various temperatures
    14.46,
    14.22,
    13.82,
    13.44,
    13.09,
    12.74,
    12.42,
    12.11,
    11.81,
    11.53,
    11.26,
    11.01,
    10.77,
    10.53,
    10.30,
    10.08,
    9.86,
    9.66,
    9.46,
    9.27,
    9.08,
    8.90,
    8.73,
    8.57,
    8.41,
    8.25,
    8.11,
    7.96,
    7.82,
    7.69,
    7.56,
    7.43,
    7.30,
    7.18,
    7.07,
    6.95,
    6.84,
    6.73,
    6.63,
    6.53,
    6.41,
};

float sensorPh()
{
   int  sensorValueph =0,avg_sensorph ; 
  // float a = analogRead(read_pin);
  for(int i=0;i<300;i++)
  {
      sensorValueph +=analogRead(A0);
  }
  avg_sensorph=  sensorValueph/300;

  float Ph = ( avg_sensorph * 0.0254) -9.8523;
  return Ph;
}
float sensorDo()
{

  int sensorValue = 0, avg_sensor = 0;
  // int  sensorValue = analogRead(A0);
  for (int i = 0; i < 300; i++) /*หาค่า เฉลี่ยของการอ่าน analog */
  {
    sensorValue += analogRead(A0);
  }
  avg_sensor = sensorValue / 300;
  // Serial.println("SensorValue : " + (String)sensorValue + "avgsensor : " + (String)avg_sensor);

  float doValue = 0.0;
  float temp = sensorTemp() + 0.5;
  //float Pr = SaturationValueTab[0];

  doValue = pgm_read_float(&SaturationValueTab[0] + (int)temp);
  float volts = (3000 * ((float)avg_sensor / 1023));
  float Do = (doValue * volts) / 1127.6;

  // Serial.println("temp : = " + (String)temp);
  // Serial.println("analogreadDo : " + (String)avg_sensor + " DO : " + (String)Do);
  // Serial.println("volt : " + (String)volts);

  // ThingSpeak.setField(2,Do);

  return Do;
}

float sensorTemp()
{
  float temp;
  sensor.requestTemperatures();
  temp = sensor.getTempC();
  return temp;
}

void senddata_thingspeak1()
{

  LINE.notify("DO:"+ (String)sensorDo()+ "Temp :" + (String)sensorTemp());
}
void senddata_thingspeak()
{
  LINE.notify("PH:"+ (String)sensorPh());
}
void send_blynk1()
{
  char tempBlynk[16];
  char DoBlynk[16];
  dtostrf(sensorTemp(), 2, 2, tempBlynk);
  Blynk.virtualWrite(V2, tempBlynk);
  dtostrf(sensorDo(), 2, 2, DoBlynk);
  Blynk.virtualWrite(V1, DoBlynk);
}
void send_blynk()
{
  
  char PhBlynk[16];
  dtostrf(sensorPh(), 2, 2,PhBlynk);
  Blynk.virtualWrite(V0,PhBlynk);

}

void onoffsensor()
{
  if (ledlink.getValue())
  {
    ledlink.off();
  }
  else
  {
    ledlink.on();
  }
}
void serialprintf(String type, float data)
{
  Serial.println(type +" sensor : " + (String)data);
  
}


// /////// ควบคุม //////////////// 
// void controlmoter(int status)
// {
//   statusmorter = status;
//   digitalWrite(relayD0, status);
//   serialprintf("morter status > " + String(status));

// }

// void moterdelay(float data, float max, float min)     // data = DO , data>= max = stop , data <= min  = start ,
// {
//   if (data >= max)
//   {
//     controlmoter(0);
//   
//     LINE.notify("ปั้มหยุดทำงาน");

//   }
//   if (data <= min)
//   {
//     controlmoter(1);
//  
//     LINE.notify("ปั้มกำลังทำงาน");
 
//   }
// }