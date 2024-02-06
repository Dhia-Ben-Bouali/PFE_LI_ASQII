#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
//#include <Adafruit_Fingerprint.h>
#define PCA9685_ADDRESS 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);
/*#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;*/
const int avant = 2400; 
const int arriere = 544;
const int stop = 1500;
const int pin_fin_de_course_2 = 5;
const int pin_fin_de_course_1 = 4;
const int pin_fin_de_course_3 = 6;
const int pin_fin_de_course_4 = 7;
const int pin_fin_de_course_5 = 8;
/****************************************************************** Setup start ********************************************************************************************************/
void setup() {
  Serial.begin(9600);
/*while (!Serial);  
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

    finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  Serial.println("Setup fingerprint done");*/
  pwm.begin();
  pwm.setPWMFreq(50);
  pinMode(pin_fin_de_course_1, INPUT_PULLUP);
  pinMode(pin_fin_de_course_2, INPUT_PULLUP);
  pinMode(pin_fin_de_course_3, INPUT_PULLUP);
  pinMode(pin_fin_de_course_4, INPUT_PULLUP);
  pinMode(pin_fin_de_course_5, INPUT_PULLUP);
  int full_time = 7000;
  full_close_secure();
  Serial.println("setup done");
}
/****************************************************************** Setup end ********************************************************************************************************/
/****************************************************************** loop  end ********************************************************************************************************/
void loop() {
  Serial.println("loop");
  Serial.println("waiting QT data");
  int etat_capteur_1 = digitalRead(pin_fin_de_course_1);
  int etat_capteur_2 = digitalRead(pin_fin_de_course_2);
  int full_time = 6000;
    if (Serial.available() > 0) {
      String QT_message;
      Serial.println(QT_message = Serial.readStringUntil('\n'));
      String tiroir, divs, lvl;
      int tiroir_cal;
      int divs_cal;
      int lvl_cal;
      if (QT_message.indexOf("/") >= 0){
        splitString(QT_message, tiroir, divs, lvl);
        tiroir_cal = tiroir.toInt();
        divs_cal = divs.toInt();
        lvl_cal = lvl.toInt();
        Serial.println(divs_cal);
        Serial.println(lvl_cal);
        Serial.println(tiroir_cal);
      }
/*********************************************************************************************************************************************************************************/
       /*if(QT_message =="en"){
        SoftwareSerial mySerial(2, 3);
        Serial.println("Ready to enroll a fingerprint!");
        Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
        id = readnumber();
        if (id == 0) {// ID #0 not allowed, try again!
          return;
        }
        divs_cal = 2;
        lvl_cal = 2;
        Serial.println(divs_cal);
        Serial.println(lvl_cal);
        Serial.print("Enrolling ID #");
        Serial.println(id);
        
        while (!  getFingerprintEnroll() );
      }*/
/*********************************************************************************************************************************************************************************/        
      if(QT_message =="on"){
        Serial.println("full open ");
        full_open(tiroir_cal);
        Serial.println("On Done");
      }
/*********************************************************************************************************************************************************************************/        
      else if(QT_message == "off"){
        Serial.println("full close default");
        full_close_secure();
        Serial.println("Off Done");
      } 
/*********************************************************************************************************************************************************************************/ 
      /*else if(QT_message =="isin"){
        SoftwareSerial mySerial(2, 3);
        getFingerprintID();
        delay(50);
      }*/
/*********************************************************************************************************************************************************************************/         
      else if(divs_cal*lvl_cal == 0){
        Serial.println("default");
        Serial.println(tiroir_cal);
        full_close(tiroir_cal);
      }
/*********************************************************************************************************************************************************************************/           
      else{
        int result = calculateValue(full_time, divs_cal , lvl_cal );
        Serial.println("tiroir: " + String(tiroir) + " divs: " + String(divs) + " lvl: " + String(lvl) + " Going: " + String(result) );
        pwm.writeMicroseconds(tiroir_cal, stop);
        delay(3000);
        pwm.writeMicroseconds(tiroir_cal, avant);
        Serial.println(result);
        delay(result);
        pwm.writeMicroseconds(tiroir_cal, stop);
        delay(1000);
      }
 /**********************************************************************************************************************************************************************************/      
    }
}
/************************************************************************************** loop end ************************************************************************************/
/********************************************************************************* funtions start ***********************************************************************************/

void splitString(String inputString, String& var1, String& var2, String& var3) {
    int slash1 = inputString.indexOf('/'); // find the position of the first slash
    int slash2 = inputString.lastIndexOf('/'); // find the position of the last slash
    var1 = inputString.substring(0, slash1); // extract the first variable
    var2 = inputString.substring(slash1+1, slash2); // extract the second variable
    var3 = inputString.substring(slash2+1); // extract the third variable 
    Serial.println("Done1");
}


void full_open(int channel){
  Serial.println("opening");
  int etat_capteur_1 = digitalRead(pin_fin_de_course_1);
  int etat_capteur_2 = digitalRead(pin_fin_de_course_2);
   do {
      etat_capteur_1 = digitalRead(pin_fin_de_course_1);
      etat_capteur_2 = digitalRead(pin_fin_de_course_2);
    } while (etat_capteur_2 == HIGH);
    Serial.println("Done2");
}

void full_close(int channel){
    Serial.println("closing");
    Serial.println(channel);
    int etat_capteur = digitalRead(channel +3);
    do {
      etat_capteur = digitalRead(channel +3);
      pwm.writeMicroseconds(channel, arriere);
    } while (etat_capteur == HIGH);
    pwm.writeMicroseconds(channel, stop);
    Serial.println("Done3");
}

void full_close_secure(){
  for(int i=1; i<=5; i++){
    Serial.println(i);
    full_close(i);
  }
  Serial.println("full close secure Done");
}

float calculateValue(int var1, int var2, int var3) {
  return (var1/var2)*var3; // calculate and return the result
}

/**************************************************************************** funtions end ****************************************************************************************/

//*********************************************************start functions fingerprint************************************************************************************
  /*uint8_t readnumber(void) {
    uint8_t num = 0;

    while (num == 0) {
      while (! Serial.available());
      num = Serial.parseInt();
    }
    return num;
  }

//-------------------------------------------------------------------------------

  uint8_t getFingerprintEnroll() {
    int p = -1;
    Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
    while (p != FINGERPRINT_OK) {
      p = finger.getImage();
      switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
      }
    }

    // OK success!

    p = finger.image2Tz(1);
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return p;
      default:
        Serial.println("Unknown error");
        return p;
    }

    Serial.println("Remove finger");
    delay(2000);
    p = 0;
    while (p != FINGERPRINT_NOFINGER) {
      p = finger.getImage();
    }
    Serial.print("ID "); Serial.println(id);
    p = -1;
    Serial.println("Place same finger again");
    while (p != FINGERPRINT_OK) {
      p = finger.getImage();
      switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
      }
    }

    // OK success!

    p = finger.image2Tz(2);
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return p;
      default:
        Serial.println("Unknown error");
        return p;
    }

    // OK converted!
    Serial.print("Creating model for #");  Serial.println(id);

    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
      Serial.println("Prints matched!");
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      return p;
    } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      Serial.println("Fingerprints did not match");
      return p;
    } else {
      Serial.println("Unknown error");
      return p;
    }

    Serial.print("ID "); Serial.println(id);
    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK) {
      Serial.println("Stored!");
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      return p;
    } else if (p == FINGERPRINT_BADLOCATION) {
      Serial.println("Could not store in that location");
      return p;
    } else if (p == FINGERPRINT_FLASHERR) {
      Serial.println("Error writing to flash");
      return p;
    } else {
      Serial.println("Unknown error");
      return p;
    }
    return true;
  }

  //---------------------------------------------------------------------------------------------

uint8_t getFingerprintID() {
  uint8_t p = -1;
  Serial.println("Waiting for a finger");
  while (p != FINGERPRINT_OK) {
    Serial.print(".");
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
    }
  }
    // OK success!

    p = finger.image2Tz();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return p;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return p;
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return p;
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return p;
      default:
        Serial.println("Unknown error");
        return p;
    }

    // OK converted!
    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK) {
      Serial.println("Found a print match!");
    //******************
      Serial.println("9bilnek");
    //********************
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      return p;
    } else if (p == FINGERPRINT_NOTFOUND) {
      Serial.println("Did not find a match");
    //******************
      Serial.println("Ma9bilnekich");
    //********************
      return p;
    } else {
      Serial.println("Unknown error");
      return p;
    }

    // found a match!
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);

    return finger.fingerID;
  }


  // returns -1 if failed, otherwise returns ID #
  int getFingerprintIDez() {
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)  return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)  return -1;

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)  return -1;

    // found a match!
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);
    return finger.fingerID;
  }
*/
//********************************************************************end functions fingerprint ***********************************************************************/