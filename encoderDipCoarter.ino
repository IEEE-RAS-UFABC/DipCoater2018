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
  pinMode(encoderPino1, INPUT);
  pinMode(encoderPino2, INPUT);
}

void loop() {

}

int encoder() {
  static bool oldEstado1; //estados anteriores dos pinos do encoder
  static bool oldEstado2; //variaveis com o prefixo static tem seus dados mantidos mesmo quando a função acaba
  bool estado1; //novos estados dos pinos
  bool estado2;

  //leitura dos novos estados dos pinos
  estado1 = digitalRead(encoderPino1);
  estado2 = digitalRead(encoderPino2);
  
  //estados novo e comparado com o antigo
  if(estado1 == oldEstado1){
    if(estado1 == HIGH){
    	if(oldEstado2 == LOW && estado2 == HIGH){
     	 oldEstado1 = estado1;
  	 	 oldEstado2 = estado2;
     	 return 1; //caso rotacao horaria
    	}
    	if(oldEstado2 == HIGH && estado2 == LOW){
      	oldEstado1 = estado1;
  	  	oldEstado2 = estado2;
      	return -1; //caso rotacao antihoraria
        }
    }
    else{
    	if(oldEstado2 == LOW && estado2 == HIGH){
     	 oldEstado1 = estado1;
  	 	 oldEstado2 = estado2;
     	 return -1; //caso rotacao horaria
    	}
    	if(oldEstado2 == HIGH && estado2 == LOW){
      	oldEstado1 = estado1;
  	  	oldEstado2 = estado2;
      	return 1; //caso rotacao antihoraria
        }
    }
  }
  if(estado2 == oldEstado2){
    if(estado2 == HIGH){
    	if(oldEstado1 == LOW && estado1 == HIGH){
    	  oldEstado1 = estado1;
    	  oldEstado2 = estado2;
      	  return -1;
    	}
    	if(oldEstado1 == HIGH && estado1 == LOW){
      		oldEstado1 = estado1;
  	  		oldEstado2 = estado2;
      	return 1;
        }     
    }
    else{
    	if(oldEstado1 == LOW && estado1 == HIGH){
    	  oldEstado1 = estado1;
    	  oldEstado2 = estado2;
      	  return 1;
    	}
    	if(oldEstado1 == HIGH && estado1 == LOW){
      		oldEstado1 = estado1;
  	  		oldEstado2 = estado2;
      	return -1;
        }
    }
  }
  oldEstado1 = estado1; 
  oldEstado2 = estado2;
  return 0; //caso sem mudanca de estado
}
