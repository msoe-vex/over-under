# spin-up
A Raider Robotics repository for VEXU Spin Up, with tooling for working inside a preconfigured vs-code dev container.

### Setup
This repository is setup as a visual studio code dev container. To work on code:
1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/).
2. Install [VS Code](https://code.visualstudio.com/). Note this is different from Visual Studio (which has a purple icon rather than a blue one).
3. Add the Dev Containers extension.
4. Open the command pallette using *Ctrl + Shift + P*, then search for *Dev Containers: Open Folder in Container* and select the folder containing a local copy of this repository.


### Organization
C++ source code is in `src`. Header files are defined in `include`.
Header files which use pros should include `main.h`, as that defines the pros library.

### Commands
Use `pros make` to build code.

In the event `pros make` builds successfully but fails to Link the project, try running `make clean` to delete any generated build files, then run `pros make` again.
<!-- * Use VS Code's **Run and Debug** menu (*Ctrl + Shift + D*) to compile and run programs in debugging mode. -->
<!-- * Run `make` to compile everything.
* Run `make clean` or `make purge` to cleanup generated files. -->

### Maintenance
* Programs which can be run should have corresponding tasks defined in `launch.json`, `tasks.json`, and `Makefile`.
* Packages are defined in `Dockerfile`. 
* VSCode extensions are defined in `devcontainer.json`.