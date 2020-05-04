/**
 * Lib name ::  ESP8266_SSD1306
 *              WebSocketsClient
 */

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "AdafruitIO_WiFi.h"
#include <Wire.h> // Only needed for Arduino 1.6.5 and earlier

#define SSD1306 ;

/* OLED 0.95 inc 128 x 64 */

#include <SSD1306Wire.h> // legacy include: `#include "SSD1306.h"

SSD1306Wire display(0x3c, D3, D5);

// My XBMP
#include <xbmp.h>
#include <show.h>

#define IO_USERNAME "Sonezakk"
#define IO_KEY "aio_BsPM83gWF77Y0G6R0DXXpDfLIIel"
#define ssid "projectsensor" // SSID of your home WiFi
#define password "0910345985"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, password);
AdafruitIO_Feed *PH = io.feed("PH");
AdafruitIO_Feed *DO = io.feed("DO");
AdafruitIO_Feed *TEMP = io.feed("TEMP");

int read_pin = A0;
int calibate = 0;

/*wifi*/
byte ledPin = 2;
// char ssid[] = "WSNCOM";   // SSID of your home WiFi
// char pass[] = "1q2w3e4r"; // password of your home WiFi
// char ssid[] = "Tonsonza";   // SSID of your home WiFi
// char pass[] = "0910345985";
int keyIndex = 0; // your network key Index number (needed only for WEP)
WiFiClient client;

//millis()
unsigned long last_time0 = 0;
unsigned long last_time1 = 0;
unsigned long last_time2 = 0;
unsigned long last_time3 = 0;

void setup()
{

  Serial.begin(74880);
  Serial.println("Booting");

  // setup pin

  // WiFiManager wifiManager;

  // // wifiManager.resetSettings();  // ใช้สำหรับล้าง config wifi manager ใหม่
  // wifiManager.setConfigPortalTimeout(180);
  // wifiManager.autoConnect("myesp8266");

  display.init();
  display.flipScreenVertically();
  display.setContrast(255);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(10);
    Serial.println("....");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  digitalWrite(LedWifi, (WiFi.status() == WL_CONNECTED) ? LOW : HIGH);
  LINE.setToken(LINE_TOKEN);
  ThingSpeak.begin(client);
  Blynk.begin(auth, ssid, password);

  //timer.setInterval(1000L, onoffsensor); //on-off  1s on app //
  sensor.begin();
}

void loop()
{
  if ((millis() - last_time0) >= 1000)
  {
    last_time0 = millis();
    Blynk.run();
    timer.run();
  }
  if ((millis() - last_time1) >= 10000)
  {
    last_time1 = millis();
    // displayLogo2(); // DO
    displayLogo(); //PH
    delay(2000);
  }
  // DO AND TEMP//
  // if ((millis() - last_time2) >= 3000)
  // {

  //   last_time2 = millis();
  //   displayCTsenser1();
  //   serialprintf("DO", sensorDo());
  //   serialprintf("Temp", sensorTemp());
  //   send_blynk1();
  // }

  // PH//
  if ((millis() - last_time2) >= 3000)
  {

    last_time2 = millis();
    displayCTsenser();

    serialprintf("PH", sensorPh());

    send_blynk();
  }
  if ((millis() - last_time3) >= 300000)
  {

    last_time3 = millis();
    senddata_thingspeak();
    // senddata_thingspeak1();
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  }

  //   for (int i = 0; i <=5 ; i++)
  //   {
  //     /* code */

  //     showph();
  //     delay(1000);
  //   }
  // }
}