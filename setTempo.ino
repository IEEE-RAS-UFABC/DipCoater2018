#include <LiquidCrystal.h> //Em teoria essas 5 coisas 
LiquidCrystal lcd(2,3,4,5,6,7); //aqui já existem no 
const int botaoSelecionar = 9; //programa do menu
const int botaoVoltar = 10;
int tempoDeFuncionamento = 0; //essa constante deve ser o mesmo usado 
//nas funções do que vao girar os motores de passo

int encoder(); //chamando a funcao encoder

void setup() {
}

void loop(){  
}


void tempo(){
  int tempoI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    tempoI = tempoI + encoder();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("tempo de banho");
    lcd.setCursor(0, 1);
    lcd.print(tempoI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      tempoDeFuncionamento = tempoI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}
