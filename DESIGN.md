# spin-up design

## Style
This code loosely follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

Some notable exceptions are as follows:
1. A few custom formatting rules are defined and automatically configured by the compiler. Use VS Code's autoformater (default: *Ctrl + Shift + F*) to format files.
2. `#pragma once` may be used in header files over `include` guards.
3. `src` files are named using `.cpp` instead of `.cc`.
4. Exceptions are allowed to be used to demark states which are clearly illegal and should never be reached.

# Organization
Each file should have a namespace; even classes. Namespaces should be organized by folder; e.g. everything in the `hardware` folder should have the `hardware` namespace. Nested namespaces may be used if additional granularity is necessary, but this use case should be rare.

The [Purdue Robot Operating System](https://pros.cs.purdue.edu/v5/index.html#) (pros) is available via the header `#include "pros.h"`. In general, `pros` code should be wrapped into generic implementations in `hardware`; thus, it shouldn't be necessary to import `pros` outside of that folder.

# Code Flow and Constructs
Virtual interfaces are used to create an abstraction layer between use cases on the robot and physical hardware. Interfaces are defined in `interface` and describe a minimal set of methods necessary for using/interacting with an object. Since these `interface`s are generic, any class which fulfills their basic requirements may be substituted as the concrete implementation. 

In contrast, subsystems should interact with `interface`s only (and not concrete implementations). For example, a drivetrain should receive `interface::Motor`s and an `interface::Controller` rather than, say, `ProsMotor` and `ProsController`. This enables these implementations to be freely swapped. Generally, users should only take references to specific `interface`s needed since taking the entire `std::unique_ptr` takes ownership of that object. For example, `HolonomicDrivetrain` may receive a controller to work with using the signature `Drive(const interface::Controller& controller) {}`. This method should be called by dereferencing the `std::unique_ptr<ProsController>` pointer managed by main, e.g. `drivetrain.Drive(*controller_ptr);`. 

# Header and Source Files
`.h` files are called header files and define static information about c++ constructs. They are used by the compiler to separate the linking of code constructs from the concrete implementations, which improves the performance of the c++ compiler. 

Header files (`.h`) should observe the following rules:
1. Begin with `#pragma once`. `#pragma once` is a directive which ensures the c++ compiler will not link the same header file more than once.
2. References to the c++ standard library are enclosed in carets, e.g. `#include <vector>`.
3.  References to other files in the project are enclosed in double quotes and always use the full file path, e.g. `#include "hardware/pros_controller.h"`. 
4. References should always point to other header files (`.h`), never implementations (`.cpp`). 
5. Define a namespace which matches the folder. Header files should always define a namespace which matches the folder the file is in.
6. If the `pros` library is needed, it may be included as `#include pros.h`. Note `pros` should only generally be used within the `hardware` folder.
7. Header files with non-trivial functions or methods should also have a single corresponding `.cpp` source file with the same name.

Header files may also optionally include implementations for constructors, methods and functions (instead of putting the implementation in a `.cpp` source file). Generally speaking, constructors should be written in-line, as should trivial getters. Methods and functions (but not constructors) which have their implementation in the `.h` file should always include the `inline` keyword, which hints to the compiler that the function call should be expanded into the actual function code at compile time.

Source files (`.cpp`) should observe the following rules:
1. Reference the header file of the same name. For example, `main.cpp` should always start with `#include "main.h"`. No other references are allowed in a source file. Note that references from the header file propagate to the corresponding implementation file, so adding `#include <vector>` in the header file will make `std::vector` available in the corresponding source file.
2. Use the same namespace as the header file. Source files should have the same namespace declaration as the header file.

# Classes and Structs
`class`es are collections of data and and methods. Methods are functions which can operate on the data of a class.
`struct`s are functionally very similar to classes; key differences are:
1. `struct`s primarily exist to hold data, whereas `class`es also include operations on their data.
2. `class` data members are named with a trailing underscore, e.g. `my_class_member_`, whereas `struct` members are named without, e.g. `my_struct_member`.
3. `class` data is should be marked private and exposed via a getter method, whereas `struct` data is typically marked public and thus exposed directly.

### const Methods
`const` is used to indicate whether a method mutates class members. Note a class member may have both a `const` and a non-`const` getter; the appropriate one will be chosen based on whether it is called from within a `const` or non-`const` method or external context. 

To prevent issues with `const` from arising in regards to `pros` implementations, some `hardware` classes mark `pros` objects as `mutable`, which allows non-`const` methods on these `pros` to manipulated in a `const` context. To help facilitate this, `const` getters return non-`const` references to the `pros` object.

### Getters
A getter is a method which is used to retrive a value from a class.  Methods (but not functions) which behave like simple getters should be named like a standard variable instead of using standard method naming convetions (e.g. `velocity()` instead of `Velocity()` or `GetVelocity()`). Note getters should also often be annotated with `[[nodiscard]]` since a call to a getter which does not use the result is redundant.

## \[\[nodiscard\]\]
`[[nodiscard]]` may be prepended to a function or method declaration with a non-void return type to indicate that calling code should actually use the return type in some way. This is enforced by the compiler at compile time via a warning. `[[nodiscard]]` should be used to annotate methods which return values and have no side-effects:
```
// function declaration
[[nodiscard]] int getValue() { return 5; };

getValue(); // compiler warning; result of getValue() should be used
if (getValue() == 1) {} // okay; getValue() is used
int value = getValue(); // also okay
```

### Factory Methods
Factory methods should be `static` methods belonging to either a concrete implementation or a subsystem. Their name should be `Make`, e.g. `MakeDriverController`. They should return one or more `std::unique_ptr`s which are set to the concrete implementation rather than the underlying interface (e.g. `ProsController`, not `interface::Controller`). This enables useage of additional, non-interface methods in `main` and supports classes which implement more than one interface (like `ProsMotor`).

## Class Members
Classes which take ownership over one or more concrete implementations, such as `HolonomicMotors`, by taking as members `std::unique_ptr`s or other non-copyable data, should have their copy constructor and copy assignment operators deleted and the rest of its constructors defined (in order to properly observe the rule of 5). As a reminder, classes which own `std::unique_ptr` cannot be copied, only moved; this can be accomplished with `std::move`. To facilitate error checking and prevent hard to detect bugs, the copy constructor and copy assignment operator should be deleted, and the other constructors/destructors (move constructor, move assignment, destructor) should be specified/assigned to `default` . See `holonomic_motors.h` for an example.

# Functions
Formally, functions behave similarity to methods, but methods are defined as a part of a class whereas functions are located in a namespace scope.

## Use Cases
Functions should be used in cases where access to encapsulated data is not required. As a reminder, you should avoid using classes to arbitrarily group similar functions together; use a namespace instead.

## Naming
Non-method functions which do more computation or which do not expose (or pretend to expose) a field on a class should be written as `Get<MyValue>`, e.g. `GetProsJoystick`. Keep in mind that classes should not be used to group arbitrary functions together; namespaces already serve this purpose.