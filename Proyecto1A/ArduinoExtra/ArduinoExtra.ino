#include <Stepper.h>

// Declaramos la variable para controlar el servo
const int spr = 100;
Stepper barreraEntrada(spr, 40, 41, 42, 43);
Stepper barreraSalida(spr, 44,45,46,47);
//Variables para bluetooth
char entradaBluetooth;
int ledBarreraEntrada = 48;
int ledBarreraSalida = 49;
int pinesBarreras[] = {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};

String inputString = "";
bool valido = false;



void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Serial1.begin(9600);
  Serial2.begin(9600);
  inputString.reserve(200);

  for(int i=0; i<13; i++){
      pinMode(pinesBarreras[i], OUTPUT);
  }

  barreraEntrada.setSpeed(10);
  barreraSalida.setSpeed(10);
}

void serialEvent(){
  while (Serial.available()){
    char inChar = (char)Serial.read();
    if (inChar != '_'){
      inputString += inChar;
    }else{
      valido = true;
    }
    
  }
}


void loop(){
  if(Serial2.available() > 0){
    entradaBluetooth = Serial2.read();

    if(entradaBluetooth == 'A'){
      digitalWrite(ledBarreraEntrada, HIGH);
      // Desplazamos a la posición 90º
      barreraEntrada.step(-66);
    }

    if(entradaBluetooth == 'B'){
      digitalWrite(ledBarreraEntrada, LOW);
      // Desplazamos a la posición 0º
      barreraEntrada.step(66);
    }

    if(entradaBluetooth == 'D'){
      digitalWrite(ledBarreraSalida, HIGH);
      // Desplazamos a la posición 90º
      barreraSalida.step(-66);
    }

    if(entradaBluetooth == 'E'){
      digitalWrite(ledBarreraSalida, LOW);
      // Desplazamos a la posición 0º
      barreraSalida.step(66);
    }
  }
  
}
