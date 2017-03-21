# zipato
ESP8266 - Library for communication with the Zipabox in Local mode API 



  Zipato  zipato("192.168.1.196:8080",<user>,<password>);
  .  
  .
  .
  .
  .    
  void printZipatoVal()  {
        if(!zipato.login( )){
            Serial.println(zipato.getErrorText());
            return;   
         }               
         
         //Serial.println(zipato.getAttribtValue(<UUID of the attribute>));
         
         Serial.println(zipato.getAttribtValue("ce2c31df-2860-4976-a3fc-39cd19ecf02a"));
         
         if(!zipato.logout()){
              Serial.println(zipato.getErrorText());
              return;    
          }  
   }
