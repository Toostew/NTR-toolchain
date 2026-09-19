this file outlines the design decisions for the preprocessor


cpp smart pointers: "oh my god"
cpp introduces smart pointers, which are an evolution of the raw pointers seen in C. unlike raw pointers, where
ownership is purely a convention the programmer has to remember and enforce manually, smart pointers use RAII
(Resource Acquisition Is Initialization) to enforce "ownership" automatically. The smart pointer's destructor
runs automatically the moment it goes out of scope, and that destructor is responsible for cleaning up
(deleting) whatever it owns. "ownership" here means "who's responsible for this data's lifetime. Specifically,
ensuring it gets cleaned up exactly once, at the right time."

unique_ptr specifically enforces EXCLUSIVE ownership - it cannot be copied (only moved), because allowing a copy
would mean two owners both believing they're responsible for cleanup, risking something called a double-free.
(when 2 owners both try to free the same resource, when only 1 free is needed) moving instead
transfers ownership cleanly. There's still only ever one owner at any moment, it just changes hands.