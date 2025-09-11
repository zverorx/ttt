# ttt
Tic Tac Toe for two players in the terminal.

## Prerequisites
Check for the following programs:
* gcc
* make
* git

## Receiving the project
You can get the source code by cloning the repository using the command:
```
git clone https://github.com/zverorx/ttt.git
```

## Compilation and installation
 To install the program, run the following commands in the terminal window:
```
make
sudo make install
```
To change the installation path, use the CONFIG_PREFIX variable:
```
sudo make CONFIG_PREFIX=/home/user install
```

To find out more about Makefile features, run 
```
make help
```

## Usage
If installation is successful, enter in the terminal line:
```
ttt
```
You will see some information about the game, a playing field and an invitation to enter.
```
 _____________________________
|         Tic Tac Toe         |
| To move, enter the row and  |
| column separated by a space.|
|                             |
| Commands:                   |
| q - exit                    |
| r - restart                 |
| n - rename                  |
|                             |
| Enjoy the game!             |
|_____________________________|

	    0   1   2
	   ___ ___ ___
	0 |___|___|___|
	1 |___|___|___|
	2 |___|___|___|

> Player_1: 
```
Enter two numbers from 0 to 2, the first number is the row number, the second is the column number and press Enter.
Your first move is done! Good luck in winning.

Don't forget the tips at the top, type 'q' to quit, 'n' to rename yourself and 'r' to start over.

## Removal
To remove, use the command:
```
sudo make uninstall
```
## License
This project is licensed under the GPLv3 license. See the LICENSE file for more details.

## Feedback
To contact the developer, you can contact by email zveror1806@gmail.com
