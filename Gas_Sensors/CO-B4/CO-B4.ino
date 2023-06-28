#include <DHT.h>

// DHT sensor specs
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

// Serial: 162741353
  float sensitivityCO = 380.0 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcCO = 0;                                // Corrected WE output in ppb/ppm 
  float WEuCO = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuCO = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoCO = 340;                              // WE Zero (mV)
  float WEeCO = 310;                              // WE Eletronic Zero (mV)
  float AEoCO = 342;                              // Aux Zero (mV)
  float AEeCO = 341;                              // Aux Eletronic Zero (mV)

  float COConcentrationPPB = WEcCO / sensitivityCO;
  float COConcentrationPPM = COConcentrationPPB / 1000;

// Correction factors that depends on the temperature
float temperature = 0;      // Temperature value
float humidity = 0;         // Humidity value
float NtCO = 0;             // nT
float KtCO = 0;             // kT
float KttCO = 0;            // kT'
float KtttCO = 0;           // kT''

void correctionFactors(float temperature){
    if(temperature < -25)                       { NtCO = 0.7; KtCO = 0.2; KttCO = -1.0; KtttCO =   55; };
    if(temperature >= -25 && temperature < -15) { NtCO = 0.7; KtCO = 0.2; KttCO = -0.5; KtttCO =   55; };
    if(temperature >= -15 && temperature <  -5) { NtCO = 0.7; KtCO = 0.2; KttCO =  0.0; KtttCO =   55; };
    if(temperature >=  -5 && temperature <   5) { NtCO = 0.7; KtCO = 0.2; KttCO =  0.0; KtttCO =   50; };
    if(temperature >=   5 && temperature <  15) { NtCO = 1.0; KtCO = 0.3; KttCO =  0.0; KtttCO =   31; };
    if(temperature >=  15 && temperature <  25) { NtCO = 3.0; KtCO = 1.0; KttCO =  1.0; KtttCO =    0; };
    if(temperature >=  25 && temperature <  35) { NtCO = 3.5; KtCO = 1.2; KttCO =  1.0; KtttCO =  -50; };
    if(temperature >=  35 && temperature <  45) { NtCO = 4.0; KtCO = 1.3; KttCO =  1.0; KtttCO = -150; };
    if(temperature >=  45)                      { NtCO = 4.5; KtCO = 1.5; KttCO =  1.0; KtttCO = -250; }; 
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
    
  // CO-B4 (Carbon Monoxide)
    WEuCO = analogRead(A3) * (5.0 / 1024) * 1000;
    AEuCO = analogRead(A4) * (5.0 / 1024) * 1000;
      WEcCO = equationWEc(WEcCO, WEuCO, WEeCO, NtCO, AEuCO, AEeCO);
      COConcentrationPPB = WEcCO / sensitivityCO;
      COConcentrationPPM = COConcentrationPPB / 1000;
      
  /* Print DHT informations */
    // Temperature and Humidity
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print("\n");
    
  /* Print Gas informations */
    // CO-B4 (Carbon Monoxide)
    Serial.print("CO-B4 (Carbon Monoxide): ");
    Serial.print("\n");
    Serial.print("WEu Raw value: ");
    Serial.print(WEuCO);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuCO);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcCO);
    Serial.print("\n");
    Serial.print("Concentrations: ");
    Serial.print(COConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(COConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n\n");
    
  delay(5000); // Time between measurement
}
