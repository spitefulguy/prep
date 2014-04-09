/*
 * stats.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: alex
 */

#include "stats.hpp"
#include <algorithm>
using namespace std;

bool Stats::comparator(const Finding &f1, const Finding &f2){
	if (f1.noun < f2.noun) return true;
	if (f1.noun > f2.noun) return false;

	if (f1.preposition_1 < f2.preposition_1) return true;
	if (f1.preposition_1 > f2.preposition_1) return false;

	if (f1.preposition_2 < f2.preposition_2) return true;
	if (f1.preposition_2 > f2.preposition_2) return false;

	return false;
}

void Stats::addElements(list<Finding> f) {
	this->elements.insert(this->elements.end(), f.begin(), f.end());
}

vector<Finding> Stats::getElements() {
	cout << "Normalizing results...\n";
	sort(this->elements.begin(), this->elements.end(), comparator);
	this->removeInvertedDublicates();

	return this->elements;
}

void Stats::removeInvertedDublicates(){
	string word;
	vector<Finding> sameWord;
	vector<Finding> cleanElements;

	//cout << "in removeInvertedDublicates\n";
	//return;
	for (vector<Finding>::iterator it = this->elements.begin() ; it != this->elements.end();){
		word = (*it).noun;
		cout << word << endl;
		string t;
		vector<Finding>::iterator itSameWord = it;;
		sameWord.clear();
		while ( itSameWord < this->elements.end() ){
			t = (*itSameWord).noun;
			//cout << t << endl;
			if ( word != t ) break;
			itSameWord++;
		}
		sameWord.insert(sameWord.begin() ,it, itSameWord);
		it += sameWord.size();

		for (itSameWord = sameWord.begin(); itSameWord != sameWord.end(); itSameWord++){
			bool dublicateFound = false;
			for (vector<Finding>::iterator itSameWordInner = itSameWord;
					itSameWordInner != sameWord.end(); itSameWordInner++ ) {
				if ((*itSameWord).preposition_1 == (*itSameWordInner).preposition_2 &&
						(*itSameWord).preposition_2 == (*itSameWordInner).preposition_1) {
					dublicateFound = true;
					cout << (*itSameWord).noun << endl;
//					cout << (*itSameWord).preposition_1 << "/" << (*itSameWord).preposition_2 << " " << (*itSameWord).noun << "\n";
//					cout << (*itSameWord).sentence_1 << "\n" << (*itSameWord).sentence_2 << "\n\n";
//					cout << "----------------------------------" << endl;
//					cout << (*itSameWordInner).preposition_1 << "/" << (*itSameWordInner).preposition_2 << " " << (*itSameWordInner).noun << "\n";
//					cout << (*itSameWordInner).sentence_1 << "\n" << (*itSameWordInner).sentence_2 << "\n\n";
				}

			}
			if (!dublicateFound) {
				cleanElements.insert(cleanElements.end(), *itSameWord);
			}
		}
	}

	this->elements = cleanElements;

}

size_t Stats::size() {
	return this->elements.size();
}








