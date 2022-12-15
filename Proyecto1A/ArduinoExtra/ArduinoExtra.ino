int luzb1[] = {13,11,9,7,5,3,14,16,20,A12,A0,A2,A4,A6,A8,A10};
int luzb2[] = {12,10,8,6,4,2,15,17,21,A13,A1,A3,A5,A7,A9,A11};

// Declaramos la variable para controlar el servo
const int spr = 100;
Stepper barreraEntrada(spr, 40, 41, 42, 43);
Stepper barreraSalida(spr, 44,45,46,47);
//Variables para bluetooth
char entradaBluetooth;
int ledBarreraEntrada = 48;
int ledBarreraSalida = 49;
int pinesBarreras = {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};

String inputString = "";
bool valido = false;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Serial1.begin(9600);
  Serial2.begin(9600);
  inputString.reserve(200);
  
  for (int i = 0; i<16; i++){
    pinMode(luzb1[i],OUTPUT);
    pinMode(luzb2[i],OUTPUT);
  }

  for(int i=0; i<13; i++){
      pinMode(pinesBarreras[i], OUTPUT);
  }
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

  if (valido){
    String strs[20];
    int StringCount = 0;

    while (inputString.length() > 0){
      int index = inputString.indexOf(',');
      if (index == -1){
        strs[StringCount++] = inputString;
        break;
      }else{
        strs[StringCount++] = inputString.substring(0, index);
        inputString = inputString.substring(index+1);
      }
    }
    
    for (int i = 0; i < 16; i++){
      Serial1.println(strs[i]);
      if (strs[i].toInt() == 1){
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], LOW);
      }else if (strs[i].toInt() == 0){
        digitalWrite(luzb1[i], LOW);
        digitalWrite(luzb2[i], HIGH);
      }else if (strs[i].toInt() == 2){
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], HIGH);
      } 
    }

    inputString = "";
    valido = false;
  }
}