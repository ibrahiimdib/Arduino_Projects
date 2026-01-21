//declaring variables 
const byte LDRpin= A0;
const byte BUZZpin=2;

 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 //setting input and output 
pinMode(LDRpin , INPUT);
pinMode(BUZZpin , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //reading analog signals of LDR
int reading= analogRead(A0);
if (reading>=800){
    tone(2,  2000);
  delay(1000);
}
else{
  noTone(2);
}
}
