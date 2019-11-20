/**
 * @Author Basilio Gómez Navarro
 * @date 17/11/2019
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 9 - Chomsky Normal Form of a Context Free Grammar.
 * Email: alu101049151@ull.edu.es
 * Grammar.h file: Grammar class. It representes a Free Context Grammar.
 *                 This file contains the class implementation. 
 * References:
 *                Practice statement:
 *                https://campusvirtual.ull.es/1920/pluginfile.php/188731/mod_assign/introattachment/0/CYA_1920_Practica_9.pdf?forcedownload=1
 * Revision history:
 *                17/11/2019 - Creation (first version) of the code
 */


#include "Grammar.h"

Grammar::Grammar (std::string& grammarDefinition) {
  readAndBuildGrammar(grammarDefinition);
}

Grammar::~Grammar () {}

/**
* Reads the grammar description of the input file and builds the grammar.
*/
void Grammar::readAndBuildGrammar(std::string& grammarDefinition) {
  std::ifstream inputFile;
  inputFile.open(grammarDefinition);

  if (!inputFile.is_open()) {
    std::cerr << "There was a problem opening the input file, please, try ";
    std::cerr << "again." << NEWLINE;
  }
  else {
    std::string read;  // stores what is read every time a line is read, in the fil
    bool isComment = true;

  //================================================
  // Reading header comments
  //================================================
    int pos;

    while (isComment) {
      std::getline(inputFile, read);
      pos = read.find(COMMENT);

      if (pos == 0)
        isComment = true;
      else 
        isComment = false;
    }

    int temp; // Used for store the amounts (alphabet size, number of states
              // etc.) temporarily

  //================================
  // Reading the alphabet symbols
  //================================
    // 'read' contains now Read the number of alphabet symbols
    temp = stoi(read);
    read.clear();
    char auxChar;

    for (int i = 0; i < temp; i++) {
      std::getline(inputFile, read);
      auxChar = read[0];
      terminals_.insertGSymbols(auxChar);
      read.clear();
    }

    //==============================
    // Reading of non-terminals
    //==============================
     std::getline(inputFile, read);  // Read the number of non-terminals.
     temp = stoi(read);
     read.clear();

     for (int i = 0; i < temp; ++i) {
       std::getline(inputFile, read);
       auxChar = read[0];
       nonTerminals_.insertGSymbols(auxChar);
       read.clear();
     }

     //==============================
     // Reading of start symbol
     //==============================
     std::getline(inputFile, read); // Read the star symbol.
     startSymbol_ = read;
     read.clear();

     //================================
     // Reading grammar productions
     //================================
     std::getline(inputFile, read); // Read the number of productions.
     temp = stoi(read);
     read.clear();

     char auxNonTerminal;
     std::string auxString;
     std::string auxGrammaticalSymb; // Temporarily stores the strings of grammar
                                    // symbols read.
     for (int i = 0; i < temp; ++i) {
       std::getline(inputFile, read);
       std::stringstream iss(read);

       iss >> auxString;
       auxNonTerminal = auxString[0]; // Read nonTerminal at the left part of the production rule.
       
       iss >> auxGrammaticalSymb;  // Read the arrow.
       auxGrammaticalSymb.clear();

       iss >> auxGrammaticalSymb;

       Production auxProduction(auxNonTerminal, auxGrammaticalSymb);
       productions_.insert(auxProduction);
     }
  }
}


/**
* Generates an NFA from the grammar read.
*/
/*
Nfa Grammar::convertToNFA() {

  // Generate the states set
  std::set<State> auxStates;
  for (auto i: nonTerminals_.getAlphabet()) {
    std::string auxStr(1, i);
    State auxState(auxStr);
    auxStates.insert(auxState);
  }
  State finalState(FINAL);
  auxStates.insert(finalState);

  // Generate the final statets set only with de state 'f'.
  std::set<std::string> auxFinalStates;
  auxFinalStates.insert(FINAL);

  // Start State will have the same id as Start Symbol.
  // The alphabet will be the same as Terminals + the epsilon.
  Alphabet auxAlphabet = terminals_;
  auxAlphabet.insertAlphabet(EPSILON);

  // Generate the set of transitions of the NFA.
  std::set<Transition> auxTransitions;

  char auxInput;
  std::string auxDestination;
  std::string auxProduction;

  for (auto i: productions_) {
   std::string auxCurrent(1, i.getLeftPart());

auxProduction = i.getRightPart();

    switch (auxProduction.size()) {
      case 1:   // If it only contains a grammatical symbol.
      {
        if (auxAlphabet.checkIfBelongs(auxProduction[0])) { // If the symbol is terminal
          auxInput = auxProduction[0];
          auxDestination = FINAL;
          
          // Generate the new transition:
          Transition auxTransition(auxInput, auxCurrent, auxDestination);
          auxTransitions.insert(auxTransition);
        }
        else if (nonTerminals_.checkIfBelongs(auxProduction[0])) { // If the symbol is non-terminal
          auxInput = EPSILON;
          auxDestination = auxProduction.substr(0,1);
          
          // Generate the new transition:
          Transition auxTransition(auxInput, auxCurrent, auxDestination);
          auxTransitions.insert(auxTransition);
        }
        auxCurrent.clear();
        auxDestination.clear();
        break;
      }
      case 2:  // If it contains two grammatical symbols.
      {
        bool isTerminal = auxAlphabet.checkIfBelongs(auxProduction[0]);
        bool isNonTerminal = nonTerminals_.checkIfBelongs(auxProduction[1]);

        if (isTerminal && isNonTerminal) {
          auxInput = auxProduction[0];
          auxDestination = auxProduction.substr(1,2);
          
          // Generate the new transition:
          Transition auxTransition(auxInput, auxCurrent, auxDestination);
          auxTransitions.insert(auxTransition);
        }
        auxCurrent.clear();
        auxDestination.clear();
        break;
      }
      default: // If it contains more than two grammatical symbols.
      {
        int j;
       
       for (j = 0; j < auxProduction.size(); ++j) {
        
        bool isTerminal = auxAlphabet.checkIfBelongs(auxProduction[j]);
        bool isTerminalToo = auxAlphabet.checkIfBelongs(auxProduction[j + 1]);
        bool isNonTerminal = nonTerminals_.checkIfBelongs(auxProduction[j]);
        bool isLastNonTerminal = nonTerminals_.checkIfBelongs(auxProduction[j + 1]);
          
          if (j < auxProduction.size() - 1) {
            if (isTerminal && isTerminalToo) { // If is a subsequence like aa...
              auxInput = auxProduction[j];   // Input

              std::string auxStateId = std::to_string(j); // New state Id
              State auxState(auxStateId);  // Generate new state
              auxStates.insert(auxState);
              
              auxDestination = auxStateId;  // Destination is the new state generated
              
              // Generate the new transition:
              Transition auxTransition(auxInput, auxCurrent, auxDestination);
              auxTransitions.insert(auxTransition);

              auxCurrent = auxDestination;  // Now the current state is the Destination state
            }
            else if (isTerminal && isLastNonTerminal) { // If is the last non-Terminal
              auxInput = auxProduction[j];   // New Input.
              auxDestination = auxProduction.substr(j + 1,1); // New Destination.

              // Generate the new transition:
              Transition auxTransition(auxInput, auxCurrent, auxDestination);
              auxTransitions.insert(auxTransition);

              auxCurrent = auxDestination;  // Now the current state is the Destination state
            }
          }
          else if (j == auxProduction.size() - 1) {
            if (isTerminal) {
              auxInput = auxProduction[j];
              auxDestination = FINAL;

              // Generate the new transition:
              Transition auxTransition(auxInput, auxCurrent, auxDestination);
              auxTransitions.insert(auxTransition);
            }
          }
        }
        auxCurrent.clear();
        auxDestination.clear();
        break;
      }
    }
  }
  Nfa nfa(startSymbol_, auxStates, auxFinalStates, auxAlphabet, auxTransitions);
  return nfa;
}
*/


void Grammar::printGrammar(std::string& outputFile) {
	std::ofstream outputGrammar;
	outputGrammar.open(outputFile);

	outputGrammar << terminals_.getGSymbols().size() << NEWLINE;
	for (auto i: terminals_.getGSymbols()) {
		outputGrammar << i << NEWLINE;
	}

	outputGrammar << nonTerminals_.getGSymbols().size() << NEWLINE;
  for (auto i: nonTerminals_.getGSymbols()) {
    outputGrammar << i << NEWLINE;
  }

	outputGrammar << startSymbol_ << NEWLINE;

	outputGrammar << productions_.size() << NEWLINE;
	for (auto i: productions_) {
		outputGrammar << i.getLeftPart() << " " <<  ARROW << " " << i.getRightPart() << NEWLINE;
	}
}



