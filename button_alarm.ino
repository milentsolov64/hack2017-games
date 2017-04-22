int i = 0;
int minutes = 4;
int seconds = 54;
int button = 2;
int led = 13;
int alarm;
int buttonState;
int digit1;
int digit2;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(alarm, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(2);
digit1=seconds%10;
digit2=seconds/10;
  if (buttonState == 1 && (digit1==5 or digit2==5))
  digitalWrite(led, HIGH);
  if (buttonState == 1 && (digit1!=5 or digit2!=5))
  digitalWrite(alarm, HIGH);

      
}
