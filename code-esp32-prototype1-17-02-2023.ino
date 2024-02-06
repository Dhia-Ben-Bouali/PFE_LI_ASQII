#include <WiFi.h>
#include <ESP32Servo.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
//#define WIFI_SSID "Orange-B53E"
//#define WIFI_PASSWORD "1AFYR7QB70J"
#define WIFI_SSID "Adel"
#define WIFI_PASSWORD "11111111"
#define API_KEY "AIzaSyDsMba1SlZqk_uaGMJbutv1VT48SHks93U"
#define DATABASE_URL "djin-2022-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "contact.asqii@gmail.com"
#define USER_PASSWORD "ASQII@2021"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;
Servo myServo,myServo1;
String stf;
char data;
const int IN1 = 26;
const int IN3 = 27;
const int ENA = 2;
const int ENB = 4;
void setup(){
  pinMode(25,INPUT);
  myServo.attach(18, 500, 2400);
  myServo1.attach(19, 500, 2400);
  //myServo.write(180);
  //myServo1.write(0);
  pinMode(33,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  Serial.begin(9500);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
#if defined(ESP8266)
   fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
#endif
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
}
void serv_on(){
    myServo.write(0);
}
void serv_off(){
    myServo.write(180);
}
void serv1_on(){
    myServo1.write(0);
}
void serv1_off(){
    myServo1.write(90);
}
void lock1open(){
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, 1);
  digitalWrite(IN3, 0);
 }
void lock1close()
{
  analogWrite(ENB, 255);
  analogWrite(ENA, 255);
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);
}
  void lock2open()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 1);
}
void lock2close()
{
  analogWrite(ENB, 255);
  analogWrite(ENA, 255);
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);
}
void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
   stf = Firebase.RTDB.getString(&fbdo, F("/test/string")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
   Serial.println(stf);
   FirebaseJson json;
   Serial.println();
   }
data = stf[0];
switch(data){
    case'a':

    if (digitalRead(25)==1){
     digitalWrite(32,HIGH);
   lock1open();
    stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
    }
    break;

    case'b':
      serv1_off();
      lock2close();
   digitalWrite(33,LOW);
   stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
        break;

        case'c':
        if (digitalRead(25)==1){
         digitalWrite(33,HIGH);
        serv1_on();
        lock2open();
    stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
        }
        break;

    case 'd':
    lock1close();
digitalWrite(32,LOW);
    stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
        break;

    case 'e':
    if (digitalRead(25)==1){
      digitalWrite(14,HIGH);
       serv_on();
     stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
    }
      break;
      case 'f':

        serv_off();
        digitalWrite(14,LOW);
         stf="off";
  Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("off")) ? "ok" : fbdo.errorReason().c_str());
      break;
    }
}
