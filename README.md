# AnyunRegex
C++ Regex

I use C++ to write a regex engine.

The main idea is use operator priority algorithm to construct a NFA and transmit to a DFA,which has a better performance than NFA.

The target to implent an entire regex:
\ escape
| . ? 
* +
[]  [^]
{n} {n,m} {n,}
and so.
