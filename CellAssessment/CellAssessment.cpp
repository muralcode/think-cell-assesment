// Author/Engineer: Lerato Mokoena on 21/04/2023.
// Copyright © 2023 Arurea Murals. All rights reserved.

#include <iostream>
#include <map>
#include <iomanip>

template <typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    interval_map(V const& val) : m_valBegin(val) {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    // O(log n)


    /*
      Lerato: Algorithm Notes:
      This version reduces the number of conditional checks and optimizes the insertion
      and deletion operations to achieve better time complexity.
      The overall time complexity of this optimized `assign` function remains O(log n).
      Where n is the number of elements in the map.
    */

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        // write your code here

        if (!(keyBegin < keyEnd))
            return;

        auto itLowerLimit = m_map.upper_bound(keyBegin);
        auto itLowerLimitSame = (itLowerLimit == m_map.begin()) ? m_map.end() : std::prev(itLowerLimit);

        auto itHigherLimit = m_map.upper_bound(keyEnd);

        if (itLowerLimitSame == m_map.end() || itHigherLimit == m_map.begin() || itLowerLimitSame->first < keyBegin) {
            if (val != m_valBegin) {
                m_map.insert(itLowerLimit, std::make_pair(keyBegin, val));
                if (itHigherLimit == m_map.end() || itHigherLimit->first != keyEnd)
                    m_map.insert(itHigherLimit, std::make_pair(keyEnd, m_valBegin));
            }
        }
        else {
            auto itEnd = std::prev(itHigherLimit);

            if (itLowerLimitSame->second == val) {
                if (itEnd->first == keyEnd) {
                    if (itEnd->second != m_valBegin)
                        itEnd->second = m_valBegin;
                    else
                        m_map.erase(itLowerLimit, itHigherLimit);
                }
            }
            else {
                m_map.erase(itLowerLimit, itHigherLimit);
                m_map.insert(itLowerLimit, std::make_pair(keyBegin, val));
                if (itEnd->first != keyEnd)
                    m_map.insert(itHigherLimit, std::make_pair(keyEnd, itEnd->second));
            }
        }
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return m_valBegin;
        }
        else
        {
            return (--it)->second;
        }
    }
};

int main() {
    // instance of interval_map class
    interval_map<int, char> m('A');
    // calling of assign() function
    m.assign(1, 3, 'B');
    // loop for maping key and its corresponding value
    for (int i = -3; i <= 5; ++i)
        std::cout << std::setw(2) << i << ' ' << m[i] << '\n';
}
