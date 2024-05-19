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
int startingMode = 1;
bool firstTime = 1;

int deadByte = B11111111;
int zeroByte = B00000011;
int oneByte = B10011111;
int twoByte = B00100101;
int threeByte = B00001101;
int fourByte = B10011000;
int fiveByte = B01001001;
int sixByte = B01000001;
int sevenByte = B00011111;
int eightByte = B00000001;
int nineByte = B00001001;
int deeByte = B10000101;
int allBytes[10] = {zeroByte, oneByte, twoByte, threeByte, fourByte, fiveByte, sixByte, sevenByte, eightByte, nineByte};

int whiteButtonPin = A5;
int blackButtonPin = A0;
int pauseButtonPin = A4;
int upButtonPin = A3;
int downButtonPin = A2;
int whiteLatchPin = 4;
int whiteClockPin = 2;
int whiteDataPin = 6;
int blackLatchPin = 11;
int blackClockPin = 9;
int blackDataPin = 13;

void setup() {
  pinMode(whiteButtonPin, INPUT_PULLUP);
  pinMode(blackButtonPin, INPUT_PULLUP);
  pinMode(pauseButtonPin, INPUT_PULLUP);
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(whiteLatchPin, OUTPUT);
  pinMode(whiteClockPin, OUTPUT);
  pinMode(whiteDataPin, OUTPUT);
  pinMode(blackLatchPin, OUTPUT);
  pinMode(blackClockPin, OUTPUT);
  pinMode(blackDataPin, OUTPUT);
}

void loop() {

  bool timersFinished = 0;
  if ((whiteMilliSeconds == 0) || (blackMilliSeconds == 0)) {
    timersFinished = 1;
  }
  bool timersJustRestarted = 0;
  static long whiteMorePaused;
  static long blackMorePaused;
  static bool whiteTurn = 1;
  static bool pauseButtonChanged;
  static bool timersRunning;
  static long whitePausedStart = 1;
  static long blackPausedStart = 1;
  bool backToPause = 0;
  bool pauseButtonPressed = digitalRead(pauseButtonPin);
  pauseButtonPressed = !pauseButtonPressed;
  if ((pauseButtonPressed) && (!pauseButtonChanged)) {
    firstTime = 0;
    backToPause = 1;
    timersRunning = !timersRunning;
    if (timersRunning) {
      timersJustRestarted = 1;    } 
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
        switch(startingMode){
          case 2:
          whiteMilliSeconds = whiteMilliSeconds + 100;
          break;

          case 3:
          whiteMilliSeconds = whiteMilliSeconds + 300;
          break;

          case 4:
          whiteMilliSeconds = whiteMilliSeconds + 500;
          break;

          case 5: 
          whiteMilliSeconds = whiteMilliSeconds + 1000;
          break;

          case 6:
          whiteMilliSeconds = whiteMilliSeconds + 1500;
          break;

          case 7:
          whiteMilliSeconds = whiteMilliSeconds + 3000;
          break;
        }
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
        switch(startingMode){
          case 2:
          blackMilliSeconds = blackMilliSeconds + 100;
          break;

          case 3:
          blackMilliSeconds = blackMilliSeconds + 300;
          break;

          case 4:
          blackMilliSeconds = blackMilliSeconds + 500;
          break;

          case 5: 
          blackMilliSeconds = blackMilliSeconds + 1000;
          break;

          case 6:
          blackMilliSeconds = blackMilliSeconds + 1500;
          break;

          case 7:
          blackMilliSeconds = blackMilliSeconds + 3000;
          break;
        }
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
      pausedTimers();
    }
  }
}


void pausedTimers() {
  if (firstTime == 1)
  {
    static bool upButtonChanged;
    bool upButtonPressed = digitalRead(upButtonPin);
    upButtonPressed = !upButtonPressed;
    if ((upButtonPressed) && (!upButtonChanged)) {
      startingMode++;
    }
    upButtonChanged = upButtonPressed;
    static bool downButtonChanged;
    bool downButtonPressed = digitalRead(downButtonPin);
    downButtonPressed = !downButtonPressed;
    if ((downButtonPressed) && (!downButtonChanged)) {
      startingMode--;
    }
    if (startingMode > 7){
      startingMode = 7;
    }
    if (startingMode < 1){
      startingMode = 1;
    }

    digitalWrite(whiteLatchPin, LOW);
    for (int whiteWorkingSegment = 0; whiteWorkingSegment < 7; whiteWorkingSegment++){
        shiftOut(whiteDataPin, whiteClockPin, MSBFIRST, allBytes[startingMode]);
    }
    digitalWrite(whiteLatchPin, HIGH);


        digitalWrite(blackLatchPin, LOW);
    for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
        shiftOut(blackDataPin, blackClockPin, MSBFIRST, allBytes[startingMode]);
    }
    digitalWrite(blackLatchPin, HIGH);

    switch(startingMode){
      case 1:
      whiteMilliSeconds = 60000;
      blackMilliSeconds = 60000;
      break;

      case 2:
      whiteMilliSeconds = 180000;
      blackMilliSeconds = 180000;
      break;

      case 3:
      whiteMilliSeconds = 300000;
      blackMilliSeconds = 300000;
      break;

      case 4:
      whiteMilliSeconds = 600000;
      blackMilliSeconds = 600000;
      break;

      case 5:
      whiteMilliSeconds = 900000;
      blackMilliSeconds = 900000;
      break;

      case 6:
      whiteMilliSeconds = 1800000;
      blackMilliSeconds = 1800000;
      break;

      case 7:
      whiteMilliSeconds = 5400000;
      blackMilliSeconds = 5400000;
      break;
    }
  }
  else{

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
    long blackSegments [7] = {hectoMinutes, printedDecaMinutes, printedMinutes, printedDecaSeconds, printedSeconds, printedDeciSeconds, printedCentiSeconds};	
    
    digitalWrite(blackLatchPin, LOW);
    for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
        shiftOut(blackDataPin, blackClockPin, MSBFIRST, allBytes[blackSegments[blackWorkingSegment]]);
    }
    digitalWrite(blackLatchPin, HIGH);
  }
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
  long blackSegments [7] = {hectoMinutes, printedDecaMinutes, printedMinutes, printedDecaSeconds, printedSeconds, printedDeciSeconds, printedCentiSeconds};	
  
  digitalWrite(blackLatchPin, LOW);
  for (int blackWorkingSegment = 0; blackWorkingSegment < 7; blackWorkingSegment++){
      shiftOut(blackDataPin, blackClockPin, MSBFIRST, allBytes[blackSegments[blackWorkingSegment]]);
  }
  digitalWrite(blackLatchPin, HIGH);
}

void finishedTimers(){
  int goodWhiteBytes [7] = {deadByte, deadByte, nineByte, deeByte, zeroByte, zeroByte, nineByte};
  int goodBlackBytes [7] = {nineByte, zeroByte, zeroByte, deeByte, nineByte, deadByte, deadByte};

  digitalWrite(whiteLatchPin, LOW);
  digitalWrite(blackLatchPin, LOW);
  for (int currentSegment = 0; currentSegment < 7; currentSegment++){
      shiftOut(whiteDataPin, whiteClockPin, MSBFIRST, goodWhiteBytes[currentSegment]);
      shiftOut(blackDataPin, blackClockPin, MSBFIRST, goodBlackBytes[currentSegment]);
  }
  digitalWrite(whiteLatchPin, HIGH);
  digitalWrite(blackLatchPin, HIGH);
}
