// **********************************
// * Structs and enums below        *
// **********************************

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
  uint8_t outputPin;
};

// Stores basic information about a quad 2-input chip 
struct QuadTwoInputChipConfig{
  const char* partNumber;
  const TwoInputGatePins* gatePins;
  TwoInputTruthTable expectedTruthTable;
};

// Stores basic information about a hex 1-input chip 
struct HexOneInputChipConfig{
  const char* partNumber;
  const OneInputGatePins* gatePins;
  OneInputTruthTable expectedTruthTable;
};


// **********************************
// * constant variables below       *
// **********************************


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

const unsigned int DELAY_TIME = 10;  // constant value in microseconds to use in delays
const int MAXIMUM_WAIT_TIME = 10000;

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

const TwoInputGatePins SN74LS02N_LAYOUT[4] = {
  {12, 11, 13},
  {10, 9, 8},
  {6, 5, 7},
  {3, 2, 4}
};

const OneInputGatePins STANDARD_HEX_1_INPUT_LAYOUT[6] = {
  {13, 12},
  {11, 10},
  {9, 8},
  {7,6}, 
  {5, 4},
  {3, 2}
};

// **********************************
// * Supported Chip Structs below   *
// **********************************


const QuadTwoInputChipConfig SN74LS00N = {
  "SN74LS00N",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_NAND
};

const QuadTwoInputChipConfig SN74LS02N = {
  "SN74LS02N",
  SN74LS02N_LAYOUT,
  EXPECTED_NOR
};

const HexOneInputChipConfig SN74LS05N = {
  "SN74LS05N",
  STANDARD_HEX_1_INPUT_LAYOUT,
  EXPECTED_NOT
};

const QuadTwoInputChipConfig SN74LS08N = {
  "SN74LS08N",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_AND
};

const QuadTwoInputChipConfig SN74LS32N = {
  "SN74LS32N",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_OR
};

const QuadTwoInputChipConfig SN74LS86N = {
  "SN74LS86N",
  STANDARD_QUAD_2_INPUT_LAYOUT,
  EXPECTED_XOR
};

// Stores the possible types of chips to be called by Menu
enum ChipType {
  ONE_INPUT_CHIP,
  TWO_INPUT_CHIP,
  THREE_INPUT_CHIP,
  FOUR_INTPUT_CHIP
};

// defines ChipConfiguration to be used in ChipMenuEntry struct as a variable
union ChipConfiguration {
  const HexOneInputChipConfig* oneInput;
  const QuadTwoInputChipConfig* twoInput;
  //ThreeInputChipConfig threeInput;
  //FourInputChipConfig fourInput;
};

struct ChipMenuEntry {
  const char* name;
  enum ChipType ctype;
  ChipConfiguration config;
};



// **********************************
// * setup and loop functions below *
// **********************************


void setup(){
  Serial.begin(9600);
  Serial.setTimeout(MAXIMUM_WAIT_TIME);
}


// =================================
// loop is EMPTY FOR NOWWWWWWW
// =================================
void loop() {
  printMainMenu();




}

// **********************************
// * Logic Chip Functions below     *
// **********************************


/**
Tests a 2-input logic gate's all possible states (2^2 total.)
- return struct TwoInputTruthTable with output values
*/
TwoInputTruthTable readTwoInputGate(int pinA, int pinB, int pinY) {
  TwoInputTruthTable result;

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delayMicroseconds(DELAY_TIME);
  result.output00 = digitalRead(pinY);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  delayMicroseconds(DELAY_TIME);
  result.output01 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  delayMicroseconds(DELAY_TIME);
  result.output10 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  delayMicroseconds(DELAY_TIME);
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
  delayMicroseconds(DELAY_TIME);
  result.output0 = digitalRead(pinY);

  digitalWrite(pinA, HIGH);
  delayMicroseconds(DELAY_TIME);
  result.output1 = digitalRead(pinY);

  return result;
}

/**
Tests a full hexa 1-input logic chip recording all scenarios inside a structure HexOneInputMeasurements
*/
HexOneInputMeasurements measureHexOneInputChip(const HexOneInputChipConfig& chip) {

  HexOneInputMeasurements results;

  results.gates[0] = readOneInputGate(chip.gatePins[0].inputPin, chip.gatePins[0].outputPin);
  results.gates[1] = readOneInputGate(chip.gatePins[1].inputPin, chip.gatePins[1].outputPin);
  results.gates[2] = readOneInputGate(chip.gatePins[2].inputPin, chip.gatePins[2].outputPin);
  results.gates[3] = readOneInputGate(chip.gatePins[3].inputPin, chip.gatePins[3].outputPin);
  results.gates[4] = readOneInputGate(chip.gatePins[4].inputPin, chip.gatePins[4].outputPin);
  results.gates[5] = readOneInputGate(chip.gatePins[5].inputPin, chip.gatePins[5].outputPin);
  
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
void configureOneInputGatePins(const OneInputGatePins layout[6]) {

  // Prepares pins for a hexa single input gate chip
 for (int i=0; i < 6; i++){
  pinMode(layout[i].inputPin, OUTPUT);
  pinMode(layout[i].outputPin, INPUT);
 }
}

// ===============================================================

// === Actual chips testing functions below ===

/**
Returns true if all gates in the parameter chip match the expected
result of the expected truth tables.Tests Quad Two input chips
*/
bool testQuadTwoInputChip(const QuadTwoInputChipConfig& chip){
  
  configureTwoInputGatePins(chip.gatePins);
  QuadTwoInputMeasurements actual = measureQuadTwoInputChip(chip);
  
  return compareQuadTwoInputTruthTable(actual, chip.expectedTruthTable);
}


/**
Returns true if all gates in the parameter chip match the expected
result of the expected truth tables.Tests Hex One input chips
*/
bool testHexOneInputChip(const HexOneInputChipConfig& chip){
  configureOneInputGatePins(chip.gatePins);
  HexOneInputMeasurements actual = measureHexOneInputChip(chip);

  return compareHexOneInputTruthTable(actual, chip.expectedTruthTable);
}

// ************************************
// * Chip Testing functions below     *
// ************************************


//Tests the hexa 1-input gate chip SN74LS05N(NOT), returns true if chip PASSED.
bool test_SN74LS05N(){
  return testHexOneInputChip(SN74LS05N);
}
//Tests the Quad 2-input gate chip SN74LS00N(NAND), returns true if chip PASSED.
bool test_SN74LS00N(){
  return testQuadTwoInputChip(SN74LS00N);
}
//Tests the Quad 2-input gate chip SN74LS02N(NOR), returns true if chip PASSED.
bool test_SN74LS02N(){
  return testQuadTwoInputChip(SN74LS02N);
}
//Tests the Quad 2-input gate chip SN74LS08N(AND), returns true if chip PASSED.
bool test_SN74LS08N(){
  return testQuadTwoInputChip(SN74LS08N);
}
//Tests the Quad 2-input gate chip SN74LS32N(OR), returns true if chip PASSED.
bool test_SN74LS32N(){
  return testQuadTwoInputChip(SN74LS32N);
}

//Tests the Quad 2-input gate chip SN74LS86N(XOR), returns true if chip PASSED.
bool test_SN74LS86N(){
  return testQuadTwoInputChip(SN74LS86N);
}


// **********************************
// * Serial functions below     *
// **********************************

void refreshScreen(){
  for (int i=0;i < 30; i++){
    Serial.println();
  }
}

void printMainMenu(){
  Serial.println("*************************************");
  Serial.println("Author: Kemuel Bermudez-Cotto");
  Serial.println("Date: 07/20/2026");

  Serial.println("**************************");
  Serial.println("* Logic Chips Tester v0  *");
  Serial.println("**************************");

  Serial.println("*************************************");
  Serial.println();
  Serial.flush();

  printMenuOptions();
}

void displaySupportedChips();


/**
Returns a ChipMenuEntry object for a Two Input Chip
*/
ChipMenuEntry makeTwoInputEntry(const char* name, const QuadTwoInputChipConfig* config){
  ChipMenuEntry entry;

  entry.name = name;
  entry.ctype = TWO_INPUT_CHIP;
  entry.config.twoInput = config;

  return entry;
}

/**
Returns a ChipMenuEntry object for a One Input Chip
*/
ChipMenuEntry makeOneInputEntry(const char* name, const HexOneInputChipConfig* config){
  ChipMenuEntry entry;

  entry.name = name;
  entry.ctype = ONE_INPUT_CHIP;
  entry.config.oneInput = config;

  return entry;
}

// Array to hold all chip entries for the Display Menu
const ChipMenuEntry supportedChips[] = {
  makeTwoInputEntry("SN74LS00N", &SN74LS00N),
  makeTwoInputEntry("SN74LS02N", &SN74LS02N),  
  makeOneInputEntry("SN74LS05N", &SN74LS05N),
  makeTwoInputEntry("SN74LS08N", &SN74LS08N),
  makeTwoInputEntry("SN74LS32N", &SN74LS32N),
  makeTwoInputEntry("SN74LS86N", &SN74LS86N)
  
}; 

bool testChipFromMenu(const ChipMenuEntry* entry){
  
  switch (entry->ctype){
    case TWO_INPUT_CHIP:
      return testQuadTwoInputChip(*entry->config.twoInput);
      break;
    
    case ONE_INPUT_CHIP:
      return testHexOneInputChip(*entry->config.oneInput);
      break;
    default:
      Serial.println("Unsupported chip type");
      return false;
  }
}

void displaySupportedChips(){

  int n = sizeof(supportedChips)/ sizeof(supportedChips[0]);

  for (int i=0; i < n; i++){
    Serial.print(i +1);
    Serial.print(". ");
    Serial.println(supportedChips[i].name);
  }
}


void printMenuOptions(){

  int selectedOption = -1;

  while (selectedOption != 3){
    Serial.println("Options:");
    Serial.println("1. Test known chip");
    Serial.println("2. Test unknown chip (NOT IMPLEMENTED)");
    Serial.println("3. Exit Program");
    Serial.println();
    Serial.println("Selected Option: \n");
    
    if (selectedOption != 1 && selectedOption != 2 && selectedOption != 3){
      Serial.println("The value provided is not valid");
      Serial.print("Value: ");
      Serial.println(selectedOption);
      Serial.println();
    }

    if (selectedOption == 1){
      displaySupportedChips();
    
      unsigned int selectedChipOption = Serial.parseInt();

      switch (selectedChipOption){
        case 1:
          Serial.println(testChipFromMenu(&supportedChips[0]));
          break;
        
        case 2:
          Serial.println(testChipFromMenu(&supportedChips[1]));
          break;

        case 3:
          Serial.println(testChipFromMenu(&supportedChips[2]));
          break;

        case 4:
          Serial.println(testChipFromMenu(&supportedChips[3]));
          break;

        case 5:
          Serial.println(testChipFromMenu(&supportedChips[4]));
          break;

        case 6:
          Serial.println(testChipFromMenu(&supportedChips[5]));
          break;

        default:
          Serial.println("Chip not available for testing");
          break;
      }
    }

    if (selectedOption == 2){
      Serial.println("Featured not implemented\n");
    }
    if (selectedOption == 3){
      Serial.println("Program Exiting...");
      while(true){ // code stops HERE
      }
    }
  }
}
