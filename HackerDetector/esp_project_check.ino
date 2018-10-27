#include <ESP8266WiFi.h>
#include<Wire.h>
//analog out port


#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

String ssid = "Rashmi"; //hotspot

//different hosts and SHA-1 keys from the certificate
const char* host = "appleid.apple.com";
const char* fingerprint = "C1 A0 0F CE D7 5B C3 56 A2 1C 86 21 0A C1 4C BD 9A FE AA 85";

const char* host2 = "www.snapchat.com";
const char* fingerprint2 = "49 73 A3 46 FC B6 14 3B 02 6C 70 6E 8A 26 92 CB 54 9A E7 D3";

const char* host3 = "www.instagram.com";
const char* fingerprint3 = "32 05 77 10 E7 F6 CE 82 A4 40 4E 65 89 30 C7 E9 98 57 B6 EA";

const char* host4 = "www.ebay.com";
const char* fingerprint4 = "F6 AC 99 99 F8 69 EB 25 91 6C F3 66 5A 1F AB 34 1B 39 F0 CE";

//stores if hacker is detected
bool appleHacker = false;
bool snapchatHacker = false;
bool instagramHacker = false;
bool ebayHacker = false;

void setup() {
  Serial.begin(115200);
  delay(5000);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Rashmi", "rechu108");
  
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);

}

//integers for counting the amount of times the connection fail via https
//up to
int countApple = 0;
int countSnap = 0;
int countInstagram = 0;
int countEbay = 0;
void loop() {
  delay(5000);
Serial.println("WiFi connected to :");
Serial.println(ssid);
  if (countApple == 0) {
    apple();
  }
  if (countSnap == 0) {
    snapchat();
  }
  if (countInstagram == 0) {
    instagram();
  }
  if (countEbay == 0) {
    ebay();
  }
  /*After running the above checks, if a hacker has been detected,
    the appropriate function gets run*/

  hackerDetected();



}

void apple() {
  //Connects to a client via the host
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  delay(2000);
  if (!client.connect(host, 443)) {
    Serial.println("connection failed for appleid.apple.com");
    //allows the connection to try and reconnect 4 times before assuming that there is a problem with the HTTPS port
    if (countApple == 3) {
      Serial.println("No HTTPS port, hacker may be trying to force you to use HTTP!");

      appleHacker = true;
    } else {
      countApple = countApple + 1;
      apple();
    }
  } else {
    //checks the certificate
    if (client.verify(fingerprint, host)) {
      Serial.println("certificate matches for appleid.apple.com");
      client.flush();
      client.stop();
    } else {

      client.flush();
      client.stop();
      Serial.println("certificate doesn't match for appleid.apple.com! Hacker dectected");


      appleHacker = true;


    }
  }
}

void snapchat() {

  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host2);
  delay(2000);
  if (!client.connect(host2, 443)) {
    Serial.println("connection failed for accounts.snapchat.com");
    if (countSnap == 3) {
      Serial.println("No HTTPS port, hacker may be trying to force you to use HTTP!");

      snapchatHacker = true;
    } else {
      countSnap = countSnap + 1;
      snapchat();
    }
  } else {

    if (client.verify(fingerprint2, host2)) {
      Serial.println("certificate matches for snapchat.com");
      client.flush();
      client.stop();
    } else {
      Serial.println("certificate doesn't match for snapchat.com! Hacker dectected");
      client.flush();
      client.stop();


      snapchatHacker = true;

    }
  }
}
void instagram() {

  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host3);
  delay(2000);
  if (!client.connect(host3, 443)) {
    Serial.println("connection failed for instagram.com");
    if (countInstagram == 3) {
      Serial.println("No HTTPS port, hacker may be trying to force you to use HTTP!");
      instagramHacker = true;
    } else {
      countInstagram = countInstagram + 1;
      instagram();
    }
  } else {

    if (client.verify(fingerprint3, host3)) {
      Serial.println("certificate matches for instagram.com");
      client.flush();
      client.stop();
    } else {
      Serial.println("certificate doesn't match for instagram.com! Hacker dectected");
      client.flush();
      client.stop();

      instagramHacker = true;



    }
  }
}

void ebay() {

  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host4);
  delay(2000);
  if (!client.connect(host4, 443)) {
    Serial.println("connection failed for ebay.com");
    if (countInstagram == 3) {
      Serial.println("No HTTPS port, hacker may be trying to force you to use HTTP!");
      ebayHacker = true;
    } else {
      countEbay = countEbay + 1;
      ebay();
    }
  } else {

    if (client.verify(fingerprint4, host4)) {
      Serial.println("certificate matches for ebay.com");
      client.flush();
      client.stop();
    } else {
      Serial.println("certificate doesn't match for ebay.com! Hacker dectected");
      client.flush();
      client.stop();


      ebayHacker = true;

    }
  }
}
//writes analog out if a hacker is detected
bool analog = false;
void hackerDetected() {

 
  if (appleHacker) {
    analog = true;
    
  }
  if (snapchatHacker) {
    if (!analog) {
      
      analog = true;
    }
  }
  if (instagramHacker) {

    if (!analog) {
      
      analog = true;
    }
  }
  if (ebayHacker) {
    if (!analog) {

     
      analog = true;
    }
  }
  if (!analog) {
    Serial.println("Hacker Detected");

  }

  delay(5000);

  //resets all values
  countApple = 0;
  countSnap = 0;
  countInstagram = 0;
  countEbay = 0;
  analog = false;
  appleHacker = false;
  snapchatHacker = false;
  instagramHacker = false;
  ebayHacker = false;
  
}
