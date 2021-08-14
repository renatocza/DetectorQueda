#include <CTBot.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float x = 0, y = 0, z = 0;

#define ssid_wifi "Your SSID"
#define password_wifi "Your PASSWORD"

//Max value allowed for trigger alarm
int maxValue = 9; //in m/s^2

//Intervals
const long MessagesInterval = 30000;
unsigned long Time1 = 0;

//TELEGRAM API TOKEN
const char* BotToken = "YOUR TOKEN";    // your Bot Token
CTBot myBot;
TBMessage msg;

void ReadValues() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  x = a.acceleration.x < 0 ? a.acceleration.x * -1 : a.acceleration.x;
  y = a.acceleration.y < 0 ? a.acceleration.y * -1 : a.acceleration.y;
  z = a.acceleration.z < 0 ? a.acceleration.z : a.acceleration.z;
}

void SendMessage() {
  Serial.println("POSSÍVEL QUEDA!");
  myBot.sendMessage(msg.sender.id, "POSSÍVEL QUEDA");
}

void CheckFall(float v1, float v2) {
  float vt = v1 - v2;
  if (vt <= maxValue * -1 || vt >= maxValue) {
    SendMessage();
    ReadValues();
  }
}

void VerifyMessages() {
  // a variable to store telegram message data
  Serial.println("Reading data");

  // if there is an incoming message...
  if (myBot.getNewMessage(msg))
  {
    // ...forward it to the sender
    myBot.sendMessage(msg.sender.id, "Monitorando");

  }

}

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  myBot.wifiConnect(ssid_wifi, password_wifi);

  // set the telegram bot token
  myBot.setTelegramToken(BotToken);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");



  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
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

  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;

      delay(1000);

  }

  Serial.println("");
  delay(500);

  //set initial x,y,z
  ReadValues();


}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - Time1 >= MessagesInterval) {
    VerifyMessages();
    Time1 = currentTime;
  }
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x1, y1, z1;

  x1 = a.acceleration.x < 0 ? a.acceleration.x * -1 : a.acceleration.x;
  y1 = a.acceleration.y < 0 ? a.acceleration.y * -1 : a.acceleration.y;
  z1 = a.acceleration.z < 0 ? a.acceleration.z : a.acceleration.z;

  //fall verification
  CheckFall(x, x1);
  CheckFall(y, y1);
  CheckFall(z, z1);

  x = x1;
  y = y1;
  z = z1;

  delay(200);

}
