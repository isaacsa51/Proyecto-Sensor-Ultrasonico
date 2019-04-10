//DEFINIR PINES UTILIZADOS
const int pinLed = 13;
const int ledR = 4;
const int ledA = 3;
const int ledV = 2;
const int pinEcho = 7;
const int pinTrigger = 6;
const int pinBuzzer = 5;
const int pinRX = 1;
const int pinTX = 0;

// VARIABLES PARA CALCULOS
unsigned int tiempo, distancia;

void setup(){
  Serial.begin(9600);
  delay(200);

  pinMode(pinEcho, INPUT);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
}

void loop(){
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);

  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  calcularDistancia();
}

void calcularDistancia(){
  tiempo = pulseIn(pinEcho, HIGH);
  distancia = tiempo / 58;

  // ENVIAR EL RESULTADO A CONSOLA
  Serial.print(distancia);
  Serial.println(" cm");
  delay(200);
  
  // MANDAR ALERTAS A CIERTAS DISTANCIAS
  alertas(distancia);
}

void aviso(int beepHertz, int ledBuzzerDelay){
  //MANDAR AVISO DEL LED Y BUZZER
  tone(pinBuzzer, beepHertz);
  delay(ledBuzzerDelay);
  noTone(pinBuzzer);
}

void alertas(int distancia){
  if(distancia > 30 && distancia <= 80){
    aviso(600, 500);
    
    digitalWrite(ledV, HIGH);
    digitalWrite(ledA, LOW);
    digitalWrite(ledR, LOW);
  } else if(distancia <= 30 && distancia > 15){
    aviso(800, 500);
    
    digitalWrite(ledA, HIGH);
    digitalWrite(ledV, LOW);
    digitalWrite(ledR, LOW);
  } else if(distancia <= 15 && distancia > 5){
    aviso(1000, 250);
    
    digitalWrite(ledR, HIGH);
    digitalWrite(ledV, LOW);
    digitalWrite(ledA, LOW);
  } else if(distancia <= 5){
    aviso(1250, 100);
    
    digitalWrite(ledR, HIGH);
    digitalWrite(ledV, LOW);
    digitalWrite(ledA, LOW);
  } else{
    digitalWrite(pinLed, LOW);
    digitalWrite(ledV, LOW);
    digitalWrite(ledA, LOW);
    digitalWrite(ledR, LOW);
    delay(500);
  }
}
