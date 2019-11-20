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
 *                 This file contains the class definition. 
 * References:
 *                Practice statement:
 *                https://campusvirtual.ull.es/1920/pluginfile.php/188731/mod_assign/introattachment/0/CYA_1920_Practica_9.pdf?forcedownload=1
 * Revision history:
 *                17/11/2019 - Creation (first version) of the code
 */


#ifndef PRACTICE9_GRAMMAR_H
#define PRACTICE9_GRAMMAR_H


#include <iostream>
#include <sstream>

//#include "Nfa.h"
#include "GSymbols.h"
#include "Production.h"

const char NEWLINE = '\n';
const std::string STICK = "|";
const std::string ARROW = "->";
const std::string FINAL = "f";
const std::string COMMENT = "//";

class Grammar {
  public:
    Grammar (GSymbols terminals, GSymbols nonTerminals, std::string starSymbol, std::set<Production> Productions);
    Grammar (std::string& grammarDefinition);
    ~Grammar ();

    /**
    * @brief Generates an NFA from the grammar read.
    * @return the nfa resulting from the conversion.
    */
  //  Nfa convertToNFA();

    /**
    * @brief Prints the Grammar in the outputFile.
    * @param ouputFile Contains the name of the output file.
    */
		void printGrammar(std::string& outputFile);

    /**
    * @brief converts the current Grammar to the Chomsky Normal Form
    * @return the grammar in Chomsky Normal Form
    */
    Grammar convertToCNF();


    Grammar& operator=(const Grammar& grammar);
  
	private:
    GSymbols getTerminals() const;
    //std::set<char> getNonTerminals() const;
    //std::string getstartSymbol() const;
    std::set<Production> getProductions() const;

    void insertProduction(Production auxProduction);
    void insertNonTerminal(char newNonterminal);
   
    /**
    * @brief Reads the grammar description of the input file and builds the grammar.
    * @param inputFile is the file that constains the Grammar description.
    */
    void readAndBuildGrammar(std::string& grammarDefinition);
    
    /**
    * @brief Is the first loop of the Chomsly Normal Form algorithm.
    */
    void firstCNF(Grammar& grammar);

    /**
    * @brief generates a new nonTerminal for a new production
    */
    char generateNonTerminal(char currentTerminal);
     
		GSymbols        terminals_;         //!< Represents the set of terminals of the grammar.
    GSymbols     nonTerminals_;         //!< Represents the set of non terminals of
                                        //!< the grammar.
    std::string    startSymbol_;        //!< Is the boot symbol.
    std::set<Production> productions_;  //!< Is the set of productions of the
                                        //!< Grammar.
};

#endif  //PRACTICE9_GRAMMAR_H
