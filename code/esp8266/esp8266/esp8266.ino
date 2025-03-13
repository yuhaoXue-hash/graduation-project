#include <ESP8266WiFi.h>

<<<<<<< HEAD
const char *ip = "192.168.74.152";
=======
const char *ip = "192.168.237.152";
>>>>>>> 11069fbe802405e2fdc63b5446eda74d191972d6
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
<<<<<<< HEAD
  if(client.connected())
=======
  while(client.connected() || client.available())
>>>>>>> 11069fbe802405e2fdc63b5446eda74d191972d6
  {
    if(client.available())
    {
      String line = client.readStringUntil('\n');
      Serial.println(line);  
      client.print(line);
    }  
  }
<<<<<<< HEAD
  else
  {
    Client_connect();
  }
  
  if(Serial.available())
  {
    String msg = Serial.readStringUntil('\n');
    client.print(msg);  
  }
=======
  
  // put your main code here, to run repeatedly:

>>>>>>> 11069fbe802405e2fdc63b5446eda74d191972d6
}

void Client_connect(void)
{
<<<<<<< HEAD
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
=======
    Serial.println("Client connecting...");
  
    while(!client.connect(ip, port))
    {
      delay(5000);
      Serial.println("Client connect fail, ");  
>>>>>>> 11069fbe802405e2fdc63b5446eda74d191972d6
    }

    Serial.println("Client connect success");
}
