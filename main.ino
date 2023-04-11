#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include "Wire.h"
Adafruit_MPU6050 mpu;

#define WIFI_SSID "Daddy"
#define WIFI_PASSWORD "09090909"

#include "SSD1306.h"
SSD1306 display(0x3c,21,22);

void OLEDInit();
void OLEDUpdate();

float baseline[3];
float features[3];
float motion_threshold = 0.7;
int p,q,r;

void setup() { 
    Serial.begin(115200);
    while (!Serial)
    delay(10); 
        OLEDInit();
    Serial.println("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }

 }
    Serial.println("MPU6050 Found!");
 
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
    case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
    case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
    case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
    
  }

  }
//  OLEDinit();
WiFiInit();
FirebaseInit();
}

void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  /* Print out the values */
//    Serial.print("Acceleration X: ");
//    Serial.print(a.acceleration.x);
//    Serial.print(", Y: ");
//    Serial.print(a.acceleration.y);
//    Serial.print(", Z: ");
//    Serial.print(a.acceleration.z);
//    Serial.println(" m/s^2");
    
    //ROTATION VALUES
    Serial.print("Rotation X: ");
    p=(g.gyro.x)*( 57.29)*(0.5);
    Serial.print((g.gyro.x)*( 57.29)*(0.5));
    Firebase.setFloat(firebaseData,"IOTLAB/Gyroscope_Sensor/Roatation_X",p);
    Serial.print(", Y: ");
    q=(g.gyro.x)*( 57.29)*(0.5);
    Serial.print((g.gyro.y)*( 57.29)*(0.5));
    Firebase.setFloat(firebaseData,"IOTLAB/Gyroscope_Sensor/Roatation_Y",q);
    Serial.print(", Z: ");
    r=(g.gyro.x)*( 57.29)*(0.5);
    Serial.print((g.gyro.z)*( 57.29)*(0.5));
    Firebase.setFloat(firebaseData,"IOTLAB/Gyroscope_Sensor/Roatation_Z",r);
    Serial.println(" deg/s");

//    Serial.print("Temperature: ");
//    Serial.print(temp.temperature);
//    Serial.println(" degC");

    Serial.println("");
    delay(500);

//    display.clear();
//    display.drawString(10,20, String ((g.gyro.x)*(57.29)));
//    display.drawString(10,20,String((g.gyro.x)*( 57.29)));
//    display.drawString(20,30,String((g.gyro.x)*( 57.29)));
//    display.display();
    OLEDUpdate(p,q,r);
  }
  
void OLEDInit(){
    display.init();
    display.setFont(ArialMT_Plain_24);
}

// Display pe dikhane ka function

void OLEDUpdate(int p, int q, int r){ 
//  String d= String(p) + "deg/s"; 
//    display.drawString(10,20,d);
//  display.drawString(10,20,String((g.gyro.x)*( 57.29)));
//  display.drawString(20,30,String((g.gyro.x)*( 57.29)));
  String s="EMERGENCY", t="SAFE";
  display.clear();
  if(p>=150 && q>=150 && r>=150){
    display.drawString(10,20,s);
    Firebase.setString(firebaseData,"IOTLAB/Gyroscope_Sensor/State",s);
    }
  else{
    display.drawString(10,20,t);
    Firebase.setString(firebaseData,"IOTLAB/Gyroscope_Sensor/State",t);
    }
  display.display();
}

void WiFiInit(){
  pinMode(2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(2,!digitalRead(2));
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
   
}

//void FirebaseInit(){
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);
//  Serial.println("Eureka!");
//}
