#include <DHT.h>
#include <ctype.h>

// Serial command character
char cmd;
String serial_out = "";
char str_buffer_float[5];

int pin_out_relay_a = 12; // digital toggle for enabling/disabling charging of the cell phone
int pin_state_relay_a = 0; // saves last known state of phone charge pin

int pin_out_relay_b = 10; // digital toggle for enabling/disabling charging of the cell phone
int pin_state_relay_b = 0; // saves last known state of phone charge pin

int pin_out_relay_c = 11; // digital toggle for enabling/disabling charging of the cell phone
int pin_state_relay_c = 0; // saves last known state of phone charge pin

// initialize temp/humidity (environment) sensor
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup () {
  Serial.begin(9600);
  dht.begin();

  // initialize output pins
  pinMode(pin_out_relay_a, OUTPUT);
  digitalWrite(pin_out_relay_a, LOW);
  pinMode(pin_out_relay_b, OUTPUT);
  digitalWrite(pin_out_relay_b, LOW);
  pinMode(pin_out_relay_c, OUTPUT);
  digitalWrite(pin_out_relay_c, LOW);
  
  test_relays();
}

void loop () {
  
  // wait 500 ms between checks for serial data.
  delay(500);
  
  // only execute when serial data is received
  while (Serial.available()) {
    cmd = Serial.read();
    
    if (cmd == 't') {
      String value_humidity = (String) dtostrf(dht.readHumidity(), 0, 2, str_buffer_float);
      String value_temperature = (String) dtostrf(dht.readTemperature(), 0, 2, str_buffer_float);
      serial_out += value_humidity + "/" + value_temperature;
      
    } else if (cmd == 'A') {
      serial_out += (String) pin_state_relay_a + "/" + (String) set_relay_a(true);
      
    } else if (cmd == 'a') {
      serial_out += (String) pin_state_relay_a + "/" + (String) set_relay_a(false);
           
    } else if (cmd == 'B') {
      serial_out += (String) pin_state_relay_b + "/" + (String) set_relay_b(true);
      
    } else if (cmd == 'b') {
      serial_out += (String) pin_state_relay_b + "/" + (String) set_relay_b(false);
      
    } else if (cmd == 'C') {
      serial_out += (String) pin_state_relay_c + "/" + (String) set_relay_c(true);
      
    } else if (cmd == 'c') {
      serial_out += (String) pin_state_relay_c + "/" + (String) set_relay_c(false);
      
    }    
  
    
    if (serial_out != "") {
      Serial.print("\n");
      Serial.print(serial_out);
      serial_out = "";
    }
  
  }
  
}

void test_relays() {
  set_relay_a(true);
  set_relay_b(true);
  set_relay_c(true);
  delay(1000);
  set_relay_a(false);
  set_relay_b(false);
  set_relay_c(false);
}


int set_relay_a(boolean on_off) {
  if (on_off) {
    digitalWrite(pin_out_relay_a, HIGH);
    pin_state_relay_a = 1;
  } else {
    digitalWrite(pin_out_relay_a, LOW);
    pin_state_relay_a = 0;
  }
  return pin_state_relay_a;
}

int set_relay_b(boolean on_off) {
  if (on_off) {
    digitalWrite(pin_out_relay_b, HIGH);
    pin_state_relay_b = 1;
  } else {
    digitalWrite(pin_out_relay_b, LOW);
    pin_state_relay_b = 0;
  }
  return pin_state_relay_b;
}

int set_relay_c(boolean on_off) {
  if (on_off) {
    digitalWrite(pin_out_relay_c, HIGH);
    pin_state_relay_c = 1;
  } else {
    digitalWrite(pin_out_relay_c, LOW);
    pin_state_relay_c = 0;
  }
  return pin_state_relay_c;
}
