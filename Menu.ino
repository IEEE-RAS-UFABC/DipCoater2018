/*IDENTAR TODO CODIGO, ORGANIZAR VARIAVEIS, NOMEA-LAS CORRETAMENTE E FAZER CABEÇALHO EXPLICANDO OQ FAZ O CODIGO*/

// include the library code:
#include <LiquidCrystal.h>

char* menu [] = {"Start Padrao", "Menu"};
char* optionSubMenu [] = {"Start", "Velocidade", "Ciclos", "Altura", "Tempo", "Padrao", "Voltar"};
char* padroes [] = {"Padrão 1",  "Padrão 2", "Padrão 3"};
char* beckers [] = {"Becker 1",  "Becker 2", "Becker 3" , "Becker 4"};
int variavel [] = {1, 2, 3, 4, 5,6,7};
int opt;

String readOption = "Start Padrao";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);
int linha = 0, option =1;

//adaptado para ler do teclado, substituir por botões
char tecla_pressionada = ' ';
bool voltar;

void setup() {
  // set up the LCD's number of columns and rows:
   Serial.begin(9600);
  lcd.begin(16, 3);
  
}

void loop(){
    	
 	lcd.setCursor(0,linha);
    lcd.print(">");                        //teste da flag sub_menu
    lcd.setCursor(1,0);
    lcd.print(menu[0]);
    lcd.setCursor(1,1);
    lcd.print(menu[1]);
      
  if(Serial.available()){
      tecla_pressionada = Serial.read();
      
      if(tecla_pressionada == '5'){ 	//tecla "ENTER"
                  
          if(readOption.equals(menu[0])){	//se cursor estiver na opcao Start programa começa
          
          	Serial.println("Programa começou");
            delay(3000);
            lcd.clear();
            delay(300);
            tecla_pressionada = ' ';
        }
         if(readOption.equals(menu[1])){	//se cursor estiver na opcao MENU entra na funcao com submenus
          
          	Serial.println("Submenu");
            voltar = false;        
            Submenu(voltar);
            lcd.clear();
            delay(300);
            tecla_pressionada = ' ';
        }
        
      }
      else{  
        lcd.clear();
        tecla_pressionada = ' ';
        
        if(linha <1){ //Faz cursor alterar entre linha 1 e linha 2
          linha++;
        }
        else {linha =0;}
        
        //atribui a opcao escolhida à linha que esta o cursor
        readOption = menu[linha];
      }
    }
}

void Submenu(bool voltar){
  
  //melhorar esse trecho, pois repete Star e velocidade 2x
   lcd.clear();
   delay(50);
   lcd.setCursor(0,0);
   lcd.print(">");                        
   lcd.setCursor(1, 0);
   lcd.print("Start");
   lcd.setCursor(1, 1);
   lcd.print("Velocidade");
  
  while(!voltar){		//enquanto voltar for falso fica lendo cursor das opcoes
    
    if(Serial.available()){
      tecla_pressionada = Serial.read();
       
      Serial.print("tecla: ");
      Serial.println(tecla_pressionada);
      delay(10);
      
      //Faz as opções do cursos "andar"
      if(tecla_pressionada == '2'){
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

          if(option <= 5){           
           option++;             
          }
          
          else option =0;
      }

      //verifica em qual opcao setada no cursor (primeira linha) e entra na função
      else if(tecla_pressionada == '5'){ 
        
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
          funcTempo();
          delay(50);
          break;

          case 6:
          funcPadrao();
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
        if(variavel.equals(optionSubMenu[option])){		//melhorar a saida do menu... 
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
}

void funcStart(){
  Serial.print("Inicia a função START");
  //código para inicializar
}
void funcVelocidade(){
  Serial.print("Inicia a função VELOCIDADE");
  //código para ajuste de velocidade de subida
}
void funcCiclos(){
  Serial.print("Inicia a função CICLOS");
  //código para ajuste de ciclos (quantos beckeres vai estar na mesa?)
}
void funcAltura(){
  Serial.print("Inicia a função ALTURA");
  //código para ajusta de altura de subida e mergulho na solução
}
void funcTempo(){
  Serial.print("Inicia a função TEMPO");
  //código para setar o tempo de exposição em cada solução
}
void funcPadrao(){
  Serial.print("Inicia a função PADRAO");
  //código para setar os diferentes tipos de padrões pre configurados (3 padrões)
}