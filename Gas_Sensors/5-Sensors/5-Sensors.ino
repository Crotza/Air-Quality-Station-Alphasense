#include <DHT.h>

// DHT sensor specs
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

#define CO_B4
#define H2S_B4
#define NO2_B43F
#define OX_B431
#define VOC_B4

#ifdef CO_B4 // Serial: 162741353
  float sensitivityCO = 380.0 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcCO = 0;                                // Corrected WE output in ppb/ppm 
  float WEuCO = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuCO = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoCO = 340;                              // WE Zero (mV)
  float WEeCO = 310;                              // WE Eletronic Zero (mV)
  float AEoCO = 342;                              // Aux Zero (mV)
  float AEeCO = 341;                              // Aux Eletronic Zero (mV)

  float NtCO = 0;               // nT
  float KtCO = 0;               // kT
  float KttCO = 0;              // kT'
  float KtttCO = 0;             // kT''

  float COConcentrationPPB = WEcCO / sensitivityCO;
  float COConcentrationPPM = COConcentrationPPB / 1000;
#endif

#ifdef H2S_B4 // Serial: 163740262
  float sensitivityH2S = 1616.0 / 1000;            // Sensor's sensitivity (mV/ppb)
  float WEcH2S = 0;                                // Corrected WE output in ppb/ppm 
  float WEuH2S = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuH2S = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoH2S = 353;                              // WE Zero (mV)
  float WEeH2S = 345;                              // WE Eletronic Zero (mV)
  float AEoH2S = 342;                              // Aux Zero (mV)
  float AEeH2S = 344;                              // Aux Eletronic Zero (mV)
  
  float NtH2S = 0;               // nT
  float KtH2S = 0;               // kT
  float KttH2S = 0;              // kT'
  float KtttH2S = 0;             // kT''
  
  float H2SConcentrationPPB = WEcH2S / sensitivityH2S;
  float H2SConcentrationPPM = H2SConcentrationPPB / 1000;
#endif

#ifdef NO2_B43F // Serial: 202742053
  float sensitivityNO2 = 311.0 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcNO2 = 0;                                // Corrected WE output in ppb/ppm 
  float WEuNO2 = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuNO2 = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoNO2 = 225;                              // WE Zero (mV)
  float WEeNO2 = 236;                              // WE Eletronic Zero (mV)
  float AEoNO2 = 216;                              // Aux Zero (mV)
  float AEeNO2 = 223;                              // Aux Eletronic Zero (mV)
  
  float NtNO2 = 0;               // nT
  float KtNO2 = 0;               // kT
  float KttNO2 = 0;              // kT'
  float KtttNO2 = 0;             // kT''

  float NO2ConcentrationPPB = WEcNO2 / sensitivityNO2;
  float NO2ConcentrationPPM = NO2ConcentrationPPB / 1000;
#endif

#ifdef OX_B431 // Serial: 204240462
  float sensitivityOX = 380.0 / 1000;             // Sensor's sensitivity (mV/ppb)
  float WEcOX = 0;                                // Corrected WE output in ppb/ppm 
  float WEuOX = 0;                                // Uncorrected raw WE output (analog pin)
  float AEuOX = 0;                                // Uncorrected raw AE output (analog pin)
  float WEoOX = 216;                              // WE Zero (mV)
  float WEeOX = 223;                              // WE Eletronic Zero (mV)
  float AEoOX = 230;                              // Aux Zero (mV)
  float AEeOX = 235;                              // Aux Eletronic Zero (mV)
  
  float NtOX = 0;               // nT
  float KtOX = 0;               // kT
  float KttOX = 0;              // kT'
  float KtttOX = 0;             // kT''

  float OXConcentrationPPB = WEcOX / sensitivityOX;
  float OXConcentrationPPM = OXConcentrationPPB / 1000;
#endif

#ifdef VOC_B4 // Serial: 207240023
  float sensitivityVOC = 537.0 / 1000;             // Sensor's sensitivity (mV/ppb)
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
#endif

// Correction factors that depends on the temperature
float temperature = 0;      // Temperature value
float humidity = 0;         // Humidity value

void correctionFactors(float temperature){
  #ifdef CO_B4
    if(temperature < -25)                       { NtCO = 0.7; KtCO = 0.2; KttCO = -1.0; KtttCO =   55; };
    if(temperature >= -25 && temperature < -15) { NtCO = 0.7; KtCO = 0.2; KttCO = -0.5; KtttCO =   55; };
    if(temperature >= -15 && temperature <  -5) { NtCO = 0.7; KtCO = 0.2; KttCO =  0.0; KtttCO =   55; };
    if(temperature >=  -5 && temperature <   5) { NtCO = 0.7; KtCO = 0.2; KttCO =  0.0; KtttCO =   50; };
    if(temperature >=   5 && temperature <  15) { NtCO = 1.0; KtCO = 0.3; KttCO =  0.0; KtttCO =   31; };
    if(temperature >=  15 && temperature <  25) { NtCO = 3.0; KtCO = 1.0; KttCO =  1.0; KtttCO =    0; };
    if(temperature >=  25 && temperature <  35) { NtCO = 3.5; KtCO = 1.2; KttCO =  1.0; KtttCO =  -50; };
    if(temperature >=  35 && temperature <  45) { NtCO = 4.0; KtCO = 1.3; KttCO =  1.0; KtttCO = -150; };
    if(temperature >=  45)                      { NtCO = 4.5; KtCO = 1.5; KttCO =  1.0; KtttCO = -250; }; 
  #endif
 
  #ifdef H2S_B4
    if(temperature < -25)                       { NtH2S = -0.6; KtH2S =  0.2; KttH2S = -14.0; KtttH2S =   52; };
    if(temperature >= -25 && temperature < -15) { NtH2S = -0.6; KtH2S =  0.2; KttH2S = -14.0; KtttH2S =   51; };
    if(temperature >= -15 && temperature <  -5) { NtH2S =  0.1; KtH2S =  0.0; KttH2S =   3.0; KtttH2S =   48; };
    if(temperature >=  -5 && temperature <   5) { NtH2S =  0.8; KtH2S = -0.3; KttH2S =   3.0; KtttH2S =   45; };
    if(temperature >=   5 && temperature <  15) { NtH2S = -0.7; KtH2S =  0.3; KttH2S =   2.0; KtttH2S =   26; };
    if(temperature >=  15 && temperature <  25) { NtH2S = -2.5; KtH2S =  1.0; KttH2S =   1.0; KtttH2S =    0; };
    if(temperature >=  25 && temperature <  35) { NtH2S = -2.5; KtH2S =  1.0; KttH2S = -01.2; KtttH2S = -065; };
    if(temperature >=  35 && temperature <  45) { NtH2S = -2.2; KtH2S =  0.9; KttH2S = -01.2; KtttH2S = -125; };
    if(temperature >=  45)                      { NtH2S = -1.8; KtH2S =  0.7; KttH2S = -01.2; KtttH2S = -180; }; 
  #endif
  
  #ifdef NO2_B43F
    if(temperature < -25)                       { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >= -25 && temperature < -15) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >= -15 && temperature <  -5) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >=  -5 && temperature <   5) { NtNO2 =  1.3; KtNO2 =  2.2; KttNO2 =  1.0; KtttNO2 =  7.0; };
    if(temperature >=   5 && temperature <  15) { NtNO2 =  1.0; KtNO2 =  1.7; KttNO2 =  1.0; KtttNO2 =  4.0; };
    if(temperature >=  15 && temperature <  25) { NtNO2 =  0.6; KtNO2 =  1.0; KttNO2 =  1.0; KtttNO2 =  0.0; };
    if(temperature >=  25 && temperature <  35) { NtNO2 =  0.4; KtNO2 =  0.7; KttNO2 =  0.4; KtttNO2 =  0.5; };
    if(temperature >=  35 && temperature <  45) { NtNO2 =  0.2; KtNO2 =  0.3; KttNO2 = -0.1; KtttNO2 =  5.0; };
    if(temperature >=  45)                      { NtNO2 = -1.5; KtNO2 = -2.5; KttNO2 = -4.0; KtttNO2 = 67.0; };
  #endif
  
  #ifdef OX_B431
    if(temperature < -25)                       { NtOX =  0.9; KtOX =  0.5; KttOX =  0.5; KtttOX =    1.0; };
    if(temperature >= -25 && temperature < -15) { NtOX =  0.9; KtOX =  0.5; KttOX =  0.5; KtttOX =    1.0; };
    if(temperature >= -15 && temperature <  -5) { NtOX =  1.0; KtOX =  0.6; KttOX =  0.5; KtttOX =    1.0; };
    if(temperature >=  -5 && temperature <   5) { NtOX =  1.3; KtOX =  0.8; KttOX =  0.6; KtttOX =    1.0; };
    if(temperature >=   5 && temperature <  15) { NtOX =  1.5; KtOX =  0.9; KttOX =  0.6; KtttOX =    1.0; };
    if(temperature >=  15 && temperature <  25) { NtOX =  1.7; KtOX =  1.0; KttOX =  1.0; KtttOX =    1.0; };
    if(temperature >=  25 && temperature <  35) { NtOX =  2.0; KtOX =  1.2; KttOX =  2.8; KtttOX =    8.5; };
    if(temperature >=  35 && temperature <  45) { NtOX =  2.5; KtOX =  1.5; KttOX =  5.0; KtttOX =   23.0; };
    if(temperature >=  45)                      { NtOX =  3.7; KtOX =  2.2; KttOX =  5.3; KtttOX =  103.0; };
  #endif

  #ifdef VOC_B4
    if(temperature < -25)                       { NtVOC =  0.9; KtVOC =  0.5; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >= -25 && temperature < -15) { NtVOC =  0.9; KtVOC =  0.5; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >= -15 && temperature <  -5) { NtVOC =  1.0; KtVOC =  0.6; KttVOC =  0.5; KtttVOC =    1.0; };
    if(temperature >=  -5 && temperature <   5) { NtVOC =  1.3; KtVOC =  0.8; KttVOC =  0.6; KtttVOC =    1.0; };
    if(temperature >=   5 && temperature <  15) { NtVOC =  1.5; KtVOC =  0.9; KttVOC =  0.6; KtttVOC =    1.0; };
    if(temperature >=  15 && temperature <  25) { NtVOC =  1.7; KtVOC =  1.0; KttVOC =  1.0; KtttVOC =    1.0; };
    if(temperature >=  25 && temperature <  35) { NtVOC =  2.0; KtVOC =  1.2; KttVOC =  2.8; KtttVOC =    8.5; };
    if(temperature >=  35 && temperature <  45) { NtVOC =  2.5; KtVOC =  1.5; KttVOC =  5.0; KtttVOC =   23.0; };
    if(temperature >=  45)                      { NtVOC =  3.7; KtVOC =  2.2; KttVOC =  5.3; KtttVOC =  103.0; };
  #endif
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
    WEuH2S = analogRead(A0) * (5.0 / 1024) * 1000;
    AEuH2S = analogRead(A1) * (5.0 / 1024) * 1000;
      WEcH2S = equationWEc(WEcH2S, WEuH2S, WEeH2S, NtH2S, AEuH2S, AEeH2S);
      H2SConcentrationPPB = WEcH2S / sensitivityH2S;
      H2SConcentrationPPM = H2SConcentrationPPB / 1000;

  // CO-B4 (Carbon Monoxide)
    WEuCO = analogRead(A3) * (5.0 / 1024) * 1000;
    AEuCO = analogRead(A4) * (5.0 / 1024) * 1000;
      WEcCO = equationWEc(WEcCO, WEuCO, WEeCO, NtCO, AEuCO, AEeCO);
      COConcentrationPPB = WEcCO / sensitivityCO;
      COConcentrationPPM = COConcentrationPPB / 1000;
      
  // VOC-B4 (Volatile Organic Compound)
    WEuVOC = analogRead(A6) * (5.0 / 1024) * 1000;
    AEuVOC = analogRead(A7) * (5.0 / 1024) * 1000;
      WEcVOC = equationWEc(WEcVOC, WEuVOC, WEeVOC, NtVOC, AEuVOC, AEeVOC);
      VOCConcentrationPPB = WEcVOC / sensitivityVOC;
      VOCConcentrationPPM = VOCConcentrationPPB / 1000;
      
  // NO2-B43F (Nitrogen Dioxide)
    WEuNO2 = analogRead(A8) * (5.0 / 1024) * 1000;
    AEuNO2 = analogRead(A9) * (5.0 / 1024) * 1000;
      WEcNO2 = equationWEc(WEcNO2, WEuNO2, WEeNO2, NtNO2, AEuNO2, AEeNO2);
      NO2ConcentrationPPB = WEcNO2 / sensitivityNO2;
      NO2ConcentrationPPM = NO2ConcentrationPPB / 1000;

  // OX-B431 (Oxidising - Ozone + Nitrogen Dioxide)
    WEuOX = analogRead(A11) * (5.0 / 1024) * 1000;
    AEuOX = analogRead(A12) * (5.0 / 1024) * 1000;
      WEcOX = equationWEc(WEcOX, WEuOX, WEeOX, NtOX, AEuOX, AEeOX);
      OXConcentrationPPB = WEcOX / sensitivityOX;
      OXConcentrationPPM = OXConcentrationPPB / 1000;

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
    Serial.print("                      WEu Raw value: ");
    Serial.print(WEuH2S);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuH2S);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcH2S);
    Serial.print(", Concentrations: ");
    Serial.print(H2SConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(H2SConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n");

    // CO-B4 (Carbon Monoxide)
    Serial.print("CO-B4 (Carbon Monoxide): ");
    Serial.print("                        WEu Raw value: ");
    Serial.print(WEuCO);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuCO);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcCO);
    Serial.print(", Concentrations: ");
    Serial.print(COConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(COConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n");

    // VOC-B4 (Volatile Organic Compound)
    Serial.print("VOC-B4 (Volatile Organic Compound): ");
    Serial.print("             WEu Raw value: ");
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

    // NO2-B43F (Nitrogen Dioxide)
    Serial.print("NO2-B43F (Nitrogen Dioxide): ");
    Serial.print("                    WEu Raw value: ");
    Serial.print(WEuNO2);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuNO2);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcNO2);
    Serial.print(", Concentrations: ");
    Serial.print(NO2ConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(NO2ConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n");

    // OX-B431 (Oxidising -> Ozone + Nitrogen Dioxide)
    Serial.print("OX-B431 (Oxidising -> Ozone + Nitrogen Dioxide): ");
    Serial.print("WEu Raw value: ");
    Serial.print(WEuOX);
    Serial.print(", AEu Raw Value: ");
    Serial.print(AEuOX);
    Serial.print(", WEc Raw Value: ");
    Serial.print(WEcOX);
    Serial.print(", Concentrations: ");
    Serial.print(OXConcentrationPPB);
    Serial.print(" ppb, ");
    Serial.print(OXConcentrationPPM);
    Serial.print(" ppm");
    Serial.print("\n\n");

  delay(12000); // Time between measurement
}
