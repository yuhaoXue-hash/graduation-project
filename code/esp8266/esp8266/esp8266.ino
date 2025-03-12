#include <ESP8266WiFi.h>

const char *ip = "192.168.74.152";
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
  if(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\n');
      Serial.println(line);  
      client.print(line);
    }  
  }
  else
  {
    Client_connect();
  }
  
  if(Serial.available())
  {
    String msg = Serial.readStringUntil('\n');
    client.print(msg);  
  }
}

void Client_connect(void)
{
    int i = 0; 
    Serial.println("Client connecting...");
      
  
    while(!client.connect(ip, port))
    {
      i++;
      if(i == 3)
      {
        Serial.println("Not connected, reconnecting...");  
        i = 0;
      }
    }

    Serial.println("Client connect success");
}
