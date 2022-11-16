#include <Servo.h>
int X;				
int Y;				
int PULSADOR = 9;	
int SW;			
int motorIzq=11;
int motorDer=10;

char opcion;
Servo motoIzq;
Servo motoDer;
void setup(){
    pinMode(motorIzq, OUTPUT);
    pinMode(motorDer, OUTPUT);
    pinMode(PULSADOR, INPUT);	
    motoIzq.attach(motorIzq);
    motoDer.attach(motorDer);
    Serial.begin(9600);
}
void loop(){
  X = analogRead(A0);			// lectura de valor de eje x
  Y = analogRead(A1);			// lectura de valor de eje x
  SW = digitalRead(PULSADOR);
  if(X > 430 && X < 570){
    if (Y > 520 && Y <= 1023){	
      Serial.println("Mapeo y arriba: ");			// si Y esta en la zona de arriba
      controlMotorIzq(map(Y, 0, 480, -255 , 0));	
      controlMotorDer(map(Y, 0, 480, -255 , 0));
    }  
    if (Y >= 0 && Y < 480){					// si Y esta en la zona de abajo
      Serial.println("Mapeo y abajo: ");
      controlMotorIzq(map(Y, 520, 1023, 0 , 255));
      controlMotorDer(map(Y, 520, 1023, 0 , 255));
    } 
  }

  if(Y > 430 && Y < 570){
    if (X >= 0 && X < 430){					// si X esta en la zona izquierda
      Serial.println("Mapeo x izquierda: ");
      controlMotorIzq(map(X, 520, 1023, 0 , 255));
      controlMotorDer(map(X, 520, 1023, 0 , -255));


    } 
    if (X > 570 && X <= 1023){					// si X esta en la zona derecha
      Serial.println("Mapeo x derecha: ");
      controlMotorIzq(map(X, 0, 480, -255 , 0));	
      controlMotorDer(map(X, 0, 480, 255 , 0));
    } 
  }
  
  
  if ((Y >  500 && Y <= 520) && (X >  500 && X <= 520)){	
    Serial.println("Mapeo muerta  ");			// si Y esta en la zmuerta
    controlMotorIzq(0);	
    controlMotorDer(0);
  } 
  //PLANO       X      Y
  //ADELANTE = 510    1023
  //ATRAS    = 510    0
  //IZQUIERDA=  0     510
  //DERECHA  = 1023   510
  //CENTRO   = 510    510
  //Si esta en el rango x:430-570, solo va adelante o atras

}

int controlMotorIzq(int value){
  motoIzq.write(map(value,-255,255,2000,1000));
}
int controlMotorDer(int value){
  motoDer.write(map(value,-255,255,1000,2000));
}

