#include <Stepper.h>

#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

// Declaramos la variable para controlar el servo
const int spr = 100;
Stepper barreraEntrada(spr, IN1, IN2, IN3, IN4);
Stepper barreraSalida(spr, 5,4,3,2);
//Variables para bluetooth
char entradaBluetooth;
int ledBarreraEntrada = 11, ledBarreraSalida = 10;
boolean alarmaActivada = false;
boolean estacionamientoLleno = false;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  pinMode(ledBarreraEntrada, OUTPUT);
  pinMode(ledBarreraSalida, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  barreraEntrada.setSpeed(10);
  barreraSalida.setSpeed(10);
}

void loop() {
  if(Serial.available() > 0){
  	entradaBluetooth = Serial.read();

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

  if(alarmaActivada == true){
  	Serial.print("A");
  }
}
