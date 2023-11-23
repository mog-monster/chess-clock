long removalAmount = 10000;
long totalMilliSeconds = removalAmount;
long constantMillis = millis();
long trackingMilliMinus;
long pausedMillis;
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
      careAboutPause = 1;
    }
    else{
      pausedStart = trackingMilliMinus;
    }
  }
  mainButtonChanged = mainButtonPressed;
  if(timersRunning){
    totalMilliSeconds = white(totalMilliSeconds, pausedStart, careAboutPause);
  }
  else{
    totalMilliSeconds = pausedTimers(totalMilliSeconds);
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

long white(long milliSeconds, long pausedStart, bool care){
  long milliMinus = millis();
  trackingMilliMinus = milliMinus;
  if(care){
  	long pausedDuration = milliMinus - pausedStart;
    pausedMillis = pausedMillis + pausedDuration;
  }
  milliMinus = milliMinus - pausedMillis;
  milliSeconds = removalAmount - milliMinus;
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
