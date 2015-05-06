// (c) Copyright 2010-2012 MCQN Ltd.
// Released under Apache License, version 2.0
//
// Simple example to show how to use the HttpClient library
// Get's the web page given at http://<kHostname><kPath> and
// outputs the content to the serial port

#include <SPI.h>
#include <HttpClient.h>
#include <WiFi.h>
#include <TCPClient.h>

char ssid[] = "energia";    // your network SSID (name) 
char pass[] = "supersecret"; // your network password (use for WPA, or use as key for WEP)

// This example downloads the URL "http://energia.nu/"

// Name of the server we want to connect to
const char kHostname[] = "energia.nu";
// Path to download (this is the bit after the hostname in the URL
// that you want to download
const char kPath[] = "/";

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

WiFiClient c;

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // Set communication pins for CC3000
  WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
  WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
  WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C

  // Start WiFi
  startWiFi();

}

void loop()
{
  int err =0;
  
  HttpClient http(c);
  
  err = http.get(kHostname, kPath);
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;
        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) &&
               ((millis() - timeoutStart) < kNetworkTimeout) )
        {
            if (http.available())
            {
                c = http.read();
                // Print out this character
                Serial.print(c);
               
                bodyLen--;
                // We read something, reset the timeout counter
                timeoutStart = millis();
            }
            else
            {
                // We haven't got any data, so let's pause to allow some to
                // arrive
                delay(kNetworkDelay);
            }
        }
      }
      else
      {
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();

  // And just stop, now that we've tried a download
  while(1);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


void startWiFi()
{
  WiFi.disconnect();
  c.stop();

  Serial.print("Connecting LaunchPad to SSID:");
  Serial.print(ssid);
  Serial.println();
  
  // Connect to network and obtain an IP address using DHCP
  if (WiFi.begin(ssid, pass) == 0) {
    Serial.println("Connected to WiFi!");
    // Wait 5 seconds to get a valid IP address
    delay(5000);
    printWifiStatus();
    Serial.println();
  } else {
    Serial.println("LaunchPad connected to network using DHCP");
    Serial.println();
  }
  
  delay(1000);
}


