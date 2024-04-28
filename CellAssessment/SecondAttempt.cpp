// Author/Engineer: Lerato Mokoena on 21/04/2023.
// Copyright © 2023 Arurea Murals. All rights reserved.

#include <map>
#include <limits>
#include <ctime>
#include <iomanip>


template<typename K, typename V>
class interval_map {
	std::map<K, V> m_map;

public:
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
	void assign_two(K const& keyBegin, K const& keyEnd, V const& val) {

		if (!(keyBegin < keyEnd)) return;

		std::pair<K, V> beginExtra;
		std::pair<K, V> endExtra;
		bool beginHasExtra = false;
		bool endHasExtra = false;

		typename std::map<K, V>::const_iterator itBegin;
		itBegin = m_map.lower_bound(keyBegin);
		if (itBegin != m_map.end() && keyBegin < itBegin->first) {
			if (itBegin != m_map.begin()) {
				beginHasExtra = true;
				--itBegin;
				beginExtra = std::make_pair(itBegin->first, itBegin->second);
			}
			// openRange for erase is prevIterator
			// insert (prevIterator->first, prevIterator->second) as well!
		}

		typename std::map<K, V>::const_iterator itEnd;
		itEnd = m_map.lower_bound(keyEnd);
		if (itEnd != m_map.end() && keyEnd < itEnd->first) {
			endHasExtra = true;
			typename std::map<K, V>::const_iterator extraIt = itEnd;
			--extraIt;
			endExtra = std::make_pair(keyEnd, extraIt->second);
			// closeRange for erase is this iterator
			// insert (keyEnd, prevIterator->second) as well!
		}

		// 4 canonical conflicts:
		//	 beginExtra w/ mid
		//	 before-mid w/ mid (beginHasExtra==false)
		//	 mid w/ endExtra
		//	 mid w/ after-mid (endHasExtra==false)

		bool insertMid = true;
		if (beginHasExtra) {
			if (beginExtra.second == val)
				insertMid = false;
		}
		else {
			if (itBegin != m_map.begin()) {
				typename std::map<K, V>::const_iterator beforeMid = itBegin;
				--beforeMid;
				if (beforeMid->second == val)
					insertMid = false;
			}
		}


		if (endHasExtra) {
			if ((insertMid && endExtra.second == val) || (!insertMid && endExtra.second == beginExtra.second))
				endHasExtra = false;
		}
		else {
			if ((insertMid && itEnd != m_map.end() && itEnd->second == val) || (!insertMid && itEnd != m_map.end() && itEnd->second == beginExtra.second))
				itEnd = m_map.erase(itEnd);
		}

		itBegin = m_map.erase(itBegin, itEnd);
		if (beginHasExtra)
			itBegin = m_map.insert(itBegin, beginExtra);
		if (insertMid)
			itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));
		if (endHasExtra)
			m_map.insert(itBegin, endExtra);
	}
};
