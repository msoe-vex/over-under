# C++ Guide
## Purpose
This document is meant as a guide for people who has at lesat a little bit of programming knowledge. If you have never done C++ before, I reccomend checking out the Resources below to learn C++. 

The Syntax Guide is meant to help someone with a little bit of C++ experience understand some strange syntax in C++. This language is exceptionally powerful but also exceptionally confusing sometimes. If something doesn't make sense or is missing from this list, feel free to make a change and make a merge request with it. Remember to ask questions!

## Resources:
**The Cherno YouTube channel:** The Cherno is a channel that makes a lot of C++ content and has a full [C++ tutuorial playlist](https://www.youtube.com/watch?v=SfGuIVzE_Os&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=5&ab_channel=TheCherno). This playlist, along with this document, is meant for people who have at least a little experience in programming. If you are going through that playlist or any other tutorial and are getting very lost, please reach out to a veteran member of the team. 

**W3 Schools tutorial:** [This series](https://www.w3schools.com/cpp/cpp_pointers.asp) of articles has some code running tools to test out yourself but mainly contains all the information you would need to know to be successful on this team. 

**C++ Code Shell**: [This](https://cpp.sh/) browser based tool allows you to quickly run C++ code. You should use it get some experience C++ coding and for practicing what you learn from videos or articles. 

## Syntax Guide

### Deconstructor: `~<ClassName>()`
If there is a `~` before what looks like a constructor, that is a deconstructor. It is called when an object is destroyed and should be used to `delete` any dynamically allocated memory with `new`.

### Initializer List: `<constructor> : <variable>(<value>)`
Constructors are typically used to assign their parameters to member variables. C++ makes this process simpler with initializer lists. After the constructor name, but before the body, there is a `:` that defines the start of the initalizer list. The list itself is a comma seperated list of variables with the values to initialize them to in paranethis after them like parameters.

### `enum class {}`
Class enums are both strongly typed and strongly scoped. This means that they do not automatically convert to ints and do not compare themselves to other enumerations. This helps avoid mistakes with many different enums. [More Info](https://www.geeksforgeeks.org/enum-classes-in-c-and-their-advantage-over-enum-datatype/).

### `namespace \<namespace name\>`
Everything after this line will be defined within the specified namespace. Namespaces define a name scope in C++. An object name can exist in one namespace and the same object name can exists in another namespace. In the same way that a variable name can exist in one class and the same variable name can exist in anther class. Usage: `<namespace>::<object>`. [More Info](https://www.geeksforgeeks.org/namespace-in-c/).

### `using namespace <namespace name> {}`
Inside of this closure, the C++ compiler will assume that you want to use the specified namespace. This is useful if many of your namespace uses are the same within a file. You can still use a typical namespace reference if you want within a `using namespace` closure.

### `[[nodiscard]]`
Welcome to the weirdest syntax you will ever seen in a programming language. This keyword goes before a method declaration and will give a warning if the return value of said method is discarded, i.e. not put into a variable. [More Info](https://en.cppreference.com/w/cpp/language/attributes/nodiscard).

### `virtual`
C++ functions are not able to be overriden by default. This keyword goes before a method declaration and allows it to be overriden. [More Info](https://www.geeksforgeeks.org/virtual-function-cpp/).

### `<method declaration> const`
When the `const` keyword is used after a method name in a declaration it makes it a const member function. Const member functions cannot change the values of memebr variables. Therefore, you can use a const method and be sure that you will not alter the state of the object you are calling it on. This is often used on getters. [More Info](https://www.geeksforgeeks.org/const-member-functions-c/#).

### `<method declaration> = 0`
This syntax makes the method a pure virtual function. This makes a class in which the method a part of abstract and unable to be instantiated without subclassing. In other words. This method does not have a body and MUST be overriden by a subclass. [More Info](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/).

### `<method declaration> = delete`
This syntax tells the compiler to disable the usages of this method. This is typically used on implicitly defined functions like copy constructor or copy assignment operator to ensure that they are not used. [More Info](https://www.ibm.com/docs/en/i/7.4?topic=definitions-deleted-functions-c11).

### `<method declaration> = default`
This explicitely tells the compiler to create the compiler default for this method. For example, if we wanted the deconstrcutor of a class to be overridable, we would need to declare it as such. However, the default deconstructor calls the destructors of the base class and members of the derived class. It would not do that if we defined it as virtual. Defining it as virtual default allows it to be overriden but if we do not is uses the default that is very helpful. [More Info](https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration).

## Moving and Copying Data
The following section covers various topics on moving and copying data and should hopfully clear up some of that standard syntax you see in our classes. Here are some relevent Cherno videos that you can follow up with some research:
- [lvalues and rvalues in C++](https://www.youtube.com/watch?v=fbYknr-HPYE&ab_channel=TheCherno)
- [Move Semantics in C++](https://www.youtube.com/watch?v=ehMg6zvXuMY&ab_channel=TheCherno)
- [std::move and the Move Assignment Operator in C++](https://www.youtube.com/watch?v=OWNeCTd7yQE&t=848s&ab_channel=TheCherno)

### `lvalues` and `rvalues`
These are different ways to describe how values are stored. You should watch [this video](https://www.youtube.com/watch?v=fbYknr-HPYE&ab_channel=TheCherno) to get a good in-depth explanation of `lvalues` and `rvalues`. Summed up, `lvalues` are values that have a storage location, like variables. `rvalues` are temporary values that do not have a location in memory, like literals. This matters most for method parameters. To specify a method parameter is an `lvalue`, use a single `&` after the parameter name. Just like you would for creating a reference variable. To specify a method parameter is an `rvalue`, use `&&` after the parameter name. 

### Copy Constructor: `<ClassName>(const <ClassName>&)`
Copy constructors are called whenever a `lvalue`, or object with a permanent location in memory is assigned to another `lvalue`. The compiler then assumes that you would like to make a copy of the object and then put that object in the new object. The copy operation can also be written as `<ClassName>& operator=(const <ClassName>&)` which denotes the exact operation described above. Typically we `delete` these constructors and operators in most of our classes as we do not want to copy them. Additionally, moving is much more memory and time efficient compared to copying.

### Move Constructor: `<ClassName>(<ClassName>&&)`
The move operation is called whenever an `rvalue`, or value without a permanent location in memory, is assigned to an `lvalue`. In this case the compiler assumes that you would like to move the temporary `rvalue` into the `lvalue`. the move operation can also be written like this: `<ClassName>& operator=(<ClassName>&&)` which denotes the equal sign to move an object when the input is a temporary `rvalue`. Typically we explicitly set the move operation and constructor of our classes to `default` to ensure that we have proper move operations. We tend to move data to new owners when creating larger data structures. 

### `std::move()`
This may look like a move operation, but although it is used often when moving, it is not. All that this method does is return the input as an `rvalue` allowing move operations to be called on the value. If you are planning on moving an object into ownership of another object, you should use this method to create an `rvalue` of that object and then assign it to it's new owner. 
