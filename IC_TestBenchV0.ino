// struct to hold all output values of a 2-input logic chip
struct TwoInputTruthTable {
  bool output00;
  bool output01;
  bool output10;
  bool output11;
};

// struct to hold all output values of a 1-input logic chip
struct OneInputTruthTable {
  bool output0;
  bool output1;
};

// Holds 4 structs of TwoInputTruthTable housing all results for an entire quad 2-input logic chip
struct QuadTwoInputMeasurements {
  TwoInputTruthTable gates[4];
};
// Holds 6 structs of OneInputTruthTable housing all results for a hexa 1-input logic chip
struct HexOneInputMeasurements {
  OneInputTruthTable gates[6];
};

// Stores the pins for a 2-input gate layout chip
struct TwoInputGatePins{
  uint8_t inputAPin;
  uint8_t inputBPin;
  uint8_t outputPin;

};

// Stores the pins for a 1-input gate layout chip
struct OneInputGatePins{
  uint8_t inputPin;
  uint8_t outputPin;;
};

// Stores basic information about a quad 2-input chip (WIP)
struct QuadTwoInputChipConfig{
  const char* partNumber;
  const TwoInputGatePins* gatePins;
  TwoInputTruthTable expectedTruthTable;
};


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
const int MAXIMUM_WAIT_TIME = 5000;

// General Gates and their constant truth tables
const TwoInputTruthTable EXPECTED_AND = { LOW, LOW, LOW, HIGH };
const TwoInputTruthTable EXPECTED_OR = { LOW, HIGH, HIGH, HIGH };
const TwoInputTruthTable EXPECTED_NOR = { HIGH, LOW, LOW, LOW };
const TwoInputTruthTable EXPECTED_XOR = { LOW, HIGH, HIGH, LOW };
const TwoInputTruthTable EXPECTED_NAND = { HIGH, HIGH, HIGH, LOW };
const OneInputTruthTable EXPECTED_NOT = { HIGH, LOW };

const TwoInputGatePins STANDARD_QUAD_2_INPUT_LAYOUT[4] = {
  {13, 12, 11},
  {10, 9, 8},
  {7, 6, 5},
  {4, 3, 2}
};

const TwoInputGatePins SN74LS02_LAYOUT[4] = {
  {12, 11, 13},
  {10, 9, 8},
  {6, 5, 7},
  {3, 2, 4}
};

const OneInputGatePins STANDARD_HEXA_1_INPUT_LAYOUT[6] = {
  {13, 12},
  {11, 10},
  {9, 8},
  {7,6}, 
  {5, 4},
  {3, 2}
};

const QuadTwoInputChipConfig SN74LS08 = {
  "SN74LS08",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_AND
};

const QuadTwoInputChipConfig SN74LS32 = {
  "SN74LS32",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_OR
};

const QuadTwoInputChipConfig SN74LS02 = {
  "SN74LS02",
  SN74LS02_LAYOUT,
  EXPECTED_NOR
};

const QuadTwoInputChipConfig SN74LS86 = {
  "SN74LS86",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_XOR
};


void setup(){
  Serial.begin(9600);
  Serial.setTimeout(MAXIMUM_WAIT_TIME);
}


// =================================
/* loop is EMPTY FOR NOWWWWWWW*/
// =================================
void loop() {
}


/**
Tests a 2-input logic gate's all possible states (2^2 total.)
- return struct TwoInputTruthTable with output values
*/
TwoInputTruthTable readTwoInputGate(int pinA, int pinB, int pinY) {
  TwoInputTruthTable result;

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delay(DELAY_TIME);
  result.output00 = digitalRead(pinY);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  delay(DELAY_TIME);
  result.output01 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  delay(DELAY_TIME);
  result.output10 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  delay(DELAY_TIME);
  result.output11 = digitalRead(pinY);

  return result;
}
/**
Tests a quad 2-input logic chip entirely and returns a structure with all of the values for each scenario
*/
QuadTwoInputMeasurements measureQuadTwoInputChip(const QuadTwoInputChipConfig& chip) {

  QuadTwoInputMeasurements results;
  
  results.gates[0] = readTwoInputGate(chip.gatePins[0].inputAPin, chip.gatePins[0].inputBPin, chip.gatePins[0].outputPin);
  results.gates[1] = readTwoInputGate(chip.gatePins[1].inputAPin, chip.gatePins[1].inputBPin, chip.gatePins[1].outputPin);
  results.gates[2] = readTwoInputGate(chip.gatePins[2].inputAPin, chip.gatePins[2].inputBPin, chip.gatePins[2].outputPin);
  results.gates[3] = readTwoInputGate(chip.gatePins[3].inputAPin, chip.gatePins[3].inputBPin, chip.gatePins[3].outputPin);

  return results;
}

/**
Tests a 1-input gate's scenarios and returns a structure OneInputTruthTable with all scenarios' results
*/
OneInputTruthTable readOneInputGate(int pinA, int pinY) {
  OneInputTruthTable result;

  digitalWrite(pinA, LOW);
  delay(DELAY_TIME);
  result.output0 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  delay(DELAY_TIME);
  result.output1 = digitalRead(pinY);

  return result;
}

/**
Tests a full hexa 1-input logic chip recording all scenarios inside a structure HexOneInputMeasurements
*/
HexOneInputMeasurements measureHexOneInputChip() {

  HexOneInputMeasurements results;

  results.gates[0] = readOneInputGate(PIN_13, PIN_12);
  results.gates[1] = readOneInputGate(PIN_11, PIN_10);
  results.gates[2] = readOneInputGate(PIN_9, PIN_8);
  results.gates[3] = readOneInputGate(PIN_7, PIN_6);
  results.gates[4] = readOneInputGate(PIN_5, PIN_4);
  results.gates[5] = readOneInputGate(PIN_3, PIN_2);
  return results;
}

/**
Compares the given results of a 2-input chip's test scenarios with the expected results.
Returns true if all scenarios tested from the chip match the expected results.
*/
bool compareTwoInputTruthTable(const TwoInputTruthTable& actual, const TwoInputTruthTable& expected) {
  return (actual.output00 == expected.output00) && 
         (actual.output01 == expected.output01) && 
         (actual.output10 == expected.output10) && 
         (actual.output11 == expected.output11);
}

/**
Compares the given results of a 1-input chip's test scenarios with expected results.
Returns true if all scenarios tested match the expected results.
*/
bool compareOneInputTruthTable(const OneInputTruthTable& actual, const OneInputTruthTable& expected) {
  return (actual.output0 == expected.output0) && 
         (actual.output1 == expected.output1);
}

/** Compares all 4 gates in a 2-input chip with all possible scenarios and returns true if it matches the expected results*/
bool compareQuadTwoInputTruthTable(const QuadTwoInputMeasurements& actual, const TwoInputTruthTable& expected){
  return compareTwoInputTruthTable(actual.gates[0], expected) &&
         compareTwoInputTruthTable(actual.gates[1], expected) &&
         compareTwoInputTruthTable(actual.gates[2], expected) &&
         compareTwoInputTruthTable(actual.gates[3], expected);
}

/** Compares all 6 gates in a 1-input chip with all possible scenarios and returns true if it matches the expected results*/
bool compareHexOneInputTruthTable(const HexOneInputMeasurements& actual, const OneInputTruthTable& expected){
  return compareOneInputTruthTable(actual.gates[0], expected) &&
         compareOneInputTruthTable(actual.gates[1], expected) &&
         compareOneInputTruthTable(actual.gates[2], expected) &&
         compareOneInputTruthTable(actual.gates[3], expected) &&
         compareOneInputTruthTable(actual.gates[4], expected) &&
         compareOneInputTruthTable(actual.gates[5], expected);
}

/** 
Setups the GPIO pins to tests a 2-input chip
*/
void configureTwoInputGatePins(const TwoInputGatePins layout[4]) {

  // Set up pins for the 4 gates in the chip
  for (int i=0; i < 4; i++){
    pinMode(layout[i].inputAPin, OUTPUT);
    pinMode(layout[i].inputBPin, OUTPUT);
    pinMode(layout[i].outputPin, INPUT);
  }
}


/** Setups the GPIO pins to test a 1-input chip*/
void configureOneInputGatepins(const OneInputGatePins layout[6]) {

  // Prepares pins for a hexa single input gate chip
 for (int i=0; i < 6; i++){
  pinMode(layout[i].inputPin, OUTPUT);
  pinMode(layout[i].outputPin, INPUT);
 }
}

// ===============================================================

// === Actual chips testing functions below ===


bool testQuadTwoInputChip(const QuadTwoInputChipConfig& chip){
  
  configureTwoInputGatePins(chip.gatePins);
  QuadTwoInputMeasurements actual = measureQuadTwoInputChip(chip);
  
  return compareQuadTwoInputTruthTable(actual, chip.expectedTruthTable);
}

//Tests the hexa 1-input gate chip SN74LS05N(NOT) and returns true if chip is good.
bool test_SN74LS05N(){
  configureOneInputGatepins(STANDARD_HEXA_1_INPUT_LAYOUT);
  HexOneInputMeasurements actual = measureHexOneInputChip();

  return compareHexOneInputTruthTable(actual, EXPECTED_NOT);
}

// **********************************
// * All the screen stuff below     *
// **********************************

void refreshScreen(){
  for (int i=0;i < 30; i++){
    Serial.println();
  }
}

void printMainMenu(){
  Serial.println("Author: Kemuel Bermudez-Cotto");
  Serial.println("Date: 07/20/2026");

  Serial.println("**************************");
  Serial.println("* Logic Chips Tester v0  *");
  Serial.println("**************************");

  printMenuOptions();
}

void printMenuOptions(){

  uint8_t selectedOption = 3;

  while (selectedOption != 0){
    Serial.println("Options:");
    Serial.println("1. Test known chip");
    Serial.println("2. Test unknown chip");
    Serial.println("3. Exit Program");
    Serial.println();
    Serial.println("Selected Option: ");
    Serial.flush();
    selectedOption = Serial.parseInt();

    if (selectedOption != 1 || selectedOption != 2 || selectedOption != 3){
      Serial.println("The value provided is not valid");
      Serial.print("Value: ");
      Serial.println(selectedOption);
      
    }
    if (selectedOption == 0){
      

    }
  }
}

