/*Função leitura do encoder
 * para chamar apenas chame 
 * "encoder()"
 * a função retorna -1, 0 ou 1 dependendo 
 * se foi girado na direção anti horaria,
 * se não foi
 * ou se foi girado na direção horaria.
 */




const int encoderPino1 = 5; //mudar para os pinos que serao usados
const int encoderPino2 = 6;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPino1, INPUT);
  pinMode(encoderPino2, INPUT);
}

void loop() {
Serial.print(encoder());
}

int encoder() {
  static bool oldEstado1; //estados anteriores dos pinos do encoder
  static bool oldEstado2; //variaveis com o prefixo static tem seus dados mantidos mesmo quando a função acaba
  bool estado1; //novos estados dos pinos
  bool estado2;
  while(not(digitalRead(encoderPino1) == HIGH || igitalRead(encoderPino2) == HIGH)){
  //leitura dos novos estados dos pinos
  //Serial.println("testando encoder");
  estado1 = digitalRead(encoderPino1);
  estado2 = digitalRead(encoderPino2);
  //Serial.println(estado1);
  //Serial.println(estado2); 
   if(oldEstado1 == LOW && oldEstado2 == HIGH && estado1 == LOW && estado2 == LOW){
     oldEstado1 = estado1;
     oldEstado2 = estado2;
     Serial.println(estado1);
     Serial.println(estado2);
     Serial.println(oldEstado1);
     Serial.println(oldEstado2);
     return -1; //caso rotacao antihoraria
     }
     if(oldEstado1 == HIGH && oldEstado2 == LOW && estado1 == LOW && estado2 == LOW){
     oldEstado1 = estado1;
     oldEstado2 = estado2;
     Serial.println(estado1);
     Serial.println(estado2);
     Serial.println(oldEstado1);
     Serial.println(oldEstado2);
     return 1; //caso rotacao antihoraria
     }
  oldEstado1 = estado1; 
  oldEstado2 = estado2;
  }
  return 0; //caso sem mudanca de estado
}
