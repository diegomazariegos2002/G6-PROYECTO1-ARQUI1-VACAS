int bloque1[] = {22,23, 24,25, 26,27, 28,29, 30,31, 32,33, 34,35, 36,37};
int bloque2[] = {38,39, 40,41, 42,43, 44,45, 46,47, 48,49, 50,51, 52,53};

int luzb1[] = {13,12, 11,10, 9,8, 7,6, 5,4, 3,2, 14,15, 16,17};
int luzb2[] = {18,19, 20,21, A0,A1, A2,A3, A4,A5, A6,A7, A8,A9, A10,A11};

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación

  for (int i = 0; i<16; i++){
    if ((i%2)!=0){
      pinMode(bloque1[i],OUTPUT);
      digitalWrite(bloque1[i], LOW);
      pinMode(bloque2[i],OUTPUT);
      digitalWrite(bloque2[i], LOW);
    }else{
      pinMode(bloque1[i],INPUT);
      pinMode(bloque2[i],INPUT);
    }
  }

  for (int i = 0; i<16; i++){
    pinMode(luzb1[i],OUTPUT);
    pinMode(luzb2[i],OUTPUT);
  }    
}

void loop()
{
  
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  //********** Parqueo 1 *************
  digitalWrite(bloque1[0], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[0], LOW);
  t = pulseIn(bloque1[1], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[0], HIGH);
      digitalWrite(luzb1[1], LOW);
    }else{
      digitalWrite(luzb1[0], LOW);
      digitalWrite(luzb1[1], HIGH);
    }    
  }else{
    digitalWrite(luzb1[0], HIGH);
    digitalWrite(luzb1[1], HIGH);
  }
  Serial.print("Parqueo 1: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 2 *************
  digitalWrite(bloque1[2], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[2], LOW);
  t = pulseIn(bloque1[3], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[2], HIGH);
      digitalWrite(luzb1[3], LOW);
    }else{
      digitalWrite(luzb1[2], LOW);
      digitalWrite(luzb1[3], HIGH);
    }    
  }else{
    digitalWrite(luzb1[2], HIGH);
    digitalWrite(luzb1[3], HIGH);
  }
  Serial.print("Parqueo 2: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 3 *************
  digitalWrite(bloque1[4], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[4], LOW);
  t = pulseIn(bloque1[5], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[4], HIGH);
      digitalWrite(luzb1[5], LOW);
    }else{
      digitalWrite(luzb1[4], LOW);
      digitalWrite(luzb1[5], HIGH);
    }    
  }else{
    digitalWrite(luzb1[4], HIGH);
    digitalWrite(luzb1[5], HIGH);
  }
  Serial.print("Parqueo 3: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 4 *************
  digitalWrite(bloque1[6], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[6], LOW);
  t = pulseIn(bloque1[7], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[6], HIGH);
      digitalWrite(luzb1[7], LOW);
    }else{
      digitalWrite(luzb1[6], LOW);
      digitalWrite(luzb1[7], HIGH);
    }    
  }else{
    digitalWrite(luzb1[6], HIGH);
    digitalWrite(luzb1[7], HIGH);
  }
  Serial.print("Parqueo 4: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();


  //********** Parqueo 5 *************
  digitalWrite(bloque1[8], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[8], LOW);
  t = pulseIn(bloque1[9], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[8], HIGH);
      digitalWrite(luzb1[9], LOW);
    }else{
      digitalWrite(luzb1[8], LOW);
      digitalWrite(luzb1[9], HIGH);
    }    
  }else{
    digitalWrite(luzb1[8], HIGH);
    digitalWrite(luzb1[9], HIGH);
  }
  Serial.print("Parqueo 5: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 6 *************
  digitalWrite(bloque1[10], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[10], LOW);
  t = pulseIn(bloque1[11], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[10], HIGH);
      digitalWrite(luzb1[11], LOW);
    }else{
      digitalWrite(luzb1[10], LOW);
      digitalWrite(luzb1[11], HIGH);
    }    
  }else{
    digitalWrite(luzb1[10], HIGH);
    digitalWrite(luzb1[11], HIGH);
  }
  Serial.print("Parqueo 6: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 7 *************
  digitalWrite(bloque1[12], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[12], LOW);
  t = pulseIn(bloque1[13], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[12], HIGH);
      digitalWrite(luzb1[13], LOW);
    }else{
      digitalWrite(luzb1[12], LOW);
      digitalWrite(luzb1[13], HIGH);
    }    
  }else{
    digitalWrite(luzb1[12], HIGH);
    digitalWrite(luzb1[13], HIGH);
  }
  Serial.print("Parqueo 7: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 8 *************
  digitalWrite(bloque1[14], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque1[14], LOW);
  t = pulseIn(bloque1[15], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb1[14], HIGH);
      digitalWrite(luzb1[15], LOW);
    }else{
      digitalWrite(luzb1[14], LOW);
      digitalWrite(luzb1[15], HIGH);
    }    
  }else{
    digitalWrite(luzb1[14], HIGH);
    digitalWrite(luzb1[15], HIGH);
  }
  Serial.print("Parqueo 8: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();


  //********** Parqueo 9 *************
  digitalWrite(bloque2[0], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[0], LOW);
  t = pulseIn(bloque2[1], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[0], HIGH);
      digitalWrite(luzb2[1], LOW);
    }else{
      digitalWrite(luzb2[0], LOW);
      digitalWrite(luzb2[1], HIGH);
    }    
  }else{
    digitalWrite(luzb2[0], HIGH);
    digitalWrite(luzb2[1], HIGH);
  }
  Serial.print("Parqueo 9: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 10 *************
  digitalWrite(bloque2[2], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[2], LOW);
  t = pulseIn(bloque2[3], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[2], HIGH);
      digitalWrite(luzb2[3], LOW);
    }else{
      digitalWrite(luzb2[2], LOW);
      digitalWrite(luzb2[3], HIGH);
    }    
  }else{
    digitalWrite(luzb2[2], HIGH);
    digitalWrite(luzb2[3], HIGH);
  }
  Serial.print("Parqueo 10: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 11 *************
  digitalWrite(bloque2[4], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[4], LOW);
  t = pulseIn(bloque2[5], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[4], HIGH);
      digitalWrite(luzb2[5], LOW);
    }else{
      digitalWrite(luzb2[4], LOW);
      digitalWrite(luzb2[5], HIGH);
    }    
  }else{
    digitalWrite(luzb2[4], HIGH);
    digitalWrite(luzb2[5], HIGH);
  }
  Serial.print("Parqueo 11: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 12 *************
  digitalWrite(bloque2[6], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[6], LOW);
  t = pulseIn(bloque2[7], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[6], HIGH);
      digitalWrite(luzb2[7], LOW);
    }else{
      digitalWrite(luzb2[6], LOW);
      digitalWrite(luzb2[7], HIGH);
    }    
  }else{
    digitalWrite(luzb2[6], HIGH);
    digitalWrite(luzb2[7], HIGH);
  }
  Serial.print("Parqueo 12: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();


  //********** Parqueo 13 *************
  digitalWrite(bloque2[8], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[8], LOW);
  t = pulseIn(bloque2[9], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[8], HIGH);
      digitalWrite(luzb2[9], LOW);
    }else{
      digitalWrite(luzb2[8], LOW);
      digitalWrite(luzb2[9], HIGH);
    }    
  }else{
    digitalWrite(luzb2[8], HIGH);
    digitalWrite(luzb2[9], HIGH);
  }
  Serial.print("Parqueo 13: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 14 *************
  digitalWrite(bloque2[10], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[10], LOW);
  t = pulseIn(bloque2[11], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[10], HIGH);
      digitalWrite(luzb2[11], LOW);
    }else{
      digitalWrite(luzb2[10], LOW);
      digitalWrite(luzb2[11], HIGH);
    }    
  }else{
    digitalWrite(luzb2[10], HIGH);
    digitalWrite(luzb2[11], HIGH);
  }
  Serial.print("Parqueo 14: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 15 *************
  digitalWrite(bloque2[12], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[12], LOW);
  t = pulseIn(bloque2[13], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[12], HIGH);
      digitalWrite(luzb2[13], LOW);
    }else{
      digitalWrite(luzb2[12], LOW);
      digitalWrite(luzb2[13], HIGH);
    }    
  }else{
    digitalWrite(luzb2[12], HIGH);
    digitalWrite(luzb2[13], HIGH);
  }
  Serial.print("Parqueo 15: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

  //********** Parqueo 16 *************
  digitalWrite(bloque2[14], HIGH);
  delayMicroseconds(10);//Enviamos un pulso de 10us
  digitalWrite(bloque2[14], LOW);
  t = pulseIn(bloque2[15], HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  if (!false){
    if (d < 200){
      digitalWrite(luzb2[14], HIGH);
      digitalWrite(luzb2[15], LOW);
    }else{
      digitalWrite(luzb2[14], LOW);
      digitalWrite(luzb2[15], HIGH);
    }    
  }else{
    digitalWrite(luzb2[14], HIGH);
    digitalWrite(luzb2[15], HIGH);
  }
  Serial.print("Parqueo 16: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();

}