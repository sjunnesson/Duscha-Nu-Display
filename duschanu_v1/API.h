void checkAPI(){
  //Initiate HTTP client
  HTTPClient http;
  //The API URL
  String request = "https://api.chucknorris.io/jokes/random";
  //Start the request
  http.begin(request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  //Print parsed value on Serial Monitor
  Serial.println(doc["value"].as<char*>());

// set current price from API
// read the char array and convert to an int
// currentPrice =  atoi(doc["value"].as<char*>()); 
  
  //Close connection
  http.end();
}
