#include <SPI.h>
#include <Ethernet.h>

#include <MD5.h>

#include <dht.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

dht DHT;

#define DHT11_PIN 7
//int trigPin = 9;
//int echoPin = 10;
//int ledPin = 13;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;
IPAddress ip(192, 168, 0, 132);
//char host[] = "184.160.214.146"; 
char host[] = "192.168.0.188"; 

long duration;
int distance;
int ledCounter = 0;

void setup(){
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600); // Starts the serial communication
  lcd.begin(16, 2);
  
}

void loop()
{

  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print((int)DHT.temperature);
  lcd.print((char)223);
  lcd.print("C    ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print((int)DHT.humidity);
  lcd.print("%   ");
  //lcd.setCursor(0,1);
  //lcd.print("D: ");
  //lcd.print(distance);
  //lcd.print("cm        ");

  sendToServer((int)DHT.temperature, (int)DHT.humidity);

  delay(2000);
}

void sendToServer(int temp2, int hum2){

  
  String temp = "temp=";
  String hum = "hum=";
  String hash2 = "hash=";

  int temp3 = temp2;
  char num[5];
  itoa(temp3, num, 10);
  
  unsigned char* hash=MD5::make_hash(num);
  char *md5str = MD5::make_digest(hash, 16);
  
  int lenght = (temp.length() + (floor(log10(abs(temp2))) + 1) + hum.length() + (floor(log10(abs(temp2))) + 1) + hash2.length() + 1 + 32);

  Serial.println("---------------------------------------");
  //Serial.println("Initialize Ethernet with DHCP:");
  Ethernet.begin(mac, ip);
  Serial.print("Assigned IP: ");
  Serial.println(Ethernet.localIP());
  delay(2000);
  Serial.println("connecting...");


  
  
  if (client.connect(host,80))
    {                                 
    //Serial.println("Sending to Server: ");                   
    client.println("POST /test.php HTTP/1.1");           
    //Serial.println("GET /test.php HTTP/1.1 ");           
    client.print("Host: ");
    client.println(host);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println("User-Agent: Arduino/1.0");
    client.print("Content-Length: ");
    client.println(lenght+1);
    client.println();
    client.print(temp);
    client.print(temp2);
    client.print("&");
    client.print(hum);
    client.print(hum2);
    client.print("&");
    client.print(hash2);
    client.println(md5str);
    
      
    Serial.println("Sending to Server: ");                   
    Serial.println("POST /test.php HTTP/1.1");           
    Serial.print("Host: ");
    Serial.println(host);
    Serial.println("Content-Type: application/x-www-form-urlencoded");
    Serial.println("Connection: close");
    Serial.println("User-Agent: Arduino/1.0");
    Serial.print("Content-Length: ");
    Serial.println(lenght+1);
    Serial.println();
    Serial.print(temp);
    Serial.print(temp2);
    Serial.print("&");
    Serial.print(hum);
    Serial.print(hum2);
    Serial.print("&");
    Serial.print(hash2);
    Serial.println(md5str); 
    }
    else
    {
    Serial.println("Cannot connect to Server");               
    }

    delay(500);

    while(client.available()) {
    char c = client.read();
    Serial.print(c);
    }

    if (!client.connected())
    {
    Serial.println("disconnecting.");
    client.stop();
    }
}
