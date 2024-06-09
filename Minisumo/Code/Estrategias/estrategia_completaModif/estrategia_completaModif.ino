#include <SparkFun_TB6612.h>

#define AIN1 5
#define BIN1 6
#define AIN2 4
#define BIN2 7
#define PWMA 9
#define PWMB 3
#define STBY 8

const int offsetA = 1;
const int offsetB = 1;
const int vel = 250;
const int velGiro = 300;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int cny_der, cny_izq, cny_atr, sharp_c, sharp_d, sharp_i, estado_switch;
char Estado=0;
enum mac1 {Nada,Bizq,Bder,Badel,Batr,Sizq,Sder,Scen};
void setup() {
   pinMode(12, INPUT_PULLUP);
   estado_switch = digitalRead(12);
   while (estado_switch == HIGH) {
    brake(motor1,motor2);
    estado_switch = digitalRead(12);
    }
    delay(5000);
}

void loop() {

  switch(Estado){
      
    case Nada:
    leer_sensores();
    forward(motor1,motor2,vel);    
    
    if(cny_izq==1 and cny_der==0){
      Estado=Bizq;
    }
    if(cny_izq==1 and cny_der==1){
      Estado=Badel;
    }
    if(cny_izq==0 and cny_der==1){
      Estado=Bder;
    }
    if(cny_atr==1){
      Estado=Batr;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_d<40 and sharp_d!=0 and sharp_d<sharp_c){
      Estado=Sder;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_i<40 and sharp_i!=0 and sharp_i<sharp_c){
      Estado=Sizq;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c<40 and sharp_c!=0){
      Estado=Scen;
    }
    break;


    
    case Bizq:
    right(motor1,motor2,velGiro);
    delay(500);
    Estado=Nada;
    break;
    case Bder:
    left(motor1,motor2,velGiro);
    delay(500);
    Estado=Nada;
    break;


    
      case Badel:
    back(motor1,motor2,vel);
    delay(100);
    right(motor1,motor2,velGiro);
    delay(500);
    Estado=Nada;
    break;


    
    case Batr:
    forward(motor1,motor2,vel);
    Estado=Nada;
    break;


    
    case Scen:
    leer_sensores();
    forward(motor1,motor2,vel);
    if(cny_izq==1 and cny_der==0){
      Estado=Bizq;
    }
    if(cny_izq==1 and cny_der==1){
      Estado=Badel;
    }
    if(cny_izq==0 and cny_der==1){
      Estado=Bder;
    }
    if(cny_atr==1){
      Estado=Batr;
    }

    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_d<20 and sharp_d!=0 and sharp_d<sharp_c){
      Estado=Sder;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_i<20 and sharp_i!=0 and sharp_i<sharp_c){
      Estado=Sizq;
    }
        if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c<20 and sharp_c!=0){
      Estado=Scen;
    }     
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c==0 and sharp_d==0 and sharp_i==0){
      Estado=Nada;
    }
    break;


    
    case Sder:
    leer_sensores();
    right(motor1,motor2,velGiro);
    if(cny_izq==1 and cny_der==0){
      Estado=Bizq;
    }
    if(cny_izq==1 and cny_der==1){
      Estado=Badel;
    }
    if(cny_izq==0 and cny_der==1){
      Estado=Bder;
    }
    if(cny_atr==1){
      Estado=Batr;
    }

    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_d<20 and sharp_d!=0 and sharp_d<sharp_c){
      Estado=Sder;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_i<20 and sharp_i!=0 and sharp_i<sharp_c){
      Estado=Sizq;
    }
        if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c<20 and sharp_c!=0){
      Estado=Scen;
    }     
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c==0 and sharp_d==0 and sharp_i==0){
      Estado=Nada;
    }    
    
    break;


    
    case Sizq:
    leer_sensores();
    left(motor1,motor2,velGiro);
    if(cny_izq==1 and cny_der==0){
      Estado=Bizq;
    }
    if(cny_izq==1 and cny_der==1){
      Estado=Badel;
    }
    if(cny_izq==0 and cny_der==1){
      Estado=Bder;
    }
    if(cny_atr==1){
      Estado=Batr;
    }

    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_d<20 and sharp_d!=0 and sharp_d<sharp_c){
      Estado=Sder;
    }
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_i<20 and sharp_i!=0 and sharp_i<sharp_c){
      Estado=Sizq;
    }
        if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c<20 and sharp_c!=0){
      Estado=Scen;
    }     
    if(cny_der==0 and cny_izq==0 and cny_atr==0 and sharp_c==0 and sharp_d==0 and sharp_i==0){
      Estado=Nada;
    }
    break;
  }
}

void leer_sensores(){
  int senal_cny_der = analogRead(A0);
  cny_der=cny(senal_cny_der);
  int senal_cny_izq = analogRead(A1);
  cny_izq=cny(senal_cny_izq);
  int senal_cny_atr = analogRead(A2);
  cny_atr=cny(senal_cny_atr);

  float senal_centro=analogRead(A3);
  sharp_c=sharp(senal_centro);
  float senal_der=analogRead(A4);
  sharp_d=sharp(senal_der);
  float senal_izq=analogRead(A5);
  sharp_i=sharp(senal_izq);
}

  int cny(int senal)
{
  unsigned int referenciaBlanco = 100;
  if(senal<referenciaBlanco ) {return 0;}
  else if(senal>=referenciaBlanco){return 1;}
}

float sharp(float senal)
{
  float distancia_cm = 6069.3 * pow(senal, -0.997);
  if((distancia_cm >= 7.0) && (distancia_cm < 83.0)){
   return distancia_cm;
   }
  else {return 0;}  
}
