/*
 * stemmer.hpp
 *
 *  Created on: Mar 5, 2014
 *      Author: alex
 */

#ifndef STEMMER_HPP_
#define STEMMER_HPP_

#include <string>

class Stemmer {

public:
	std::string stem(std::string str);
	void stem(char *s_word);
private:
	char * b;       /* buffer for word to be stemmed */
	int k,k0,j;     /* j is a general offset into the string */

	int cons(int i);

	int m();

	int vowelinstem();

	int doublec(int j);

	int cvc(int i);

	int ends(char * s);

	void setto(char * s);

	void r(char * s) { if (m() > 0) setto(s); };

	void step1ab();

	void step1c();

	void step2();

	void step3();

	void step4();

	void step5();

	int stem(char * p, int i, int j);
};


#endif /* STEMMER_HPP_ */
