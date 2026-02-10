# ttt

Tic Tac Toe for two players in the terminal

## Prerequisites

Check for the following programs:

* `gcc`
* `make`

## Receiving the project

### Download the archive:

```bash
curl -L -o ttt.zip https://github.com/zverorx/ttt/archive/refs/tags/v1.zip
```

```bash
unzip ttt.zip
```

### Clone a repository:

```bash
git clone https://github.com/zverorx/ttt.git
```

## Compilation

Go to the source directory and run:

```bash
make
```

To find out more about Makefile features, run: 

```
make help
```

## Usage

```bash
$ ./ttt
```

The result of executing the command:

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

## License

This project is licensed under the GPLv3. See the LICENSE file for more details.

## Feedback

To contact the developer, you can email zveror1806@gmail.com.
