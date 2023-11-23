long removalAmount = 10000;
long totalMilliSeconds = removalAmount;
long valueBelowZero;
long trackingMilliMinus;
long totalPaused;
int mainButtonPin = A5;

void setup() {
  
  pinMode(mainButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  static bool mainButtonChanged;
  static bool timersRunning;
  static bool timersFinished = 0;
  if(totalMilliSeconds == 0){
    timersFinished = 1;
  }
  static long pausedStart;
  bool careAboutPause = 0;
  bool backToPause = 0;
  bool mainButtonPressed = digitalRead(mainButtonPin);
  mainButtonPressed = !mainButtonPressed;
  if((mainButtonPressed) && (!mainButtonChanged)){
    mainButtonChanged = 1;
    backToPause = 1;
    timersRunning = !timersRunning;
    if(timersRunning){
      careAboutPause = 1;
    }
    else{
      pausedStart = trackingMilliMinus;
    }
  }
  mainButtonChanged = mainButtonPressed;
  if(timersFinished){
    if(backToPause){
      totalMilliSeconds = removalAmount;
      totalPaused = totalPaused + removalAmount;
      timersRunning = 0;
      pausedStart = trackingMilliMinus;
    }
    else{
      finishedTimers();
    }
  }
  else{
    if(timersRunning){
      totalMilliSeconds = white(totalMilliSeconds, pausedStart, careAboutPause);
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

long white(long milliSeconds, long pausedStart, bool care){
  long milliMinus = millis();
  trackingMilliMinus = milliMinus;
  if(care){
  	long pausedDuration = milliMinus - pausedStart;
    totalPaused = totalPaused + pausedDuration;
  }
  totalPaused = totalPaused - valueBelowZero;
  valueBelowZero = 0;
  milliMinus = milliMinus - totalPaused;
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
  if(milliSeconds <= 0){
    valueBelowZero = milliSeconds;
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