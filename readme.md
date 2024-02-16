# rx
## regular expression match / tester

Command line testing application for "c++ standard regex implemnetation", aka "#include \<regex\>".
  
### Regular Expressions
  
Regular expressions are a standardized way to express patterns to be matched against sequences of characters.

* The standard C++ library provides support for regular expressions in the <regex> header through a series of operations. All these operations make use of some typical regex parameters:
* Target sequence (subject): The sequence of characters searched for the pattern. Generally, this is a range specified by two iterators, but some functions also accept a c-string or a string object instead.
* Regular expression (pattern): The pattern which is searched for in the target sequence. This must be an object of a basic_regex type (such as regex), generally constructed from a string with a special syntax that describes what constitutes a match (see ECMAScript syntax).
* Matches array: Some operations allow to retrieve information about matches. This information is stored in one of the special match_results array types (such as cmatch or smatch).
* Replacement string: Some operations can replace matches. These replacements are specified in strings that allow for a special format (see ECMAScript syntax).
