
/*
 * A 7 segment digital dice to demonstrate the Otemba
 * by FakuFaku, 2012
 */

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Pin definitions
int anode = 2;    //Display pin 12
int anode2 = A0;

int segA = A1;      //Display pin 11
int segB = A2;      //Display pin 7
int segC = 3;       //Display pin 4
int segD = 1;       //Display pin 2
int segE = 0;       //Display pin 1
int segF = 13;      //Display pin 10
int segG = 12;       //Display pin 5

int colons = 4;     //Display pin 3

const static int theButton = A5;

const static int led = 9;

// state
#define RUNNING 0
#define PRESSED 1
int state = RUNNING;

unsigned long blink_timer;
#define RUN_TIME 100
#define WIN_TIME 1000

int current_number;

void setup()
{
  // initialize the button
  pinMode(theButton, INPUT);
  digitalWrite(theButton, HIGH); // pull-up

  // initialize the led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //These pins are used to control the display
  pinMode(segA, OUTPUT);
  digitalWrite(segA, HIGH);
  pinMode(segB, OUTPUT);
  digitalWrite(segB, HIGH);
  pinMode(segC, OUTPUT);
  digitalWrite(segC, HIGH);
  pinMode(segD, OUTPUT);
  digitalWrite(segD, HIGH);
  pinMode(segE, OUTPUT);
  digitalWrite(segE, HIGH);
  pinMode(segF, OUTPUT);
  digitalWrite(segF, HIGH);
  pinMode(segG, OUTPUT);
  digitalWrite(segG, HIGH);

  pinMode(colons, OUTPUT);
  digitalWrite(colons, HIGH);
  
  /*
  for (int i = 0 ; i < 18 ; i ++)
    digitalWrite(i, LOW);
   */

  pinMode(anode, OUTPUT);
  digitalWrite(anode, HIGH);
  pinMode(anode2, OUTPUT);
  digitalWrite(anode2, HIGH);


  blink_timer = millis();

  current_number = readTimer() % 6 + 1;

  setupTimer();

}

void loop()
{
  if (state == RUNNING)
  {
    if (millis() % RUN_TIME < RUN_TIME/2)
      digitalWrite(led, HIGH);
    else
      digitalWrite(led, LOW);

    // change current number
    if (millis() - blink_timer > RUN_TIME)
    {
      current_number = readTimer() % 6 + 1;
      blink_timer = millis();
      lightNumber(' ');
    }

    // display number
    lightNumber(current_number);

    // if the button is pressed get the current number and switch state
    while (digitalRead(theButton) == LOW)
    {
      current_number = readTimer() % 6 + 1;
      state = PRESSED;
      blink_timer = millis();
    }
  }
  else
  {
    if (millis() % WIN_TIME < WIN_TIME/2)
    {
      lightNumber(current_number);
      digitalWrite(led, HIGH);
    }
    else
    {
      lightNumber(' ');
      digitalWrite(led, LOW);
    }

    while (digitalRead(theButton) == LOW)
    {  
      state = RUNNING;
    }
  }
}


void setupTimer()
{
  TCCR1B |= 1;  // clock divider 1
}

int readTimer()
{
  return TCNT1;
}


//Given a number, turns on those segments
//If number == 10, then turn off all segments
void lightNumber(int numberToDisplay)
{

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH
  
  digitalWrite(anode, HIGH);
  digitalWrite(anode2, HIGH);

  /*
Segments
   -  A
   F / / B
   -  G
   E / / C
   -  D
   */

  switch (numberToDisplay)
  {

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

    /*
Segments
     -  A
     F / / B
     -    G
     E / / C
     - D
     */

    //Letters
  case 'b': //cdefg
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case 'L': //def
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    break;
  case 'u': //cde
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    break;

  case 'g': //abcdfg
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case 'r': //eg
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case 'n': //ceg
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

    //case r
  case 'e': //adefg
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case 'd': //bcdeg
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
  case ' ': //None
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 'y': //bcdfg
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;
    //case e 
    //case L
  case 'o': //cdeg
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  }
}

