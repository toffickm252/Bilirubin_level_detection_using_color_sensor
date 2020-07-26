#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE); //3f//27

int frequency = 0;
int R_frequency = 0;
int G_frequency = 0;
float B_frequency = 0;
float percentage = 0.0;
int total = 0;
float division = 0.0;
float bilirubin = 0.0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  lcd.begin(16,2);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.home();
  lcd.print("BILIRUBIN LEVEL");
  lcd.setCursor(0,1);
  lcd.print("DETECTOR");
  delay(2000);
  lcd.clear();

  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  //frequency2 = pulseIn(sensorOut, LOW);
  //frequency3 = pulseIn(sensorOut, LOW);
  //frequency2 = pulseIn(sensorOut, LOW);
  //frequency3 = pulseIn(sensorOut, LOW);
  
  lcd.setCursor(0,0);
  lcd.print("RGB VALUES");
  lcd.setCursor(0,1);
  lcd.print("MANIPULATION");
  delay(2000);
  lcd.clear();


  //lcd.setCursor(0,0);
  //lcd.print(frequency1);
  R_frequency = map(frequency, 25, 72, 255, 0);
  lcd.setCursor(0,0);
  lcd.print("R= ");//printing name
  lcd.print(R_frequency);//printing RED color frequency
  lcd.print("  ");
  delay(1000);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  
  G_frequency= map(frequency, 30, 90, 255, 0);
  // Printing the value on the serial monitor
  lcd.setCursor(0,1);
  lcd.print("G= ");//printing name
  lcd.print(G_frequency);//printing RED color frequency
  lcd.print("  ");
  delay(1000);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  B_frequency= map(frequency, 25, 70, 255, 0);
  
  // Printing the value on the serial monitor
  //lcd.setCursor(0,1);
  lcd.print("B= ");//printing name
  lcd.print(B_frequency);//printing RED color frequency
  lcd.println("  ");
  delay(1000);
  lcd.clear();

  total = R_frequency + G_frequency + B_frequency;
  division = B_frequency / total;
  percentage = division * 100;
  //Serial.println(total);
  //Serial.print(division);

  
  lcd.setCursor(0,0);
  lcd.print("NORMAL BLUE %=");
  lcd.setCursor(0,1);
  lcd.print(percentage);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  bilirubin = -0.75979 * percentage + 25.5876;
  Serial.println(bilirubin);

  if (bilirubin < 4){
    lcd.print("NORMAL JAUNDICE");
  }
  else if(bilirubin > 4 && bilirubin <= 10){
    lcd.print("MILD JAUNDICE");
  }
  else if(bilirubin > 10 && bilirubin <= 20){
    lcd.print("SEVERE JAUNDICE");
  }
  else if(bilirubin > 20){
    lcd.print("CRITICAL JAUNDICE"); 
  }
  delay(3000);
  lcd.clear();

 
  
}
