#include <DHT.h>

// DHT sensor specs
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

// Serial: 202742053
  float sensitivityNO2 = 311.0 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcNO2 = 0;                                // Corrected WE output in ppb/ppm 
  float WEuNO2 = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuNO2 = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoNO2 = 225;                              // WE Zero (mV)
  float WEeNO2 = 236;                              // WE Eletronic Zero (mV)
  float AEoNO2 = 216;                              // Aux Zero (mV)
  float AEeNO2 = 223;                              // Aux Eletronic Zero (mV)
  
  float NO2ConcentrationPPB = WEcNO2 / sensitivityNO2;
  float NO2ConcentrationPPM = NO2ConcentrationPPB / 1000;

// Correction factors that depends on the temperature
float temperature = 0;      // Temperature value
float humidity = 0;         // Humidity value
float NtNO2 = 0;            // nT
float KtNO2 = 0;            // kT
float KttNO2 = 0;           // kT'
float KtttNO2 = 0;          // kT''

void correctionFactors(float temperature){
    if(temperature < -25)                       { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >= -25 && temperature < -15) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >= -15 && temperature <  -5) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >=  -5 && temperature <   5) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >=   5 && temperature <  15) { NtNO2 =  1.0; KtNO2 =  1.7; KttNO2 =  1.0; KtttNO2 =  4.0; };
    if(temperature >=  15 && temperature <  25) { NtNO2 =  0.6; KtNO2 =  1.0; KttNO2 =  1.0; KtttNO2 =  0.0; };
    if(temperature >=  25 && temperature <  35) { NtNO2 =  0.4; KtNO2 =  0.7; KttNO2 =  0.4; KtttNO2 =  0.5; };
    if(temperature >=  35 && temperature <  45) { NtNO2 =  0.2; KtNO2 =  0.3; KttNO2 = -0.1; KtttNO2 =  5.0; };
    if(temperature >=  45)                      { NtNO2 = -1.5; KtNO2 = -2.5; KttNO2 = -4.0; KtttNO2 = 67.0; };
}

float equationWEc(float WEc, float WEu, float WEe, float Nt, float AEu, float AEe){
  // Algorithms to correct the WE output for the effects of temperature
  WEc = ((WEu - WEe) - (Nt * (AEu - AEe)));
  //WEc = (WEu - WEe) - Kt * (WEo / AEo) * (AEu - AEe);
  //WEc = (WEu - WEe) - (WEo - AEo) - Ktt * (AEu - AEe);
  //WEc = (WEu - WEe) - WEo - Kttt;

  return WEc;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // DHT data (Temperature and Humidity)
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    correctionFactors(temperature);

  // NO2-B43F (Nitrogen Dioxide)
    WEuNO2 = analogRead(A8) * (5.0 / 1024) * 1000;
    AEuNO2 = analogRead(A9) * (5.0 / 1024) * 1000;
      WEcNO2 = equationWEc(WEcNO2, WEuNO2, WEeNO2, NtNO2, AEuNO2, AEeNO2);
      NO2ConcentrationPPB = WEcNO2 / sensitivityNO2;
      NO2ConcentrationPPM = NO2ConcentrationPPB / 1000;

  /* Print DHT informations */
    // Temperature and Humidity
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print("\n");

    // NO2-B43F (Nitrogen Dioxide)
    Serial.print("NO2-B43F (Nitrogen Dioxide): ");
    Serial.print("WEu Raw value: ");
    Serial.print(WEuNO2);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuNO2);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcNO2);
    Serial.print("\n");
    Serial.print("Concentrations: ");
    Serial.print(NO2ConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(NO2ConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n\n");
    
  delay(12000); // Time between measurement
}
