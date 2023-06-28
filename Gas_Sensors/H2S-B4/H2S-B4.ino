#include <DHT.h>

// DHT sensor specs
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

// Serial: 163740262
  float sensitivityH2S = 1616 / 1000;              // Sensor's sensitivity (mV/ppb)
  float WEcH2S = 0;                                // Corrected WE output in ppb/ppm 
  float WEuH2S = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuH2S = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoH2S = 353;                              // WE Zero (mV)
  float WEeH2S = 345;                              // WE Eletronic Zero (mV)
  float AEoH2S = 342;                              // Aux Zero (mV)
  float AEeH2S = 344;                              // Aux Eletronic Zero (mV)
  
  float H2SConcentrationPPB = WEcH2S / sensitivityH2S;
  float H2SConcentrationPPM = H2SConcentrationPPB / 1000;

// Correction factors that depends on the temperature
float temperature = 0;      // Temperature value
float humidity = 0;         // Humidity value
float NtH2S = 0;            // nT
float KtH2S = 0;            // kT
float KttH2S = 0;           // kT'
float KtttH2S = 0;          // kT''
  
void correctionFactors(float temperature){
    if(temperature < -25)                       { NtH2S = -0.6; KtH2S =  0.2; KttH2S = -14.0; KtttH2S =   52; };
    if(temperature >= -25 && temperature < -15) { NtH2S = -0.6; KtH2S =  0.2; KttH2S = -14.0; KtttH2S =   51; };
    if(temperature >= -15 && temperature <  -5) { NtH2S =  0.1; KtH2S =  0.0; KttH2S =   3.0; KtttH2S =   48; };
    if(temperature >=  -5 && temperature <   5) { NtH2S =  0.8; KtH2S = -0.3; KttH2S =   3.0; KtttH2S =   45; };
    if(temperature >=   5 && temperature <  15) { NtH2S = -0.7; KtH2S =  0.3; KttH2S =   2.0; KtttH2S =   26; };
    if(temperature >=  15 && temperature <  25) { NtH2S = -2.5; KtH2S =  1.0; KttH2S =   1.0; KtttH2S =    0; };
    if(temperature >=  25 && temperature <  35) { NtH2S = -2.5; KtH2S =  1.0; KttH2S = -01.2; KtttH2S = -065; };
    if(temperature >=  35 && temperature <  45) { NtH2S = -2.2; KtH2S =  0.9; KttH2S = -01.2; KtttH2S = -125; };
    if(temperature >=  45)                      { NtH2S = -1.8; KtH2S =  0.7; KttH2S = -01.2; KtttH2S = -180; }; 
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

  // H2S-B4 (Hydrogen Sulfide)
    WEuH2S = analogRead(A3) * (5.0 / 1024) * 1000;
    AEuH2S = analogRead(A4) * (5.0 / 1024) * 1000;
      WEcH2S = equationWEc(WEcH2S, WEuH2S, WEeH2S, NtH2S, AEuH2S, AEeH2S);
      H2SConcentrationPPB = WEcH2S / sensitivityH2S;
      H2SConcentrationPPM = H2SConcentrationPPB / 1000;

  /* Print DHT informations */
    // Temperature and Humidity
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print("\n");
  
  /* Print Gas informations */
    // H2S-B4 (Hydrogen Sulfide)
    Serial.print("H2S-B4 (Hydrogen Sulfide): ");
    Serial.print("\n");
    Serial.print("WEu Raw value: ");
    Serial.print(WEuH2S);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuH2S);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcH2S);
    Serial.print("\n");
    Serial.print("Concentrations: ");
    Serial.print(H2SConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(H2SConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n\n");

  delay(12000); // Time between measurement
}
