int bloque1[] = {22,23, 24,25, 26,27, 28,29, 30,31, 32,33, 34,35, 36,37};

int luzb1[] = {13,11,9,7,5,3,14,16,20,A12,A0,A2,A4,A6,A8,A10};
int luzb2[] = {12,10,8,6,4,2,15,17,21,A13,A1,A3,A5,A7,A9,A11};

int disponibilidad[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int robo = 0;

int alarmaReserva1[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

int buzzer = A14;
int alarmaAnti = A15;
bool shute1[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

String inputString = "";
bool valido = false;

//Disponible - 0
//Ocupado - 1
//Reservado - 2

// ---------------------------------PARA LCD-------------------------
// libreria para el manejo de LCD
#include <LiquidCrystal.h>

// asignamos los pines de salida del arduino
const int rs1 = 38, en1 = 39, d41 = 40, d51 = 41, d61 = 42, d71 = 43;

// inicializamos el objeto LCD
LiquidCrystal lcd(rs1, en1, d41, d51, d61, d71);

// Creamos los array que utiliza la funicion createChar()
// Creamos los caracteres epeciales para el carro
byte carchar4[8]= {B00000,B00000,B01110,B11111,B11011,B11111,B01110,B00000};
byte carchar5[8]={B11111,B11111,B00011,B00011,B00011,B11111,B11111,B00000};
byte carchar7[8]={B11111,B11111,B00000,B00000,B11111,B11111,B11111,B00000};
byte carchar8[8]={B11111,B11111,B00000,B00000,B11111,B11111,B11111,B00000};
byte carchar9[8]={B11000,B11110,B00110,B00011,B01111,B01111,B01111,B01111};

// Creamos las flechas
byte arrowchar[8]={B00100, B01110, B11111, B01110, B01110,B01110,B00000,B00000};
byte arrowchar2[8]={B00100, B00110, B11111, B11111, B00110,B00100,B00000,B00000};
// Creamos la barra invertida
byte negchar[8]={ B00000,B10000,B11000,B01100,B00110,B00011,B00001,B00000};




unsigned long  TiempoAnterior;

// para los delay en intervalos usando millis
#define INTERVALO_MENSAJE1 5000
#define INTERVALO_MENSAJE2 7000
#define INTERVALO_MENSAJE3 11000
#define INTERVALO_MENSAJE4 15000
unsigned long tiempo_1 = 0;
unsigned long tiempo_2 = 0;
unsigned long tiempo_3 = 0;
unsigned long tiempo_4 = 0;


// --------------------------------------FIN PARA LCD ------------------------------



void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Serial1.begin(9600);//iniciailzamos la comunicación
  
  for (int i = 0; i<16; i++){ 
    pinMode(bloque1[i],INPUT);
  }

  for (int i = 0; i<16; i++){
    pinMode(luzb1[i],OUTPUT);
    pinMode(luzb2[i],OUTPUT);
  }   

  pinMode(buzzer,OUTPUT); 
  pinMode(alarmaAnti,OUTPUT); 


   //------------------------------------------SETUP LCD-----------------
  // indicamos el tamaño del display
    // inicializamos la pantalla indicando filas y columnas
  lcd.begin(16,2);
  // asignamos un numero a la funcion createChar seguido de el nombre de el array creado
 
  // Este es un nuevo caracter
  lcd.createChar(6,negchar);

  // Creamos las flechas
  lcd.createChar(2,arrowchar);
  lcd.createChar(3,arrowchar2);

 //Creamos las partes del carro 
  lcd.createChar(4,carchar4);
  lcd.createChar(5,carchar5);
  lcd.createChar(7,carchar7);
  lcd.createChar(8,carchar8);
  lcd.createChar(9,carchar9);


  TiempoAnterior = millis();
  
  //--------------------------------FIN SETUP LCD---------------------------------  

}

void loop(){
// ----- PARA EL LCD -----
int Parqueos_Disponibles = 0;
int Parqueos_Reservados = 0;
int Parqueos_Ocupados = 0;

  //********** Nivel 1*************
  for (int i = 0; i < 16; i++){
    if (disponibilidad[i] != 2 && shute1[i] == false){
      //|| shute == false
      if (digitalRead(bloque1[i]) == HIGH){
        //Rojo
        digitalWrite(luzb1[i], HIGH);
        digitalWrite(luzb2[i], LOW);
        disponibilidad[i] = 1;
        Parqueos_Ocupados ++;
        
      }else{
        //Verde
        if (disponibilidad[i] == 1 and robo == 1){

        }        
        digitalWrite(luzb1[i], LOW);
        digitalWrite(luzb2[i], HIGH);
        disponibilidad[i] = 0;
        Parqueos_Disponibles++;
      }    
    }else{
      //Amarillo
      if (digitalRead(bloque1[i]) == HIGH){
        disponibilidad[i] = 1;
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
      Parqueos_Reservados++;
      
    }
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Alarma antirrobos
  //Si está desocupado (disponible = 0) y la alarma sigue activa (alarma=true) se eniende la alarma
  for (int i = 0; i < 16; i++){
    if (disponibilidad[i] == 0  && alarmaReserva1[i] == true){
      digitalWrite(alarmaAnti, HIGH);
      break;
    }else{
      digitalWrite(alarmaAnti, LOW);
    }
  }

  String reporte = "";
  for (int i = 0; i<15; i++){
    reporte.concat(disponibilidad[i]);
    reporte.concat(",");
  }  
  reporte.concat(disponibilidad[15]);
  Serial1.print(reporte);
  
  delay(100);

  //Aqui se lee la respuesta de Python 
  
  String ret = Serial1.readString();

  String strs[32];
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
    if (i < 16){
      disponibilidad[i] = strs[i].toInt();
    }else{
      if (strs[i].toInt() == 1){
        alarmaReserva1[i-15] = true;
      }else{
        alarmaReserva1[i-15] = false;
      }
    }  
  }

  robo = disponibilidad[16];
  
  delay(500);
  //-------------------------------LCD LOOP-------------------------

  if(Parqueos_Disponibles==0){
      if(millis()-TiempoAnterior >= 1000){
        TiempoAnterior = millis();
    // limpiamos la pantalla LCD
    lcd.clear();
  lcd.setCursor(6,1);
  lcd.write("[");
  lcd.setCursor(7,1);
  lcd.write("/");
  lcd.setCursor(8,1);
  lcd.write("_");
  lcd.setCursor(9,1);
  lcd.write(6);
  lcd.setCursor(10,1);
  lcd.write("]");
  lcd.setCursor(7,0);
  lcd.write(6);
  lcd.setCursor(8,0);
  lcd.write(8);
  lcd.setCursor(9,0);
  lcd.write("/");
  lcd.setCursor(13,1);
  lcd.write("X");
  lcd.setCursor(13,0);
  lcd.write("X");
  lcd.setCursor(3,1);
  lcd.write("X");
  lcd.setCursor(3,0);
  lcd.write("X");
  }
  if(millis()-TiempoAnterior >= 1000){
    TiempoAnterior = millis();
    lcd.clear();
  lcd.setCursor(5,0);
  lcd.write("PARQUEO");
  lcd.setCursor(6,1);
  lcd.write("LLENO");
   lcd.setCursor(13,1);
  lcd.write("X");
  lcd.setCursor(13,0);
  lcd.write("X");
  lcd.setCursor(3,1);
  lcd.write("X");
  lcd.setCursor(3,0);
  lcd.write("X");
   

  }
  
  
 

  }else{
     
      // son if para no utilizar delay ya que el delay pausa todo el codigo
      // por lo tanto se utilizaron los millies 
      if(millis() > tiempo_1 + INTERVALO_MENSAJE1){
        tiempo_1 = millis();
      lcd.setCursor(0,0);
      lcd.print("PARQUEOS ");
      lcd.setCursor(0,1);
      lcd.print("DISPONIBLES: ");
      lcd.print(Parqueos_Disponibles);
        
       
    }
   
    if(millis() > tiempo_2 + INTERVALO_MENSAJE2){
        tiempo_2 = millis();
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PARQUEOS ");
      lcd.setCursor(0,1);
      lcd.print("0CUPADOS: ");
      lcd.print(Parqueos_Ocupados);
        
       
    }
   
    if(millis() > tiempo_3 + INTERVALO_MENSAJE3){
        tiempo_3 = millis();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PARQUEOS ");
        lcd.setCursor(0,1);
        lcd.print("RESERVADOS: ");
        lcd.print(Parqueos_Reservados);
        
     
    }
    if(millis() > tiempo_4 + INTERVALO_MENSAJE4){
        tiempo_4 = millis();
        // Este ciclo for es para el desplazamiento a la derecha 
      for(int i= 0; i<24;i++){
      // idicamos la posicion de el caracter en el display + i 
      // Como i va aumentando los caracteres se empiezan a desplazar
      lcd.setCursor(1+i,1);
      // Escribimos sobre la LCD
      lcd.write("[");
      lcd.setCursor(2+i,1);
      lcd.write(4);
      lcd.setCursor(3+i,1);
      lcd.write("_");
      lcd.setCursor(4+i,1);
      lcd.write(4);
      lcd.setCursor(5+i,1);
      lcd.write("]");
      lcd.setCursor(2+i,0);
      lcd.write("/");
      lcd.setCursor(3+i,0);
      lcd.write(8);
      lcd.setCursor(4+i,0);
      lcd.write(9);
      lcd.setCursor(7+i,1);
      lcd.write(3);
      lcd.setCursor(7+i,0);
      lcd.write(3);
      // Estas son las flechas
      lcd.setCursor(15,0);
      lcd.write(2);
      lcd.setCursor(15,1);
      lcd.write(2);
     
      lcd.setCursor(-9+i,0);
      lcd.write("AVANCE");
      
      lcd.setCursor(i,1);
      lcd.write(3);
      lcd.setCursor(i,0);
      lcd.write(3);
      delay(100);
      
      // leugo se borra 
    
      lcd.clear();
  
  
  }// fin del for
    }// fin del delay    
  
  }// fin de else

  

// ------------------------------FIN LOOP LCD--------------------------------
}
