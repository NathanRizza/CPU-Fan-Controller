// Programmer: Nathan Rizza

/*thermistor parameters:
 * RT0: 10 000 Ω
 * B: 3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
 */

//These values are in the datasheet
#define resistanceThermO 10000   // Ω
#define B 3977      // K
//--------------------------------------


#define VCC 5    //Supply voltage
#define resistance 10000  //R=10KΩ

//Variables
float thermR, resistorVoltage, ln, temp, T0, readVoltage, convertedVoltage, tempC, ratio, FanSpeed;
int outputVoltage;

void setup() {
  Serial.begin(9600);
  T0 = 25 + 273.15; 
}

void loop() {
  
  readVoltage = analogRead(A0);
  
  convertedVoltage = (5.00 / 1023.00) * readVoltage;
  
  resistorVoltage = VCC - convertedVoltage;
  
  thermR = convertedVoltage / (resistorVoltage / resistance);
  
  ln = log(thermR/resistanceThermO);
  
  temp = (1 / ((ln / B) + (1 / T0)));
  
  tempC = temp - 273.15;
  
  ratio = ((tempC/60));
  
  if(ratio>=1 || ratio<= 0)
  {
	  outputVoltage = 255;
  }
  else
  {  
	  outputVoltage = 255*ratio;
  }
  
  analogWrite(3,outputVoltage); //PWN pins 3, 5, 6, 9, 10, 11

  FanSpeed = ((float(outputVoltage)/255)*100);
  
  Serial.print("Temp (C):\t");
  Serial.print(tempC);
  Serial.print("\t\t\t\t");
  Serial.print("FanSpeed:\t");
  Serial.print(FanSpeed);
  Serial.print("%");
  //Serial.print(outputVoltage);
  Serial.println("");
  delay(1000);

}
