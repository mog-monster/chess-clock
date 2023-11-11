// here will be my chess clock stuff

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

static bool running;
unsigned long removalAmount = 6000000;
unsigned long milliMinus = millis();
unsigned long milliSeconds = removalAmount - milliMinus;
unsigned long centiSeconds = milliSeconds / 10;
unsigned long printedCentiSeconds = centiSeconds % 10;
unsigned long deciSeconds = milliSeconds/100;
unsigned long printedDeciSeconds = deciSeconds % 10;
unsigned long seconds = milliSeconds/1000;
if(seconds==1){
  running = 1;
}
unsigned long printedSeconds = seconds % 10;
unsigned long decaSeconds = milliSeconds/10000;
unsigned long printedDecaSeconds = decaSeconds % 6;
unsigned long minutes = milliSeconds/60000;
unsigned long printedMinutes = minutes % 10;
unsigned long decaMinutes = milliSeconds/600000;
unsigned long printedDecaMinutes = decaMinutes % 10;
unsigned long hectoMinutes = milliSeconds/6000000;

if(running){
  if((milliSeconds == 0) || (hectoMinutes > 2)){
    Serial.println("0 : 0 : 0 :: 0 : 0 :: 0 : 0");
    while((milliSeconds == 0) || (hectoMinutes > 2)){
      delay(1);
    }
  }
}

Serial.print(hectoMinutes);
Serial.print(" : ");
Serial.print(printedDecaMinutes);
Serial.print(" : ");
Serial.print(printedMinutes);
Serial.print(" :: ");
Serial.print(printedDecaSeconds);
Serial.print(" : ");
Serial.print(printedSeconds);
Serial.print(" :: ");
Serial.print(printedDeciSeconds);
Serial.print(" : ");
Serial.println(printedCentiSeconds);


}


