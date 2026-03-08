# ttt

Tic Tac toe with a bot in the terminal

## Prerequisites

Check for the following programs:

* `g++` or `gcc`
* `make`

## Receiving the project

### Download the archive:

```bash
curl -L -o ttt.zip https://github.com/zverorx/ttt/archive/refs/tags/v2.zip
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

If you have a gcc compiler:

```bash
make CXX=gcc
```

## Usage

```bash
./bin/ttt
```

Follow the prompts on screen to play.

Have a nice game!

## Example of a game session

```
 _____________________________
|         Tic Tac Toe         |
|          GAME OVER          |
|        The winner is        |
|                             |
|          ><[O_O]><          |
|                             |
| Commands:                   |
| - quit (to exit)            |
| - rest (to restart)         |
|                             |
|       Come back again!      |
|_____________________________|

[=============================]
            0   1   2
           ___ ___ ___
        0 |_X_|___|_O_|
        1 |___|_X_|_O_|
        2 |___|___|_O_|

0> START
1> 2 2
1> 0 0
2> 1 2
2> 1 1
3> 0 2
```

## License

This project is licensed under the GPLv3. See the LICENSE file for more details.

## Feedback

To contact the developer, you can email zveror1806@gmail.com.
