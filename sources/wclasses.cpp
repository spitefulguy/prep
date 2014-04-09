/*
 * wclasses.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: alex
 */

#include "wclasses.hpp"
#include <iostream>
using namespace std;

WClasses::WClasses(boost::filesystem::path p_preposition,
	boost::filesystem::path p_stopWords,
	boost::filesystem::path p_nouns) {

	if (checkPath(p_preposition) == -1) return;
	if (checkPath(p_stopWords) == -1) return;
	if (checkPath(p_nouns) == -1) return;

	stopWords = getFileContent(p_stopWords);
	nouns = getFileContent(p_nouns);
	prepositions = getFileContent(p_preposition);

	cout << "Prepositions loaded: " << prepositions.size() << "\n";
	cout << "Nouns loaded: " << nouns.size() << "\n";
	cout << "Stop words loaded: " << stopWords.size() << "\n";
}

bool WClasses::isNoun(std::string word) {
	set <string>::iterator it;
	it = nouns.find(word);
	return it == nouns.end() ? false : true;
}

bool WClasses::isPreposition(std::string word){
	//cout << word << "\n";
	set <string>::iterator it;
	it = prepositions.find(word);
	//cout << word << (it == prepositions.end() ? false : true) << "\n";
	return it == prepositions.end() ? false : true;
}

bool WClasses::isStopWord(std::string word){
	set <string>::iterator it;
	it = stopWords.find(word);
	return it == stopWords.end() ? false : true;
}

bool WClasses::isNoun(char *s_word) {
	string word;
	word.assign(s_word);
	return isNoun(word);
}

bool WClasses::isPreposition(char *s_word){
	string word;
	word.assign(s_word);
	return isPreposition(word);
}

bool WClasses::isStopWord(char *s_word){
	string word;
	word.assign(s_word);
	return isStopWord(word);
}


set<string> WClasses::getFileContent(boost::filesystem::path path){

	boost::filesystem::ifstream ifs_content(path);
	string content;
	set<string> set_content;
	while (getline(ifs_content, content)) {
		if (content.length()) {
			set_content.insert(content);
		}
	}
	return set_content;
}

int WClasses::checkPath(const boost::filesystem::path p) {

using namespace boost::filesystem;

	try {
		if (exists(p)) {
			if (!is_directory(p)){
				return 0;
			} else {
				cout << p << " exists, but is neither a regular file nor a directory\n";
			}
		}
		else {
		  cout << p << " does not exist\n";
		}
	} catch (const filesystem_error& ex){
		cout << ex.what() << '\n';
	}
	return -1;
}


//set<string> WClasses::Resources::getNouns(boost::filesystem::path p_nouns) {
//	ifstream ifs_nouns(p_nouns.c_str());
//	string str_noun;
//	string buf;
//	set<string> set_nouns;
//
//
//	while (getline(ifs_nouns, str_noun)) {
//		if ( str_noun.length() ) {
//			size_t space_pos = str_noun.find_first_of(' ');
//			str_noun.erase(space_pos, str_noun.length() - space_pos);
//			size_t underline_pos;
//
//			while ( str_noun.length() ){
//				underline_pos = str_noun.find_last_of('_');
//
//				if (underline_pos == string::npos) {
//					set_nouns.insert( str_noun );
//					break;
//				}
//
//				buf = str_noun.substr(underline_pos + 1) ;
//				set_nouns.insert( buf );
//				str_noun.erase(underline_pos, str_noun.length() - underline_pos);
//			}
//		}
//	}
//
//	return set_nouns;
//}


