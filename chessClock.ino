long startingAmount = 10000;

int latchPin = 10;
int clockPin = 11;
int dataPin = 12;
int mainButtonPin = A5;
 
int zeroByte = B11111100;
int oneByte = B01100000;
int twoByte = B11011010;
int threeByte = B11110010;
int fourByte = B01100110;
int fiveByte = B10110110;
int sixByte = B10111110;
int sevenByte = B11100000;
int eightByte = B11111110;
int nineByte = B11110110;
int allBytes [10] = {zeroByte, oneByte, twoByte, threeByte, fourByte, fiveByte, sixByte, sevenByte, eightByte, nineByte};

void setup ()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(mainButtonPin, INPUT_PULLUP);
}

void loop() {
  static bool timersRunning;
  static bool timersFinished;
  long totalMilliSeconds = startingAmount;
  bool mainButtonPressed = digitalRead(mainButtonPin);
  mainButtonPressed = !mainButtonPressed;
  bool mainButtonChanged = mainButtonPressed;
  if((mainButtonPressed)&&(mainButtonPressed!=mainButtonChanged)){
    timersRunning = !timersRunning;
  }
  if(timersRunning){
    long whiteMilliseconds = white();
  }
  else{
    long totalMilliseconds = pausedTimers();

  }
}
long pausedTimers(){
  long milliSeconds = startingAmount;
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
  long allSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};
  digitalWrite(latchPin, LOW);
  for (int workingSegment = 0; workingSegment < 7; workingSegment++){
      shiftOut(dataPin, clockPin, MSBFIRST, allBytes[allSegments[workingSegment]]);
  }
  digitalWrite(latchPin, HIGH);
}


long white(){
  long milliMinus = millis();
  long milliSeconds = startingAmount - milliMinus;
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
  long allSegments [7] = {printedCentiSeconds, printedDeciSeconds, printedSeconds, printedDecaSeconds, printedMinutes, printedDecaMinutes, hectoMinutes};	

  if(milliSeconds <= 0){
    milliSeconds = 0;
  }
  digitalWrite(latchPin, LOW);
  for (int workingSegment = 0; workingSegment < 7; workingSegment++){
      shiftOut(dataPin, clockPin, MSBFIRST, allBytes[allSegments[workingSegment]]);
  }
  digitalWrite(latchPin, HIGH);
  return milliSeconds;
}
