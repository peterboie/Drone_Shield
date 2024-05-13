#include <WiFiS3.h>

//ip address of drone
#define ip_address "192.168.10.1"

//LED variables
const int connected_blue_led = A5;
const int not_connected_yellow_led = A4;

//button variables
const int First_routine_button = 2;
const int Second_routine_button = A3;
const int takeoff_button = A2;
const int land_button = A1;
const int up_button = 4;
const int down_button = A0;
const int forward_button = 5;
const int back_button = 7;
const int turn_left_button = 8;
const int turn_right_button = 6;
const int flip_forward_button = 12;
const int flip_backward_button = 11;
const int flip_left_button = 10;
const int flip_right_button = 9;

//flag to run certain commands once when connected to drone while in the main loop
bool wfi_connected = false;

//delay between button presses
const int pause_interval = 4000;

//udp commands in an array
char* drone_commands[15] = { "command", "takeoff", "land", "up 50", "cw 90", "forward 150", "ccw 90", "flip b", "flip f", "flip l", "flip r", "up 160", "up 5", "down 5", "down 100" };

//wifi network name from drone and password
const char* ssid = "TELLO-E92F57";
const char* password = "engineeringwonder";

//udp port
const int port = 8889;
//attach object
WiFiUDP Udp;

void setup() {
  //set all pin modes. All buttons use the internal pullup resistors.
  pinMode(connected_blue_led, OUTPUT);
  pinMode(not_connected_yellow_led, OUTPUT);
  pinMode(First_routine_button, INPUT_PULLUP);
  pinMode(Second_routine_button, INPUT_PULLUP);
  pinMode(takeoff_button, INPUT_PULLUP);
  pinMode(land_button, INPUT_PULLUP);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(forward_button, INPUT_PULLUP);
  pinMode(back_button, INPUT_PULLUP);
  pinMode(turn_left_button, INPUT_PULLUP);
  pinMode(turn_right_button, INPUT_PULLUP);
  pinMode(flip_forward_button, INPUT_PULLUP);
  pinMode(flip_backward_button, INPUT_PULLUP);
  pinMode(flip_left_button, INPUT_PULLUP);
  pinMode(flip_right_button, INPUT_PULLUP);

  //turn the yello LED on and blue off because wifi not connected
  digitalWrite(not_connected_yellow_led, HIGH);
  digitalWrite(connected_blue_led, LOW);
}

void loop() {
  //run this loop while the Arduino is NOT connected to the drones wifi
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    digitalWrite(not_connected_yellow_led, HIGH);
    digitalWrite(connected_blue_led, LOW);
   
    wfi_connected = false;
    delay(500);
  }
  //once if connects to the drone it will run this once to set up the udp connection
  if (wfi_connected == false) {
    Udp.begin(port);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[0]);
    Udp.endPacket();
    digitalWrite(connected_blue_led, HIGH);
    digitalWrite(not_connected_yellow_led, LOW);
    //the flag turns to true so this won't run again unless the wifi becomes disconnected
    wfi_connected = true;
  }

  //read the state of each button and store the value in a new variable
  int First_routine_button_state = digitalRead(First_routine_button);
  int Second_routine_button_state = digitalRead(Second_routine_button);
  int takeoff_button_state = digitalRead(takeoff_button);
  int land_button_state = digitalRead(land_button);
  int up_button_state = digitalRead(up_button);
  int down_button_state = digitalRead(down_button);
  int forward_button_state = digitalRead(forward_button);
  int back_button_state = digitalRead(back_button);
  int turn_left_button_state = digitalRead(turn_left_button);
  int turn_right_button_state = digitalRead(turn_right_button);
  int flip_forward_button_state = digitalRead(flip_forward_button);
  int flip_backward_button_state = digitalRead(flip_backward_button);
  int flip_left_button_state = digitalRead(flip_left_button);
  int flip_right_button_state = digitalRead(flip_right_button);

  //check each button. If the button is low (pressed) it will execute the code in the if statement
  if (First_routine_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    firstFlight();
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (Second_routine_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    SecondFlight();
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (takeoff_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    //everytime you send a udp command to the drone you need the following three lines:
    Udp.beginPacket(ip_address, port);
    //instead of using the array you could just put the upd command inside of quotes in the parenthises(see drone SDK manual for list of commands)
    Udp.write(drone_commands[1]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (land_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[2]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (up_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[3]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (down_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write("down 50");
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (forward_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write("forward 50");
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (back_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write("back 50");
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (turn_left_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[6]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (turn_right_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[4]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (flip_forward_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[8]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (flip_backward_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[7]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (flip_left_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[9]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
  if (flip_right_button_state == LOW) {
    digitalWrite(not_connected_yellow_led, HIGH);
    Udp.beginPacket(ip_address, port);
    Udp.write(drone_commands[10]);
    Udp.endPacket();
    delay(pause_interval);
    digitalWrite(not_connected_yellow_led, LOW);
  }
}

void firstFlight() {
  // Take off
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[1]);
  Udp.endPacket();
  delay(8000);
  // up 50
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[3]);
  Udp.endPacket();
  delay(5000);
  // cw 90
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[4]);
  Udp.endPacket();
  delay(5000);
  // forward 150
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[5]);
  Udp.endPacket();
  delay(5000);
  // ccw 90
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[6]);
  Udp.endPacket();
  delay(5000);
  // flip back
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[7]);
  Udp.endPacket();
  delay(5000);
  // flip forward
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[8]);
  Udp.endPacket();
  delay(5000);
  // flip Left
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[9]);
  Udp.endPacket();
  delay(5000);
  // flip right
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[10]);
  Udp.endPacket();
  delay(5000);
  // ccw 90
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[6]);
  Udp.endPacket();
  delay(5000);
  // forward 150
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[5]);
  Udp.endPacket();
  delay(5000);
  // land
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[2]);
  Udp.endPacket();
  delay(5000);
}

void SecondFlight() {
  // Take off
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[1]);
  Udp.endPacket();
  delay(8000);
  // up 160
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[11]);
  Udp.endPacket();
  delay(12000);
  // up 5
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[12]);
  Udp.endPacket();
  delay(12000);
  // down 5
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[13]);
  Udp.endPacket();
  delay(5000);
  // up 5
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[12]);
  Udp.endPacket();
  delay(11000);
  // down 100
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[14]);
  Udp.endPacket();
  delay(5000);
  // land
  Udp.beginPacket(ip_address, port);
  Udp.write(drone_commands[2]);
  Udp.endPacket();
  delay(5000);
}
