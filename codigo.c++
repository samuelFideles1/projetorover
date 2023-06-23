//codigo

#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 

#define L_S A0 //ir sensor Left
#define R_S A1 //ir sensor Right

#define echo 3    //Echo pin
#define trigger 2 //Trigger pin

#define servo 11

int Set=15;
int distance_L, distance_F, distance_R; 
void setup(){ // configuração aqui, para executar uma vez

Serial.begin(9600); // iniciar a comunicação serial em 9600bps

pinMode(R_S, INPUT); // declarar if sensor como entrada  
pinMode(L_S, INPUT); // declarar se sensor como entrada

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
analogWrite(enA, 30); // Escreva o ciclo de trabalho 0 a 255 Ative o pino A para a velocidade do motor1 
analogWrite(enB, 30); // Escreva o ciclo de trabalho 0 a 255 Ative o pino B para a velocidade do motor2 

pinMode(servo, OUTPUT);
void setup(){ // configuração aqui, para executar uma vez

Serial.begin(9600); // iniciar a comunicação serial em 9600bps

pinMode(R_S, INPUT); // declarar if sensor como entrada  
pinMode(L_S, INPUT); // declarar se sensor como entrada

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
analogWrite(enA, 30); // Escreva o ciclo de trabalho 0 a 255 Ative o pino A para a velocidade do motor1 
analogWrite(enB, 30); // Escreva o ciclo de trabalho 0 a 255 Ative o pino B para a velocidade do motor2 

pinMode(servo, OUTPUT);
for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
 for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }

 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }

distance_F = Ultrasonic_read();

delay(500);
}
void loop(){  
// Seguidor de Linha e Evitar Obstáculos

distance_F = Ultrasonic_read();
Serial.print("D F=");Serial.println(distance_F);

//se o sensor direito e o sensor esquerdo estiverem na cor branca, ele chamará a função forword//
 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){
  if(distance_F > Set){forword();}
    else{Check_side();}  
 } 
 
 //se o sensor direito for preto e o sensor esquerdo for branco, ele chamará a função virar à direita
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnRight();}  

//se o sensor direito for branco e o sensor esquerdo for preto, ele chamará a função virar à esquerda//

else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnLeft();} 
    
delay(10);
}
void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;      // Converter ângulo em microssegundos
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); // Ciclo de atualização do servo
}

//**********************leitura ultrassônica****************************
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
 if(distance_L > distance_R){
 turnLeft();
 delay(500);
 forword();
 delay(600);
 turnRight();
 delay(500);
 forword();
 delay(600);
 turnRight();
 delay(400);
 }
 
else{
 turnRight();
 delay(500);
 forword();
 delay(600);
 turnLeft();
 delay(500);
 forword();
 delay(600); 
 turnLeft();
 delay(400);
 }
} 

void Check_side(){
    Stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
   // compareDistance();
}
void forword(){  //forword
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
void backword(){ //backword
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}

void turnRight(){ //Vire à direita
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}

void turnLeft(){ //Vire à esquerda
digitalWrite(in1, HIGH); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
void Stop(){ //parar
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
