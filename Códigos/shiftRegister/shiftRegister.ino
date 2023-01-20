#ifdef __AVR_ATmega2560__
  const byte CLOCKOUT = 11;  // Mega 2560
#else
  const byte CLOCKOUT = 9;   // Uno, Duemilanove, etc.
#endif

int i;

void setup()
{
    pinMode (CLOCKOUT, OUTPUT); 
    // set up Timer 1
    TCCR1A = bit (COM1A0);                  // toggle OC1A on Compare Match
    TCCR1B = bit (WGM12) | bit (CS10);      // CTC, no prescaling
    OCR1A =  15;                             // output every cycle
    pinMode(46, OUTPUT);
    pinMode(44, INPUT);
    digitalWrite(46, HIGH);
    Serial.begin(9600);
}

void loop()
{
  Serial.println("Value:");
  digitalWrite(46, LOW);
  digitalWrite(46, HIGH);
  for(i; i < 8; i++)
  {
    if(digitalRead(45) == HIGH)
    {
      Serial.print(digitalRead(44));
    }
  }
  i = 0;
  Serial.println(" ");
}
