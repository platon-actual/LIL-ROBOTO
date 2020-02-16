#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>

const bool IS_DEBUG = true;
const byte DNS_PORT = 53;

#define PWM_1 D1
#define PIN_A1 D5
#define PIN_A2 D6

#define PWM_2 D2
#define PIN_B1 D7
#define PIN_B2 D8

#define TURBO_ON 1023
#define TURBO_OFF 600

int poder = TURBO_ON;

const char* ssid = "EL_Robot";
const char* password = "12341234";

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

/// my own, personal, includes
#include <webpage.h>

ESP8266WebServer server(80);
DNSServer DNS;

void log_debug(char* msg){
  if (IS_DEBUG == true){
    Serial.println(msg);
  }
}

void handleRoot(){
  char* pagina = main_page;
  server.send(200, "text/html", pagina);
}

void setLed(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void testPwm(){
  digitalWrite(PIN_A1, HIGH);
  digitalWrite(PIN_A2, LOW);
  analogWrite(PWM_1, 1000); analogWrite(PWM_2, 1000);
  delay (1000);
  analogWrite(PWM_1, 0); analogWrite(PWM_2, 0);
  delay (1000);
  digitalWrite(PIN_A2, HIGH);
  digitalWrite(PIN_A1, LOW);
  analogWrite(PWM_1, 1000); analogWrite(PWM_2, 1000);
  delay (1000);
  analogWrite(PWM_1, 0); analogWrite(PWM_2, 0);
  delay (100);

  log_debug("test PWM");
  /* parte del debug */
  server.send(200, "text/plain", "");
}

void move_fwd(){
  digitalWrite(PIN_A2, HIGH);
  digitalWrite(PIN_A1, LOW);
  digitalWrite(PIN_B2, LOW);
  digitalWrite(PIN_B1, HIGH);
  analogWrite(PWM_1, poder);
  analogWrite(PWM_2, poder);

  log_debug("move forward");
  /* parte del debug */
  server.send(200, "text/plain", "");
}
void move_left(){
  digitalWrite(PIN_A2, HIGH);
  digitalWrite(PIN_A1, LOW);
  digitalWrite(PIN_B2, HIGH);
  digitalWrite(PIN_B1, LOW);
  analogWrite(PWM_1, poder);
  analogWrite(PWM_2, poder);

  log_debug("move LEFT");
  /* parte del debug */
  server.send(200, "text/plain", "");
}
void move_right(){
  digitalWrite(PIN_A2, LOW);
  digitalWrite(PIN_A1, HIGH);
  digitalWrite(PIN_B2, LOW);
  digitalWrite(PIN_B1, HIGH);
  analogWrite(PWM_1, poder);
  analogWrite(PWM_2, poder);

  log_debug("move RIGHT");
  /* parte del debug */
  server.send(200, "text/plain", "");
}
void stop(){
  analogWrite(PWM_1, 0);
  analogWrite(PWM_2, 0);
  
  log_debug("move STOP");
  /* parte del debug */
  server.send(200, "text/plain", "");
}

void turbo(){
  if (server.arg("modo") == "ON"){
    poder = TURBO_ON;
    server.send(200, "text/plain", "1023");
    Serial.println("TURBO ON");
  }
  if (server.arg("modo") == "OFF"){
    poder = TURBO_OFF;
    server.send(200, "text/plain", "600");
    Serial.println("TURBO OFF");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hola! Si usted lee esto, funca el serial.");

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PWM_1, OUTPUT);
  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_A2, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);

  Serial.print("Setting up soft-AP ...");


  
  WiFi.softAP(ssid /*, password*/);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  DNS.start(DNS_PORT, "*", local_ip);
  //delay(100);

  server.on("/", handleRoot);
  server.on("/setled", setLed);
  server.on("/testmotors", testPwm);

  server.on("/goon", move_fwd);
  server.on("/goleft", move_left);
  server.on("/goright", move_right);
  server.on("/stop", stop);
  server.on("/turbo", turbo);
  server.onNotFound(handleRoot);

  server.begin();
  if (!MDNS.begin("autito"))
    Serial.println("mDNS: ERROR!!!!");
  Serial.println("mDNS started, nerd.");
  Serial.println("Server started. Nerd.");
}

void loop() {
  server.handleClient();
}