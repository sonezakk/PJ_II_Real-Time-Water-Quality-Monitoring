#include<cal.h>
// Global val
int step = 1;
int LedWifi = D4;

int getBarsSignal(long rssi)
{
  // 5. High quality: 90% ~= -55db
  // 4. Good quality: 75% ~= -65db
  // 3. Medium quality: 50% ~= -75db
  // 2. Low quality: 30% ~= -85db
  // 1. Unusable quality: 8% ~= -96db
  // 0. No signal
  int bars;

  if (rssi > -55)
  {
    bars = 5;
  }
  else if (rssi < -55 & rssi > -65)
  {
    bars = 4;
  }
  else if (rssi < -65 & rssi > -75)
  {
    bars = 3;
  }
  else if (rssi < -75 & rssi > -85)
  {
    bars = 2;
  }
  else if (rssi < -85 & rssi > -96)
  {
    bars = 1;
  }
  else
  {
    bars = 0;
  }
  return bars;
}

void displayWifiSignal(int x = 117, int y = 10, boolean show = true)
{
  long rssi = WiFi.RSSI();
  int bars = getBarsSignal(rssi); 

  //Serial.println("Wifi status : " + WiFi.status());

  for (int b = 0; b <= bars; b++)
  {
    // display.fillRect(59 + (b*5),33 - (b*5),3,b*5,WHITE);
    display.fillRect(x + (b * 2), y - (b * 2), 1, b * 2); // ( x, x, ความกว้างของขีด, ความสูงของขีด )
  }
  if (show)
    display.display();
}



void displayCTsenser1()
{
  display.clear();

  display.drawLine(0, 0, 127 ,0);    //x,y,x,y
  display.drawLine(0, 63, 127, 63);
  display.drawLine(25, 21, 25, 63);
  display.drawLine(0, 21, 127, 21);

  // หัวตาราง
  display.setFont(ArialMT_Plain_10);
  display.drawString(20, 6, " DATA SENSOR ");


//   // ข้อความในตาราง
  display.drawString(2, 25, " DO ");
  display.drawString(65, 25, (String)sensorDo());

   display.drawString(2, 38, " T ");
   display.drawString(65, 38, (String)sensorTemp());

   display.drawString(2, 50, " IP ");
   display.drawString(40, 50, WiFi.localIP().toString());

    displayWifiSignal(116,15);
  display.display();
}

void displayCTsenser()
{
  display.clear();

  display.drawLine(0, 0, 127 ,0);    //x,y,x,y
  display.drawLine(0, 63, 127, 63);
  display.drawLine(25, 21, 25, 63);
  display.drawLine(0, 21, 127, 21);

  // หัวตาราง
  display.setFont(ArialMT_Plain_10);
  display.drawString(20, 6, " DATA SENSOR ");


//   // ข้อความในตาราง
  display.drawString(2, 25, " PH  ");
  display.drawString(65, 25, (String)sensorPh());

  //  display.drawString(2, 38, " T ");
  //  display.drawString(65, 38, (String)sensorTemp());

   display.drawString(2, 50, " IP ");
   display.drawString(40, 50, WiFi.localIP().toString());

    displayWifiSignal(116,15);
  display.display();
}

void displayLogo() //PH SENSOR
{
  display.clear();
  display.drawXbm(0, 0, LOGO_DO_width, LOGO_DO_height, LOGO_PH_bits);
  display.setFont(ArialMT_Plain_10);
  // display.drawString(10, 50, WiFi.localIP().toString());

  display.display();
}
 
void displayLogo2()   //DO SENSOR
{
  display.clear();
  display.drawXbm(0, 0, LOGO_DO_width, LOGO_DO_height, LOGO_DO_bits);
  display.setFont(ArialMT_Plain_10);
  // display.drawString(10, 50, WiFi.localIP().toString());

  display.display();
}
