/**
 * @Author Basilio Gómez Navarro
 * @date 17/11/2019
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 9 - Chomsky Normal Form of a Context Free Grammar.
 * Email: alu101049151@ull.edu.es
 * Production.h file: Production class. It represents a Free Context Grammar
 *                    production.
 *                    This file contains the class implementation. 
 * References:
 *                Practice statement:
 *                https://campusvirtual.ull.es/1920/pluginfile.php/188731/mod_assign/introattachment/0/CYA_1920_Practica_9.pdf?forcedownload=1
 * Revision history:
 *                17/11/2019 - Creation (first version) of the code
 */

#include "Production.h"

Production::Production () {}

/**
* Parameter constructor that receives a non-terminal (leftPart)
* and a string of grammatical symbols (rightPart).
*/
Production::Production (char leftPart, std::string rightPart): 
  leftPart_(leftPart),
  rightPart_(rightPart) {}


Production::Production (const Production& production): 
  leftPart_(production.leftPart_),
  rightPart_(production.rightPart_) {}

Production:: ~Production () {}


/**
* Returns the non-terminal that is on the left side of the production.
*/
char Production::getLeftPart () const {
  return leftPart_;
}


/**
* Returns the string of grammatical symbols that is on the right side 
* of the production rule.
*/
std::string Production::getRightPart () const {
  return rightPart_;
}


/**
* Allows modify the non-terminal on the right of the production rule.
*/
void Production::setLeftPart (char leftPart) {
  leftPart_ = leftPart;
}



/**
* Allows to set the grammatical symbols string of the right side.
*/
void Production::setRightPart (std::string& auxStr) {
  rightPart_ = auxStr;
}


int Production::operator< (const Production& production) const {
  if (this->leftPart_ == production.leftPart_) return 1;
  if (this->leftPart_ < production.leftPart_) return 1;
  return 0;
}
