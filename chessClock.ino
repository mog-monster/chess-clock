// here will be my chess clock stuff

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

static bool running;
long removalAmount = 10000;
long milliMinus = millis();
long milliSeconds = removalAmount - milliMinus;
long centiSeconds = milliSeconds / 10;
long printedCentiSeconds = centiSeconds % 10;
long deciSeconds = milliSeconds/100;
if(deciSeconds==1){
  running = 1;
}
long printedDeciSeconds = deciSeconds % 10;
long seconds = milliSeconds/1000;
long printedSeconds = seconds % 10;
long decaSeconds = milliSeconds/10000;
long printedDecaSeconds = decaSeconds % 6;
long minutes = milliSeconds/60000;
long printedMinutes = minutes % 10;
long decaMinutes = milliSeconds/600000;
long printedDecaMinutes = decaMinutes % 10;
long hectoMinutes = milliSeconds/6000000;

if(running){
  if(milliSeconds <= 0){
    Serial.println("0 : 0 : 0 :: 0 : 0 :: 0 : 0");
    while(true){
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


