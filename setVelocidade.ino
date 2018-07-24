#include <LiquidCrystal.h> //Em teoria essas 4 coisas 
LiquidCrystal lcd(2,3,4,5,6,7); //aqui já existem no 
const int botaoSelecionar = 9; //programa do menu
const int botaoVoltar = 10;

int velocidadeDeFuncionamento = 0; //esse deve ser o mesmo usado 
//nas funções do que vao girar os motores de passo

int encoder(); //chamando a funcao encoder

void setup() {
}

void loop(){  
}


void velocidade(){
  int velocidadeI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    velocidadeI = velocidadeI + encoder();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set velocidade");
    lcd.setCursor(0, 1);
    lcd.print("(cm/min)");
    lcd.setCursor(10,10);
    lcd.print(velocidadeI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      velocidadeDeFuncionamento = velocidadeI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}
