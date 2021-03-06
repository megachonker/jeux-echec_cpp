#pragma once
#include <stdio.h>

//macro pour les couleur
#define GREEN()     "\033[1;32m"
#define BLUE()      "\033[1;34m"
#define RED()       "\033[1;31m"
#define YELLO()     "\033[1;93m"
#define GREY()      "\033[1;90m"
#define CLRCOLOR()  "\033[0m"

//definition des marcro variadique

#ifdef DEBUG_ON
#define DEBUG(...) do {std::cout << GREEN() "\033[K\t\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;} while(0)
#else
#define DEBUG(...) do {}while(0);
#endif
#ifdef INFO_ON
#define INFO(...) do { std::cout << BLUE() "\033[K" << __VA_ARGS__ << CLRCOLOR() << std::endl;} while(0)
#else
#define INFO(...) do {}while(0);
#endif
#ifdef WARN_ON
#define WARNING(...) do {std::cerr << YELLO() "\033[K\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;} while(0)
#else
#define WARNING(...) do {}while(0);
#endif
#ifdef VERBEUX_ON
#define VERBEUX(...) do {std::cout << GREY() "\033[K\t\t\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;} while(0)
#else
#define VERBEUX(...);
#endif