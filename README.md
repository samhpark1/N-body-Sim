# N-body-Sim
Elementary n-body simulation accounting only for baryonic matter and ignoring particles g forces on each other
## How to run
SFML is required to run this program
* MacOS
  ```console
  brew install sfml
  ```
* Linux
  ```console
  sudo apt update
  sudo apt install libsfml-dev
  ```
##Compilation
```console
g++  main.cpp -I<path_to_SFML> -L<path_to_SFML> -lsfml-graphics -lsfml-window -lsfml-system
```
##Execution
```console
./a.out <number of particles> <time value scalar>
```
* number of particles: depends on computational power of computer, recommend starting at 5000
* time value scalar: scalar to speed/slow simulation
  * default: 1
  * suggested max: 5
  * (NOTE: increasing excessively will result in inaccuracies)
    
