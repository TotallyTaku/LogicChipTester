// struct to hold all output values of a 2-input logic chip
struct TwoInputResults {
  bool out00;
  bool out01;
  bool out10;
  bool out11;
};

// struct to hold all output values of a 1-input logic chip
struct SingleInputResults {
  bool out0;
  bool out1;
};

// Holds 4 structs fo TwoInputResults housing all results for an entire quad 2-input logic chip
struct QuadGateResults {
  TwoInputResults gate0;
  TwoInputResults gate1;
  TwoInputResults gate2;
  TwoInputResults gate3;
};

struct HexaGateResults {
  SingleInputResults gate0;
  SingleInputResults gate1;
  SingleInputResults gate2;
  SingleInputResults gate3;
  SingleInputResults gate4;
  SingleInputResults gate5;
}

/**
Struct to store basic information of a chip
- String name
- String family
- int num_inputs
- int num_outputs
*/
struct chipInfo {
  String name;
  String family;
  int num_inputs;
  int num_outputs;

};


void setup() {
  Serial.begin(9600);

  // Declaring constants for all avaialable pins to be used.
  const int PIN_13 = 13;
  const int PIN_12 = 12;
  const int PIN_11 = 11;
  const int PIN_10 = 10;
  const int PIN_9 = 9;
  const int PIN_8 = 8;
  const int PIN_7 = 7;
  const int PIN_6 = 6;
  const int PIN_5 = 5;
  const int PIN_4 = 4;
  const int PIN_3 = 3;
  const int PIN_2 = 2;
  const int PIN_1 = 1;
  const int PIN_0 = 0;
  const int PIN_A0 = A0;
  const int PIN_A1 = A1;
  const int PIN_A2 = A2;
  const int PIN_A3 = A3;
  const int PIN_A4 = A4; 
  const int PIN_A5 = A5;

  const int PINS =  {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, A0, A1, A2, A3, A4, A5};

  const int DELAY_TIME = 500; // constant value in milliseconds to use in delays
}

void loop() {
  
}


/**
Tests a 2-input logic gate's all possible states (2^2 total.)
- return struct TwoInputResults with output values
*/
TwoInputResults test_single_two_input_gate(int pinA, int pinB, int pinY){
  TwoInputResults result;

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delay(DELAY_TIME);
  result.out00 = digitalRead(pinY);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  delay(DELAY_TIME);
  result.out01 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  delay(DELAY_TIME);
  result.out10 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  delay(DELAY_TIME);
  result.out11 = digitalRead(pinY);
  
  return result;
}

QuadGateResults run_quad_two_input_gate_test(){

  QuadGateResults results;

  results.gate0 = test_one_two_input_gate(PIN_13, PIN_12, PIN_11);
  results.gate1 = test_one_two_input_gate(PIN_10, PIN_9, PIN_8);
  results.gate2 = test_one_two_input_gate(PIN_7, PIN_6, PIN_5);
  results.gate3 = test_one_two_input_gate(PIN_4, PIN_3, PIN_2);

  return results;
}

SingleInputResults test_single_input_gate(int pinA, int pinY){
  SingleInputResults result;

  digitalWrite(pinA, LOW);
  delay(DELAY_TIME);
  result.out0 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  delay(DELAY_TIME);
  result.out1 = digitalRead(pinY);

  return result;
}

HexaGateResults run_hexa_one_input_gate(){

  HexaGateResults results;

  results.gate0 = test_single_input_gate(PIN_13, PIN_12);
  results.gate1 = test_single_input_gate(PIN_11, PIN_10):
  results.gate2 = test_single_input_gate(PIN_9, PIN_8);
  results.gate3 = test_single_input_gate(PIN_7, PIN_6);
  results.gate4 = test_single_input_gate(PIN_5, PIN_4);
  results.gate5 = test_single_input_gate(PIN_3, PIN_2);

  return results;
}


const TwoInputResults EXPECTED_AND = {LOW, LOW, LOW, HIGH};
const TwoInputResults EXPECTED_OR = {LOW, HIGH, HIGH, HIGH};
const TwoInputResults EXPECTED_NOR = {HIGH, LOW, LOW, LOW};
const TwoInputResults EXPECTED_XOR = {LOW, HIGH, HIGH, LOW};
const TwoInputResults EXPECTED_NAND = {HIGH, HIGH, HIGH, LOW};
const SingleInputResults EXPECTED_NOT = {HIGH, LOW};

bool compare_two_input_results(const TwoInputResults& actual, const TwoInputResults& expected){
  return (actual.out0 == expected.out0) &&
         (actual.out01 == expected.out01) &&
         (actual.out10 == expected.out10) &&
         (actual.out11 == expected.out11);
}

bool compare_one_input_results(const SingleInputResults& actual, const SingleInputResults& expected){
  return (actual.out0 == expected.out0) &&
         (actual.out1 == expected.out1);
}

void two_input_gate_pin_setup(){
  // first gate (top-left)
  pinMode(PIN_13, OUTPUT);
  pinMode(PIN_12, OUTPUT);
  pinMode(PIN_11, INPUT);
  
  // second gate (bottom-left)
  pinMode(PIN_10, OUTPUT);
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_8, INPUT);

  // third gate (top-right)
  pinMode(PIN_7, OUTPUT); 
  pinMode(PIN_6, OUTPUT); 
  pinMode(PIN_5, INPUT);

  // fourth gate (bottom-left)
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_3, OUTPUT); 
  pinMode(PIN_2, INPUT);
}

void one_input_gate_pin_setup(){

  // first gate (top-left)
  pinMode(PIN_13, OUTPUT);
  pinMode(PIN_12, INPUT);

  // second gate (mid-left)
  pinMode(PIN_11, OUTPUT);
  pinMode(PIN_10, INPUT);

  // third gate (bottom-left)
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_8, INPUT);

  // fourth gate (top-right)
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_6, INPUT);

  // fifth gate (mid-right)
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_4, INPUT);

  // sixth gate (bottom-right)
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_2, INPUT);

}