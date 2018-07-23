/*Função leitura do encoder
 * para chamar apenas chame 
 * "encoder()"
 * a função retorna -1, 0 ou 1 dependendo 
 * se foi girado na direção anti horaria,
 * se não foi
 * ou se foi girado na direção horaria.
 */




const int encoderPino1 = 5;
const int encoderPino2 = 6;

void setup() {
  pinMode(encoderPino1, INPUT);
  pinMode(encoderPino2, INPUT);
}

void loop() {

}

int encoder() {
  static bool oldEstado1;
  static bool oldEstado2;
  bool estado1;
  bool estado2;

  estado1 = digitalRead(encoderPino1);
  estado2 = digitalRead(encoderPino2);
  
  if(estado1 == oldEstado1){
    if(oldEstado2 == LOW && estado2 == HIGH){
      return 1;
    }
    if(oldEstado2 == HIGH && estado2 == LOW){
      return -1;
    }
  }
  if(estado2 == oldEstado2){
    if(oldEstado1 == LOW && estado1 == HIGH){
      return 1;
    }
    if(oldEstado1 == HIGH && estado1 == LOW){
      return -1;
    }
  }
  else{
    return 0;
  }
  
  oldEstado1 = estado1;
  oldEstado2 = estado2;

}
