/*
 * wclasses.hpp
 *
 *  Created on: Mar 5, 2014
 *      Author: alex
 */

#ifndef WCLASSES_HPP_
#define WCLASSES_HPP_

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <set>

class WClasses {

	std::set<std::string> stopWords;
	std::set<std::string> nouns;
	std::set<std::string> prepositions;

public:
	WClasses(boost::filesystem::path p_preposition,
			boost::filesystem::path p_stopWords,
			boost::filesystem::path p_nouns);
	bool isNoun(std::string);
	bool isPreposition(std::string);
	bool isStopWord(std::string);
	bool isNoun(char *);
	bool isPreposition(char *);
	bool isStopWord(char *);

private:
	std::set<std::string> getFileContent(boost::filesystem::path path);
	int checkPath(const boost::filesystem::path p);
};



#endif /* WCLASSES_HPP_ */
