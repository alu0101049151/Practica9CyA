/**
 * @Author Basilio Gómez Navarro
 * @date 17/11/2019
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 9 - Chomsky Normal Form of a Context Free Grammar.
 * Email: alu101049151@ull.edu.es
 * GSymbols.h file: GSymbols class. It representes a set of grammatical 
 *                  symbols, in this case, it can be a set of terminal symbols
 *                  or a set of non-terminal symbols)
 *                  This file contains the class implementation. 
 * References:
 *                Practice statement:
 *                https://campusvirtual.ull.es/1920/pluginfile.php/188731/mod_assign/introattachment/0/CYA_1920_Practica_9.pdf?forcedownload=1
 * Revision history:
 *                17/11/2019 - Creation (first version) of the code
 */


 #include "GSymbols.h"


GSymbols::GSymbols () {}

GSymbols::~GSymbols () {}

/**
* Inserts the symbol passed as a parameter in the alphabet. 
*/
void GSymbols::insertGSymbols (const char symbol) {
	gramSymbols_.insert(symbol);
}

/**
* @brief returns alphabet.
*/
std::set<char> GSymbols::getGSymbols() const {
  return gramSymbols_;
}

/**
* @brief check if a symbol belongs tot the alphabet.
* @return true if it belongs or false if not.
*/
bool GSymbols::checkIfBelongs(char toCheck) {
  bool belong = false;
  for (auto i: gramSymbols_) {
    if (i == toCheck)
      belong = true;
  }
  return belong;
}

GSymbols& GSymbols::operator= (const GSymbols &symbols) {
  this->gramSymbols_ = symbols.gramSymbols_;
  return *this;
}

