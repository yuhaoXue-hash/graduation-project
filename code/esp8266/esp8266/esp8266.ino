#include <ESP8266WiFi.h>

const char *ip = "192.168.237.152";
const int port = 50000;

const char *ssid = "ESP";
const char *password = "12345678"; 

WiFiClient client; 

void setup()
{
  Serial.begin(9600);
  Serial.println("");

  WiFi.mode(WIFI_STA);    //设置无线终端模式  

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
     delay(1000);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");

  Client_connect();
}

void loop() 
{
  while(client.connected() || client.available())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\n');
      Serial.println(line);  
      client.print(line);
    }  
  }
  
  // put your main code here, to run repeatedly:

}

void Client_connect(void)
{
    Serial.println("Client connecting...");
  
    while(!client.connect(ip, port))
    {
      delay(5000);
      Serial.println("Client connect fail, ");  
    }

    Serial.println("Client connect success");
}
