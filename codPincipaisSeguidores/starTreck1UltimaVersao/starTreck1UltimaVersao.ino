/*
  #define sen1  11
  #define sen2  12
  #define sen3  10
  #define sen4  13
  #define sen5  9
  int motorA = 6;
  int motorB = 5;

  int entradaDireta1 = 8;
  int entradaDireta2 = 7;
  int entradaEsquerda3 = 4;
  int entradaEsquerda4 = 3;

*/
//starwars
#define sen1  13
#define sen2  12
#define sen3  11
#define sen4  6
#define sen5  7


int motorA = 3;
int motorB = 10;

int entradaDireta1 = 4;
int entradaDireta2 = 5;
int entradaEsquerda3 = 8;
int entradaEsquerda4 = 9;

int comecoFim = 0;
boolean comeco = false;
int primeiraVez = 0;

int ValDirExt = 0;

//starwars\\



//int Vel = 100;
//int brack = 0;

int novaVelocidadeA;
int novaVelocidadeB;
int buzze = 2;

int erro;
int espera = 0;

//int va = 0;
//int vb = 0;

int centro, direita, esquerda, extremaDireita;
int extremaEsquerda, dirExt;
float inte = 0;
float kp = 40;
float ki = 0;
float kd = 5;
float erro_anterior = 0;
float sinalPid;

int VelocidadeConstatnteA = 0;
int VelocidadeConstatnteB = 0;

int entrouNaCurva = 0;


boolean comecoCurva = false;

long tempoInicial = 0l;

void setup() {
  Serial.begin(9600);

  pinMode(entradaDireta1, OUTPUT);
  pinMode(entradaDireta2, OUTPUT);
  pinMode(entradaEsquerda3, OUTPUT);
  pinMode(entradaEsquerda4, OUTPUT);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  pinMode(buzze, OUTPUT);
  //  pinMode(sen2, OUTPUT);
  //  pinMode(sen3, OUTPUT);
  //  pinMode(sen4, OUTPUT);
  for (int i = 1000; i < 5000; i++) {
    tone(buzze, i, 200);
  }
}

void trocaSinaisDosvaloresAbaixoDeZero(float novaVelocidadeA, float novaVelocidadeB ) {



  if (novaVelocidadeA < 0) {
    novaVelocidadeA = novaVelocidadeA = 0;
  }


  if (novaVelocidadeB < 0) {
    novaVelocidadeB = novaVelocidadeB  = 0;
  }


  frente(novaVelocidadeA, novaVelocidadeB);

}

void re(float velA, float velB){
  digitalWrite(entradaDireta1, LOW);
  digitalWrite(entradaDireta2, HIGH);
  digitalWrite(entradaEsquerda3, LOW);
  digitalWrite(entradaEsquerda4, HIGH);

   analogWrite(motorA, velA);
    analogWrite(motorB, velB);
}


void frente(float novaVelocidadeA, float novaVelocidadeB) {

  digitalWrite(entradaDireta1, LOW);
  digitalWrite(entradaDireta2, HIGH);
  digitalWrite(entradaEsquerda3, HIGH);
  digitalWrite(entradaEsquerda4, LOW);
  //delay(800);
 // delay(800);
//  Serial.println("Velocidade mudada pelo pid");
//  Serial.print("A");
//  Serial.println(novaVelocidadeA);
//  Serial.print("B");
//  Serial.println(novaVelocidadeB);
//  delay(800);

  
  if (novaVelocidadeA > 200) {
    novaVelocidadeA = 170;
    novaVelocidadeB = 100;//100;
//    Serial.println("Velocidade do motor A maior mudar rotação");
//    
//    Serial.println(novaVelocidadeB);
//    Serial.println(novaVelocidadeA);
//    delay(800);
    digitalWrite(entradaDireta1, LOW);
    digitalWrite(entradaDireta2, HIGH);
    digitalWrite(entradaEsquerda3, LOW);
    digitalWrite(entradaEsquerda4, HIGH);

    novaVelocidadeA = novaVelocidadeA - (novaVelocidadeA * 0.2);
    novaVelocidadeB = novaVelocidadeB - (novaVelocidadeB * 0.2);
    
    analogWrite(motorA, novaVelocidadeA);//78 velocidade minima// 158 velocidade media
    analogWrite(motorB, novaVelocidadeB);//45 velocidade minima // 54 velocidade media---------------------------------------
  }
  else if (novaVelocidadeB > 200) {
    novaVelocidadeB = 170;
    novaVelocidadeA = 100;//100;
//    Serial.println("Velocidade do motor B maior mudar rotação");
//    
//    Serial.println(novaVelocidadeB);
//    Serial.println(novaVelocidadeA);
//    delay(800);
    
    digitalWrite(entradaDireta1, HIGH);
    digitalWrite(entradaDireta2, LOW);
    digitalWrite(entradaEsquerda3, HIGH);
    digitalWrite(entradaEsquerda4, LOW);

    
    novaVelocidadeA = novaVelocidadeA - (novaVelocidadeA * 0.2);
    novaVelocidadeB = novaVelocidadeB - (novaVelocidadeB * 0.2);
    
    analogWrite(motorA, novaVelocidadeA);//78 velocidade minima// 158 velocidade media
    analogWrite(motorB, novaVelocidadeB);//45 velocidade minima // 54 velocidade media---------------------------------------
  }
  else {
    analogWrite(motorA, novaVelocidadeA);//78 velocidade minima// 158 velocidade media
    analogWrite(motorB, novaVelocidadeB);//45 velocidade minima // 54 velocidade media---------------------------------------
  }

}



void lerSensores() {

  extremaEsquerda = digitalRead(sen1);
  esquerda = digitalRead(sen2);
  centro = digitalRead(sen3);
  direita = digitalRead(sen4);
  extremaDireita = digitalRead(sen5);
  dirExt = analogRead(A5);
  mudarValorDaLeituraParaUmOuZero();
}
void mudarValorDaLeituraParaUmOuZero() {

  if (dirExt < 500) {
    ValDirExt = 0;
  } else {
    ValDirExt = 1;
  }

}


void controlePid(int erro) {

  /*if (comecoCurva) {

    VelocidadeConstatnteA = 80;//+5
    VelocidadeConstatnteB = 80;
    kp = 15.6;//15.2//16
    kd = 15.6;//5.2//6
    
    }*/
  //else {
  VelocidadeConstatnteA = 110;//+5
  VelocidadeConstatnteB = 110;//+5
  kp = 40;//15.2//16
  kd = 6.5;//6.5;//40.50;//5.2//6
  ki = 0;


  sinalPid = kp * erro + kd * (erro_anterior - erro);// + ki * (inte + erro_anterior);


  //}

  /*delay(200);
    Serial.print("velocidade A");
    Serial.println(VelocidadeConstatnteA);
    Serial.print("velocidade B");
    Serial.println(VelocidadeConstatnteB);*/
  //+ kd * (erro_anterior - erro)

  novaVelocidadeA = VelocidadeConstatnteA + sinalPid ;
  novaVelocidadeB = VelocidadeConstatnteB - sinalPid ;

  erro_anterior = erro;

  trocaSinaisDosvaloresAbaixoDeZero(novaVelocidadeA, novaVelocidadeB);

}

long retornaTempoParaOControleDoBuzzer() {

  long tempoAtual = millis();
  if (tempoAtual > (tempoInicial + 500)) {
    return  tempoInicial = tempoAtual;
  }
  return 0l;
}

void loop() {

  
  lerSensores();

  // 1 0 0 0 0   --> Erro -4
  // 1 1 0 0 0   --> Erro -3
  // 0 1 0 0 0   --> Erro -2
  // 0 1 1 0 0   --> Erro -1
  // 0 0 1 0 0   --> Erro  0
  // 0 0 1 1 0   --> Erro  1
  // 0 0 0 1 0   --> Erro  2
  // 0 0 0 1 1   --> Erro  3
  // 0 0 0 0 1   --> Erro  4

  //0 0 1 0 0 :0

  if (espera < 1) {
    espera++;
    delay(2000);
  }
  /*else if ( ((extremaEsquerda == 0) || (extremaEsquerda == 1)) &&
    (centro == 1) && (esquerda == 0) &&
    (direita == 0) && (dirExt == 1)
    && (extremaDireita == 0)  ) {

    if (entrouNaCurva < 1) {
      Serial.println(entrouNaCurva);
      comecoCurva = !comecoCurva;
      tone(buzze, 5000, retornaTempoParaOControleDoBuzzer());
      entrouNaCurva++;
    }

    }*/
//
//  else if ((centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
//    if( comecoFim <= 1 ) {
//       if(comeco == true){
//         frente(50, 50);
//         delay(800);
//         frente(0, 0);
//         delay(3000);
//         comecoFim = 0;
//         comeco = false;
//       }
//   }
//  }

  long tempoLigado = millis(); //parar sozinho
  if ( (centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0)  ) {
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
    entrouNaCurva = 0;
    noTone(buzze);
  }
  //0 1 0 0 0 :-2
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(-2);
//    
//    comeco = true;
//    comecoFim = 1;
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 0 :2
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(2);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //1 1 0 0 0 :-3
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-3);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 1 :3
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(3);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //1 0 0 0 0 :-4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-4);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 0 1 :4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(4);
//    comeco = true;
//    comecoFim = 1;
    entrouNaCurva = 0;
    noTone(buzze);
  }

  /*else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    frente(0,0);
    entrouNaCurva = 0;
    noTone(buzze);
    }*/

  //parar sozinho
  else if(ValDirExt == 1 && tempoLigado > 20000){
    delay(100);
    re(70, 70);
    re(0, 0);
    delay(3000);
  }
 /*   else if(ValDirExt == 1 && centro == 1){
      if( primeiraVez == 0 ) {
          delay(100);
      }
      else if(primeiraVez == 1){
         delay(100);
         re(70, 70);
         re(0, 0);
         delay(3000);
         //comecoFim = 0;
         //comeco = false;
         }
    }  */

  //  //1 0 0 0 0 :-5

}
