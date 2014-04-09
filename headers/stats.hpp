/*
 * stats.hpp
 *
 *  Created on: Apr 9, 2014
 *      Author: alex
 */

#ifndef STATS_HPP_
#define STATS_HPP_

#include "cmp.hpp"
#include <list>
#include <vector>

class Stats{
	std::vector<Finding> elements;
public:
	void addElements(std::list<Finding>);
	std::vector<Finding> getElements();
	size_t size();
private:
	static bool comparator(const Finding &f1, const Finding &f2);
	void removeInvertedDublicates();
	};


#endif /* STATS_HPP_ */
