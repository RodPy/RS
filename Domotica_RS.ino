// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

//Modificado por RS Tech para usos demostrativos. 

/************************** Configuration ***********************************/

// Configuraci�n de los usuarios y contrase�as en config.h
#include "config.h"

/************************ Pines del NodeMCU *******************************/

// Pines del NodeMCU
#define rele1 16 // PIN DEL RELE CONECTAR EN D1


/************************ Configuraci�n del Feed de Adafruit *******************************/

AdafruitIO_Feed *digital1 = io.feed("voz"); 				


/************************ SETUP******************************/

void setup() {
  
  pinMode(rele1, OUTPUT);
  
  // start the serial connection
  Serial.begin(115200);
  
// Validador de conexi�n con Adafruit IO
 while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Variable de recepci�n
  digital1->onMessage(handleMessage);
 
  // Conexi�n 
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital1->get();
 
}

/************************ Programa Principal*******************************/

void loop() {


  io.run();

}

/********************** Programa de Recepci�n *****************************/


/* Funci�n para la recepci�n desde Adafruit 
La "PALABRA" clave se configura en IFTTT como las variables de retorno del dispositivo, 
En el caso actual usamos como variables de respuesta :
- ON1   :  para encender el Rel�.
- OFF1 :  para apagar el Rel�.
 
*/
 void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  String  sms= data->toString();
  
  if (sms == "ON1"){
    digitalWrite(rele1, HIGH);
    Serial.println("Enciendo Dispositivo");
  }
  if (sms == "OFF1"){
    digitalWrite(rele1, LOW);
	Serial.println("Apagando Dispositivo");
  }


  
 }