For some, the pthreads library might be working on their native environments on Windows and that’s most likely because MinGW provides a wrapper for pthreads which automatically converts the pthreads code to equivalent multi-threaded Windows API code. From what I have read, it works fine on almost all of the basic functionality and more. 

If you want to run Linux as a virtual machine to run your code but it ends up eating a whole lot of ram and resources of your laptop and everything becomes choppy, then try Windows Subsystem for Linux (WSL). It is essentially a virtual machine software built right into your OS minus the whole graphical user interface. Consequently, it ends up being very resource friendly. You can also then use VSCode with all its features and IntelliSense through an extension and run everything as if it’s running natively.

## Pre-Requisites:

1)	Enable Virtualization in BIOS
If you performed Lab 1 and was able to install VMWare without any problem then you already have virtualization enabled. If not, go to your BIOS settings and enable it. Each bios is different but its usually under ‘Device Security’ or something along the lines.
Note for all my fellow Valorant players, if do not have TPM 2.0, then Vanguard won’t let you play with virtualization enabled. This applies to LoL as well I believe. 

## Steps:

### 1)	Install WSL
If you are on Windows 11, chances are you already have WSL installed on your system. 
If you are on Windows 10, download WSL from Microsoft Store.

### 2)	Update WSL
Note: If you are in the WSL terminal window (the penguin logo), then write ‘wsl.exe’ with each command. Command prompt, PowerShell works with both. 
Any command with <> written, replace it with your respective selection. Do NOT include the <>
```
wsl.exe –update
```

### 3)	Install Linux Distro
```
wsl –install
```
Two dashes before install. Installs the default distro (Ubuntu). You can install a range of other distros as well. Type in its name after install <space> <distro_name>

### 4)	Run the distro
```
wsl -d <distro_name>
```
If you went with the default Ubuntu then type ubuntu. 
You can also install ‘Windows Terminal’ app from Microsoft Store and it can the drop-down menu next to the new tab button from which you can open your distro.
Setup your user and password

### 5)	Updating and Installing packages
```
sudo apt update // download the updated packages
sudo apt upgrade // install them
sudo apt autoremove //remove old dependencies
sudo apt install gcc // install compiler
```

### 6)	Accessing Files
Navigate between files and directories using bash commands we studied in Lab 1. 
By default, the working directory is the home directory of the user on a virtual drive. To access the files on Windows drive, you don’t have to manually mount the drives since its already done. Access them with the following command:
```
cd /mnt/<drive_letter>
```

### 7)	Running the code
Now that you are in your directory where your code exists, type the following to compile the code:`
```
gcc <file_name>.c -o <output_name>.exe -pthread
```
An executable file should appear in your directory. If error occurs during compilation, then they will be displayed there. 
After compiling, to run the code, run the exe file:
```
./<output_name>.exe 
```
and viola, the code executes. 

### 8)	Running with VSCode
To run the code directory from VSCode terminal and not have red errors everywhere in your code, do the following. It will also give autocomplete and IntelliSense which cannot work well when there are errors in your file.
i.	Install ‘WSL’ Extension by Microsoft in VSCode 
ii.	In your code directory, type the following:
```
code .
```

It will install the vscode server when executing the command for the first time. VSCode should open now running Ubuntu and WSL. Now its like running VSCode on a Linux machine. The terminal is bash by default. Use it to run the code using the command from step 7. 

