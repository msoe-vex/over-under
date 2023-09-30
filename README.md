# Raider Robotics Over Under Project
<!-- add a CI status here when we have that -->

PROS workspace for the 2023-2024 VEX U game Over Under.

## Reccomended Tools
[Visual Studio Code](https://code.visualstudio.com/)

### Git Tools:
We use Git to organize our software development. There are two main ways to interact with Git. There is the [Command Line Interface (CLI)](https://git-scm.com/downloads) that has you using commands in shell. There are also a few different GUI applications that can be used to interact with Git. My personal favorites are [GitHub Desktop](https://desktop.github.com/) and [Sublime Merge](https://www.sublimemerge.com/). GitHub Desktop is a little more user friendly but Sublime Merge has a better branch visualizer. I personally user GitHub Desktop most of the time.

## Cloning the Repository
<!-- To build this project with Docker Desktop, autocrlf must be set to false in Git **before cloning**. This can be done with the following command:

`git config --global core.autocrlf false` -->
You can clone the resposity using the built in funtionality in most Git GUI applications once you login with your GitHub account. If you choose to do it using the command line, you can do it through HTTPS or SSH. Either will work just fine but I reccomend setting up SSH at some point in your GitHub account as it is more secure and professional. 

If you are using the command line, run the below command in the folder that you want the the `over-under` project folder to exist INSIDE OF. In other words, don't make an `over-under` folder and run the command inside of that, you will have two layers of `over-under`. You should create a folder to hold repositories in and run the below command in there. Command to run: `git clone` followed by the path copies from the repo's green Code button like the image below. If you are using SSH, it should look like: `git clone git@github.com:msoe-vex/over-under.git`

## Development Environment Options
### Docker Containers through VSCode's Dev Containers
This option utilizes VSCode's Dev Containers extension to open the project within a Linux Docker Container that has a full Rust development environment as well as all required and reccomended extentions. This option also containerizes this development environment so that it doesn't mess with anything else on your computer.

## Using PROS and vex-rt
Opening a terminal in VSCode should gain you access to the PROS CLI and Cargo, Rust's package manager.

**Building and uploading the program:** In order to upload the program, first run the command `cargo run` in the terminal. This command runs a script called `upload.sh` in the `build` directory, which handles building the project. Next, run the command `pros upload` in a terminal **outside of the dev container**. This command will upload the code to the currently connected VEX Brain or Controller. Brains or Controllers should be connected to laptops with a USB cable. The command cannot be run inside the dev container due to WSL not detecting the V5 brain.

**Another useful PROS command:** `pros ut` will upload the built code to the currently connected VEX Brain or Controller and display the Brain's output on the terminal where the command was run.

**Another useful Cargo command:** `cargo check` will check the project for errors. This command is also automatically run by the Rust Analyzer VS Code extenstion.

## Troubleshooting

### vex-rt
1. go to https://discord.gg/UBuzRySp and ask `@magik` from QUEEN for help
2. if they don't respond: good luck


### PROS
If you have any issues with PROS, especially if you are getting error messages about the PROS Toolchain. Restarting your computer works more often than it should. You can also try uninstalling PROS from the Exention and doing the same with the extension yourself. If you are still having issues or are having other issues, constact a veteran member.


