## 📄 __Ruby__ - game engine for visual novels
___ 

### Requirements

+ Compiler with support C++23
+ CMake >= 3.5
+ OS Windows
___

### Quick start

All the required libraries are already installed in the __extern__ folder, so you don't need to install anything externally.

There are two compilation flags: compile engine dll and compile demo project. The _build.py_ script located in the __scripts__ folder is responsible for compiling both. To start building:

```powershell
python3 scripts/build.py ?<flags>?
```
Where _flags_ are the compilation flags mentioned above. There are currently two flags available:
1) -dll : is responsible for compiling the engine itself (its dll). Accepts either __true__ or __false__ as input in any register.
2) -pg : is responsible for assembling the demo project (playground). Accepts the same values as -dll.

By default, (when launched without specifying flags), -dll is set to __true__, and -pg is set to __false__.