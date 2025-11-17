#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

#define pinGas 4
int valorGas;
unsigned long tempoAnterior = 0; 
unsigned long tempoAtual;
bool limite;

BluetoothSerial BT;

void setup() {
Serial.begin(9600);
  pinMode (pinGas, INPUT);

  if (BT.begin("dedinho")) 
  { 
    Serial.println("Bluetooth (Slave) inicializado.");
    Serial.print("Endereco BLUT:  ");
    //F4:65:0B:54:70:12
    Serial.println(BT.getBtAddressString());
  } 
  else 
  {
    Serial.println("ERRO ao inicializar Bluetooth!");
    return; // Não continua se o BT falhar
  }
}

void loop() {




  valorGas = analogRead(4); 

  tempoAtual = millis();
  if (valorGas >= 680)
  {
    limite = true;
    if (tempoAtual - tempoAnterior >=500)
  Serial.println (valorGas);
  }

  else
{
  limite = false; 
}
  


if (BT.available()) // isso é pra conferir se a biblioteca de blutout ta funcionado certinho
  {
    String mensagemRecebida = BT.readStringUntil('\n'); // lê a mensagem recebida até o caractere de nova linha /n
   
    Serial.println("Mensagem Recebida:" + mensagemRecebida); // exibe a mensagem recebida no monitor serial
  }

JsonDocument doc;

  doc["limite"] = limite;
  
  String jsonString;
  
  serializeJson(doc, jsonString);


  // Envio Bluetooth
  if (BT.available())
  {

    // String mensagemEnviar = Serial.readStringUntil('\n');
    // mensagemEnviar.trim(); // remove espaços em branco extras
    // BT.println(mensagemEnviar); // envia a mensagem via Bluetooth
    // Serial.println("Mensagem Enviada:" + mensagemEnviar);

    String mensagemEnviar = jsonString;
    
    BT.println(jsonString);

  }
  
}
