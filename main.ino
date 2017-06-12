/* EA076 - Projeto 3: Robô com detector de obstáculo

    Isabella Bigatto    138537
    Júlia Dias          156019

    Objetivo: implementar um robô autônomo que detecta obstáculos através de um sensor infravermelho
    e controla a velocidade das rodas via PWM.

*/

#include <stdio.h>
#include <TimerOne.h>

//Atribuição das portas do Arduino às variáveis utilizadas para o controle do carrinho

#define receptor A0
#define velocidadeA 3
#define motorA_hor 5
#define motorA_anti 6
#define motorB_hor 11
#define motorB_anti 10
#define velocidadeB 9

int sensor, contador = 0, flag = 0;

/* Inicialização da interrupção de tempo, da porta serial e definição dos pinos como entrada ou saída */

void setup() {
  pinMode(receptor, INPUT);
  pinMode(motorA_hor, INPUT);
  pinMode(motorA_anti, INPUT);
  pinMode(motorB_hor, INPUT);
  pinMode(motorB_anti, INPUT);
  pinMode(velocidadeA, INPUT);
  pinMode(velocidadeB, INPUT);
  Timer1.initialize(500000);                 //Interrupção a cada 0,5s
  Timer1.attachInterrupt(tempo);
  Serial.begin(9600);
}

/* Função atribuída à interrupção */

void tempo() {
  sensor = analogRead(A0); // Leitura dos valores do sensor
  if (flag == 1) {         // Contagem de tempo usada quando o robô encontra um obstáculo para fazer a manobra de desvio
    contador++;
  }
}

void loop() {

  /* Bloco que faz o robô andar para frente */
  
  if (sensor > 650) {
    analogWrite(velocidadeA, 200);
    analogWrite(velocidadeB, 255);
    digitalWrite(motorA_hor, HIGH);
    digitalWrite(motorA_anti, LOW);
    digitalWrite(motorB_anti, HIGH);
    digitalWrite(motorB_hor, LOW);
  }

  /* Quando um obstáculo é detectado */

  if ((sensor <= 650)) {

    // os dois motores param
    analogWrite(velocidadeA, 0);
    analogWrite(velocidadeB, 0);
    digitalWrite(motorA_hor, LOW);
    digitalWrite(motorB_anti, LOW);
    delay(1000);

    flag = 1;   // aciona uma flag para começar a contagem do contador, que determina por quanto tempo o robô vai dar ré

    while (contador < 10) {
      analogWrite(velocidadeA, 200);
      analogWrite(velocidadeB, 0);
      digitalWrite(motorA_anti, HIGH);
      digitalWrite(motorA_hor, LOW);
      digitalWrite(motorB_anti, HIGH);
      digitalWrite(motorB_hor, LOW);
    }
    contador = 0;
    flag = 0;
  }
}
