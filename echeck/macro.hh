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
#define DEBUG(...) std::cout << GREEN() "\033[K\t\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;
#else
#define DEBUG(...) ;
#endif
#ifdef INFO_ON
#define INFO(...) std::cout << BLUE() "\033[K\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;
#else
#define INFO(...) ;
#endif
#ifdef WARN_ON
#define WARNING(...) std::cout << YELLO() "\033[K\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;
#else
#define WARNING(...) ;
#endif
#ifdef VERBEUX_ON
#define VERBEUX(...) std::cout << GREY() "\033[K\t\t\t" << __VA_ARGS__ << CLRCOLOR() << std::endl;
#else
#define VERBEUX(...);
#endif