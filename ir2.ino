#include <IRremote.h>
#define irin 9
#define irout 6
#define trigger 7
#define lockbtn 5

IRrecv receiver(irin);
IRsend sender(irout);

uint32_t data,adress,command;
uint8_t len = 32;
bool locked = false;
String protocol;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger,INPUT);
  IrReceiver.begin(irin,ENABLE_LED_FEEDBACK);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    if(IrReceiver.decodedIRData.decodedRawData!=0){
      if (locked == false){
          data = IrReceiver.decodedIRData.decodedRawData;
          adress = IrReceiver.decodedIRData.address;
          command = IrReceiver.decodedIRData.command;
          protocol = IrReceiver.getProtocolString();
      }

    }
     Serial.println(protocol);
     Serial.println(data,HEX);
     Serial.println(adress);
     Serial.println(command);

     // sender.sendNEC(data,32);
      IrReceiver.resume(); // Enable receiving of the next value
  }

  if(digitalRead(trigger)==HIGH){
    
      if (protocol == "NEC"){
        sender.sendNEC(adress,command,0);
      }
      else if (protocol == "Denon"){
        sender.sendDenon(adress,command,0);
      }
      else if (protocol == "Samsung"){
        sender.sendSamsung(adress,command,0);
      }
      else if (protocol == "Sharp"){
        sender.sendSharp(adress,command,0);
      }
      else if (protocol == "LG"){
        sender.sendLG(adress,command,0);
      }
      else if (protocol == "LG2"){
        sender.sendLG2(adress,command,0);
      }
      else if (protocol == "Panasonic"){
        sender.sendPanasonic(adress,command,0);
      }
      else if (protocol == "SamsungLG"){
        sender.sendSamsungLG(adress,command,0);
      }
      else if (protocol == "Onkyo"){
        sender.sendOnkyo(adress,command,0);
      }
      
    //sender.sendNEC(0x60,data);
    delay(900);

  }

  if(digitalRead(lockbtn)==HIGH){
    locked = true;
    delay(900);
  }
}


/*
        switch (protocol) {
     default:
     case UNKNOWN:
         return (F("UNKNOWN"));
         break;
     case PULSE_DISTANCE:
         return (F("PulseDistance"));
         break;


     case JVC:
         return (F("JVC"));
         break;
  



     case KASEIKYO:
         return (F("Kaseikyo"));
         break;
     case KASEIKYO_DENON:
         return (F("Kaseikyo_Denon"));
         break;
     case KASEIKYO_SHARP:
         return (F("Kaseikyo_Sharp"));
         break;
     case KASEIKYO_JVC:
         return (F("Kaseikyo_JVC"));
         break;
     case KASEIKYO_MITSUBISHI:
         return (F("Kaseikyo_Mitsubishi"));
         break;
     case RC5:
         return (F("RC5"));
         break;
     case RC6:
         return (F("RC6"));
         break;


     case SONY:
         return (F("Sony"));
         break;

     case APPLE:
         return (F("Apple"));
         break;
*/