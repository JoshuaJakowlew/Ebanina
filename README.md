# Ebanina
Ebanina is a library, that creates a huge horrible ebanina from a small and pretty number. If you don't know what is ebanina - visit it official page in Vkontakte: https://vk.com/ebaninaofficial

Ebanina allows you to create something horrible using bitwise operations. Sample:
> Ebanina(42) = (-~0<<(-~0<<0))|(-~0<<((-~0<<0)|(-~0<<(-~0<<0))))|(-~0<<((-~0<<0)|(-~0<<(-~0<<(-~0<<0)))))

This library allows you to create Ebanina in a very simple and fast way. To illustrate the power of the library: Ebanina(2^10000000 - 1 ) was computing about 1.5 hour on my PC.

## Example
A sample code is provided via library. It illustrates the main features of Ebanina. This program was also used to compute the Ebanina world record.

## Community
HuHguZ wrote a web-version of Ebanina.
source code: https://github.com/HuHguZ/huhguz.github.io/tree/master/ebanina
website: https://huhguz.github.io/ebanina/eb

pravdakotchestno wrote a Hello world program using precomputed ebanina
source code: https://github.com/pravdakotchestno/CPPandCprograms/blob/master/OtherPrograms/strangeCode/ebnprinter.c

## Build
Ebanina was developed using Visual Studio 2017. VS Project is provided. Ebanina depends on mpir - https://github.com/wbhart/mpir. To simlify the inastallation process, precompiled .lib files of mpir and Ebanina are also provided.

## Tutorial
To start using Ebanina include its header in your files.
Ebanina is pretty simple.
```cpp
#include "Ebanina.h"

Ebanina ebanina(42); // Create ebanina from number
Ebanina ebanina(mpz_class(42)); // Create ebanina from big integer class
Ebanina ebanina(2, 8); // Create ebanina from 2^8
Ebanina enanina("FF", 16) // Create ebanina from string with given base
```

To start using Ebanina just call `ebanina.create()`. To show or save your result use `ebanina.getString()` or `ebanina.toFile`

```cpp
#include "Ebanina.h"
#include <string>
#include <iostream>

Ebanina enanina(8); // Create an instance of Ebanina class

ebanina.create(); // Compute ebanina

std::string e = ebanina.getString(); // Get our ebanina
std::cout << e << std::endl; // Outputs -~0<<(-~0|-~0<<-~0)

ebanina.toFile("8.ebanina"); // Save our ebanina to file
```

Ebanina supports long arithmetic, so don't limit yourself with 64-bit numbers!