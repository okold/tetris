# Tetris
An implementation of the game Tetris for the Atari ST.

This is an assignment for COMP 2659 - Computing Machinery II at Mount Royal University in the Winter 2020 semester, written by Olga Koldachenko and Colton Paquette to demonstrate knowlege of low-level programming.

## Compilation
This project uses the STeem emulator, which can be found at https://github.com/steem-engine/steem-engine. This also requires TOS 1.04 and the cc68x compiler, as well as a shell.

* Run your shell, gulam shell was used when making this project
* Navigate to the repository
* Run `make tetris`

## Known Issues
* There's no mapping for text/characters, and as such no score/menus. FONTLIB needs to be completely reimplimented.
* Interrupts have not been implemented. This requires a rewrite of the keyboard inputs and screen refreshes, as currently inputs are based on the character given through Cnecin() (see INPUT.C and part of MAIN.C). If you've got capslock on, you won't be able to move the tetronimos!
