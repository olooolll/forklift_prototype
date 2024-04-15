#include <IRremote.hpp>

// Motores
int motor_1 = 2,
    motor_2 = 5,
    motor_3 = 3,
    motor_4 = 4;

// Sensor IR
int sensor_ir = 8;

// Valor TRUE
int valor = 1;

void setup() {  
    pinMode(motor_1, OUTPUT);
    pinMode(motor_2, OUTPUT);
    pinMode(motor_3, OUTPUT);
    pinMode(motor_4, OUTPUT);
  
    IrReceiver.begin(sensor_ir, ENABLE_LED_FEEDBACK); // Começa a receber
  
    Serial.begin(9600);
}

void andar_palet(){
    
    valor = 1;

    while (valor){

        if (IrReceiver.decode()) {
            IrReceiver.resume();

            switch(IrReceiver.decodedIRData.decodedRawData){
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
                    Serial.println("Nem um andar selecionado");
                    break;  
            }
	
        }

    }
}

void pratileira_palet(){
    
    valor = 1;

    while(valor){
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
                    Serial.println("Nem um palet selecionado");
                    break;
            }
        } 
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
                Serial.println("Linha não seleceionado");
          		Serial.println(IrReceiver.decodedIRData.decodedRawData);	
          	
    			break;
          	
        }
        
    }
}
