# TOTAL:
- GUI -> ~30%
- LOGIC -> 100%
- DATA -> 0%
***

Priority. [^1]
[^1]: Smaller number; more important
***
### Project structure
- [x] Should be refactored

## GUI

- [ ] :
<details>
  <summary>create default menu -> ~%90</summary>
Data required, continue game, stats window - should be implemented.
</details>

> priority: 2


- [ ] :
<details>
  <summary>UI should be implemented for Sudoku mesh</summary>
<p>remove console debuging, output Sudoku game into GUI
<p>GUI structure and logic:
<p>Sudoku consists of 9x9 mesh where each submesh is 3x3 where each cell is 1x1. Each cell is separate Window.
<p>Window class structure:
<pre>
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
</pre>
possibly  converted into passive if correct number was inserte
</details>

> priority: 1

- [ ] :
<details>
    <summary>advanced </summary>
<p>Creating advanced style and interface;
</details>

> priority: 5

## Logic
- [x] puzzle must be puzzle -> 100%

## Data
- [ ] :
<details>
  <summary>storage i/o</summary>
<p>Implement two types of data and i/o logic
</details>

> priority 3
- [ ] :
<details>
  <summary>type 1: binary </summary>
<p>Personal records, ability to continue game if it was closed etc.
<p>Some sort of game content which should not be stored in executable binary
</details>

> priority: 3

- [ ] :
<details>
<summary>type 2: text </summary>
<p>Configs for visual part of App
</details>

> priority 6  


