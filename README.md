# Senior C++ think-cell-assessment
## Task Description

Fun fact, this assessment was an exciting opprotunity to have engaged in a mind bending coding problem.

interval_map<K,V> is a data structure that efficiently associates intervals of keys of type K with values of type V. Your task is to implement the assign member function of this data structure, which is outlined below.
interval_map<K, V> is implemented on top of std::map. In case you are not entirely sure which functions std::map provides, what they do and which guarantees they provide, we provide an excerpt of the C++ standard here: 
Each key-value-pair (k,v) in the std::map means that the value v is associated with the interval from k (including) to the next key (excluding) in the std::map.
Example: the std::map (0,'A'), (3,'B'), (5,'A') represents the mapping.

  0 -> 'A'   
  1 -> 'A'   
  2 -> 'A'   
  3 -> 'B'  
  4 -> 'B'  
  5 -> 'A'   
  6 -> 'A'  
  7 -> 'A'
  
### ... all the way to numeric_limits<int>::max()

The representation in the std::map must be canonical, that is, consecutive map entries must not have the same value: ..., (0,'A'), (3,'A'), ... is not allowed. Initially, the whole range of K is associated with a given initial value, passed to the constructor of the interval_map<K,V> data structure.
Key type K
besides being copyable and assignable, is less-than comparable via operator<
is bounded below, with the lowest value being std::numeric_limits<K>::lowest()
does not implement any other operations, in particular no equality comparison or arithmetic operators
Value type V
besides being copyable and assignable, is equality-comparable via operator==
does not implement any other operations.

### Documentation
if you need more context on the standard library i.e (std::map) please refer to the cppreference website:
- [cpprefernce](https://en.cppreference.com/w/cpp/container/map/)


In order to build the app you may use visual studio, the following software package is required:
- [Visual Studio](https://visualstudio.microsoft.com/)

