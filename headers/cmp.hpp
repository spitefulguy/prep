/*
 * cmp.hpp
 *
 *  Created on: Mar 7, 2014
 *      Author: alex
 */

#ifndef CMP_HPP_
#define CMP_HPP_

#include <boost/filesystem.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/seek.hpp>

#include <set>
#include <list>

#include "wclasses.hpp"

#define WORD_DELIMETERS " ,:;.()/\n"
#define MAX_WORDS_RIGTH 3

struct Phrase {
	std::string preposition;
	std::string noun;
	boost::filesystem::path path;
	std::string sentence;
//	ssize_t offSentenceInFile;
//	ssize_t offPhraseInSentence;
};

struct Finding {
	std::string preposition_1;
	std::string preposition_2;
	std::string noun;
	std::string sentence_1;
	std::string sentence_2;
//	boost::filesystem::path path_1;
//	boost::filesystem::path path_2;
//	ssize_t offSentenceInFile_1;
//	ssize_t offPhraseInSentence_1;
//	ssize_t offSentenceInFile_2;
//	ssize_t offPhraseInSentence_2;
};

class CMP {
	static const int WORD_MAX_SIZE = 256;
	static const int BUF_SIZE = 4096;
	WClasses *wclasses;

public:
	CMP(WClasses *wclasses);
	std::list <Finding> compare(boost::filesystem::path file1, boost::filesystem::path file2);
	void printResult(std::list <Finding>);
	void printResult(std::vector <Finding>);

private:
	std::list <Finding> findIntersection(std::list<Phrase>, std::list<Phrase>);
	void proccessSentence(char *s_sentence,
			std::list<Phrase> &set_Phrase,
			size_t offset,
			boost::filesystem::path path);
	std::list<Phrase> getPhrase(boost::filesystem::path path);
	std::string findNoun(char *);

};


#endif /* CMP_HPP_ */
