#include <IRremote.hpp>

const int motor_1 = 2,
          motor_2 = 5,
          motor_3 = 3,
          motor_4 = 4;

const int sensor_ir = 8;
const int PINO_SENSOR_S0 = 8;
const int PINO_SENSOR_S1 = 9;
const int PINO_SENSOR_S2 = 11;
const int PINO_SENSOR_S3 = 12;
const int PINO_SENSOR_OUT = 10;

const int PINO_LED_VERMELHO = 2;
const int PINO_LED_VERDE = 3;
const int PINO_LED_AZUL = 4;

int valor = 1;
int vermelho = 0;
int verde = 0;
int azul = 0;

void setup() {
    pinMode(motor_1, OUTPUT);
    pinMode(motor_2, OUTPUT);
    pinMode(motor_3, OUTPUT);
    pinMode(motor_4, OUTPUT);

    pinMode(sensor_ir, INPUT);

    pinMode(PINO_SENSOR_S0, OUTPUT);
    pinMode(PINO_SENSOR_S1, OUTPUT);
    pinMode(PINO_SENSOR_S2, OUTPUT);
    pinMode(PINO_SENSOR_S3, OUTPUT);
    pinMode(PINO_SENSOR_OUT, INPUT);

    pinMode(PINO_LED_VERMELHO, OUTPUT);
    pinMode(PINO_LED_VERDE, OUTPUT);
    pinMode(PINO_LED_AZUL, OUTPUT);

    digitalWrite(PINO_SENSOR_S0, HIGH);
    digitalWrite(PINO_SENSOR_S1, LOW);
}

void pratileira_palet() {
    valor = 1;

    while (valor) {
        if (IrReceiver.decode()) {
            IrReceiver.resume();

            switch (IrReceiver.decodedIRData.decodedRawData) {
                case 4010852096:
                    Serial.println("palet 1");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                case 3994140416:
                    Serial.println("palet 2");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                case 3977428736:
                    Serial.println("palet 3");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                case 3944005376:
                    Serial.println("palet 4");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                case 3927293696:
                    Serial.println("palet 5");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                case 3910582016:
                    Serial.println("palet 6");
                    // Logica para ir até a linha do palet
                    andar_palet();
                    break;

                default:
                    Serial.println("Nenhum palet selecionado");
                    break;
            }
        }
    }
}

void andar_palet() {
    valor = 1;

    while (valor) {
        if (IrReceiver.decode()) {
            IrReceiver.resume();

            switch (IrReceiver.decodedIRData.decodedRawData) {
                case 4111122176:
                    Serial.println("palet de cima");
                    // Logica para pegar o palet
                    valor = 0;
                    break;

                case 4144545536:
                    Serial.println("palet de baixo");
                    // Logica para pegar o palet
                    valor = 0;
                    break;

                default:
                    Serial.println("Nenhum andar selecionado");
                    break;
            }
        }
    }
}

void leitura_cores() {
    digitalWrite(PINO_SENSOR_S2, LOW);
    digitalWrite(PINO_SENSOR_S3, LOW);
    if (digitalRead(PINO_SENSOR_OUT) == HIGH) {
        vermelho = pulseIn(PINO_SENSOR_OUT, LOW);
    } else {
        vermelho = pulseIn(PINO_SENSOR_OUT, HIGH);
    }
    digitalWrite(PINO_SENSOR_S3, HIGH);

    if (digitalRead(PINO_SENSOR_OUT) == HIGH) {
        azul = pulseIn(PINO_SENSOR_OUT, LOW);
    } else {
        azul = pulseIn(PINO_SENSOR_OUT, HIGH);
    }
    digitalWrite(PINO_SENSOR_S2, HIGH);

    if (digitalRead(PINO_SENSOR_OUT) == HIGH) {
        verde = pulseIn(PINO_SENSOR_OUT, LOW);
    } else {
        verde = pulseIn(PINO_SENSOR_OUT, HIGH);
    }
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.resume();

        switch (IrReceiver.decodedIRData.decodedRawData) {
            case 4010852096:
                Serial.println("Linha 1");
                // Logica de ir até a linha
                pratileira_palet();
                break;

            case 3994140416:
                Serial.println("Linha 2");
                // Logica de ir até a linha
                pratileira_palet();
                break;

            case 3977428736:
                Serial.println("Linha 3");
                // Logica de ir até a linha
                pratileira_palet();
                break;

            default:
                Serial.println("Linha não selecionado");
                Serial.println(IrReceiver.decodedIRData.decodedRawData);
                break;
        }
    }

    leitura_cores(); // Chama a rotina que le as cores

    // Verifica qual cor foi detectada
    if (vermelho < azul && vermelho < verde) {
        digitalWrite(PINO_LED_VERMELHO, HIGH); // Vermelho em nivel alto
        digitalWrite(PINO_LED_VERDE, LOW);     // Verde em nivel baixo
        digitalWrite(PINO_LED_AZUL, LOW);      // Azul em nivel baixo
    } else if (azul < vermelho && azul < verde) {
        digitalWrite(PINO_LED_VERMELHO, LOW);  // Vermelho em nivel baixo
        digitalWrite(PINO_LED_VERDE, LOW);     // Verde em nivel baixo
        digitalWrite(PINO_LED_AZUL, HIGH);     // Azul em nivel alto
    } else if (verde < vermelho && verde < azul) {
        digitalWrite(PINO_LED_VERMELHO, LOW);  // Vermelho em nivel baixo
        digitalWrite(PINO_LED_VERDE, HIGH);    // Verde em nivel alto
        digitalWrite(PINO_LED_AZUL, LOW);      // Azul em nivel baixo
    }

    delay(100); // Aguarda 100 milissegundos
}
