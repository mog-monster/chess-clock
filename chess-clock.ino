long whiteBase = 1;
long blackBase = 1;
long whiteMilliSeconds = 1;
long blackMilliSeconds = 1;
long trackingWhiteMinus = 1;
long trackingBlackMinus = 1;
long trackingWhitePlus;
long trackingBlackPlus;
long totalPaused = 1;
long totalBlackPaused = 1;
long totalWhitePaused = 1;
long whiteValueUnder;
long blackValueUnder;
bool blackCare;
bool whiteCare;
int whiteButtonPin = A5;
int blackButtonPin = A4;
int pauseButtonPin = A3;
int otherButtonPin = A2;
int secondsKnob = A1;
int minutesKnob = A0;

void setup() {

  pinMode(whiteButtonPin, INPUT_PULLUP);
  pinMode(blackButtonPin, INPUT_PULLUP);
  pinMode(pauseButtonPin, INPUT_PULLUP);
  pinMode(otherButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println();
}

void loop() {

  static bool whiteTurn = 1;
  bool timersFinished = 0;
  if(whiteMilliSeconds == 0) || (blackMilliSeconds == 0){
    timersFinished = 1;
  }
  static bool pauseButtonChanged;
  static bool timersRunning;
  static long whitePausedStart = 1;
  static long blackPausedStart = 1;
  blackCare = 1;
  whiteCare = 1;
  static bool whiteJustEnded = 0;
  static bool blackJustEnded = 0;
  bool backToPause = 0;
  bool pauseButtonPressed = digitalRead(pauseButtonPin);
  pauseButtonPressed = !pauseButtonPressed;
  if((pauseButtonPressed) && (!pauseButtonChanged)){
    backToPause = 1;
    timersRunning = !timersRunning;
    if(timersRunning){
      careAboutPause = 1;
      long moreTotalPaused = whiteTrackingPlus - whiteBase;
      moreTotalPaused = blackTrackingPlus - blackBase;
      whiteTotalPaused = whiteTotalPaused + moreTotalPaused;
      blackTotalPaused = blackTotalPaused + moreTotalPaused;
    }
    else{
      whitePausedStart = whiteTrackingMinus;
      blackPausedStart = blackTrackingMinus;
      whiteTrackingPlus = whiteBase;
      blackTrackingPlus = blackBase;
    }
    whiteBase = whiteMilliSeconds;
    blackBase = blackMilliSeconds;
  }
  pauseButtonChanged = pauseButtonPressed;
  
  if(timersFinished){
    if(backToPause){
      whiteBase = 1;
      blackBase = 1;
      whiteMilliSeconds = 1;
      blackMilliSeconds = 1;
      whiteTotalPaused++;
      blackTotalPaused++;
      timersRunning = 0;
      whitePausedStart = trackingWhiteMinus;
      whitePausedStart = trackingWhitePlus;
      delay(3000);
    }
    else{
      finishedTimers();
    }
  }
  else{
    if(timersRunning){
      if(whiteTurn){
        white(whitePausedStart);
        static bool whiteButtonChanged;
        bool whiteButtonPressed = digitalRead(whiteButtonPin);
        whiteButtonPressed = !whiteButtonPressed;
        if((whiteButtonPressed) && (!whiteButtonChanged)){
          whiteTurn = 0;
          whiteJustEnded = 1;
          bool moreBlackPaused = blackTrackingPlus - blackBase;
          blackTotalPaused = blackTotalPaused + moreBlackPlaused;
        }
        whiteBase = whiteMilliSeconds;
        whiteButtonChanged = whiteButtonPressed;
      }
      else{
        black(blackPausedStart);
        static blackButtonChanged;
        bool blackButtonPressed = digitalRead(blackButtonPin);
        blackButtonPressed = !blackButtonPressed;
        if((blackButtonPressed) && (!blackButtonChanged)){
          blackTurn = 0;
          blackJustEnded = 1;
          bool moreWhitePaused = whiteTrackingPlus - whiteBase;
          whiteTotalPaused = whiteTotalPaused + moreWhitePlaused;
        }
        blackBase = blackMilliSeconds;
        blackButtonChanged = blackButtonPressed;
      }

    }
    else{
      pausedTimers();
    }
  }
}


void pausedTimers(){
  static bool otherButtonChanged;
  static bool doAddition = 1;
  bool otherButtonPressed = digitalRead(otherButtonPin);
  otherButtonPressed = !otherButtonPressed;
    if((otherButtonPressed) && (!otherButtonChanged)){
	  doAddition = !doAddition;
    }
    static bool whiteButtonChanged;
    bool whiteButtonPressed = digitalRead(whiteButtonPin);
    whiteButtonPressed = !whiteButtonPressed;
    if((whiteButtonPressed) && (!whiteButtonChanged)){
      whiteTurn = 0;
      whiteJustEnded = 1;
      bool moreBlackPaused = blackTrackingPlus - blackBase;
      blackTotalPaused = blackTotalPaused + moreBlackPlaused;
    }
    whiteBase = whiteMilliSeconds;
    whiteButtonChanged = whiteButtonPressed;
  otherButtonChanged = otherButtonPressed;
  long minutesInput = analogRead(minutesKnob);
  long secondsInput = analogRead(secondsKnob);
  long minutesMap = map(minutesInput, 0, 1023, 0, 19);
  long secondsMap = map(secondsInput, 0, 1023, 0, 99);
  long halfMinuteAdd = minutesMap*30000;
  long decaMinuteAdd = secondsMap*600000;
  if(doAddition){
    totalMilliSeconds = baseMilliSeconds + halfMinuteAdd + decaMinuteAdd;
  }
  else{
    totalMilliSeconds = baseMilliSeconds - halfMinuteAdd - decaMinuteAdd;
  }
  if(totalMilliSeconds > 59999999){
    totalMilliSeconds = 59999999;
  }
  if(totalMilliSeconds < 1){
    totalMilliSeconds = 1;
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

void white(long pausedStart){
  long milliMinus = millis();
  whiteTrackingMinus = milliMinus;
  if(whiteCare){
  	long pausedDuration = milliMinus - pausedStart;
    whiteTotalPaused = totalPaused + pausedDuration;
    whiteCare = 0;
  }
  whiteTotalPaused = totalPaused - whiteValueUnder;  
  whiteValueUnder = 0;
  milliMinus = milliMinus - totalPaused;
  whiteMilliSeconds = whiteBase - milliMinus;
  if(whiteMilliSeconds <= 0){
    whiteValueUnder = whiteMilliSeconds;
    whiteMilliSeconds = 0;
  }
  long centiSeconds = whiteMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = whiteMilliSeconds/100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = whiteMilliSeconds/1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = whiteMilliSeconds/10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = whiteMilliSeconds/60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = whiteMilliSeconds/600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = whiteMilliSeconds/6000000;
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
  Serial.print(printedCentiSeconds);
  Serial.println("    WHITE");
}

void black(long pausedStart){
  long milliMinus = millis();
  blackTrackingMinus = milliMinus;
  if(blackCare){
  	long pausedDuration = milliMinus - pausedStart;
    blackTotalPaused = totalPaused + pausedDuration;
    blackCare = 0;
  }
  blackTotalPaused = blackTotalPaused - blackValueUnder;  
  blackValueUnder = 0;
  milliMinus = milliMinus - blackTotalPaused;
  blackMilliSeconds = blackBase - milliMinus;
  if(blackMilliSeconds <= 0){
    blackValueUnder = blackMilliSeconds;
    blackMilliSeconds = 0;
  }
  long centiSeconds = blackMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = blackMilliSeconds/100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = blackMilliSeconds/1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = blackMilliSeconds/10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = blackMilliSeconds/60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = blackMilliSeconds/600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = blackMilliSeconds/6000000;
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
  Serial.print(printedCentiSeconds);
  Serial.print("    BLACK");
}

void finishedTimers(){
  Serial.println("g : o : o :: d : g. ::   :");
}
