
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


//starwars
/*#define sen1  13
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


  //starwars\\
*/


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
int extremaEsquerda, esquerdaExterno;
float inte = 0;
float kp = 40;
float ki = 0;
float kd = 5;
float erro_anterior = 0;
float sinalPid;

int teste = 0;

int VelocidadeConstatnteA = 0;
int VelocidadeConstatnteB = 0;

int entrouNaCurva = 0;


boolean comecoCurva = false;

long tempoInicial = 0l;

int comecoFim = 0;

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

  delay(2500);
}

void trocaSinaisDosvaloresAbaixoDeZero(int novaVelocidadeA, int novaVelocidadeB ) {



  if (novaVelocidadeA < 0) {
    novaVelocidadeA = novaVelocidadeA * (-1);
  }


  if (novaVelocidadeB < 0) {
    novaVelocidadeB = novaVelocidadeB  * (-1);
  }


  frente(novaVelocidadeA, novaVelocidadeB);

}


void frente(int novaVelocidadeA, int novaVelocidadeB) {





  digitalWrite(entradaDireta1, LOW);
  digitalWrite(entradaDireta2, HIGH);
  digitalWrite(entradaEsquerda3, LOW);
  digitalWrite(entradaEsquerda4, HIGH);
  //delay(500);
  // delay(500);
  /*Serial.print("A");
  Serial.println(novaVelocidadeA);
  Serial.print("B");
  Serial.println(novaVelocidadeB);
*/
  if (novaVelocidadeA > 130) {
    novaVelocidadeA = 90;
    novaVelocidadeB = 80;

    digitalWrite(entradaDireta1, LOW);
    digitalWrite(entradaDireta2, HIGH);
    digitalWrite(entradaEsquerda3, HIGH);
    digitalWrite(entradaEsquerda4, LOW);

    analogWrite(motorA, novaVelocidadeA);//78 velocidade minima// 158 velocidade media
    analogWrite(motorB, novaVelocidadeB);//45 velocidade minima // 54 velocidade media---------------------------------------
  }
  else if (novaVelocidadeB > 130) {
    novaVelocidadeB = 90;
    novaVelocidadeA = 80;
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
  direita = analogRead(A5);
  //Serial.println(direita);
  extremaDireita = digitalRead(sen5);
  //esquerdaExterno = analogRead();
  mudarValorDaLeituraParaUmOuZero();
}
void mudarValorDaLeituraParaUmOuZero() {

  if (direita < 200) {
    direita = 0;
  } else {
    direita = 1;
  }

}


void controlePid(int erro) {

  /*if (comecoCurva) {

    VelocidadeConstatnteA = 100;//+5
    VelocidadeConstatnteB = 100;//+5
    kp = 30;//16
    kd = 0.6;//5.2//6
    ki = 0;
    }
    else {*/
  VelocidadeConstatnteA = 90;//+5
  VelocidadeConstatnteB = 90;//+5
  kp = 20;//16
  kd = 1.5;//5.2//6
  ki = 0;
  //}

  /*delay(200);
    Serial.print("velocidade A");
    Serial.println(VelocidadeConstatnteA);
    Serial.print("velocidade B");
    Serial.println(VelocidadeConstatnteB);*/
  //+ kd * (erro_anterior - erro)



  sinalPid = kp * erro + kd * (erro_anterior - erro) + ki * (inte + erro_anterior);

  novaVelocidadeA = VelocidadeConstatnteA + sinalPid ;
  novaVelocidadeB = VelocidadeConstatnteB - sinalPid ;

  if (erro == 4 || erro == -4)
  {
    novaVelocidadeA = novaVelocidadeA - (novaVelocidadeA * 0.2);
    novaVelocidadeB = novaVelocidadeB - (novaVelocidadeB * 0.2);
  }

  erro_anterior = erro;

  trocaSinaisDosvaloresAbaixoDeZero(novaVelocidadeA, novaVelocidadeB);
}

long retornaTempoParaControleDoBuzzer() {
  long tempoAtual = millis();
  if (tempoAtual > (tempoInicial + 500)) {
    return  tempoInicial = tempoAtual;
  }
  return 0l;
}

void loop() {

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
  


  lerSensores();




    if ((centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
     if( comecoFim >= 1 ) {
     frente(0, 0);
     tone(buzze, 2000, retornaTempoParaControleDoBuzzer());
     delay(2000);
      } 
      ++comecoFim;
    }

  else if ( (centro == 1) && (esquerda == 0) &&
            (direita == 0) && (extremaEsquerda == 0)
            && (extremaDireita == 0)  ) {
    controlePid(0);
  }



  //0 1 1 0 0 :-1
  else if ((centro == 1) && (esquerda == 1) &&
           (direita == 0) && (extremaEsquerda == 0)
           && (extremaDireita == 0) ) {
    controlePid(-1);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 1 1 0 :1
  else if ((centro == 1) && (esquerda == 0) &&
           (direita == 1) && (extremaEsquerda == 0)
           && (extremaDireita == 0) ) {
    controlePid(1);
    entrouNaCurva = 0;
    noTone(buzze);
  }


  //0 1 0 0 0 :-2
  else if ((centro == 0) && (esquerda == 1) &&
           (direita == 0) && (extremaEsquerda == 0)
           && (extremaDireita == 0) ) {
    controlePid(-2);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 0 :2
  else if ((centro == 0) && (esquerda == 0) &&
           (direita == 1) && (extremaEsquerda == 0)
           && (extremaDireita == 0) ) {
    controlePid(2);
    entrouNaCurva = 0;
    noTone(buzze);
  }


  //1 1 0 0 0 :-3
  else if ((centro == 0) && (esquerda == 1) &&
           (direita == 0) && (extremaEsquerda == 1)
           && (extremaDireita == 0) ) {
    controlePid(-3);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 1 :3
  else if ((centro == 0) && (esquerda == 0) &&
           (direita == 1) && (extremaEsquerda == 0) &&
           (extremaDireita == 1) ) {

    controlePid(3);
    entrouNaCurva = 0;
    noTone(buzze);

  }


  //1 0 0 0 0 :-4
  else if ((centro == 0) && (esquerda == 0)
           && (direita == 0) && (extremaEsquerda == 1)
           && (extremaDireita == 0) ) {
    controlePid(-4);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 0 1 :4
  else if ((centro == 0) && (esquerda == 0) &&
           (direita == 0) && (extremaEsquerda == 0)
           && (extremaDireita == 1) ) {
    controlePid(4);
    entrouNaCurva = 0;
    noTone(buzze);
  }

 

  //  //1 0 0 0 0 :-5

}
