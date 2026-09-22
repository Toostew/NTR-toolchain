this file outlines the design decisions for the preprocessor, as well as new concepts I encounter

the Include, Define and undefine Handlers:
   if you notice, all 3 handlers take arguments without quotations, and this is simply because of a simplification trade off:
    the whole reason there's a need for it is to allow for special names that would otherwise wouldn't be supported. Take for
    example #include. If I had #include "file name.txt", the #include should be able to parse the file name as file name.txt, which
    is expected behaviour and you can see this in g++. however, because I am using istringstream, which conveniently splits
    strings into distinct "chunks" seperated by whitespace, implementing this would be a bit of a headache, since it will split text
    even when bounded by quotations. So the choice was either implement a way for whitespace to be ignored when bounded within quotations,
    like "file name.txt", or just ban spaces outright; which is what I went for. Since spaces aren't allowed there really isn't any need
    for quotations anymore. I do however plan to return and maybe reimplement this so you COULD allow whitespace, which means wrapping the
    argument in quotations, but that's for another time.


std::vector<std::string> MacroTable::getMacros():
    this function irks me because I NEED to get a list of every single key from the macrotable in order to expand macros during preprocessing.
    In order to keep the hashmap (unordered map) private I needed to expose a function that returns a list of every macro,
     this function, when invoked will linearly catalog every single pair, and record pair.first
    into a vector to be returned. This cataloging occurs EVERY TIME THE FUNCTION IS CALLED, so it's wildly inefficient. ideally, you'd want to save the keys
    and have them persist in some way so that the lookup is instant O(1) and you dont have to constantly catalog them again. For now, I don't know how to do that

Error codes:
    So far I've implemented some rudimentary error codes for debugging, they are:
    10: Cycle detected, specifically when a #include directive detects the same file within the file stack
    20: Unable to open file for a variety of reasons, File doesnt exist, file not readable, or inaccessible 



New concepts:

cpp smart pointers: "oh my god"
cpp introduces smart pointers, which are an evolution of the raw pointers seen in C. unlike raw pointers, where
ownership is purely a convention the programmer has to remember and enforce manually, smart pointers use RAII
(Resource Acquisition Is Initialization) to enforce "ownership" automatically. The smart pointer's destructor
runs automatically the moment it goes out of scope, and that destructor is responsible for cleaning up
(deleting) whatever it owns. "ownership" here means "who's responsible for this data's lifetime. Specifically,
ensuring it gets cleaned up exactly once, at the right time."

unique_ptr specifically enforces EXCLUSIVE ownership. It cannot be copied (only moved), because allowing a copy
would mean two owners both believing they're responsible for cleanup, risking something called a double-free.
(when 2 owners both try to free the same resource, when only 1 free is needed) moving instead
transfers ownership cleanly. There's still only ever one owner at any moment, it just changes hands.



iterators:
an iterator is an object that represents a POSITION inside a container. It doesn't hold the data itself,
it just marks "where you are" and lets you move around/access whatevers at that position. think of it
like a bookmark in a book; it doesn't contain the pages, it just marks where you are in it.

.end() - NOT the last real element. it's a conceptual "one past the last element" position, used purely
as a sentinel to mean "you've gone past everything real / found nothing." comparing your iterator against
.end() is the idiomatic way to check if a search actually found something:

    auto it = someMap.find(key);
    if (it != someMap.end()) {
        // found it
    } else {
        // not found
    }

->first and ->second:
dereferencing a map iterator gives you a std::pair<key, value>. .first is the key, .second is the value.
since the iterator behaves like a pointer, you access these with -> (same pattern as currentEntry->fileStream
from the fileEntry pointer stuff - dereference + member access in one operator).

in short they're the general, uniform way the STL lets you walk through ANY
container (vectors, maps, sets, etc) with the same syntax, regardless of how that container's actually laid
out in memory. range-based for loops are secretly using iterators under the hood too, just hidden from view.

