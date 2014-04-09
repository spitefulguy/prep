/*
 * cmp.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: alex
 */

#include "cmp.hpp"
#include "stemmer.hpp"

#include <iostream>
using namespace std;


CMP::CMP(WClasses *wclasses) {
	this->wclasses = wclasses;
}

void CMP::printResult(list <Finding> findings) {
	if (!findings.size()) return;

	list <Finding>::iterator it = findings.begin();

	while ( it != findings.end() ){

		cout << (*it).preposition_1 << "/" << (*it).preposition_2 << " " << (*it).noun << "\n";
		cout << (*it).sentence_1 << "\n" << (*it).sentence_2 << "\n\n";
		it++;
	}
}

void CMP::printResult(vector <Finding> findings) {
	if (!findings.size()) return;

	vector <Finding>::iterator it = findings.begin();

	while ( it != findings.end() ){

		cout << (*it).preposition_1 << "/" << (*it).preposition_2 << " " << (*it).noun << "\n";
		cout << (*it).sentence_1 << "\n" << (*it).sentence_2 << "\n\n";
		it++;
	}
}

list<Phrase> CMP::getPhrase(boost::filesystem::path path){

		list <Phrase> list_Phrase;

		char buf[BUF_SIZE];
		boost::filesystem::ifstream infile(path);

		int i = 0;
		size_t offset = 0;
		char c;
		char pre_c = '\0';
		do {
			pre_c = c;
			infile.get(c);
			offset++;
			if (!(strchr(".!?;", c) || (c == pre_c && c == '\n'))) {
				buf[i] = c;
				i++;

			} else {
				buf[i] = c;
				buf[i + 1] = '\0';
				i = 0;
				if ( i == BUF_SIZE ) {
					cout << "ERROR: getPhrase() buffer out of range\n";
				}
				proccessSentence(buf, list_Phrase, offset, path);

			}
		} while (infile.good()) ;

		return list_Phrase;
}

void CMP::proccessSentence(char *s_sentence,
		list<Phrase> &list_Phrase,
		size_t offset,
		boost::filesystem::path path){

	Phrase Phrase;

	string noun;

	char c;
	char word[WORD_MAX_SIZE];
	int i = 0;
	int j = 0;

	//cout << s_sentence << "\n";

	while ( (c = s_sentence[j++]) ) {

		if (strchr(WORD_DELIMETERS, c)) {
			word[i] = '\0';
			i = 0;
			if (wclasses->isPreposition(word)) {
				noun = findNoun(s_sentence + j);

				if (noun.length()) {
					//cout << word << " " << noun << "\n";
					Phrase.noun = noun;
					Phrase.preposition.assign(word);
					Phrase.path = path;
					Phrase.sentence.assign(s_sentence);
					list_Phrase.push_back(Phrase);
				}
			}
		} else {
			word[i++] = tolower(c);
		}
		if ( i == WORD_MAX_SIZE ) {
			cout << "ERROR: proccessSentence() buffer out of range\n";
		}
	}
}

list <Finding> CMP::compare(boost::filesystem::path file_1, boost::filesystem::path file_2) {
	list <Phrase> Phrases_1;
	list <Phrase> Phrases_2;

	Phrases_1 = getPhrase(file_1);
	Phrases_2 = getPhrase(file_2);

	cout << "Phrase found in " << file_1.c_str() << " : " << Phrases_1.size() << "\n";
	cout << "Phrase found in " << file_2.c_str() << " : " << Phrases_2.size() << "\n";

	list<Finding> result;
	result = findIntersection(Phrases_1, Phrases_2);
	cout << "Differences found: " << result.size() << "\n";

	list <Finding>::iterator it;
	it = result.begin();

	return result;
}

list <Finding> CMP::findIntersection(list<Phrase> list_1, list<Phrase> list_2) {

	list <Finding> result;

	list <Phrase>::iterator it_1;
	list <Phrase>::iterator it_2;
	it_1 = list_1.begin();
	it_2 = list_2.begin();
	//ssize_t count = 0;

	while (it_1 != list_1.end()) {
		it_2 = list_2.begin();
		while (it_2 != list_2.end()) {
			//count++;;
			if ((*it_1).noun == (*it_2).noun &&
					(*it_1).preposition != (*it_2).preposition) {
				Finding finding;

				finding.noun = (*it_1).noun;

				finding.preposition_1 = (*it_1).preposition;
				finding.sentence_1 = (*it_1).sentence;

				finding.sentence_2 = (*it_2).sentence;
				finding.preposition_2 = (*it_2).preposition;

//				if ( (*it_1).preposition < (*it_2).preposition ) {
//					finding.preposition_1 = (*it_1).preposition;
//					finding.sentence_1 = (*it_1).sentence;
//
//					finding.sentence_2 = (*it_2).sentence;
//					finding.preposition_2 = (*it_2).preposition;
//				} else {
//					finding.preposition_1 = (*it_2).preposition;
//					finding.sentence_1 = (*it_2).sentence;
//
//					finding.sentence_2 = (*it_1).sentence;
//					finding.preposition_2 = (*it_1).preposition;
//				}

				result.push_back(finding);
			}
			it_2++;
		}
		it_1++;
	}
	//cout << count << endl;
	return result;
}

string CMP::findNoun(char *s_sentence) {
	string noun;
	Stemmer stemmer;

	//noun = stemmer.stem(noun);

	char word[WORD_MAX_SIZE];
	int i = 0;
	int words_count = 0;

	do {
		if (strchr(WORD_DELIMETERS, s_sentence[0])) {
			word[i] = '\0';
			if (words_count == MAX_WORDS_RIGTH) return noun;
			words_count++;

			//cout << word << " -- " ;
			//stemmer.stem(word);
			//cout << word << "\n";


			if (wclasses->isPreposition(word)){
				return noun;
			}
			if (wclasses->isStopWord(word)){
				i = 0;
				continue;
			}
			//if (wclasses->isNoun(word)) {
				noun.assign(word, i);
				return noun;
			//}
			i = 0;
		} else {
			word[i++] = tolower(s_sentence[0]);
		}
	} while ( *(s_sentence++) );
	return noun;
}


