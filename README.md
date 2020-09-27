![CMake](https://github.com/foldedwave/Instil/workflows/CMake/badge.svg?branch=master)

# Instil
IoC container for C++.

The container currently allows for registration and retrieval of fully constructed object instances by supplying a base type. Singleton and Transient scopes are supported and Named scopes are currently being worked on. Object lifetime management is also incomplete.

# Getting Started
These are the basic steps to adding a type `FirstClass` with a parameterless constructor that inherits from IFirstClass.

```

#include "Instil/Container.h" // for Container, Container<>::build
#include "Instil/TypeInfo.h"  // for REGISTER_PARSE_TYPE
#include "Instil/Scope.h"     // for Scope, Singleton, Transient

REGISTER_TYPE_INFO(FirstClass);

Container<IFirstClass, FirstClass>::Register(Scope::Singleton);

```

To register a second class into the container, with a constructor that has a parameter of type `IFirstClass*`

```

Container<ISecondClass, SecondClass, IFirstClass>::Register(Scope::Singleton);

```

Each type registered to the container can have a scope of either Singleton (one instance for the entirety of the program), Transient (one instance per call to the container), or NamedScope (objects are requested with a named scope and live for the lifetime of that scope).

