
#ifndef Zipato_H
#define Zipato_H
#include <ArduinoJson.h>
#include <ESP8266WiFi.h> 
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>      //version=1.1
#include <Hash.h>

#include "Arduino.h"

class Zipato {

    public:
        // Constructor 
        Zipato (String host, String username, String password );
        
        
        bool login();
        bool logout();
        
        String getErrorText();
        String getAttribtValue(String attribut);

    private:
        String _jsessionid;
        String _host;
        String _username;
        String _password; 
        String _payload;
        String _errorText;
        
        HTTPClient _http;

 
        bool get(String url);
    
    
       
};

#endif
