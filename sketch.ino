#define ENABLE 17
#define STEP 4
#define DIR 2

#define BOTAO_POWER 15
#define DIR_BOTAO 16

int estadoBotaoPower = 0;
int ultimoEstadoBotaoPower = 0;
int estadoDirBotao = 0;
int ultimoEstadoDirBotao = 0;

bool motorEnabled = false;
bool motorDirection = false;

void setup(){
  pinMode(ENABLE, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(BOTAO_POWER, INPUT_PULLUP);
  pinMode(DIR_BOTAO, INPUT_PULLUP);

  digitalWrite(ENABLE, HIGH);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, LOW);

  Serial.begin(9600);
  Serial.println("Motor desativado.");
}

void loop(){
  estadoBotaoPower = digitalRead(BOTAO_POWER);

  if (estadoBotaoPower == LOW && ultimoEstadoBotaoPower == HIGH){
    delay(50);
    if (digitalRead(BOTAO_POWER) == LOW){
      motorEnabled = !motorEnabled;
      digitalWrite(ENABLE, motorEnabled ? LOW : HIGH);

      Serial.print("Motor ");
      Serial.println(motorEnabled ? "ativado" : "desativado");
    }
  }

  ultimoEstadoBotaoPower = estadoBotaoPower;

  if (motorEnabled){
    estadoDirBotao = digitalRead(DIR_BOTAO);

    if (estadoDirBotao == LOW && ultimoEstadoDirBotao == HIGH){
      delay(50);
      if(digitalRead(DIR_BOTAO) == LOW){
        motorDirection = !motorDirection;
        digitalWrite(DIR, motorDirection ? HIGH : LOW);

        Serial.print("Direção do motor: ");
        Serial.println(motorDirection ? "Horário" : "Anti-horário");
      }
    }

    ultimoEstadoDirBotao = estadoDirBotao;

    digitalWrite(STEP, HIGH);
    delay(100);
    digitalWrite(STEP, LOW);
    delay(100);
  }
}