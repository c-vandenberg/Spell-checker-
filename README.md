# Spell-checker-
In an attempt to compare the different data structures in their Big O notation with regards to insertion, deletion, lookup and sorting I implemented various data structures to store a dictionary of ~150,000 words that would be used to spell check a given text.

The two main data structures I looked at were a hash table and a trie. Although lookup was faster with the trie method, overall I found the hash table was the better of the two especially when you took into account memory allocation.
