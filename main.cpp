/*
 * main.cpp
 *
 *  Created on: Mar 2, 2014
 *      Author: alex
 */



#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iostream>

#include "wclasses.hpp"
#include "cmp.hpp"
#include "stats.hpp"

#define PATH_1 "../resources/BE/"
#define PATH_2 "../resources/AE/"
//#define MARKERS "prepositions.txt"

#define PATH_NOUNS "../resources/nouns"
#define PATH_PREPOSITIONS "../resources/prepositions_short"
#define PATH_STOPWORDS "../resources/stop_words"

int checkPath(const boost::filesystem::path p) {

using namespace boost::filesystem;
using namespace std;

	try {
		if (exists(p)) {
			if (is_directory(p)){
					if (!is_empty(p)) {
						return 0;
					} else {
						cout << p << " exists, but empty\n";
					}
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

int main(int argc, char *argv[]) {
	using namespace boost::filesystem;
	using namespace std;

	path p_preposition(PATH_PREPOSITIONS);
	path p_nouns(PATH_NOUNS);
	path p_stopWords(PATH_STOPWORDS);

	WClasses wclasses(p_preposition, p_stopWords, p_nouns);
	CMP cmp(&wclasses);

	path p_dir_texts_1(PATH_1);
	path p_dir_texts_2(PATH_2);

	if (checkPath(p_dir_texts_1) == -1) {
		return -1;
	}
	directory_iterator iterator_1(p_dir_texts_1);
	const directory_iterator iterator_1_start(p_dir_texts_1);

	if (checkPath(p_dir_texts_2) == -1) {
		return -1;
	}
	directory_iterator iterator_2(p_dir_texts_2);
	const directory_iterator iterator_2_start(p_dir_texts_2);


	cout << "Files found in " << PATH_1 << endl;
	while (iterator_1 != directory_iterator()) {
		cout << *iterator_1 << "\n";
		iterator_1++;
	}
	cout << endl;
	iterator_1 = iterator_1_start;

	cout << "Files found in " << PATH_2 << endl;
	while (iterator_2 != directory_iterator()) {
		cout << *iterator_2 << "\n";
		iterator_2++;
	}
	cout << endl;
	iterator_2 = iterator_2_start;

	//vector <Finding> result;
	list <Finding> t;
	Stats stats;
	while (iterator_1 != directory_iterator()) {
		while (iterator_2 != directory_iterator()) {
				cout << "\nComparing " << *iterator_1 << " --- " << *iterator_2 << "\n";
				t = cmp.compare((*iterator_1).path() , (*iterator_2).path());
				stats.addElements(t);
				iterator_2++;
			}
		directory_iterator it_0(p_dir_texts_2);
		iterator_2 = it_0;
		iterator_1++;
	}
	//sort(result.begin(), result.end(), findingCompare);
	//stats.getElements();
	cout << "Differences found total: " << stats.size() << endl;
	cmp.printResult(stats.getElements());


	return 0;

}




