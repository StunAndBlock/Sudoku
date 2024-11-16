# TOTAL:
- GUI -> 0%
- LOGIC -> ~90%
- DATA -> 0%
***

Priority. [^1]
[^1]: Smaller number; more important
***
### Project structure
Should be refactored

## GUI
<details>
  <summary >create default menu</summary>
starting game, personal records, etc.
personal records require work with Data
</details>

> priority: 2

<details>
  <summary>default WinApi UI should be implemented </summary>
remove console debuging, output Sudoku game into GUI
GUI structure and logic:
Sudoku consists of 9x9 mesh where each submesh is 3x3 where each cell is 1x1. Each cell is separate Window.
Window class structure:
class baseCell{
    protected:
        HWND hMain_;
    ...
}
//* only displaing number of Sudoku *//
class passiveCell : private baseCell{
    ...
}
//* interactive, this is missing spot where certain number can be inserted *//
class activeCell : private baseCell{
    ...
}
possibly  converted into passive if correct number was inserte
</details>

> priority: 2

<details>
    <summary>advanced </summary>
Creating advanced style and interface;
</details>

> priority: 5

## Logic

<details>
  <summary>puzzle must be puzzle</summary>
Everything except generating missing fields is done
</details>

> priority: 1

## Data
<details>
  <summary>storage i/o</summary>
Implement two types of data and i/o logic
</details>

> priority 3
<details>
  <summary>type 1: binary </summary>
Personal records, ability to continue game if it was closed etc.
Some sort of game content which should not be stored in executable binary
</details>

> priority: 3

<summary>type 2: text </summary>
Configs for visual part of App
</details>

> priority 6  


