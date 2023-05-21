#include <Wire.h>//se llama la libreria Wire que nos ayudara a comunicarnos con el dispositivos de I2C
#include <LiquidCrystal_I2C.h>//se instala la libreria LiquidCrystal_I2C para trabajar con el i2c del lcd junto con el MÃ³dulo serial I2C
#include <Keypad.h>//se crea la libreria para iniciar el teclado matricial
#include <RTClib.h>//se instala y llama la libreria RTClib para poder utilizar el modulo RTC
#include <Servo.h>//se instala esta libreria para el servo motor

#define lcdAddress 0x27  //se indica la direcciÃ³n que toma el modulo i2c
#define filas 2//se indica que numero de filas que tiene el lcd que son dos para despues utilizarlo
#define columnas 16//se indica el numero de columnas que tiene el lcd que son 16 

const int pul1 = 2;
const int cau = 4;
int park;
int ser;
int lou;
int RS=10;
int ZK;

LiquidCrystal_I2C pantallalcd(lcdAddress, columnas, filas);//se llama la libreria LiquidCrystal_I2C se le indica el nombre de pantallalcd se le indica la direcciÃ³n del lcd,la variable columnas y filas

Servo dota;//SE CREA LA VARIABLE PARA EL SERVO MOTOR
Servo jota;//SE CREA OTRA  VARIABLE PARA EL SERVO MOTOR}
RTC_DS3231 THC;//crea objeto del tipo RTC_DS3231

#define Epul_1() pinMode(pul1,INPUT);
#define Epul_2() pinMode(cau,INPUT); 
#define salida() pinMode(ser,OUTPUT);

void setup() {
  Epul_1();
  Epul_2();
  salida();
  Serial.begin(9600);
 pantallalcd.init();//se indica que la pantallalcd que en eso se iniciara
 pantallalcd.backlight();//se indica que la pantallalcd para su iluminaciÃ³n
 THC.begin();//se inicializa el THC
 THC.adjust(DateTime(__DATE__, __TIME__));//funcion que permite establecer fecha y horario 
 dota.attach(3);//se indica en que pin se coloca
 jota.attach(5);//se indica en que pin se coloca
}
void loop() {
  pantallalcd.setCursor(2,0);
  pantallalcd.print("PARQUEO THC");
  pantallalcd.setCursor(0,1);
  pantallalcd.print("DIS:");
  pantallalcd.print(RS);
  pantallalcd.setCursor(9,1);
  pantallalcd.print("OCU:");
  pantallalcd.print(ZK);
  dota.write(0);
  DateTime fecha = THC.now();//funcion que devuelve fecha y horario en formato
  ser = digitalRead(pul1);
  RS==park;
  if(ser==HIGH && RS>0){
    pantallalcd.clear();
    RS--;
    ZK++;
    pantallalcd.setCursor(3,0);
    pantallalcd.print("BIENVENIDO");
    pantallalcd.setCursor(0,1);//se dise que en la columna 0 se imprima lo siguiente y que se coloque en la fila 0
    pantallalcd.print("ENTRADA:");
    pantallalcd.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.second());//funcion que obtiene los segundos de la fecha completa
    dota.write(90);//se indica los grados a moverse el servo motor
    delay(3000);
    dota.write(0);
    pantallalcd.clear();
    Serial.print("ENTRADA:");
    Serial.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.println(fecha.second());//funcion que obtiene los segundos de la fecha completa

  }else{
    if(ser==HIGH && RS==0){
     pantallalcd.clear();
     pantallalcd.setCursor(2,0);
     pantallalcd.print("LO SENTIMOS");
     pantallalcd.setCursor(1,1);
     pantallalcd.print("ESTAMOS LLENOS");
     delay(2000);
     pantallalcd.clear();
    
    }
  }
  
  lou=digitalRead(cau);
  if(lou==HIGH && RS<10){
    RS++;
    ZK--;   
    pantallalcd.clear();
    pantallalcd.setCursor(2,0);
    pantallalcd.print("FELIZ VIAJE");
    pantallalcd.setCursor(0,1);
    pantallalcd.print("SALIDA:");
    pantallalcd.print( fecha.hour());//funcion que obtiene la hora de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.second());//funcion que obtiene los segundos de la fecha completa
    jota.write(90);//se indica los grados a moverse el servo motor
    delay(3000);
    jota.write(0);
    pantallalcd.clear();
    Serial.print("SALIDA:");
    Serial.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.println(fecha.second());//funcion que obtiene los segundos de la fecha completa
  }else{}
}


