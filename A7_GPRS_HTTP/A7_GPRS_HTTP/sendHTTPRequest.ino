void constructHTTPRequest(char* msg){  
  msg[0] = 0;
  strcat(msg, "GET /log.php?");  
  strcat(msg, "te=");
  strcat(msg, temperature);
  strcat(msg, "&");
  strcat(msg, "do=");
  strcat(msg, DO);
  strcat(msg, "&");
  strcat(msg, "pH=");
  strcat(msg, pH);
  strcat(msg, "&");
  strcat(msg, "tu=");
  strcat(msg, turbidity);
  strcat(msg, "&");
  strcat(msg, "la=");
  strcat(msg, lat);
  strcat(msg, "&");
  strcat(msg, "ln=");
  strcat(msg, lng);  
  strcat(msg, " HTTP/1.1\r\nHost: ");
  strcat(msg, server);
  strcat(msg, "\r\nConnection: close\r\n\r\n");
}


void HTTPRequest(char* msg){
  
  a7Client.write(msg);
}
