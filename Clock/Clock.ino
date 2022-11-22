#include <LCD_I2C.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TinyXML.h>

const char *ssid     = "Maison";
const char *password = "01020304050607080908070605";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 3600);
LCD_I2C lcd(0x27, 16, 2);

int WaitForMeteo = 0;
int MaxMeteto = 180;

WiFiClient client;
void setup()
{
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD_I2C) from calling Wire.begin()
  Serial.begin(115200);

  lcd.backlight();
  lcd.setCursor(1, 1);
  lcd.print("Connecting ...");

  Serial.println("Connecting");
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print ( "." );
  }

  timeClient.begin();
}

String requestMeteo(){
  //token 4b342b5ebe3c33b3e670fc324d4dee3ee8cc8be65f430fdaceb098e1c95f625a
  //67482
  //request https://api.meteo-concept.com/api/forecast/daily?token=4b342b5ebe3c33b3e670fc324d4dee3ee8cc8be65f430fdaceb098e1c95f625a&insee=67482


}

void loop()
{
  if(WaitForMeteo >= MaxMeteto){
    WaitForMeteo = 0;
    //request meteo
  }else{
    WaitForMeteo += 1;
  }
  
  timeClient.update();
  lcd.setCursor(1, 1);
  lcd.clear();

  lcd.print(timeClient.getFormattedTime());
  Serial.println(timeClient.getFormattedTime());
  Serial.print("test");

  lcd.backlight();
  delay(1000);
}
