/*IDENTAR TODO CODIGO, ORGANIZAR VARIAVEIS, NOMEA-LAS CORRETAMENTE E FAZER CABEÇALHO EXPLICANDO OQ FAZ O CODIGO*/

// include the library code:
#include <LiquidCrystal.h>
#include <Encoder.h>

//dados iniciais para stepper
const int stepPinTopo = 10; //vaai ter que alterar os pinos e parte do codigo para usar pino maior que 7
const int stepPinBase = 11;
const int dirPin = 12;
const float motorAngle = 1.8; //já esta configurado para o nosso motor
const float stepSize = 0.5;//full=1, half=0.5, quarter=0.25, etc...

//dados iniciais para menu
bool saiu;
char* menu [] = {"Start Padrao", "Menu"};
char* optionSubMenu [] = {"Start", "Ciclos", "banhos", "velocidade", "Altura", "Tempo banho", "Tempo Secagem", "padroes", "Medir Distancia", "Levantar Garra"};
char* padroes [] = {"Padrão 1",  "Padrão 2", "Padrão 3"};
char* beckers [] = {"Becker 1",  "Becker 2", "Becker 3" , "Becker 4"};
int variavel [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int opt;
String readOption = "Start Padrao";

//dados iniciais para "start"
int   alturaSeguraDeFuncionamento = 0;
int   ciclosDeFuncionamento = 0;
int   banhosDeFuncionamento = 0;
int   velocidadeDeFuncionamento [] = {0, 0, 0, 0};
int   alturaDeFuncionamento [] = {0, 0, 0, 0};
int   tempoDeBanhoDeFuncionamento [] = {0, 0, 0, 0};
int   tempoDeSecagemDeFuncionamento [] = {0, 0, 0, 0};



//dados iniciais para encoder
int semovido = 0;
Encoder myEnc(30, 31);

//dados iniciais botões
const int botaoSelecionar = 34;
const int botaoVoltar = 35;
const int fimDeCurcoTopo = 38;
const int fimDeCurcoBase = 39;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int linha = 0, option = 0;

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

  Serial.println("sim to ligado");
}

void loop() {

  lcd.setCursor(0, linha);
  lcd.print(">");                        //teste da flag sub_menu
  lcd.setCursor(1, 0);
  lcd.print(menu[0]);
  lcd.setCursor(1, 1);
  lcd.print(menu[1]);

  if (digitalRead(botaoSelecionar) == HIGH) { //tecla "ENTER"
    while (digitalRead(botaoSelecionar) == HIGH) {
    }
    if (readOption.equals(menu[0])) { //se cursor estiver na opcao Start programa começa

      Serial.println("Programa começou");
      delay(3000);
      lcd.clear();
      funcStart();
      delay(50);
      tecla_pressionada = ' ';
    }
    if (readOption.equals(menu[1])) { //se cursor estiver na opcao MENU entra na funcao com submenus

      Serial.println("Submenu");
      voltar = false;
      Submenu(voltar);
      lcd.clear();
      delay(300);
      tecla_pressionada = ' ';
    }

  }
  semovido = encoder();
  if (semovido != 0) {
    /* Serial.println("moveu");
     Serial.println(semovido);*/
    linha = linha + semovido;
    semovido = 0;
    lcd.clear();
    delay(25);
    if (linha > 1) {
      linha = 0;
    }
    if (linha < 0) {
      linha = 1;
    }
  }

  //atribui a opcao escolhida à linha que esta o cursor
  readOption = menu[linha];


}

void Submenu(bool voltar) {

  //melhorar esse trecho, pois repete Star e velocidade 2x
  lcd.clear();
  delay(50);
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print(optionSubMenu[option]);
  lcd.setCursor(1, 1);
  lcd.print(optionSubMenu[option + 1]);

  while (!voltar) { //enquanto voltar for falso fica lendo cursor das opcoes
    //Faz as opções do cursos "andar"
    semovido = encoder();
    if (semovido != 0 || saiu == HIGH) {
      saiu = LOW;
      option = option + semovido;
      if (option > 9) {
        option = 0;
      }
      if (option < 0) {
        option = 9;
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">");

      lcd.setCursor(1, 0);
      lcd.print(optionSubMenu[option]);
      Serial.print("Linha 0: ");
      Serial.println(optionSubMenu[option]);

      lcd.setCursor(1, 1);
      lcd.print(optionSubMenu[option + 1]);
      Serial.print("Linha 1: ");
      Serial.println(option);

      //verifica qual opção escolhida na primeira linha do menu

    }
    opt = variavel[option];
    //verifica em qual opcao setada no cursor (primeira linha) e entra na função
    if (digitalRead(botaoSelecionar) == HIGH) {
      while (digitalRead(botaoSelecionar) == HIGH) {
      }
      switch (opt) {

        case 1:
          funcStart();
          delay(50);
          break;

        case 2:
          funcCiclos();
          delay(50);
          break;

        case 3:
          funcBanhos();
          delay(50);
          break;

        case 4:
          funcVelocidade();
          delay(50);
          break;

        case 5:
          funcAltura();
          delay(50);
          break;

        case 6:
          funcTempoDeBanho();
          delay(50);
          break;

        case 7:
          funcTempoDeSecagem();
          delay(50);
          break;

        case 8:
          funcPadroes();
          delay(50);
          break;

        case 9:
          funcMedirDistancia();
          delay(50);
          break;

        case 10:
          funcLevantarGarra();
          delay(50);
          break;

        default:
          Serial.println("Opcao invalida");
          Serial.println(opt);
      }
    }
    if (digitalRead(botaoVoltar) == HIGH) {
      while (digitalRead(botaoVoltar) == HIGH) {
      }
      voltar = HIGH;
      lcd.clear();
      delay(25);
    }
  }
}
void funcPadroes() {
  ciclosDeFuncionamento = 10;
  banhosDeFuncionamento = 4;
  int x = 0;
  for (int i = 60; i > 25 ; i = i - 10) {
    velocidadeDeFuncionamento[x] = i;
    x++;
  }
  for (int i = 0; i < 4; i++) {
    alturaDeFuncionamento[i] = 15;
    tempoDeBanhoDeFuncionamento[i] = 5;
    tempoDeSecagemDeFuncionamento[i] = 5;
  }
}
void funcStart() {
  bool erro = LOW, erroV = LOW, erroA = LOW, erroB = LOW, erroS = LOW, pausado = LOW;
  if (ciclosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Quant de ciclos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
    erro = HIGH;
    delay(900);
  }
  if (banhosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Quant de banhos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
    erro = HIGH;
    delay(900);
  }
  for (int becker = 0; becker < banhosDeFuncionamento; becker++) {
    if (velocidadeDeFuncionamento[becker] == 0) {
      erroV = HIGH;
      Serial.println("erro velocidade");
      erro = HIGH;
    }
    if (alturaDeFuncionamento[becker] == 0) {
      erroA = HIGH;
      erro = HIGH;
    }
    if (tempoDeBanhoDeFuncionamento[becker] == 0) {
      erroB = HIGH;
      erro = HIGH;
    }
    if (tempoDeSecagemDeFuncionamento[becker] == 0) {
      erroS = HIGH;
      erro = HIGH;
    }
  }
  if (erroV == HIGH) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Velocidades");
    lcd.setCursor(0, 1);
    lcd.print("nao configuradas");
    delay(900);
  }
  if (erroA == HIGH) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Alturas");
    lcd.setCursor(0, 1);
    lcd.print("nao configuradas");
    delay(900);
  }
  if (erroB == HIGH) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Tempos de banho");
    lcd.setCursor(0, 1);
    lcd.print("nao configurados");
    delay(900);
  }
  if (erroS == HIGH) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Tempos de secagem");
    lcd.setCursor(0, 1);
    lcd.print("nao configurados");
    delay(900);
  }
  if (erro == HIGH) {
    Serial.print("Foram encontrados erros ao tentar iniciar o programa");
    saiu = HIGH;
    lcd.clear();
    delay(50);
  }
  else {
    Serial.println("programa rodando");
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Programa rodando");
    while (digitalRead(fimDeCurcoTopo) == LOW) {
      stepperRotate(-0.50, 260, HIGH); //anti horario sobe
    }
    lcd.clear();
    delay(50);
    lcd.setCursor(1, 0);
    lcd.print("Eixo vertical");
    lcd.setCursor(1, 1);
    lcd.print("calibrado");
    while (digitalRead(fimDeCurcoBase) == LOW) {
      stepperRotate(-0.50, 20, LOW);
    }
    lcd.clear();
    delay(50);
    lcd.setCursor(1, 0);
    lcd.print("Base calibrada");
    for (int cicloAtual = 0; cicloAtual < ciclosDeFuncionamento; cicloAtual++) {
      while (digitalRead(fimDeCurcoTopo) == LOW) {
        lcd.setCursor(9, 1);
        lcd.print("^");
        stepperRotate(-0.75, 260, HIGH);
        lcd.setCursor(9, 1);
        lcd.print(" ");
      }
      stepperRotate((alturaSeguraDeFuncionamento * 5), (300), HIGH);
      for (int banhoAtual = 0; banhoAtual < banhosDeFuncionamento; banhoAtual++) {
        lcd.clear();
        delay(50);
        lcd.setCursor(0, 0);
        lcd.print("Ciclo");
        lcd.setCursor(6, 0);
        lcd.print(cicloAtual + 1);
        lcd.setCursor(0, 1);
        lcd.print("banho");
        lcd.setCursor(6, 1);
        lcd.print(banhoAtual + 1);
        lcd.setCursor(9, 1);
        lcd.print("v");
        stepperRotate(((alturaDeFuncionamento[banhoAtual] * 5) - (alturaSeguraDeFuncionamento * 5)), (velocidadeDeFuncionamento[banhoAtual] * 5), HIGH);
        lcd.setCursor(9, 1);
        lcd.print(" ");
        Serial.println("esperando banho");
        for (int i = 0; i < tempoDeBanhoDeFuncionamento[banhoAtual]; i++) {
          delay(940);
          int minutos = (tempoDeBanhoDeFuncionamento[banhoAtual] - i) / 60;
          int segundos = (tempoDeBanhoDeFuncionamento[banhoAtual] - i) - (minutos * 60);
          lcd.setCursor(9, 1);
          lcd.print("       ");
          delay(50);
          lcd.print(String(minutos) + ":" + String(segundos));
        }
        Serial.println("acabou");
        stepperRotate(((alturaDeFuncionamento[banhoAtual] * -5) + (alturaSeguraDeFuncionamento * 5)), (velocidadeDeFuncionamento[banhoAtual] * 5), HIGH);
        Serial.println("esperando secagem");
        for (int j = 0; j < tempoDeSecagemDeFuncionamento[banhoAtual]; j++) {
          for (int i = 0; i < 940; i++) {
            delay(1);
            if (digitalRead(botaoSelecionar)) {
              pausado = HIGH;
              lcd.clear();
              delay(25);
              lcd.setCursor(0, 0);
              lcd.print("pausado");
              while (pausado == HIGH) {
                if (digitalRead(botaoVoltar)) {
                  lcd.clear();
                  delay(25);
                  lcd.setCursor(0, 0);
                  lcd.print("continuando...");
                  pausado = LOW;
                }
              }
            }
          }
          int minutos = (tempoDeSecagemDeFuncionamento[banhoAtual] - j) / 60;
          int segundos = (tempoDeSecagemDeFuncionamento[banhoAtual] - j) - (minutos * 60);
          lcd.setCursor(9, 1);
          lcd.print("       ");
          delay(50);
          lcd.print(String(minutos) + ":" + String(segundos));

        }
        Serial.println("acabou");
        lcd.setCursor(9, 0);
        lcd.print("->");
        stepperRotate(1.25, 20, LOW);
        lcd.setCursor(9, 0);
        lcd.print("  ");
      }
      while (digitalRead(fimDeCurcoBase) == LOW) {
        lcd.setCursor(9, 0);
        lcd.print("<-");
        stepperRotate(-0.50, 20, LOW);
        lcd.setCursor(9, 0);
        lcd.print("  ");
      }
    }
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("prog terminado");
    delay(1000);
    lcd.clear();
    delay(50);
    saiu = HIGH;
    Serial.print("Final");
  }
}
void funcVelocidade() {
  if (banhosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("quant de banhos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
    delay(1200);
  }
  else {
    int mudouuu;
    for (int becker = 0; becker < banhosDeFuncionamento; becker++) {
      int velocidadeI = velocidadeDeFuncionamento[becker];
      bool rodando = LOW;
      lcd.clear();
      delay(50);
      lcd.setCursor(0, 0);
      lcd.print("Set velocidade");
      lcd.setCursor(0, 1);
      lcd.print("Becker ");
      lcd.setCursor(7, 1);
      lcd.print(becker + 1);
      lcd.setCursor(12, 1);
      lcd.print(velocidadeI, DEC);
      delay(600);
      while (rodando == LOW) {
        mudouuu = encoder();
        if (mudouuu != 0) {
          velocidadeI = velocidadeI + mudouuu;
          if (velocidadeI > 60) {
            velocidadeI = 60;
          }
          if (velocidadeI < 1) {
            velocidadeI = 1;
          }
          lcd.clear();
          delay(50);
          lcd.setCursor(0, 0);
          lcd.print("Set velocidade");
          lcd.setCursor(0, 1);
          lcd.print("(cm/min)");
          lcd.setCursor(10, 1);
          lcd.print(velocidadeI, DEC);
        }
        if (digitalRead(botaoSelecionar)) {
          while (digitalRead(botaoSelecionar) == HIGH) {
          }
          rodando = HIGH;
          velocidadeDeFuncionamento[becker] = velocidadeI;
        }
        if (digitalRead(botaoVoltar)) {
          while (digitalRead(botaoVoltar) == HIGH) {
          }
          rodando = HIGH;
          becker = 999;
        }
      }
    }
  }
  saiu = HIGH;
}

void funcCiclos() {
  int mudouuu;
  int ciclosI = ciclosDeFuncionamento;
  bool rodando = LOW;
  lcd.clear();
  delay(25);
  lcd.setCursor(0, 0);
  lcd.print("ciclos totais");
  lcd.setCursor(0, 1);
  lcd.print(ciclosI, DEC);
  delay(600);
  while (rodando == LOW) {
    mudouuu = encoder();
    if (mudouuu != 0) {
      ciclosI = ciclosI + mudouuu;
      if (ciclosI < 1) {
        ciclosI = 1;
      }
      lcd.clear();
      delay(25);
      lcd.setCursor(0, 0);
      lcd.print("ciclos totais");
      lcd.setCursor(0, 1);
      lcd.print(ciclosI, DEC);
    }
    if (digitalRead(botaoSelecionar)) {
      while (digitalRead(botaoSelecionar) == HIGH) {
      }
      rodando = HIGH;
      ciclosDeFuncionamento = ciclosI;
    }
    if (digitalRead(botaoVoltar)) {
      while (digitalRead(botaoVoltar) == HIGH) {
      }
      rodando = HIGH;
    }
  }
  saiu = HIGH;
}
void funcAltura() {
  if (banhosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("quant de banhos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
  }
  else {
    int mudouuu;
    bool rodando = LOW;
    int becker = 0;
    int alturaSI = alturaSeguraDeFuncionamento;
    lcd.clear();
    delay(25);
    lcd.setCursor(0, 0);
    lcd.print("Set altura segura");
    lcd.setCursor(0, 1);
    lcd.print("cm");
    lcd.setCursor(8, 1);
    lcd.print(alturaSI, DEC);
    delay(600);
    while (rodando == LOW) {
      mudouuu = encoder();
      if (mudouuu != 0) {
        alturaSI = alturaSI + mudouuu;
        if (alturaSI > 18) {
          alturaSI = 18;
        }
        if (alturaSI < 0) {
          alturaSI = 0;
        }
        lcd.clear();
        delay(25);
        lcd.setCursor(0, 0);
        lcd.print("Set altura segura");
        lcd.setCursor(0, 1);
        lcd.print("cm");
        lcd.setCursor(8, 1);
        lcd.print(alturaSI, DEC);
      }
      if (digitalRead(botaoSelecionar)) {
        while (digitalRead(botaoSelecionar) == HIGH) {
        }
        rodando = HIGH;
        alturaSeguraDeFuncionamento = alturaSI;
      }
      if (digitalRead(botaoVoltar)) {
        while (digitalRead(botaoVoltar) == HIGH) {
        }
        rodando = HIGH;
        becker = 999;
      }
    }

    for (becker = 0; becker < banhosDeFuncionamento; becker++) {
      int alturaI = alturaDeFuncionamento[becker];
      rodando = LOW;
      lcd.clear();
      delay(25);
      lcd.setCursor(0, 0);
      lcd.print("Set altura");
      lcd.setCursor(0, 1);
      lcd.print("Becker ");
      lcd.setCursor(7, 1);
      lcd.print(becker + 1);
      lcd.setCursor(12, 1);
      lcd.print(alturaI, DEC);
      delay(600);
      while (rodando == LOW) {
        mudouuu = encoder();
        if (mudouuu != 0) {
          alturaI = alturaI + mudouuu;
          if (alturaI > 240) {
            alturaI = 240;
          }
          if (alturaI < 1) {
            alturaI = 1;
          }
          lcd.clear();
          delay(25);
          lcd.setCursor(0, 0);
          lcd.print("Set altura");
          lcd.setCursor(0, 1);
          lcd.print("cm");
          lcd.setCursor(8, 1);
          lcd.print(alturaI, DEC);
        }
        if (digitalRead(botaoSelecionar)) {
          while (digitalRead(botaoSelecionar) == HIGH) {
          }
          rodando = HIGH;
          alturaDeFuncionamento[becker] = alturaI;
        }
        if (digitalRead(botaoVoltar)) {
          while (digitalRead(botaoVoltar) == HIGH) {
          }
          rodando = HIGH;
          becker = 999;
        }
      }
    }
  }
  saiu = HIGH;
}
void funcTempoDeBanho() {
  if (banhosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("quant de banhos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
  }
  else {
    int mudouuu;
    for (int becker = 0; becker < banhosDeFuncionamento; becker++) {
      int tempoI = tempoDeBanhoDeFuncionamento[becker];
      bool rodando = LOW;
      lcd.clear();
      delay(25);
      lcd.setCursor(0, 0);
      lcd.print("tempo de banho");
      lcd.setCursor(12, 1);
      lcd.print(tempoI, DEC);
      lcd.setCursor(0, 1);
      lcd.print("Becker ");
      lcd.setCursor(7, 1);
      lcd.print(becker + 1);
      delay(600);
      while (rodando == LOW) {
        mudouuu = encoder();
        if (mudouuu != 0) {
          tempoI = tempoI + (mudouuu * 10);
          if (tempoI < 1) {
            tempoI = 1;
          }
          lcd.clear();
          delay(25);
          lcd.setCursor(0, 0);
          lcd.print("tempo de banho");
          lcd.setCursor(0, 1);
          lcd.print(tempoI, DEC);
          lcd.setCursor(4, 1);
          lcd.print("segundos");
        }
        if (digitalRead(botaoSelecionar)) {
          while (digitalRead(botaoSelecionar) == HIGH) {
          }
          rodando = HIGH;
          tempoDeBanhoDeFuncionamento[becker] = tempoI;
        }
        if (digitalRead(botaoVoltar)) {
          while (digitalRead(botaoVoltar) == HIGH) {
          }
          rodando = HIGH;
          becker = 999;
        }
      }
    }
  }
  saiu = HIGH;
}
void funcTempoDeSecagem() {
  if (banhosDeFuncionamento == 0) {
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("quant de banhos");
    lcd.setCursor(0, 1);
    lcd.print("nao configurada");
  }
  else {
    int mudouuu;
    for (int becker = 0; becker < banhosDeFuncionamento; becker++) {
      int tempoI = tempoDeSecagemDeFuncionamento[becker];
      bool rodando = LOW;
      lcd.clear();
      delay(25);
      lcd.setCursor(0, 0);
      lcd.print("tempo de Secagem");
      lcd.setCursor(12, 1);
      lcd.print(tempoI, DEC);
      lcd.setCursor(0, 1);
      lcd.print("Becker ");
      lcd.setCursor(7, 1);
      lcd.print(becker + 1);
      delay(600);
      while (rodando == LOW) {
        mudouuu = encoder();
        if (mudouuu != 0) {
          tempoI = tempoI + (mudouuu * 10);
          if (tempoI < 1) {
            tempoI = 1;
          }
          lcd.clear();
          delay(25);
          lcd.setCursor(0, 0);
          lcd.print("tempo de Secagem");
          lcd.setCursor(0, 1);
          lcd.print(tempoI, DEC);
        }
        if (digitalRead(botaoSelecionar)) {
          while (digitalRead(botaoSelecionar) == HIGH) {
          }
          rodando = HIGH;
          tempoDeSecagemDeFuncionamento[becker] = tempoI;
        }
        if (digitalRead(botaoVoltar)) {
          while (digitalRead(botaoVoltar) == HIGH) {
          }
          rodando = HIGH;
          becker = 999;
        }
      }
    }
  }
  saiu = HIGH;
}
void funcLevantarGarra() {
  while (digitalRead(fimDeCurcoTopo) == LOW) {
    lcd.setCursor(9, 1);
    lcd.print("^");
    stepperRotate(-0.75, 260, HIGH);
  }
  lcd.setCursor(9, 1);
  lcd.print(" ");
}
void funcMedirDistancia() {
  int mudouuu;
  int posicao = 0;
  float mover = 0;
  bool rodando = LOW;
  lcd.clear();
  delay(25);
  lcd.setCursor(0, 0);
  lcd.print("Medir distancia");
  lcd.setCursor(0, 1);
  lcd.print("Aguarde...");
  while (digitalRead(fimDeCurcoTopo) == LOW) {
    lcd.setCursor(9, 1);
    lcd.print("^");
    stepperRotate(-0.75, 260, HIGH);
  }
  lcd.setCursor(0, 1);
  lcd.print("               ");
  while (rodando == LOW) {
    mudouuu = encoder();
    if (mudouuu != 0) {
      posicao = posicao + mudouuu;
      if (posicao < 0) {
        posicao = 0;
      }
      else {
        mover = mover + (mudouuu * 5);
      }
      lcd.clear();
      delay(25);
      lcd.setCursor(0, 0);
      lcd.print("Medir distancia");
      lcd.setCursor(0, 1);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print(posicao, DEC);
      lcd.setCursor(4, 1);
      lcd.print("Cm");
    }
    if (mover > 0) {
      stepperRotate(0.5, 260, HIGH);
      mover = mover - 0.5;
    }
    if (mover < 0) {
      stepperRotate(-0.5, 260, HIGH);
      mover = mover + 0.5;
    }
    stepperRotate(-0.75, 260, HIGH);
    if (digitalRead(botaoSelecionar)) {
      while (digitalRead(botaoSelecionar) == HIGH) {
      }
      rodando = HIGH;
      while (digitalRead(fimDeCurcoTopo) == LOW) {
        lcd.setCursor(9, 1);
        lcd.print("^");
        stepperRotate(-0.75, 260, HIGH);
      }
      lcd.setCursor(9, 1);
      lcd.print(" ");
    }
    if (digitalRead(botaoVoltar)) {
      while (digitalRead(botaoVoltar) == HIGH) {
      }
      rodando = HIGH;
      while (digitalRead(fimDeCurcoTopo) == LOW) {
        lcd.setCursor(9, 1);
        lcd.print("^");
        stepperRotate(-0.75, 260, HIGH);
      }
      lcd.setCursor(9, 1);
      lcd.print(" ");
    }
  }
  saiu = HIGH;
}

void funcBanhos() { //seta quantidade de banhos
  int mudouuu;
  int banhoI = banhosDeFuncionamento;
  bool rodando = LOW;
  lcd.clear();
  delay(25);
  lcd.setCursor(1, 0);
  lcd.print("quantidade de");
  lcd.setCursor(1, 1);
  lcd.print("banhos");
  lcd.setCursor(9, 1);
  lcd.print(banhoI, DEC);
  delay(600);
  while (rodando == LOW) {
    mudouuu = encoder();
    if (mudouuu != 0) {
      banhoI = banhoI + mudouuu;
      if (banhoI > 4) {
        banhoI = 1;
      }
      if (banhoI < 1) {
        banhoI = 4;
      }
      lcd.clear();
      delay(25);
      lcd.setCursor(1, 0);
      lcd.print("quantidade de");
      lcd.setCursor(1, 1);
      lcd.print("banhos");
      lcd.setCursor(9, 1);
      lcd.print(banhoI, DEC);
    }
    if (digitalRead(botaoSelecionar)) {
      while (digitalRead(botaoSelecionar) == HIGH) {
      }
      rodando = HIGH;
      banhosDeFuncionamento = banhoI;
    }
    if (digitalRead(botaoVoltar)) {
      while (digitalRead(botaoVoltar) == HIGH) {
      }
      rodando = HIGH;
    }
  }
  saiu = HIGH;
}

int encoder() {
  long newPosition = myEnc.read();
  static long oldPosition;
  if (newPosition == oldPosition + 4) {
    oldPosition = newPosition;
    return 1;
  }
  if (newPosition == oldPosition - 4) {
    oldPosition = newPosition;
    return -1;
  }
  return 0;
}



void stepperRotate(float rotation, float rpm, bool motor) {
  if (rotation > 0) {
    digitalWrite(dirPin, HIGH); //se rotation for positivo
  }
  else {
    digitalWrite(dirPin, LOW); //se negativo
    rotation = rotation * -1;
  }
  delay(50);

  float stepsPerRotation = (360.00 / motorAngle) / stepSize; //calculando quantos passos em uma volta

  float totalSteps = rotation * stepsPerRotation; //multiplica passos em uma volta pela quantidade de voltas desejadas
  //Serial.println(totalSteps); // debug

  unsigned long stepPeriodmicroSec = ((60.0000 / (rpm * stepsPerRotation)) * 1E6 / 2.0000) - 5; //caculando tempo de pulso para velocidade especifica

  if (motor == HIGH) {
    for (unsigned long i = 0; i < totalSteps; i++) {
      PORTB = PORTB | 0b00010000; //Se precisar usar pinos acima do 7 precisa mudar para PORTB
      delayMicroseconds(stepPeriodmicroSec);
      PORTB = PORTB & ~0b00010000;
      delayMicroseconds(stepPeriodmicroSec);
    }
  }
  else {
    for (unsigned long i = 0; i < totalSteps; i++) {
      PORTB = PORTB | 0b00100000; //Se precisar usar pinos acima do 7 precisa mudar para PORTB abaixo de 7 PORTD
      delayMicroseconds(stepPeriodmicroSec);
      PORTB = PORTB & ~0b00100000;
      delayMicroseconds(stepPeriodmicroSec);
    }
  }
}
