#include <iostream>
#include<map>
#include <limits>

template<typename K, typename V>
class interval_map {
public:
	std::map<K, V> m_map;


	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		// INSERT YOUR SOLUTION HERE
		if (!(keyBegin <= keyEnd)) return; // nothing to do

		typename std::map<K, V>::iterator  itBegin, itPrevBegin, itEnd, itPrevEnd, theEnd;
		theEnd = m_map.end();
		itBegin = itPrevBegin = m_map.lower_bound(keyBegin);
		itEnd = itPrevEnd = m_map.lower_bound(keyEnd);
		itPrevEnd--;
		itPrevBegin--;

		if (!(itPrevEnd->second == val)) m_map.insert(itEnd, std::make_pair(keyEnd, itPrevEnd->second));
		if (!(itPrevBegin->second == val)) m_map.insert(itBegin, std::make_pair(keyBegin, val));

		typename std::map<K, V>::iterator beginErase, endErase;
		beginErase = endErase = m_map.upper_bound(keyBegin);
		if (beginErase != theEnd) {
			while (endErase->first < keyEnd) {
				endErase++;
				if (endErase == theEnd) break;
			}
			m_map.erase(beginErase, endErase);
		}

	}
		// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};



int main()
{
	//map<int, string> myMap;
	//map<int, string>::iterator it = myMap.end();
	//myMap.insert(it, pair<int, string>(1, "b"));
	//myMap.insert(it, pair<int, string>(6, "n"));
	//myMap.insert(it, pair<int, string>(3, "l"));
	//myMap.insert(it, pair<int, string>(9, "k"));
	//myMap.insert(it, pair<int, string>(4, "g"));

	//it = myMap.begin();

	//cout << myMap.lower_bound(2)->first << '\t' << myMap.lower_bound(2)->second << '\n';
	//cout << myMap.upper_bound(9)->first << '\t' << myMap.upper_bound(9)->second << '\n';

	//while (it != myMap.end())
	//{
	//	cout << it->first << '\t' << it->second <<endl;
	//	it++;
	//}



	interval_map<int, char> myInterval('h');


	myInterval.assign(1, 12, 'k');
	myInterval.assign(8, 10, 'c');
	myInterval.assign(9, 14, 'h');
	//myInterval.assign(3, 5, 'j');
	//myInterval.assign(4, 8, 'b');

	std::map<int, char>::iterator m = myInterval.m_map.begin();
	while (m != myInterval.m_map.end())
	{
		std::cout << m->first << '\t' << m->second << '\n';
		m++;
	}



}