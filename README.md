CPPItertools
============

range-based for loop add-ons inspired by the python builtins and itertools
library.

##### Table of Contents
[range](#range)<br />
[filter](#filter)<br />
[filterfalse](#filterfalse)<br />
[takewhile](#takewhile)<br />
[dropwhile](#dropwhile)<br />
[enumerate](#enumerate)<br />
[cycle](#cycle)<br />
[compress](#compress)<br />
[zip](#zip)<br />
[chain](#chain)<br />
[reverse](#reverse)<br />
[slice](#slice)<br />
[moving_section](#moving_section)<br />

##### Combinatoric fuctions
[product](#product)<br />
[combinations](#combinations)<br />
[permutations](#permutations)<br />
[powerset](#powerset)<br />

range
-----

Uses an underlying iterator to acheive the same effect of the python range
function.  `range` can be used in three different ways:

Only the stopping point is provided.  Prints 0 1 2 3 4 5 6 7 8 9
```c++
for (auto i : range(10)) {
    cout << i << '\n';
}
```

The start and stop are both provided.  Prints 10 11 12 13 14
```c++
for (auto i : range(10, 15)) {
    cout << i << '\n';
}
```

The start, stop, and step are all provided.  Prints 20 22 24 26 28
```c++
for (auto i : range(20, 30, 2)) {
    cout << i << '\n';
}
```

Negative values are allowed as well.  Prints 2 1 0 -1 -2
```c++
for (auto i : range(2, -3, -1)) {
    cout << i << '\n';
}
```

enumerate
---------

Can be used with any class with an iterator.  Continually "yields" containers
similar to pairs.  They are basic structs with a .index and a .element.  Usage
appears as:

```c++
vector<int> vec{2, 4, 6, 8};
for (auto e : enumerate(vec)) { 
    cout << e.index
         << ": "
         << e.element
         << '\n';
}
```

filter
------
Called as `filter(predicate, iterable)`.  The predicate can be any callable.
`filter` will only yield values that are true under the predicate.

Prints values greater than 4:  5 6 7 8
```c++
vector<int> vec{1, 5, 4, 6, 7, 3, 2, 8, 3, 2, 1};
for (auto i : filter([] (int i) { return i > 4; }, vec)) {
    cout << i <<'\n';
}

```

filterfalse
-----------
Similar to filter, but only prints values that are false under the predicate.

Prints values not greater than 4: 1 4 3 2 3 2 1 
```c++
vector<int> vec{1, 5, 4, 6, 7, 3, 2, 8, 3, 2, 1};
for (auto i : filter([] (int i) { return i > 4; }, vec)) {
    cout << i <<'\n';
}

```

takewhile
---------
Yields elements from an iterable until the first element that is false under
the predicate is encountered.

Prints 1 2 3 4.  (5 is false under the predicate)
```c++
vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1};
for (auto i : takewhile([] (int i) {return i < 5;}, ivec)) {
    cout << i << '\n';
}
```

dropwhile
---------
Yields all elements after and including the first element that is false under
the predicate.

Prints 5 6 7 1 2
```c++
vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 1, 2};
for (auto i : dropwhile([] (int i) {return i < 5;}, ivec)) {
    cout << i << '\n';
}
```

cycle
-----

Repeatedly produce all values of an iterable.  The loop will be infinite, so a
`break` is necessary to exit.

Prints 1 2 3 repeatedly until `some_condition` is true
```c++
vector<int> vec{1, 2, 3};
for (auto i : cycle(vec)) {
    cout << i << '\n';
    if (some_condition) {
        break;
    }
}
```


zip
---

Takes an arbitrary number of ranges of different types and efficiently iterates over 
them in parallel (so an iterator to each container is incremented simultaneously). 
When you dereference an iterator to "zipped" range you get a tuple of whatever elements 
the iterators were holding.

Example usage:
```c++
array<int,4> i{{1,2,3,4}};                                            
vector<float> f{1.2,1.4,12.3,4.5,9.9};                                
vector<string> s{"i","like","apples","alot","dude"};             
array<double,5> d{{1.2,1.2,1.2,1.2,1.2}};                             

for (auto e : zip(i,f,s,d)) {                                        
    cout << std::get<0>(e) << ' '                                
         << std::get<1>(e) << ' '                                      
         << std::get<2>(e) << ' '                                      
         << std::get<3>(e) << '\n';                               
    std::get<1>(e)=2.2f; // modify the float array                     
}
```


a `zip_longest` also exists where the range terminates on the longest
range instead of the shortest. because of that you have to return a
`boost::optional<T>` where `T` is whatever type the iterator dereferenced
to (`std::optional` when it is released, if ever)


compress
--------

Yields only the values corresponding to true in the selectors iterable.
Terminates on the shortest sequence.

Prints 2 6
```c++
vector<int> ivec{1, 2, 3, 4, 5, 6};
vector<bool> bvec{false, true, false, false, false, true};
for (auto i : compress(ivec, bvec) {
    cout << i << '\n';
}
```

chain
-----

This can chain any set of ranges together as long as their iterators
dereference to the same type.

```c++
vector<int> empty{};                                                 
vector<int> vec1{1,2,3,4,5,6};                                       
array<int,4> arr1{{7,8,9,10}};                                       

for (auto i : chain(empty,vec1,arr1)) {                             
    cout << i << '\n';                                          
}
```

reverse
-------

Iterates over elements of a sequence in reverse order.

```c++
for (auto i : reverse(a)) {                                          
    cout << i << '\n';                                           
}
```

slice
-----

Returns selected elements from a range, parameters are start, stop and step.
the range returned is [start,stop) where you only take every step element

This outputs `0 3 6 9 12`
```c++
vector<int> a{0,1,2,3,4,5,6,7,8,9,10,11,12,13};
for (auto i : slice(a,0,15,3)) {
    cout << i << '\n';
}
```

moving_section
-------------

Takes a section from a range and increments the whole section.  

Example:
`[1, 2, 3, 4, 5, 6, 7, 8, 9]`  

take a section of size 4, output is:
```
1 2 3 4 
2 3 4 5 
3 4 5 6 
4 5 6 7 
5 6 7 8 
6 7 8 9 
```

Example Usage:
```c++
std::vector<int> v = {1,2,3,4,5,6,7,8,9};                                      
for (auto sec : moving_section(v,4)) {                                         
    for (auto i : sec) {                                                       
        std::cout << i << " ";                                                 
        i.get() = 90; 
        //has to be accessed with get if you want to store references
        //because it is stored in a reference_wrapper (std::vector 
        //cannot hold references)
    }                                                                          
    std::cout << std::endl;                                                    
}
```  

product
------

Generates the cartesian project of the given ranges put together  

Example usage: 
```c++
std::vector<int> v1{1,2,3};                                                    
std::vector<int> v2{7,8};                                                      
std::vector<std::string> v3{"the","cat"};                                      
std::vector<std::string> v4{"hi","what","up","dude"}; 
for (auto t : product(v1,v2,v3,v4)) {                                          
    std::cout << std::get<0>(t) << ", "                                        
        << std::get<1>(t) << ", "                                              
        << std::get<2>(t) << ", "                                              
        << std::get<3>(t) << std::endl;                                        
} 
```

combinations
-----------

Generates n length unique sequences of the input range, there is also a
combinations_with_replacement

Example usage:
```c++
std::vector<int> v = {1,2,3,4,5};                                              
for (auto i : combinations(v,3)) {                                             
    //std::cout << i << std::endl;                                             
    for (auto j : i ) std::cout << j << " ";                                   
    std::cout<<std::endl;                                                      
}
```


permutations
-----------

Generates all the permutations of a range using `std::next_permutation`  

Example usage:
```c++
std::vector<int> v = {1,2,3,4,5};                                              
for (auto vec : permutations(v)) {                                             
    for (auto i : vec) {                                                       
        std::cout << i << " ";                                                 
    }                                                                       
    std::cout << std::endl;                                                 
} 
```

powerset
-------

Generates every possible subset of a set, never run it since it runs in 𝚯(2^n).

Example usage:
```c++
std::vector<int> vec {1,2,3,4,5,6,7,8,9};                                      
for (auto v : powerset(vec)) {                                                 
    for (auto i : v) std::cout << i << " ";                                    
    std::cout << std::endl;                                                    
}
```

  
