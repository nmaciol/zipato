#include "Zipato.h"


Zipato::Zipato (String host, String username, String password) {
  
    _host        = host;
    _username    = username;
    _password    = password;
    
}

String Zipato::getAttribtValue(String attribut) {
    
    StaticJsonBuffer<512>   jsonBuffer;
 
    String url = "http://" + (String)(_host) + "/zipato-web/v2/attributes/" + attribut + "/value";

    if (!this->get(url)) { return "";  }

    JsonObject& root = jsonBuffer.parseObject(_payload);

    if (root.containsKey("value") ){
        return root["value"].asString();
    } else{
        root.prettyPrintTo(Serial);
        return "";
    }
     
}





bool Zipato::get(String url){

        _http.setReuse(true);
        _http.begin(url);
     
        if( _jsessionid != "" ) {  _http.addHeader("Cookie", "JSESSIONID=" + _jsessionid); }
        int httpCode = _http.GET();

        if(httpCode > 0) {

            if(httpCode == HTTP_CODE_OK) {

                _payload = _http.getString();
                return true;

            } else {
                // Http  Status Code != 200
                _errorText =  "GET - HTTP StatusCode = " + httpCode;
            }
            
        } else {
            // Http connection 
            _errorText =  _http.errorToString(httpCode).c_str();
        }
        _http.end();
        return false;

        
}

String Zipato::getErrorText(){


        if((_errorText).length() == 0){

            return _payload;
           
        } else {

            return _errorText;
        }
}


bool Zipato::login() {
        StaticJsonBuffer<512>   jsonBuffer;     
        
        //    1 1 1 1 1 1 1 1 1
                     
        String url = "http://" + (String)(_host) + "/zipato-web/v2/user/init";
        _jsessionid = "";
        if (!this->get(url)) { return false;  }

        JsonObject& root = jsonBuffer.parseObject(_payload);

        _jsessionid = root["jsessionid"].asString();
                
        String token = sha1(root["nonce"].asString() + sha1(_password));
     
        //     2 2 2 2 2 2 2 2 2
                
        url = "http://" + (String)(_host) + "/zipato-web/v2/user/login?username=" + _username + "&token=" + token;
        if (!this->get(url)) { return false; }

        JsonObject& root2 = jsonBuffer.parseObject(_payload);

        if (strcmp( root2["success"].asString(), "true" ) != 0 ) {return false;}
       
        return true;

}

bool Zipato::logout() {
       
        String url = "http://" + (String)(_host) + "/zipato-web/v2/user/logout";

        if (!this->get(url)) { return false;  }

        return true;
}

