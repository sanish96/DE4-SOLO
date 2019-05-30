#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_INA219.h>
//#include <movingAvg.h>

Adafruit_INA219 ina219;
//movingAvg avgCurrent(20);



// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);


void setup() 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");

  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  // turn on motor
//  myMotor->run(RELEASE);

//  uint8_t i;
  
  Serial.print("tick");

//  myMotor->run(FORWARD);
//  for (i=0; i<255; i++) {
//    myMotor->setSpeed(i);
//  }

//  avgCurrent.begin();

}

void loop() {

//  float shuntvoltage = 0;
//  float busvoltage = 0;
//  float current_mA = 0;
//  float loadvoltage = 0;
//  float power_mW = 0;
//  float avg = 0;
//
//  shuntvoltage = ina219.getShuntVoltage_mV();
//  busvoltage = ina219.getBusVoltage_V();
//  current_mA = ina219.getCurrent_mA();
//  power_mW = ina219.getPower_mW();
//  loadvoltage = busvoltage + (shuntvoltage / 1000);
//
//  avg = avgCurrent.reading(current_mA);
//
//  Serial.print("Current:       "); Serial.print(current_mA); Serial.print(" mA");
//  Serial.print(",");
//  Serial.print("Avg Current:       "); Serial.print(avg); Serial.println(" mA");
//
//  delay(500);
  myMotor->run(FORWARD);

  int var = 0;
  int current_array[200];
  float current_mA = 0;
  float average_tot = 0;
  float average = 0;

  while (var < 200) {
  var++;
  current_mA = ina219.getCurrent_mA();
//  Serial.print("Current Value:       ");
    Serial.println(current_mA);
  current_array[var]=current_mA;
//  Serial.print("Curent Array:       ");
//  Serial.print(current_array);
  average_tot+=current_mA;
//  Serial.print("Average Total:       ");
//  Serial.println(average);
  delay(50);
}
  average = average_tot/var;

  Serial.print("Final Average:       ");
  Serial.println(average);

  myMotor->run(RELEASE);
  delay(2000);
}
