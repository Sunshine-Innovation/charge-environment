int pin_A0_light = A0;
int pin_A1_temperature = A1;
float tempPin = 0.0;
float voltage_out = 0.0;
float voltage_in = 0.0;
int resistor1 = 1000;
int resisitor2 = 1000;
int digital_0 = 0;
int RED_LED = 4;
int GREEN_LED = 5;
float temperature_ChipConversionConstant = 0.48828125;
float light_ChipConversionConstant = 100/1024.0;


void setup() {
  Serial.begin(9600);
  pinMode(pin_A0_light, INPUT);
  pinMode(pin_A1_temperature, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(digital_0, INPUT);
}



void loop(){
  Serial.println("program execution start....");
  
  float lightSensorValue = analogRead(pin_A0_light);
  float temperatureSensorValue = analogRead(pin_A1_temperature);

  float pin_temperature = temperatureSensorValue*temperature_ChipConversionConstant;
  float light_intensity = (float) lightSensorValue*light_ChipConversionConstant;
  int fahrenheit = CelsiusToFarehieght(pin_temperature);

  float currentValueOfBattery = analogRead(digital_0);
  voltage_out = getCurrentVoltageOutOfBattery(currentValueOfBattery);
  voltage_in = getCurrentVoltageIn(voltage_out);

  if (voltage_in>3.7){ digitalWrite(GREEN_LED, HIGH);}
  if (voltage_in<1.85){ digitalWrite(RED_LED, HIGH);}
  
  Serial.print("Light Intensity = ");
  Serial.print(light_intensity);
  Serial.println("%");
  delay(2000);

  Serial.print("TEMPERATURE = ");
  Serial.print(pin_temperature);
  Serial.println("C");
  delay(2000);

  Serial.print("TEMPERATURE = ");
  Serial.print(fahrenheit);
  Serial.println("F");
  delay(2000);

  Serial.print("currentValueOfBattery");
  Serial.print(voltage);
  Serial.println("V");
  delay(2000);
}

float CelsiusToFarehieght(float celiusToConvert){ return (celiusToConvert*1.8) + 32; }
float getCurrentVoltageOutOfBattery(float valueOfBattery){ return (valueOfBattery*5.0)/1024; }
float getCurrentVoltageIn(float voltageOut){ return voltageOut/(resisitor2/(resistor1+resisitor2)); }
