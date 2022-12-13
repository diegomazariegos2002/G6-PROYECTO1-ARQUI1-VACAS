int luzb1[] = {13,11,9,7,5,3,14,16,20,A12,A0,A2,A4,A6,A8,A10};
int luzb2[] = {12,10,8,6,4,2,15,17,21,A13,A1,A3,A5,A7,A9,A11};

String inputString = "";
bool valido = false;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Serial1.begin(9600);
  inputString.reserve(200);
  
  for (int i = 0; i<16; i++){
    pinMode(luzb1[i],OUTPUT);
    pinMode(luzb2[i],OUTPUT);
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