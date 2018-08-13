
#define sen1  13
#define sen2  12
#define sen3  11
#define sen4  6
#define sen5  7


int sensorPin[5];

int motorA = 3;
int motorB = 10;

int Din1 = 4;
int Din2 = 5;
int Ein3 = 8;
int Ein4 = 9;

int Vel = 100;
int brack = 0;
int novaVelocidadeA; 
int novaVelocidadeB;
int buzze = 2;

int erro;
int espera = 0;

int va = 0;
int vb = 0;

int centro, direita, esquerda, extremaDireita; 
int extremaEsquerda;

float kp = 40;
float ki = 0;
float kd = 5;
float erro_anterior = 0;
float sinalPid;

int VelocidadeConstatnteA = 0;
int VelocidadeConstatnteB = 0;

int entrouNaCurva = 0;


boolean comecoCurva = false;

void setup() {
  Serial.begin(9600);

  pinMode(Din1, OUTPUT);
  pinMode(Din2, OUTPUT);
  pinMode(Ein3, OUTPUT);
  pinMode(Ein4, OUTPUT);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  pinMode(buzze, OUTPUT);
  //  pinMode(sen2, OUTPUT);
  //  pinMode(sen3, OUTPUT);
  //  pinMode(sen4, OUTPUT);
  for(int i = 1000; i < 5000; i++){ 
    tone(buzze, i, 200); 
  }
}

void frente(int novaVelocidadeA,int novaVelocidadeB) {


  if(novaVelocidadeA < 0){
    novaVelocidadeA = novaVelocidadeA * (-1);
  }


  if(novaVelocidadeB < 0){
    novaVelocidadeB = novaVelocidadeB * (-1);
  }
  /*delay(500);
   Serial.print("A");
   Serial.println(novaVelocidadeA);
   Serial.print("B");
   Serial.println(novaVelocidadeB);
   */
  digitalWrite(Din1, LOW);
  digitalWrite(Din2, HIGH);
  digitalWrite(Ein3, HIGH);
  digitalWrite(Ein4, LOW);

  analogWrite(motorA, novaVelocidadeA);//78 velocidade minima// 158 velocidade media
  analogWrite(motorB, novaVelocidadeB);//45 velocidade minima // 54 velocidade media---------------------------------------

}



void lerSensores() {

  extremaEsquerda = digitalRead(sen1);
  esquerda = digitalRead(sen2);
  centro = digitalRead(sen3);
  direita = digitalRead(sen4);
  extremaDireita = digitalRead(sen5);


}



void controlePid(int erro){

  if(comecoCurva){         
    VelocidadeConstatnteA = 60;//+5
    VelocidadeConstatnteB = 60;//+5
      kp = 9.877;//15.2//16
      kd = 9.877;//5.2//6
         
  }
  else{
    VelocidadeConstatnteA = 70;//+5
    VelocidadeConstatnteB = 70;
      kp = 14.816;//15.2//16
      kd = 14.816;//5.2//6
     
  }

  /*delay(200);
   Serial.print("velocidade A");
   Serial.println(VelocidadeConstatnteA);
   Serial.print("velocidade B");
   Serial.println(VelocidadeConstatnteB);*/
  //+ kd * (erro_anterior - erro)
  


  sinalPid = kp * erro + kd * (erro_anterior - erro);

  novaVelocidadeA = VelocidadeConstatnteA + sinalPid ;
  novaVelocidadeB = VelocidadeConstatnteB - sinalPid ;

  erro_anterior = erro;


  frente(novaVelocidadeA,novaVelocidadeB);



}

void loop() {

  lerSensores();

  //0 1 0 0 0 0 0  --> Erro -4
  //0 1 1 0 0 0 0  --> Erro -3
  //0 0 1 0 0 0 0  --> Erro -2
  //0 0 1 1 0 0 0  --> Erro -1
  //0 0 0 1 0 0 0  --> Erro  0
  //0 0 0 1 1 0 0  --> Erro  1
  //0 0 0 0 1 0 0  --> Erro  2
  //0 0 0 0 1 1 0  --> Erro  3
  //0 0 0 0 0 1 0  --> Erro  4



  //0 0 1 0 0 :0

  if(espera < 1){
    espera++;
    delay(2000);
  }
  else if ((centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    
    if(entrouNaCurva < 1){ 
    Serial.println(entrouNaCurva);
    comecoCurva = !comecoCurva;      
    tone(buzze, 5000, 200);
    entrouNaCurva++;
    }
    
  }


  else if ((centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    frente(0,0);
    tone(buzze,2000,500);
  }


  if ( (centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda== 0) && (extremaDireita == 0)  ) {
    controlePid(0);

  }




  //0 1 1 0 0 :-1
  else if ((centro == 1) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(-1);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 1 1 0 :1
  else if ((centro == 1) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(1);
    entrouNaCurva;
    noTone(buzze);
  }
  //0 1 0 0 0 :-2
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(-2);
    entrouNaCurva;
    noTone(buzze);
  }

  //0 0 0 1 0 :2
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(2);
    entrouNaCurva;
    noTone(buzze);
  }


  //1 1 0 0 0 :-3
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-3);
    entrouNaCurva;
    noTone(buzze);
  }

  //0 0 0 1 1 :3
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(3);
    noTone(buzze);
  }

  //1 0 0 0 0 :-4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-4);
    noTone(buzze);
  }

  //0 0 0 0 1 :4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(4);
    noTone(buzze);
  }




  //  //1 0 0 0 0 :-5



}













