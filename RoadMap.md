#Where we want to go with this

# Road Map #

  * 1 = Finish all functions in libdbook and implement all in dbook-tool.
  * 2 = Backend support.
  * 3 = Unicode support.

## 1 = Finish all functions in libdbook and implement all in dbook-tool ##

This phase is already under way. No real discussion needed.

## 2 = Backend support ##

Hold a linked list of backend structs, each holding a bunch of function pointers to the relevant lookup functions. The user should be able to construct a nsswitch-a-like config where each backend is queried until a match is found **or** a menu of all possible matches is show (?).

## 3 = Unicode support. ##

If we want this to be useful in the typesetting world, unicode is absolutely needed. Look at libiconv/libintl? I don't know much about it.