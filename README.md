Dron
====

Dron (Dobi's Tron/Snake game) uses SFML 1.6 (http://www.sfml-dev.org) and is written in C++.
It is licensed unter the GNU General Public License version 3 or later (see LICENSE).

Dron is controlled via keyboard or joypad.
It can be played by 1-6 players, human or computer steered.
You can collect three different items
- the chartreuse one (an abridger) shortens your body immediately.
- The orange one (a battering ram) is reclined until you hit something.
- the violet one (a fragmenter) desintegrates your body immediately.
The little deviation from a classical tron concept towards a snake like game is intended
to reduce the needed precision of input timing and thus weight the tactical aspects more.
The Sound is generated via a software synthesizer and the graphics (lol) also get along
without external data.
GLSL is used for post processing the in game screen. If this is not possible on the the current hardware,
the game simply runs without these effect. 
See HACKING for a broad overview of the source code.

You are welcome to contact me for any kind of feedback (see AUTHORS).