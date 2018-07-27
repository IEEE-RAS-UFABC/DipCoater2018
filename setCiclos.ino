#include <LiquidCrystal.h> //Em teoria essas 5 coisas 
LiquidCrystal lcd(2,3,4,5,6,7); //aqui já existem no 
const int botaoSelecionar = 9; //programa do menu
const int botaoVoltar = 10;
int ciclosDeFuncionamento = 0; //essa constante deve ser o mesmo usado 
//nas funções do que vao girar os motores de passo

int encoder(); //chamando a funcao encoder

void setup() {
}

void loop(){  
}


void funcCiclos(){
  int ciclosI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    ciclosI = ciclosI + encoder();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ciclos totais");
    lcd.setCursor(0, 1);
    lcd.print(ciclosI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      ciclosDeFuncionamento = ciclosI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}
