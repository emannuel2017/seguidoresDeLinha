
#define sen1  13
#define sen2  12
#define sen3  11
#define sen4  6
#define sen5  7


int motorA = 3;
int motorB = 10;

int AfrenteDireita = 4;
int AtrazDireita = 5;
int BfrenteDireita = 8;
int BtrazDireita = 9;



//starwars\\




int novaVelocidadeA;
int novaVelocidadeB;

int buzze = 2;



int centro, direita, esquerda, extremaDireita;
int extremaEsquerda, direitaExterno;

int erro;
float integral = 0;
float kp = 40;
float ki = 0;
float kd = 5;
float erro_anterior = 0;
float sinalPid;

int VelocidadeConstatnteA = 0;
int VelocidadeConstatnteB = 0;

long tempoInicial = 0l;

void setup() {
  Serial.begin(9600);

  pinMode(AfrenteDireita, OUTPUT);
  pinMode(AtrazDireita, OUTPUT);
  pinMode(BfrenteDireita, OUTPUT);
  pinMode(BtrazDireita, OUTPUT);

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

void re(float velA, float velB) {
  digitalWrite(AfrenteDireita, LOW);
  digitalWrite(AtrazDireita, HIGH);
  digitalWrite(BfrenteDireita, LOW);
  digitalWrite(BtrazDireita, HIGH);

  analogWrite(motorA, velA);
  analogWrite(motorB, velB);
}


void frente(float novaVelocidadeA, float novaVelocidadeB) {

  digitalWrite(AfrenteDireita, LOW);
  digitalWrite(AtrazDireita, HIGH);
  digitalWrite(BfrenteDireita, HIGH);
  digitalWrite(BtrazDireita, LOW);
  //  para de observar no Serial
  //  Serial.println("Velocidade mudada pelo pid");
  //  Serial.print("A");
  //  Serial.println(novaVelocidadeA);
  //  Serial.print("B");
  //  Serial.println(novaVelocidadeB);
  //  delay(800);


  if (novaVelocidadeA > 200) {
    novaVelocidadeA = 170;
    novaVelocidadeB = 100;//100;
    //  para de observar no Serial

    //    Serial.println("Velocidade do motor A maior mudar rotação");
    //
    //    Serial.println(novaVelocidadeB);
    //    Serial.println(novaVelocidadeA);
    //    delay(800);
    digitalWrite(AfrenteDireita, LOW);
    digitalWrite(AtrazDireita, HIGH);
    digitalWrite(BfrenteDireita, LOW);
    digitalWrite(BtrazDireita, HIGH);

    novaVelocidadeA = novaVelocidadeA - (novaVelocidadeA * 0.2);
    novaVelocidadeB = novaVelocidadeB - (novaVelocidadeB * 0.2);

    analogWrite(motorA, novaVelocidadeA);
    analogWrite(motorB, novaVelocidadeB);
  }
  else if (novaVelocidadeB > 200) {
    novaVelocidadeB = 170;
    novaVelocidadeA = 100;
    //  para de observar no Serial

    //    Serial.println("Velocidade do motor B maior mudar rotação");
    //
    //    Serial.println(novaVelocidadeB);
    //    Serial.println(novaVelocidadeA);
    //    delay(800);

    digitalWrite(AfrenteDireita, HIGH);
    digitalWrite(AtrazDireita, LOW);
    digitalWrite(BfrenteDireita, HIGH);
    digitalWrite(BtrazDireita, LOW);


    novaVelocidadeA = novaVelocidadeA - (novaVelocidadeA * 0.2);
    novaVelocidadeB = novaVelocidadeB - (novaVelocidadeB * 0.2);

    analogWrite(motorA, novaVelocidadeA);
    analogWrite(motorB, novaVelocidadeB);  }
  else {
    analogWrite(motorA, novaVelocidadeA);
    analogWrite(motorB, novaVelocidadeB);
  }

}



void lerSensores() {

  extremaEsquerda = digitalRead(sen1);
  esquerda = digitalRead(sen2);
  centro = digitalRead(sen3);
  direita = digitalRead(sen4);
  extremaDireita = digitalRead(sen5);
  direitaExterno = analogRead(A5);
  mudarValorAnalogicoParaDigital();
}
void mudarValorAnalogicoParaDigital() {

  if (direitaExterno < 500) {
    direitaExterno = 0;
  } else {
    direitaExterno = 1;
  }

}


void controlePid(int erro) {


  VelocidadeConstatnteA = 110;
  VelocidadeConstatnteB = 110;
  kp = 40;
  kd = 6.5;
  ki = 0;//ainda não e necessário o uso do itegral '+ ki * (inte + erro_anterior)' na formula atual do código


  sinalPid = kp * erro + kd * (erro_anterior - erro);




  /*delay(200);
    Serial.print("velocidade A");
    Serial.println(VelocidadeConstatnteA);
    Serial.print("velocidade B");
    Serial.println(VelocidadeConstatnteB);*/


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

  

  if (espera < 1) {
    espera++;
    delay(2000);
  }


  long tempoLigado = millis(); //parar sozinho

  if ( tempoLigado > 20000 && direitaExterno == 1 )
  {
    frente(110, 110);
    delay(1500);
    frente(0, 0);
    delay(3500);
  }

//0 0 1 0 0 :0 erro
  else if ( (centro == 1) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0)  ) {
    controlePid(0);
  }

  //0 1 1 0 0 :erro -1
  else if ((centro == 1) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(-1);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 1 1 0 :erro 1
  else if ((centro == 1) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(1);
    entrouNaCurva = 0;
    noTone(buzze);
  }
  //0 1 0 0 0 :erro -2
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(-2);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 0 :erro 2
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 0) ) {
    controlePid(2);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //1 1 0 0 0 :erro -3
  else if ((centro == 0) && (esquerda == 1) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-3);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 1 1 :erro 3
  else if ((centro == 0) && (esquerda == 0) && (direita == 1) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(3);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //1 0 0 0 0 :erro -4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 1) && (extremaDireita == 0) ) {
    controlePid(-4);
    entrouNaCurva = 0;
    noTone(buzze);
  }

  //0 0 0 0 1 :erro 4
  else if ((centro == 0) && (esquerda == 0) && (direita == 0) && (extremaEsquerda == 0) && (extremaDireita == 1) ) {
    controlePid(4);
    entrouNaCurva = 0;
    noTone(buzze);
  }
}
