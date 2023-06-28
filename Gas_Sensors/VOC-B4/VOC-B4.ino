#include <DHT.h>

// DHT sensor specs
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

// Serial: 207240023
  float sensitivityVOC = 0.537 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcVOC = 0;                                // Corrected WE output in ppb/ppm 
  float WEuVOC = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuVOC = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoVOC = 473;                              // WE Zero (mV)
  float WEeVOC = 340;                              // WE Eletronic Zero (mV)
  float AEoVOC = 324;                              // Aux Zero (mV)
  float AEeVOC = 351;                              // Aux Eletronic Zero (mV)
  
  float NtVOC = 0;               // nT
  float KtVOC = 0;               // kT
  float KttVOC = 0;              // kT'
  float KtttVOC = 0;             // kT''

  float VOCConcentrationPPB = WEcVOC / sensitivityVOC;
  float VOCConcentrationPPM = VOCConcentrationPPB / 1000;

// Correction factors that depends on the temperature
float temperature = 0;      // Temperature value
float humidity = 0;         // Humidity value

void correctionFactors(float temperature){
    if(temperature < -25)                       { NtVOC =  0.9; KtVOC =  0.5; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >= -25 && temperature < -15) { NtVOC =  0.9; KtVOC =  0.5; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >= -15 && temperature <  -5) { NtVOC =  1.0; KtVOC =  0.6; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >=  -5 && temperature <   5) { NtVOC =  1.3; KtVOC =  0.8; KttVOC =  0.6; KtttVOC =    1.0; };
    if(temperature >=   5 && temperature <  15) { NtVOC =  1.5; KtVOC =  0.9; KttVOC =  0.6; KtttVOC =    1.0; };
    if(temperature >=  15 && temperature <  25) { NtVOC =  1.7; KtVOC =  1.0; KttVOC =  1.0; KtttVOC =    1.0; };
    if(temperature >=  25 && temperature <  35) { NtVOC =  2.0; KtVOC =  1.2; KttVOC =  2.8; KtttVOC =    8.5; };
    if(temperature >=  35 && temperature <  45) { NtVOC =  2.5; KtVOC =  1.5; KttVOC =  5.0; KtttVOC =   23.0; };
    if(temperature >=  45)                      { NtVOC =  3.7; KtVOC =  2.2; KttVOC =  5.3; KtttVOC =  103.0; };
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

  // VOC-B4 (Volatile Organic Compound)
    WEuVOC = analogRead(A0) * (5.0 / 1024) * 1000;
    AEuVOC = analogRead(A1) * (5.0 / 1024) * 1000;
      WEcVOC = equationWEc(WEcVOC, WEuVOC, WEeVOC, NtVOC, AEuVOC, AEeVOC);
      VOCConcentrationPPB = WEcVOC / sensitivityVOC;
      VOCConcentrationPPM = VOCConcentrationPPB / 1000;

  /* Print DHT informations */
    // Temperature and Humidity
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print("\n");
  
  /* Print Gas informations */
    // VOC-B4 (Volatile Organic Compound)
    Serial.print("VOC-B4 (Volatile Organic Compound): ");
    Serial.print("WEu Raw value: ");
    Serial.print(WEuVOC);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuVOC);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcVOC);
    Serial.print(", Concentrations: ");
    Serial.print(VOCConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(VOCConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n");

  delay(12000); // Time between measurement
}
