//Stepper Board Code
//Adaptado do original de Kevin Darrah  2017
//https://www.youtube.com/user/kdarrah1234


const int stepPin = 2;
const int dirPin = 3;
const int actPin = 4;//not used
const float motorAngle = 1.8; //já esta configurado para o nosso motor
const float stepSize = 0.03125;//full=1, half=0.5, quarter=0.25, etc...


void stepperRotate(float rotation, float rpm);

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  stepperRotate(1, 200);// Chamada da funcao
  //primeira informacao quantidade de rotacoes e direcao(se negativo anti-horario)
  //segunga informacao velocidade em RPM
}

void stepperRotate(float rotation, float rpm) {
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

  for (unsigned long i = 0; i < totalSteps; i++) {
    PORTD = PORTD | (1 << stepPin); //Se precisar usar pinos acima do 7 precisa mudar para PORTB
    delayMicroseconds(stepPeriodmicroSec);
    PORTD = PORTD & ~(1 << stepPin);
    delayMicroseconds(stepPeriodmicroSec);
  }

}
