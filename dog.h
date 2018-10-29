#ifndef DOG_H
#define DOG_H

#include <emscripten/val.h>
#include <string>

using std::string;

class Dog {
  string name;

  public:
    Dog (string n);
    string getGreeting ();
    void makeSound (emscripten::val func );
    Dog* newDog(string n);
    void hey(Dog*);
};

#endif
