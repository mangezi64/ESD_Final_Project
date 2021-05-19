   
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;
char MESSAGE[300];
char MESSAGE2[300];
char lat[12];
char lon[12];
char wspeed[12];

char phone[16];
char datetime[24];

#define PIN_TX    10
#define PIN_RX    11
#define PHONE_N "+250*********"
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);

  

  //******** Initialize sim808 module *************
  while(!sim808.init())
  {
      Serial.print("Sim808 init error\r\n");
      delay(1000);
  }
  delay(3000);

  if( sim808.attachGPS())
      Serial.println("GPS power success");
  else 
      Serial.println("Open the GPS power failure");
      
  Serial.println("Start System:\n");
}

int asto = 0;
void loop()
{
  if (asto==0){
    while(!sim808.getGPS()){}
    sim808.getGPS();
    Serial.print(sim808.getGPS());

      //Time---------------------------------------
      Serial.print(sim808.GPSdata.year);
      Serial.print("/");
      Serial.print(sim808.GPSdata.month);
      Serial.print("/");
      Serial.print(sim808.GPSdata.day);
      Serial.print(" ");
      Serial.print(sim808.GPSdata.hour);
      Serial.print(":");
      Serial.print(sim808.GPSdata.minute);
      Serial.print(":");
      Serial.print(sim808.GPSdata.second);
      Serial.print(":");
      Serial.println(sim808.GPSdata.centisecond);
      //GPS Location-------------------------------
      Serial.print("latitude :");
      Serial.println(sim808.GPSdata.lat);
      Serial.print("longitude :");
      Serial.println(sim808.GPSdata.lon);
      
  
      float la = sim808.GPSdata.lat;
      float lo = sim808.GPSdata.lon;
  
      dtostrf(la, 6, 3, lat); //put float value of la into char array of lat. 6 = number of digits before decimal sign. 3 = number of digits after the decimal sign.
      dtostrf(lo, 6, 3, lon); //put float value of lo into char array of lon
      
    // Send Location--------------------------------------------------------------------------------------------------------------------------------------------------------------------
      sprintf(MESSAGE, "Latitude : %s\nLongitude : %s\nLocation Link.\nhttp://www.latlong.net/Show-Latitude-Longitude.html\nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon, lat, lon);
      sprintf(MESSAGE2, "Latitude : %s\nLongitude : %s\n", lat, lon);
       Serial.println("Sim808 init success");
       Serial.println("Start to send message ...");
       Serial.println(MESSAGE);
       Serial.print("Message send to: ");
       Serial.println(PHONE_N);
       sim808.sendSMS(PHONE_N,MESSAGE);
       sim808.sendSMS(PHONE_N,MESSAGE2);
       asto=1;
  }
  asto=1;
  readSMS1();
  
}


void readSMS1(){

  
  //*********** Detecting unread SMS ************************
   messageIndex = sim808.isSMSunread();

   //*********** At least, there is one UNREAD SMS ***********
   if (messageIndex > 0)
   { 
      Serial.print("messageIndex: ");
      Serial.println(messageIndex);
      
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
                 
      //***********In order not to full SIM Memory, is better to delete it**********
      sim808.deleteSMS(messageIndex);
      Serial.print("From number: ");
      Serial.println(phone);  
      Serial.print("Datetime: ");
      Serial.println(datetime);        
      Serial.print("Recieved Message: ");
      Serial.println(message); 

      while(!sim808.getGPS()){}
      sim808.getGPS();

   
      Serial.print(sim808.GPSdata.year);
      Serial.print("/");
      Serial.print(sim808.GPSdata.month);
      Serial.print("/");
      Serial.print(sim808.GPSdata.day);
      Serial.print(" ");
      Serial.print(sim808.GPSdata.hour);
      Serial.print(":");
      Serial.print(sim808.GPSdata.minute);
      Serial.print(":");
      Serial.print(sim808.GPSdata.second);
      Serial.print(":");
      Serial.println(sim808.GPSdata.centisecond);
      Serial.print("latitude :");
      Serial.println(sim808.GPSdata.lat);
      Serial.print("longitude :");
     
  
      float la = sim808.GPSdata.lat;
      float lo = sim808.GPSdata.lon;
  
      dtostrf(la, 6, 3, lat); //put float value of la into char array of lat. 6 = number of digits before decimal sign. 3 = number of digits after the decimal sign.
      dtostrf(lo, 6, 3, lon); //put float value of lo into char array of lon
    
      sprintf(MESSAGE, "Latitude : %s\nLongitude : %s\nLocation Link.\nhttp://www.latlong.net/Show-Latitude-Longitude.html\nhttp://maps.google.com/maps?q=%s,%s\n", lat, lon, lat, lon);
      sprintf(MESSAGE2, "Latitude : %s\nLongitude : %s\n", lat, lon);
       Serial.println("Sim808 init success");
       Serial.println("Start to send message ...");
       Serial.println(MESSAGE);
       Serial.println(phone);
       sim808.sendSMS(phone,MESSAGE);
       //sim808.sendSMS(phone,MESSAGE2);
      //************* Turn off the GPS power ************
      sim808.detachGPS();
      
   }
   }
