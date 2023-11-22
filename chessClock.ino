long startingAmount = 10000;
long totalMilliSeconds = startingAmount;
int mainButtonPin = A5;

void setup() {
  
  pinMode(mainButtonPin, INPUT_PULLUP);
		Serial.begin(9600);
}

void loop() {
  
  static bool mainButtonChanged;
  static bool timersRunning;
  static bool timersFinished;
  static long pausedStart;
  static long pausedEnd;
  static long pausedDuration;
  bool careAboutPause;
  bool mainButtonPressed = digitalRead(mainButtonPin);
  mainButtonPressed = !mainButtonPressed;
  if((mainButtonPressed) && (!mainButtonChanged)){
      mainButtonChanged = 1;
      timersRunning = !timersRunning;
    if(timersRunning){
      pausedEnd = millis();
      careAboutPause = 1;
    }
    else{
      pausedStart = millis();
    }
  }
  mainButtonChanged = mainButtonPressed;
  if(totalMilliSeconds == 0){
    delay(5000);
    finishedTimers();
  }
  else{
    if(timersRunning){
      pausedDuration = pausedEnd - pausedStart; 
      totalMilliSeconds = white(totalMilliSeconds, pausedDuration, careAboutPause);
    }
    else{
      totalMilliSeconds = pausedTimers(totalMilliSeconds);
    }
  }
}

long pausedTimers(long milliSeconds){
  long centiSeconds = milliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = milliSeconds/100;
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
    return(milliSeconds);
}

long white(long milliSeconds, long pausedDuration, bool care){
  long milliMinus = millis();
  milliSeconds = startingAmount - milliMinus;
  if(care){
  milliSeconds = milliSeconds + pausedDuration;
  }
  long centiSeconds = milliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = milliSeconds/100;
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
  if(milliSeconds<=0){
    milliSeconds = 0;
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
  return(milliSeconds);
}

void finishedTimers(){
  Serial.println("good g.");
}