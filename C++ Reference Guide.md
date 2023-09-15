### `enum class {}`
Class enums are both strongly typed and strongly scoped. This means that they do not automatically convert to ints and do not compare themselves to other enumerations. This helps avoid mistakes with many different enums.

### `namespace \<namespace name\> {}`
Everything within this closure will be defined within the specified namespace. Namespaces define a name scope in C++. An object name can exist in one namespace and the same object name can exists in another namespace. In the same way that a variable name can exist in one class and the same variable name can exist in anther class. Usage: `<namespace>::<object>`.

### `using namespace <namespace name> {}`
Inside of this closure, the C++ compiler will assume that you want to use the specified namespace. This is useful if many of your namespace uses are the same within a file. You can still use a typical namespace reference if you want within a `using namespace` closure.

### `[[nodiscard]]`
Welcome to the weirdest syntax you will ever seen in a programming language. This keyword goes before a method declaration and will give a warning if the return value of said method is discarded, i.e. not put into a variable.

### `virtual`
C++ functions are not able to be overriden by default. This keyword goes before a method declaration and allows it to be overriden.

### `<method declaration> const`
When the `const` keyword is used after a method name in a declaration it makes it a const member function. Const member functions cannot change the values of memebr variables. Therefore, you can use a const method and be sure that you will not alter the state of the object you are calling it on. This is often used on getters.

### `<method declaration> = 0`
This syntax makes the method a pure virtual function. This makes a class in which the method a part of abstract and unable to be instantiated without subclassing. In other words. This method does not have a body and MUST be overriden by a subclass.

### `<method declaration> = delete`
This syntax 
