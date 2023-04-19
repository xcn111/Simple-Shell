# 学校的大作业，代码很乱请多多包涵

# Simple Shell

#### The shell supports the following commands:

i. cd <directory> - Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.

ii. clr - Clear the screen.

iii. dir <directory> - List the contents of directory <directory>.

iv. environ - List all the environment strings.

v. echo <comment> - Display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).

vi. help - Display the user manual using the more filter.

vii. pause - Pause operation of the shell until 'Enter' is pressed.

viii. quit - Quit the shell.

ix. myshell batcfile - Take its command lines from a file where is located at <batchfile>.

#### The shell supports I/O redirection:

< inputfile : redirect the input to inputfile.

\> outputfile : redirect the output to outputfile.

\>> outputfile : redirect the output to outputfile, create "outputfile" if it does not exist.

#### The shell supports background execution of programs:

An '&' at the end of command line indicates that the program should be executed in the background, which means the program will be executed in a child process.



#### Here's an example of the shell

input:

```
dir
cd /home/john
dir
echo hello world &
pause

quit
```

the shell display:

```
/home/john/projects/test >dir
myshell  myshell.cpp  README  txt
/home/john/projects/test >cd /home/john
/home/john >dir 
下载     Documents  Music     projects    snap       test.sh.save
Desktop  Downloads  Pictures  Public    Templates  Videos
/home/john >echo hello world &
hello world
/home/john >pause
Press Enter to continue...

/home/john >quit
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-q2qjx0lg.yts" 1>"/tmp/Microsoft-MIEngine-Out-3ilps1vh.1ho"

按任意键继续...

```
