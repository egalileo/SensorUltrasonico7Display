#define DA1 1
#define DB1 2
#define DC1 3
#define DD1 4
#define DE1 5
#define DF1 6 
#define DG1 7

#define DA2 8
#define DB2 9
#define DC2 10
#define DD2 11
#define DE2 12
#define DF2 13
#define DG2 A0

#define DP A1
#define TRIG A2
#define ECHO A3


byte pinesUnidades[] = {1,2,3,4,5,6,7};
byte pinesDecenas[] = {8,9,10,11,12,13,A0};

byte matriz[10][7] = {
  {1,1,1,1,1,1,0}, //cero
  {0,1,1,0,0,0,0}, //uno
  {1,1,0,1,1,0,1}, //dos
  {1,1,1,1,0,0,1}, //tres
  {0,1,1,0,0,1,1}, //cuatro
  {1,0,1,1,0,1,1}, //cinco
  {1,0,1,1,1,1,1}, //seis  
  {1,1,1,0,0,0,0}, //siete
  {1,1,1,1,1,1,1}, //ocho
  {1,1,1,1,0,1,1} //nueve
};

void setup()
{
  
  for( byte x=0; x<sizeof(pinesUnidades); x++){
  	pinMode(pinesUnidades[x], OUTPUT);
    pinMode(pinesDecenas[x], OUTPUT);
  }
  pinMode(DP, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

void loop(){
  digitalWrite(DP,HIGH);
  int distancia = medirCM();
  mostrarUnidades(getUnidades(distancia));
  mostrarDecenas(getDecenas(distancia));
  delay(100);
}

void mostrarUnidades(int numero){
  byte pin, valor;
  for(int i = 0; i < 7; i++){
    pin = pinesUnidades[i];
    valor = matriz[numero][i];
    digitalWrite(pin, valor);
  }
}

void mostrarDecenas(int numero){
  byte pin, valor;
  for(int i = 0; i < 7; i++){
    pin = pinesDecenas[i];
    valor = matriz[numero][i];
    digitalWrite(pin, valor);
  }
}

int medirCM(){
  long distancia, tiempo;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  tiempo = pulseIn(ECHO, HIGH);
  distancia = tiempo * 10 / 292 / 2;
  return (int) distancia;
}

int getDecenas(int distancia){
  return (int) distancia / 100;
}

int getUnidades(int distancia){
  float decimales = (float) distancia/100;
  int enteros = (int) decimales;
  return round(((decimales - enteros)*100)/10);
}
}