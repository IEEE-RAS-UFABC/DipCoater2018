/*IDENTAR TODO CODIGO, ORGANIZAR VARIAVEIS, NOMEA-LAS CORRETAMENTE E FAZER CABEÇALHO EXPLICANDO OQ FAZ O CODIGO*/

// include the library code:
#include <LiquidCrystal.h>

//dados iniciais para stepper
const int stepPinTopo = 10; //vaai ter que alterar os pinos e parte do codigo para usar pino maior que 7
const int stepPinBase = 11;
const int dirPin = 12;
const float motorAngle = 1.8; //já esta configurado para o nosso motor
const float stepSize = 0.03125;//full=1, half=0.5, quarter=0.25, etc...

//dados iniciais para menu
char* menu [] = {"Start Padrao", "Menu"};
char* optionSubMenu [] = {"Start", "Velocidade", "Ciclos", "Altura", "Tempo banho", "Tempo Secagem", "Voltar"};
char* padroes [] = {"Padrão 1",  "Padrão 2", "Padrão 3"};
char* beckers [] = {"Becker 1",  "Becker 2", "Becker 3" , "Becker 4"};
int variavel [] = {1, 2, 3, 4, 5,6,7};
int opt;
String readOption = "Start Padrao";

//dados iniciais para "start"
int   velocidadeDeFuncionamento = 20; //iniciando variaveis de Funcionamento em valores seguros
int   tempoDeBanhoDeFuncionamento = 2;
int   tempoDeSecagemDeFuncionamento = 2;
int   ciclosDeFuncionamento = 2;
int   alturaDeFuncionamento = 5;
int   banhosDeFuncionamento = 1;

//dados iniciais para encoder
int semovido = 0;
const int encoderPino1 = 30; //pinos usados pelo encoder
const int encoderPino2 = 31;

//dados iniciais botões
const int botaoSelecionar = 34;
const int botaoVoltar = 35;
const int fimDeCurcoTopo = 38;
const int fimDeCurcoBase = 39;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int linha = 0, option =1;

//adaptado para ler do teclado, substituir por botões
char tecla_pressionada = ' ';
bool voltar;

//Declaracoes das funcoes
void stepperRotate(float rotation, float rpm, bool motor); // se mototor = HIGH motor do topo se FALSE motor da base
int encoder(); //quando chamado te devolve se ouve rotação pra esquerda(-1) ou pra direita(1) ou 0
void funcVelocidade();
void funcCiclos();
void funcAltura();

void setup() {
  //pinos do steper
  pinMode(stepPinTopo, OUTPUT);
  pinMode(stepPinBase, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //pinos dos botoes
  pinMode(botaoSelecionar, INPUT);
  pinMode(botaoVoltar, INPUT);
  
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 3);

  //pinos encoder
  pinMode(encoderPino1, INPUT);
  pinMode(encoderPino2, INPUT);
  Serial.println("sim to ligado");
}

void loop(){
      
  lcd.setCursor(0,linha);
    lcd.print(">");                        //teste da flag sub_menu
    lcd.setCursor(1,0);
    lcd.print(menu[0]);
    lcd.setCursor(1,1);
    lcd.print(menu[1]);
      
      if(digitalRead(botaoSelecionar) == HIGH){   //tecla "ENTER"
                  
          if(readOption.equals(menu[0])){ //se cursor estiver na opcao Start programa começa
          
            Serial.println("Programa começou");
            delay(3000);
            lcd.clear();
            funcStart();
            delay(50);
            tecla_pressionada = ' ';
        }
         if(readOption.equals(menu[1])){  //se cursor estiver na opcao MENU entra na funcao com submenus
          
            Serial.println("Submenu");
            voltar = false;        
            Submenu(voltar);
            lcd.clear();
            delay(300);
            tecla_pressionada = ' ';
        }
        
      }
  semovido = encoder();
  if(semovido != 0){
    Serial.println("moveu");
    Serial.println(semovido);
     linha = linha + semovido;
     semovido=0;
     lcd.clear();
    if(linha>1){
      linha = 0;
    }
    if(linha<0){
      linha = 1;
    }
  }
        
  //atribui a opcao escolhida à linha que esta o cursor
  readOption = menu[linha];
      
    
}

void Submenu(bool voltar){
  
  //melhorar esse trecho, pois repete Star e velocidade 2x
   lcd.clear();
   delay(50);
   lcd.setCursor(0,0);
   lcd.print(">");                        
   lcd.setCursor(1, 0);
   lcd.print(optionSubMenu[option]);
   lcd.setCursor(1, 1);
   lcd.print(optionSubMenu[option + 1]);
  
  while(!voltar){   //enquanto voltar for falso fica lendo cursor das opcoes
      //Faz as opções do cursos "andar"
      semovido = encoder();
      if(semovido != 0){
        option = option + semovido;
        if(option > 5){           
          option = 0;            
        }        
        if(option < 1){
          option = 5;
        }
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(">");     

        lcd.setCursor(1, 0);        
        lcd.print(optionSubMenu[option]);
        Serial.print("Linha 0: ");
        Serial.println(optionSubMenu[option]);

        lcd.setCursor(1, 1);
        lcd.print(optionSubMenu[option+1]);
        Serial.print("Linha 1: ");
        Serial.println(option);

        //verifica qual opção escolhida na primeira linha do menu
         opt = variavel[option];     
      }

      //verifica em qual opcao setada no cursor (primeira linha) e entra na função
      else if(digitalRead(botaoSelecionar) == HIGH){ 
        
        switch (opt) {

          case 1:
          funcStart();
          delay(50);
          break;

          case 2:
          funcVelocidade();
          delay(50);
          break;

          case 3:
          funcCiclos();
          delay(50);
          break;

          case 4:
          funcAltura();
          delay(50);
          break;

          case 5:
          funcTempoDeBanho();
          delay(50);
          break;

          case 6:
          funcTempoDeSecagem();
          delay(50);
          break;

          case 7:
          voltar = true;
          delay(50);
          break;

        default:
          Serial.println("Opcao invalida");
      }
        /*
         Serial.println(optionSubMenu[option]);        
        if(variavel.equals(optionSubMenu[option])){   //melhorar a saida do menu... 
          Serial.print("escolha submenu: ");
          Serial.println(submenu[0]);
          voltar = true;
          Serial.print("SAIU: ");
          Serial.println(voltar);
        }
        */
      }
      
      else Serial.println("NONE");
            
     
  }
}

void funcStart(){
  while(digitalRead(fimDeCurcoTopo) == LOW){
    stepperRotate(-0.07, 30, HIGH); //anti horario sobe
  }
  while(digitalRead(fimDeCurcoBase) == LOW){
    stepperRotate(-0.07, 60, LOW);
  }
  for(int cicloAtual; cicloAtual < ciclosDeFuncionamento; cicloAtual++){ 
    for(int banhoAtual; banhoAtual < banhosDeFuncionamento; banhoAtual++){
      stepperRotate((alturaDeFuncionamento/2), velocidadeDeFuncionamento, HIGH);
      delay(tempoDeBanhoDeFuncionamento);
      while(digitalRead(fimDeCurcoTopo) == LOW){
        stepperRotate(-0.07, velocidadeDeFuncionamento, HIGH);
      }
      delay(tempoDeSecagemDeFuncionamento);
      stepperRotate((5/4), 60, LOW);   
    }
    while(digitalRead(fimDeCurcoBase) == LOW){
        stepperRotate(-0.07, 60, LOW);
      }
  }

}
void funcVelocidade(){
  int velocidadeI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    velocidadeI = velocidadeI + encoder();
    if(velocidadeI>300){
      velocidadeI = 300;
    }
    if(velocidadeI<1){
      velocidadeI = 1;
    };
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set velocidade");
    lcd.setCursor(0, 1);
    lcd.print("(cm/min)");
    lcd.setCursor(10,1);
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
void funcCiclos(){
  int ciclosI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    ciclosI = ciclosI + encoder();
    if(ciclosI<1){
      ciclosI = 1;
    }
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
void funcAltura(){
  int alturaI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    alturaI = alturaI + encoder();
    if(alturaI>240){
      alturaI = 240;
    }
    if(alturaI<1){
      alturaI = 1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Set altura");
    lcd.setCursor(0, 1);
    lcd.print("cm");
    lcd.setCursor(8,1);
    lcd.print(alturaI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      alturaDeFuncionamento = alturaI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
}
}
void funcTempoDeBanho(){
  int tempoI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    tempoI = tempoI + encoder();
    if(tempoI<1){
      tempoI = 1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("tempo de banho");
    lcd.setCursor(0, 1);
    lcd.print(tempoI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      tempoDeBanhoDeFuncionamento = tempoI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}
void funcTempoDeSecagem(){
  int tempoI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    tempoI = tempoI + encoder();
    if(tempoI<1){
      tempoI = 1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("tempo de Secagem");
    lcd.setCursor(0, 1);
    lcd.print(tempoI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      tempoDeSecagemDeFuncionamento = tempoI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}
void funcPadrao(){
  Serial.print("Inicia a função PADRAO");
  //código para setar os diferentes tipos de padrões pre configurados (3 padrões)
}

void funcBanhos(){//seta quantidade de banhos
  int banhoI = 0;
  bool rodando = LOW;
  while(rodando == LOW){
    banhoI = banhoI + encoder();
    if(banhoI>4){
      banhoI = 1;
    }
    if(banhoI<1){
      banhoI = 4;
    }
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("quantidade de");
    lcd.setCursor(1, 1);
    lcd.print("banhos");
    lcd.setCursor(9, 1);
    lcd.print(banhoI, DEC);
    delay(200);
    if(digitalRead(botaoSelecionar)){
      rodando = HIGH;
      banhosDeFuncionamento = banhoI;
    }
    if(digitalRead(botaoVoltar)){
      rodando = HIGH;
    }
  }
}

int encoder() {
  static bool oldEstado1; //estados anteriores dos pinos do encoder
  static bool oldEstado2; //variaveis com o prefixo static tem seus dados mantidos mesmo quando a função acaba
  bool estado1; //novos estados dos pinos
  bool estado2;
  while(digitalRead(encoderPino1) == LOW && igitalRead(encoderPino2) == LOW){
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



void stepperRotate(float rotation, float rpm, bool motor) {
  if (rotation > 0) {
    digitalWrite(dirPin, HIGH); //se rotation for positivo
  }
  else {
    digitalWrite(dirPin, LOW); //se negativo
    rotation = rotation * -1;
  }

  float stepsPerRotation = (360.00 / motorAngle) / stepSize; //calculando quantos passos em uma volta

  float totalSteps = rotation * stepsPerRotation; //multiplica passos em uma volta pela quantidade de voltas desejadas
  //Serial.println(totalSteps); // debug

  unsigned long stepPeriodmicroSec = ((60.0000 / (rpm * stepsPerRotation)) * 1E6 / 2.0000) - 5; //caculando tempo de pulso para velocidade especifica

  if(motor == HIGH){
    for (unsigned long i = 0; i < totalSteps; i++) {
    PORTB = PORTB | (1 << stepPinTopo - 8); //Se precisar usar pinos acima do 7 precisa mudar para PORTB
    delayMicroseconds(stepPeriodmicroSec);
    PORTB = PORTB & ~(1 << stepPinTopo - 8);
    delayMicroseconds(stepPeriodmicroSec);
    }
  }
  else{
    for (unsigned long i = 0; i < totalSteps; i++) {
    PORTB = PORTB | (1 << (stepPinBase - 8)); //Se precisar usar pinos acima do 7 precisa mudar para PORTB abaixo de 7 PORTD
    delayMicroseconds(stepPeriodmicroSec);
    PORTB = PORTB & ~(1 << stepPinBase - 8);
    delayMicroseconds(stepPeriodmicroSec);
    }
  }
  

}
