const long removalAmount = 10000;
long totalMilliSeconds = removalAmount;
long trackingMilliMinus;
long totalPaused;
int mainButtonPin = A5;

void setup() {
  
  pinMode(mainButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  Serial.print("MilliSeconds at loop start");
  Serial.println(totalMilliSeconds);
  Serial.print("Total paused at loop start");
  Serial.println(totalPaused);
  static bool mainButtonChanged;
  static bool timersRunning;
  static bool timersFinished;
  static long pausedStart;
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
    Serial.print("MilliSeconds after white");
    Serial.println(totalMilliSeconds);
    Serial.print("Total paused after white");
    Serial.println(totalPaused);
  }
  else{
    totalMilliSeconds = pausedTimers(totalMilliSeconds);
    Serial.print("MilliSeconds after pause");
    Serial.println(totalMilliSeconds);
    Serial.print("Total paused after pause");
    Serial.println(totalPaused);
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
  Serial.print("MilliMinus step 1 ");
  Serial.println(milliMinus);
  trackingMilliMinus = milliMinus;
  if(care){
  	long pausedDuration = milliMinus - pausedStart;
    Serial.print("MilliMinus step 2 ");
    Serial.println(milliMinus);
    totalPaused = totalPaused + pausedDuration;
    Serial.print("MilliMinus step 3 ");
    Serial.println(milliMinus);
  }
  milliMinus = milliMinus - totalPaused;
  Serial.print("MilliMinus step 4 ");
  Serial.println(milliMinus);
  milliSeconds = removalAmount - milliMinus;
  Serial.print("MilliMinus step 5 ");
  Serial.println(milliMinus);
  Serial.print("milliseconds after calculations");
  Serial.println(milliSeconds);
  Serial.print("total pause after calculations");
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