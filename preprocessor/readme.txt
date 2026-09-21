this file outlines the design decisions for the preprocessor, as well as new concepts I encounter


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



