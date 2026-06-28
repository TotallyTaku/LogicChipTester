// struct to hold all output values of a 2-input logic chip
struct TwoInputResults {
  bool out00;
  bool out01;
  bool out10;
  bool out11;
};

// struct to hold all output values of a 1-input logic chip
struct SingleInputResults {
  bool out00;
  bool out01;
};

// Holds 4 structs of TwoInputResults housing all results for an entire quad 2-input logic chip
struct QuadGateResults {
  TwoInputResults gate0;
  TwoInputResults gate1;
  TwoInputResults gate2;
  TwoInputResults gate3;
};
// Holds 6 structs of SingleInputResults housing all results for a hexa 1-input logic chip
struct HexaGateResults {
  SingleInputResults gate0;
  SingleInputResults gate1;
  SingleInputResults gate2;
  SingleInputResults gate3;
  SingleInputResults gate4;
  SingleInputResults gate5;
};

// Stores the pins for a 2-input gate layout chip
struct TwoInputGateLayout{
  int pinA;
  int pinB;
  int pinY;
};

// Stores the pins for a 1-input gate layout chip
struct SingleInputGateLayout{
  int pinA;
  int pinY;
};

// Stores basic information about a quad 2-input chip (WIP)
struct QuadTwoInputChip{
  String name;
  const TwoInputGateLayout* layout;
  TwoInputResults expected;
};

void setup(){
  Serial.begin(9600);
}


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

const int DELAY_TIME = 10;  // constant value in milliseconds to use in delays

// General Gates and their constant truth tables
const TwoInputResults EXPECTED_AND = { LOW, LOW, LOW, HIGH };
const TwoInputResults EXPECTED_OR = { LOW, HIGH, HIGH, HIGH };
const TwoInputResults EXPECTED_NOR = { HIGH, LOW, LOW, LOW };
const TwoInputResults EXPECTED_XOR = { LOW, HIGH, HIGH, LOW };
const TwoInputResults EXPECTED_NAND = { HIGH, HIGH, HIGH, LOW };
const SingleInputResults EXPECTED_NOT = { HIGH, LOW };

const TwoInputGateLayout STANDARD_QUAD_2_INPUT_LAYOUT[4] = {
  {13, 12, 11},
  {10, 9, 8},
  {7, 6, 5},
  {4, 3, 2}
};

const TwoInputGateLayout SN74LS02_LAYOUT[4] = {
  {12, 11, 13},
  {10, 9, 8},
  {6, 5, 7},
  {3, 2, 4}
};

const SingleInputGateLayout STANDARD_HEXA_1_INPUT_LAYOUT[6] = {
  {13, 12},
  {11, 10},
  {9, 8},
  {7,6}, 
  {5, 4},
  {3, 2}
};

const QuadTwoInputChip SN74LS08 = {
  "SN74LS08",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_AND
};

const QuadTwoInputChip SN74LS32 = {
  "SN74LS32",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_OR
};

const QuadTwoInputChip SN74LS02 = {
  "SN74LS02",
  SN74LS02_LAYOUT,
  EXPECTED_NOR
};

const QuadTwoInputChip SN74LS86 = {
  "SN74LS86",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_XOR
};


// =================================
/* loop is EMPTY FOR NOWWWWWWW*/
// =================================
void loop() {
}


/**
Tests a 2-input logic gate's all possible states (2^2 total.)
- return struct TwoInputResults with output values
*/
TwoInputResults test_single_two_input_gate(int pinA, int pinB, int pinY) {
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
/**
Tests a quad 2-input logic chip entirely and returns a structure with all of the values for each scenario
*/
QuadGateResults run_quad_two_input_gate(const QuadTwoInputChip& chip) {

  QuadGateResults results;
  
  results.gate0 = test_single_two_input_gate(chip.layout[0].pinA, chip.layout[0].pinB, chip.layout[0].pinY);
  results.gate1 = test_single_two_input_gate(chip.layout[1].pinA, chip.layout[1].pinB, chip.layout[1].pinY);
  results.gate2 = test_single_two_input_gate(chip.layout[2].pinA, chip.layout[2].pinB, chip.layout[2].pinY);
  results.gate3 = test_single_two_input_gate(chip.layout[3].pinA, chip.layout[3].pinB, chip.layout[3].pinY);

  return results;
}

/**
Tests a 1-input gate's scenarios and returns a structure SingleInputResults with all scenarios' results
*/
SingleInputResults test_single_input_gate(int pinA, int pinY) {
  SingleInputResults result;

  digitalWrite(pinA, LOW);
  delay(DELAY_TIME);
  result.out00 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  delay(DELAY_TIME);
  result.out01 = digitalRead(pinY);

  return result;
}

/**
Tests a full hexa 1-input logic chip recording all scenarios inside a structure HexaGateResults
*/
HexaGateResults run_hexa_single_input_gate() {

  HexaGateResults results;

  results.gate0 = test_single_input_gate(PIN_13, PIN_12);
  results.gate1 = test_single_input_gate(PIN_11, PIN_10);
  results.gate2 = test_single_input_gate(PIN_9, PIN_8);
  results.gate3 = test_single_input_gate(PIN_7, PIN_6);
  results.gate4 = test_single_input_gate(PIN_5, PIN_4);
  results.gate5 = test_single_input_gate(PIN_3, PIN_2);

  return results;
}

/**
Compares the given results of a 2-input chip's test scenarios with the expected results.
Returns true if all scenarios tested from the chip match the expected results.
*/
bool compare_two_input_results(const TwoInputResults& actual, const TwoInputResults& expected) {
  return (actual.out00 == expected.out00) && 
         (actual.out01 == expected.out01) && 
         (actual.out10 == expected.out10) && 
         (actual.out11 == expected.out11);
}

/**
Compares the given results of a 1-input chip's test scenarios with expected results.
Returns true if all scenarios tested match the expected results.
*/
bool compare_single_input_results(const SingleInputResults& actual, const SingleInputResults& expected) {
  return (actual.out00 == expected.out00) && 
         (actual.out01 == expected.out01);
}

/** Compares all 4 gates in a 2-input chip with all possible scenarios and returns true if it matches the expected results*/
bool compare_quad_gate_results(const QuadGateResults& actual, const TwoInputResults& expected){
  return compare_two_input_results(actual.gate0, expected) &&
         compare_two_input_results(actual.gate1, expected) &&
         compare_two_input_results(actual.gate2, expected) &&
         compare_two_input_results(actual.gate3, expected);
}

/** Compares all 6 gates in a 1-input chip with all possible scenarios and returns true if it matches the expected results*/
bool compare_hexa_gate_results(const HexaGateResults& actual, const SingleInputResults& expected){
  return compare_single_input_results(actual.gate0, expected) &&
         compare_single_input_results(actual.gate1, expected) &&
         compare_single_input_results(actual.gate2, expected) &&
         compare_single_input_results(actual.gate3, expected) &&
         compare_single_input_results(actual.gate4, expected) &&
         compare_single_input_results(actual.gate5, expected);
}

/** 
Setups the GPIO pins to tests a 2-input chip
*/
void two_input_gate_pin_setup(const TwoInputGateLayout layout[4]) {

  // Set up pins for the 4 gates in the chip
  for (int i=0; i < 4; i++){
    pinMode(layout[i].pinA, OUTPUT);
    pinMode(layout[i].pinB, OUTPUT);
    pinMode(layout[i].pinY, INPUT);
  }
}


/** Setups the GPIO pins to test a 1-input chip*/
void single_input_gate_pin_setup(const SingleInputGateLayout layout[6]) {

  // Prepares pins for a hexa single input gate chip
 for (int i=0; i < 6; i++){
  pinMode(layout[i].pinA, OUTPUT);
  pinMode(layout[i].pinY, INPUT);
 }
}

// ===============================================================

// === Actual chips testing functions below ===


bool test_quad_chip(const QuadTwoInputChip& chip){
  
  two_input_gate_pin_setup(chip.layout);
  QuadGateResults actual = run_quad_two_input_gate(chip);
  
  return compare_quad_gate_results(actual, chip.expected);
}

//Tests the hexa 1-input gate chip SN74LS05N(NOT) and returns true if chip is good.
bool test_SN74LS05N(){
  single_input_gate_pin_setup(STANDARD_HEXA_1_INPUT_LAYOUT);
  HexaGateResults actual = run_hexa_single_input_gate();

  return compare_hexa_gate_results(actual, EXPECTED_NOT);
}

