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
 *                  This file contains the class definition.
 * References:
 *                Practice statement:
 *                https://campusvirtual.ull.es/1920/pluginfile.php/188731/mod_assign/introattachment/0/CYA_1920_Practica_9.pdf?forcedownload=1
 * Revision history:
 *                17/11/2019 - Creation (first version) of the code
 */

#ifndef PRACTICE9_GSYMBOLS_H
#define PRACTICE9_GSYMBOLS_H

#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

class GSymbols {
	
	public:
		GSymbols ();
		~GSymbols ();

		/**
		* @brief inserts a new symbol into the alphabet.
		* @param symbol is the new symbol to insert.
		*/
		void insertGSymbols (const char symbol);

    /**
    * @brief returns alphabet.
    */
    std::set<char> getGSymbols() const;

    /**
    * @brief check if a symbol belongs tot the alphabet.
    * @return true if it belongs or false if not.
    */
    bool checkIfBelongs(char toCheck);

    GSymbols& operator= (const GSymbols &gsymbols);

	private:
		std::set<char> gramSymbols_; //!< Represents the set of grammatical symbols. 
};

#endif //PRACTICE9_GSYMBOLS_H

