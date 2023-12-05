long whiteBase = 1;
long blackBase = 1;
long whiteMilliSeconds = 1;
long blackMilliSeconds = 1;
long whiteTrackingMinus = 1;
long blackTrackingMinus = 1;
long whiteTotalPaused = 1;
long blackTotalPaused = 1;
long whiteValueUnder;
long blackValueUnder;
bool blackStarted;
bool whiteStarted;

int whiteButtonPin = A5;
int blackButtonPin = A0;
int pauseButtonPin = A4;
int otherButtonPin = A3;
int secondsKnob = A2;
int minutesKnob = A1;
int whiteLatchPin = 3;
int whiteClockPin = 5;
int whiteDataPin = 7;
int blackLatchPin = 13;
int blackClockPin = 11;
int blackDataPin = 9;

int allBytes [10] = {B11111100, B01100000, B11011010, B11110010,
  B01100110, B10110110, B10111110, B11100000, B11111110,
                   B11110110};

void setup() {
  pinMode(whiteButtonPin, INPUT_PULLUP);
  pinMode(blackButtonPin, INPUT_PULLUP);
  pinMode(pauseButtonPin, INPUT_PULLUP);
  pinMode(otherButtonPin, INPUT_PULLUP);
  pinMode(whiteLatchPin, OUTPUT);
  pinMode(whiteClockPin, OUTPUT);
  pinMode(whiteDataPin, OUTPUT);
  pinMode(blackLatchPin, OUTPUT);
  pinMode(blackClockPin, OUTPUT);
  pinMode(blackDataPin, OUTPUT);
  Serial.begin(9600);
  Serial.println();
}

void loop() {

  bool timersFinished = 0;
  if ((whiteMilliSeconds == 0) || (blackMilliSeconds == 0)) {
    timersFinished = 1;
  }
  bool timersJustRestarted = 0;
  static long whiteMorePaused;
  static long blackMorePaused;
  static bool bothChange = 1;
  static bool whiteOrBlackChange;
  static bool whiteTurn = 1;
  static bool pauseButtonChanged;
  static bool timersRunning;
  static long whitePausedStart = 1;
  static long blackPausedStart = 1;
  bool backToPause = 0;
  bool pauseButtonPressed = digitalRead(pauseButtonPin);
  pauseButtonPressed = !pauseButtonPressed;
  if ((pauseButtonPressed) && (!pauseButtonChanged)) {
    backToPause = 1;
    timersRunning = !timersRunning;
    if (timersRunning) {
      timersJustRestarted = 1;
      bothChange = 1;
    } 
    else {
      whitePausedStart = whiteTrackingMinus;
      blackPausedStart = blackTrackingMinus;
      if(whiteTurn){
        whiteMorePaused = whiteBase - whiteMilliSeconds;
        whiteTotalPaused = whiteTotalPaused + whiteMorePaused;
      }
      else{
        blackMorePaused = blackBase - blackMilliSeconds;
        blackTotalPaused = blackTotalPaused + blackMorePaused;
      }
    }
    whiteBase = whiteMilliSeconds;
    blackBase = blackMilliSeconds;
  }
  pauseButtonChanged = pauseButtonPressed;

  static bool whiteButtonChanged;
  bool whiteButtonPressed = digitalRead(whiteButtonPin);
  whiteButtonPressed = !whiteButtonPressed;
  if ((whiteButtonPressed) && (!whiteButtonChanged)) {
    if(timersRunning){
      if(whiteTurn){
        whiteTurn = 0;
        blackStarted = 1;
        whitePausedStart = whiteTrackingMinus;
        whiteMorePaused = whiteBase - whiteMilliSeconds;
        whiteTotalPaused = whiteTotalPaused + whiteMorePaused;
        blackBase = blackMilliSeconds;
        whiteBase = whiteMilliSeconds;
      }
    }
    else{
      if(bothChange){
        bothChange = 0;
        whiteOrBlackChange = 1;
      }
      else if(whiteOrBlackChange){
        whiteOrBlackChange = 1;
      }
      else{
        bothChange = 1;
      }
    }
  }
  whiteButtonChanged = whiteButtonPressed;

  static bool blackButtonChanged;
  bool blackButtonPressed = digitalRead(blackButtonPin);
  blackButtonPressed = !blackButtonPressed;
  if ((blackButtonPressed) && (!blackButtonChanged)) {
    if(timersRunning){
      if(!whiteTurn){
        whiteTurn = 1;
        whiteStarted = 1;
        blackPausedStart = blackTrackingMinus;
        blackMorePaused = blackBase - blackMilliSeconds;
        blackTotalPaused = blackTotalPaused + blackMorePaused;
        blackBase = blackMilliSeconds;
        whiteBase = whiteMilliSeconds;
      }
    }
    else{
      if(bothChange){
        bothChange = 0;
        whiteOrBlackChange = 0;
      }
      else if(whiteOrBlackChange){
        whiteOrBlackChange = 0;
      }
      else{
        bothChange = 1;
      }
    }

  }
  blackButtonChanged = blackButtonPressed;

  if(timersJustRestarted){
    if(whiteTurn){
      whiteStarted = 1;
    }
    else{
      blackStarted = 1;
    }
  }
  if (timersFinished) {
    if (backToPause) {
      if(whiteTurn){
        whiteMorePaused = whiteBase - whiteMilliSeconds;
        whiteTotalPaused = whiteTotalPaused + whiteMorePaused;
        whitePausedStart = whiteTrackingMinus;
      }
      else{
        blackMorePaused = blackBase - blackMilliSeconds;
        blackTotalPaused = blackTotalPaused + blackMorePaused;
        blackPausedStart = blackTrackingMinus;
      }
      whiteBase = 1;
      blackBase = 1;
      whiteMilliSeconds = 1;
      blackMilliSeconds = 1;
      whiteTotalPaused++;
      blackTotalPaused++;
      timersRunning = 0;
      whiteTurn = 1;
      delay(3000);
    } 
    else {
      finishedTimers();
    }
  } else {
    if (timersRunning) {
      if (whiteTurn) {
        white(whitePausedStart);

      } 
      else {
        black(blackPausedStart);
      }

    } 
    else {
      pausedTimers(bothChange, whiteOrBlackChange);
    }
  }
}


void pausedTimers(bool bothChange, bool whiteOrBlackChange) {
  static bool otherButtonChanged;
  static bool doAddition = 1;
  bool otherButtonPressed = digitalRead(otherButtonPin);
  otherButtonPressed = !otherButtonPressed;
  if ((otherButtonPressed) && (!otherButtonChanged)) {
    doAddition = !doAddition;
  }
  otherButtonChanged = otherButtonPressed;
  long minutesInput = analogRead(minutesKnob);
  long secondsInput = analogRead(secondsKnob);
  long minutesMap = map(minutesInput, 0, 1023, 0, 19);
  long secondsMap = map(secondsInput, 0, 1023, 0, 60);
  long halfMinuteAdd = minutesMap * 30000;
  long decaMinuteAdd = secondsMap * 600000;

  if (doAddition) {
    if(bothChange){
      whiteMilliSeconds = whiteBase + halfMinuteAdd + decaMinuteAdd;
      blackMilliSeconds = blackBase + halfMinuteAdd + decaMinuteAdd;
    }
    else{
      if(whiteOrBlackChange){
        whiteMilliSeconds = whiteBase + halfMinuteAdd + decaMinuteAdd;
        blackMilliSeconds = blackBase;
      }
      else{
            blackMilliSeconds = blackBase + halfMinuteAdd + decaMinuteAdd;
            whiteMilliSeconds = whiteBase;
      }
    }
  } 
  else {
    if(bothChange){
      whiteMilliSeconds = whiteBase - halfMinuteAdd - decaMinuteAdd;
      blackMilliSeconds = blackBase - halfMinuteAdd - decaMinuteAdd;
    }
    else{
      if(whiteOrBlackChange){
        whiteMilliSeconds = whiteBase - halfMinuteAdd - decaMinuteAdd;
        blackMilliSeconds = blackBase;
      }
      else{
            blackMilliSeconds = blackBase - halfMinuteAdd - decaMinuteAdd;
            whiteMilliSeconds = whiteBase;
      }
    }
  }
  if(whiteMilliSeconds > 36000000){
    whiteMilliSeconds = 36000000;
  }
  if(blackMilliSeconds > 36000000){
    blackMilliSeconds = 36000000;
  }
  if(whiteMilliSeconds < 1){
    whiteMilliSeconds = 1;
  }
  if(blackMilliSeconds < 1){
    blackMilliSeconds = 1;
  }
  long centiSeconds = whiteMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = whiteMilliSeconds / 100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = whiteMilliSeconds / 1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = whiteMilliSeconds / 10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = whiteMilliSeconds / 60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = whiteMilliSeconds / 600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = whiteMilliSeconds / 6000000;
  long whiteSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};	
  
  digitalWrite(whiteLatchPin, LOW);
  for (int whiteWorkingSegment = 0; whiteWorkingSegment < 7; whiteWorkingSegment++){
      shiftOut(whiteDataPin, whiteClockPin, MSBFIRST, allBytes[whiteSegments[whiteWorkingSegment]]);
  }
  digitalWrite(whiteLatchPin, HIGH);
  
  centiSeconds = blackMilliSeconds / 10;
  printedCentiSeconds = centiSeconds % 10;
  deciSeconds = blackMilliSeconds / 100;
  printedDeciSeconds = deciSeconds % 10;
  seconds = blackMilliSeconds / 1000;
  printedSeconds = seconds % 10;
  decaSeconds = blackMilliSeconds / 10000;
  printedDecaSeconds = decaSeconds % 6;
  minutes = blackMilliSeconds / 60000;
  printedMinutes = minutes % 10;
  decaMinutes = blackMilliSeconds / 600000;
  printedDecaMinutes = decaMinutes % 10;
  hectoMinutes = blackMilliSeconds / 6000000;
  long blackSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};	
  
  digitalWrite(blackLatchPin, LOW);
  for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
      shiftOut(blackDataPin, blackClockPin, MSBFIRST, allBytes[blackSegments[blackWorkingSegment]]);
  }
  digitalWrite(blackLatchPin, HIGH);
}

void white(long pausedStart) {
  long milliMinus = millis();
  whiteTrackingMinus = milliMinus;
  if (whiteStarted) {
    long pausedDuration = milliMinus - pausedStart;
    whiteTotalPaused = whiteTotalPaused + pausedDuration;
    whiteStarted = 0;
  }
  whiteTotalPaused = whiteTotalPaused - whiteValueUnder;
  whiteValueUnder = 0;
  milliMinus = milliMinus - whiteTotalPaused;
  whiteMilliSeconds = whiteBase - milliMinus;
  if (whiteMilliSeconds <= 0) {
    whiteValueUnder = whiteMilliSeconds;
    whiteMilliSeconds = 0;
  }
  long centiSeconds = whiteMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = whiteMilliSeconds / 100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = whiteMilliSeconds / 1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = whiteMilliSeconds / 10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = whiteMilliSeconds / 60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = whiteMilliSeconds / 600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = whiteMilliSeconds / 6000000;
  long whiteSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};	
  
  digitalWrite(whiteLatchPin, LOW);
  for (int whiteWorkingSegment = 0; whiteWorkingSegment < 7; whiteWorkingSegment++){
      shiftOut(whiteDataPin, whiteClockPin, MSBFIRST, allBytes[whiteSegments[whiteWorkingSegment]]);
  }
  digitalWrite(whiteLatchPin, HIGH);
  
}

void black(long pausedStart) {
  long milliMinus = millis();
  blackTrackingMinus = milliMinus;
  if (blackStarted) {
    long pausedDuration = milliMinus - pausedStart;
    blackTotalPaused = blackTotalPaused + pausedDuration;
    blackStarted = 0;
  }
  blackTotalPaused = blackTotalPaused - blackValueUnder;
  blackValueUnder = 0;
  milliMinus = milliMinus - blackTotalPaused;
  blackMilliSeconds = blackBase - milliMinus;
  if (blackMilliSeconds <= 0) {
    blackValueUnder = blackMilliSeconds;
    blackMilliSeconds = 0;
  }
  long centiSeconds = blackMilliSeconds / 10;
  long printedCentiSeconds = centiSeconds % 10;
  long deciSeconds = blackMilliSeconds / 100;
  long printedDeciSeconds = deciSeconds % 10;
  long seconds = blackMilliSeconds / 1000;
  long printedSeconds = seconds % 10;
  long decaSeconds = blackMilliSeconds / 10000;
  long printedDecaSeconds = decaSeconds % 6;
  long minutes = blackMilliSeconds / 60000;
  long printedMinutes = minutes % 10;
  long decaMinutes = blackMilliSeconds / 600000;
  long printedDecaMinutes = decaMinutes % 10;
  long hectoMinutes = blackMilliSeconds / 6000000;
  long blackSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};	
  
  digitalWrite(blackLatchPin, LOW);
  for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
      shiftOut(blackDataPin, blackClockPin, MSBFIRST, allBytes[blackSegments[blackWorkingSegment]]);
  }
  digitalWrite(blackLatchPin, HIGH);
}

void finishedTimers(){
  int goodBytes [7] = {B00000000, B00000000, B11110110,
      B01111010, B11111100, B11111100, B11110110};

  digitalWrite(whiteLatchPin, LOW);
  for (int whiteWorkingSegment = 0; whiteWorkingSegment < 7; whiteWorkingSegment++){
      shiftOut(whiteDataPin, whiteClockPin, MSBFIRST, goodBytes[whiteWorkingSegment]);
  }
  digitalWrite(whiteLatchPin, HIGH);
  
    digitalWrite(blackLatchPin, LOW);
  for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
      shiftOut(blackDataPin, blackClockPin, MSBFIRST, goodBytes[blackWorkingSegment]);
  }
  digitalWrite(blackLatchPin, HIGH);
}
