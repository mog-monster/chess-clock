long baseMilliSeconds = 1;
long totalMilliSeconds = 1;
long trackingMilliMinus = 1;
long trackingMilliPlus;
long totalPaused = 1;
long valueUnderZero;
int mainButtonPin = A5;
int minutesKnob = A3;
int secondsKnob = A4;

void setup() {
  
  pinMode(mainButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println();
}

void loop() {

  static bool mainButtonChanged;
  static bool timersRunning;
  bool timersFinished = 0;
  if(totalMilliSeconds == 0){
    timersFinished = 1;
  }
  static long pausedStart = 1;
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
      long moreTotalPaused = trackingMilliPlus - baseMilliSeconds;
      totalPaused = totalPaused + moreTotalPaused;
    }
    else{
      pausedStart = trackingMilliMinus;
      trackingMilliPlus = baseMilliSeconds;
    }
    baseMilliSeconds = totalMilliSeconds;
  }
  mainButtonChanged = mainButtonPressed;
  if(timersFinished){
    if(backToPause){
      baseMilliSeconds = 1;
      totalMilliSeconds = 1;
      totalPaused++;
      timersRunning = 0;
      pausedStart = trackingMilliMinus;
      delay(1000);
    }
    else{
      finishedTimers();
    }
  }
  else{
    if(timersRunning){
      white(pausedStart, careAboutPause);
    }
    else{
      pausedTimers();
    }
  }
}


void pausedTimers(){
  long analogInOne = analogRead(A4);
  long analogInTwo = analogRead(A3);
  long mapOne = map(analogInOne, 0, 1023, 0, 19);
  long mapTwo = map(analogInTwo, 0, 1023, 0, 99);
  long halfMinuteAdd = mapOne*30000;
  long decaMinuteAdd = mapTwo*600000;
  totalMilliSeconds = baseMilliSeconds + halfMinuteAdd + decaMinuteAdd;  
  long centiSeconds = totalMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = totalMilliSeconds/100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = totalMilliSeconds/1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = totalMilliSeconds/10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = totalMilliSeconds/60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = totalMilliSeconds/600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = totalMilliSeconds/6000000;
  Serial.print(hectoMinutes);
  Serial.print(" : ");
  Serial.print(printedDecaMinutes);
  Serial.print(" : ");
  Serial.print(printedMinutes);
  Serial.print(" :: ");
  Serial.print(printedDecaSeconds);
  Serial.print(" : ");
  Serial.print(printedSeconds);
  Serial.print(". :: ");
  Serial.print(printedDeciSeconds);
  Serial.print(" : ");
  Serial.println(printedCentiSeconds);
}

void white(long pausedStart, bool care){
  long milliMinus = millis();
  trackingMilliMinus = milliMinus;
  if(care){
  	long pausedDuration = milliMinus - pausedStart;
    totalPaused = totalPaused + pausedDuration;
  }
  totalPaused = totalPaused - valueUnderZero;  
  valueUnderZero = 0;
  milliMinus = milliMinus - totalPaused;
  totalMilliSeconds = baseMilliSeconds - milliMinus;
  if(totalMilliSeconds <= 0){
    valueUnderZero = totalMilliSeconds;
    totalMilliSeconds = 0;
  }
  long centiSeconds = totalMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = totalMilliSeconds/100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = totalMilliSeconds/1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = totalMilliSeconds/10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = totalMilliSeconds/60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = totalMilliSeconds/600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = totalMilliSeconds/6000000;
  Serial.print(hectoMinutes);
  Serial.print(" : ");
  Serial.print(printedDecaMinutes);
  Serial.print(" : ");
  Serial.print(printedMinutes);
  Serial.print(" :: ");
  Serial.print(printedDecaSeconds);
  Serial.print(" : ");
  Serial.print(printedSeconds);
  Serial.print(". :: ");
  Serial.print(printedDeciSeconds);
  Serial.print(" : ");
  Serial.println(printedCentiSeconds);
}

void finishedTimers(){
  Serial.println("g : o : o :: d : g. ::   :");
}
