#define LA1 2
#define LB1 3
#define LC1 4
#define LD1 5
#define LE1 6
#define LF1 7
#define LG1 8
#define DP1 9

#define LA2 A0
#define LB2 A1
#define LC2 A2
#define LD2 A3
#define LE2 A4
#define LF2 10
#define LG2 11

#define ECHO 12
#define TRIG 13

byte integerPines[] = {LA1,LB1,LC1,LD1,LE1,LF1,LG1};
byte decimalPines[] = {LA2,LB2,LC2,LD2,LE2,LF2,LG2};

byte matrix[10][7] = {
  {1,1,1,1,1,1,0}, //cero
  {0,1,1,0,0,0,0}, //uno
  {1,1,0,1,1,0,1}, //dos
  {1,1,1,1,0,0,1}, //tres
  {0,1,1,0,0,1,1}, //cuatro
  {1,0,1,1,0,1,1}, //cinco
  {1,0,1,1,1,1,1}, //seis
  {1,1,1,0,0,0,0}, //siete
  {1,1,1,1,1,1,1}, //ocho
  {1,1,1,0,0,1,1} //nueve 
};

void setup()
{
  for(int i = 2; i <= 11; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(LA2, OUTPUT);
  pinMode(LB2, OUTPUT);
  pinMode(LC2, OUTPUT);
  pinMode(LD2, OUTPUT);
  pinMode(LE2, OUTPUT);
  pinMode(LF2, OUTPUT);
  pinMode(LG2, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  
}

void loop()
{
  digitalWrite(DP1,HIGH);
  int distance = medirCM();
  showIntegers(getIntegers(distance));
  showDecimal(getDecimals(distance));
  delay(100);
}
void showIntegers(int number){
  byte pin, value;
  for(int i = 0; i < 7; i++){
    pin = integerPines[i];
    value = matrix[number][i];
    digitalWrite(pin, value);
  }
}

void showDecimal(int number){
  byte pin, value;
  for(int i = 0; i < 7; i++){
    pin = decimalPines[i];
    value = matrix[number][i];
    digitalWrite(pin, value);
  }
}

int medirCM(){
  long distance, time;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  time = pulseIn(ECHO, HIGH);
  distance = time * 10 / 292 / 2;
  return (int) distance;
}

int getIntegers(int distance){
  return (int) distance / 100;
}

int getDecimals(int distance){
  float decimales = (float) distance/100;
  int enteros = (int) decimales;
  return round(((decimales - enteros)*100)/10);
}