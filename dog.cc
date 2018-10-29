#include <iostream>
#include <string>

#include "dog.h"
#include "emscripten/bind.h"

using namespace emscripten;
using namespace std;

Dog::Dog(string n): name(n) {}

string Dog::getGreeting () {
  return "My name is " + name + ", hello from C++!";
}

void Dog::makeSound (emscripten::val func) {
  cout << "bark!" << func.call<string>("apply", emscripten::val::undefined()) << '\n';
}

Dog* Dog::newDog(string n) {
  return new Dog(n);
}

void Dog::hey(Dog* dog) {
  cout << "hey " << dog->name << '\n';
}

EMSCRIPTEN_BINDINGS (c) {
  class_<Dog>("Dog")
    .constructor<string>()
    .function("makeSound", &Dog::makeSound)
    .function("getGreeting", &Dog::getGreeting)
    .function("newDog", &Dog::newDog, allow_raw_pointers())
    .function("hey", &Dog::hey, allow_raw_pointers());
}
