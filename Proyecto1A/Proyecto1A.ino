int bloque1[] = {22,23, 24,25, 26,27, 28,29, 30,31, 32,33, 34,35, 36,37};
int bloque2[] = {38,39, 40,41, 42,43, 44,45, 46,47, 48,49, 50,51, 52,53};

int luzb1[] = {13,11,9,7,5,3,14,16,20,A12,A0,A2,A4,A6,A8,A10};
int luzb2[] = {12,10,8,6,4,2,15,17,21,A13,A1,A3,A5,A7,A9,A11};

int disponibilidad[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int disponibilidad2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int alarmaReserva1[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
int alarmaReserva2[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

int buzzer = A14;
bool shute1[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
bool shute2[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

String inputString = "";
bool valido = false;

//Disponible - 0
//Ocupado - 1
//Reservado - 2

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Serial1.begin(9600);//iniciailzamos la comunicación
  
  for (int i = 0; i<16; i++){ 
    pinMode(bloque1[i],INPUT);
    pinMode(bloque2[i],INPUT);
  }

  for (int i = 0; i<16; i++){
    pinMode(luzb1[i],OUTPUT);
    pinMode(luzb2[i],OUTPUT);
  }   

  pinMode(buzzer,OUTPUT); 
}

void loop(){
  //********** Nivel 1*************
  for (int i = 0; i < 16; i++){
    if (disponibilidad[i] != 2 && shute1[i] == false){//|| shute == false
      if (digitalRead(bloque1[i]) == HIGH){
        //Rojo
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], LOW);
        disponibilidad[i] = 1;
      }else{
        //Verde
        digitalWrite(luzb1[i], LOW);
        digitalWrite(luzb2[i], HIGH);
        disponibilidad[i] = 0;
      }    
    }else{
      //Amarillo
      if (digitalRead(bloque1[i]) == HIGH){
        disponibilidad2[i] = 1;
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], LOW);
        shute1[i] = true;
        digitalWrite(buzzer, HIGH);
      }else{
        disponibilidad[i] = 2;
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], HIGH);
        shute1[i] = false;
        digitalWrite(buzzer, LOW);
      }
      
    }
  }

  //********** Nivel 2*************
  for (int i = 0; i < 16; i++){
    if (disponibilidad2[i] != 2 && shute2[i] == false){//|| shute == false
      if (digitalRead(bloque2[i]) == HIGH){
        //Rojo
        disponibilidad2[i] = 1;
      }else{
        //Verde
        disponibilidad2[i] = 0;
      }    
    }else{
      //Amarillo
      if (digitalRead(bloque2[i]) == HIGH){
        disponibilidad2[i] = 1;
        shute2[i] = true;
        digitalWrite(buzzer, HIGH);
      }else{
        disponibilidad2[i] = 2;
        shute2[i] = false;
        digitalWrite(buzzer, LOW);
      }
    }
  }

  String lucesNivel2 = "";
  for (int i = 0; i<15; i++){
    lucesNivel2.concat(disponibilidad2[i]);
    lucesNivel2.concat(",");
  }
  lucesNivel2.concat(disponibilidad2[15]);
  lucesNivel2.concat("_");
  Serial.print(lucesNivel2);

  String reporte = "";
  for (int i = 0; i<16; i++){
    reporte.concat(disponibilidad[i]);
    reporte.concat(",");
  }  
  for (int i = 0; i<15; i++){
    reporte.concat(disponibilidad2[i]);
    reporte.concat(",");
  }  
  reporte.concat(disponibilidad2[15]);
  Serial1.print(reporte);
  
  delay(100);

  //Aqui se lee la respuesta de Python 
  
  String ret = Serial1.readString();

  String strs[20];
  int StringCount = 0;

  while (ret.length() > 0){
    int index = ret.indexOf(',');
    if (index == -1){
      strs[StringCount++] = ret;
      break;
    }else{
      strs[StringCount++] = ret.substring(0, index);
      ret = ret.substring(index+1);
    }
  }
  
  for (int i = 0; i < 32; i++){
    if (i<16){
      disponibilidad[i] = strs[i].toInt();
    }else{
      disponibilidad2[i-16] = strs[i].toInt();
    }
  }
  
  delay(500);
}
