# Lem-in

Final grade 125/100 (full bonus)<br>
* `Processing maps of 5000 rooms / 10000 pipes in less than 12 seconds to validate`
* `In less than 3 seconds for max grade`
* `Those maps are processed in 0.03 to 0.07 sec`

Lem-in is an algorithm project, where ants have to go the fastest as posible from start-room to end-room.<br>

## Challenge

Find the shortest path to get **n** ants across a colony (comprised of rooms and tunnels). <br>
<br>
At the beginning of the game, all the ants are in the room **##start**.<br>
The goal is to bring them to the room **##end** with as few moves as possible. <br>
<strong>Each room can only contain one ant at a time (except at **##start** and **##end** which can contain as many ants as necessary). <br></strong>
<br>
Some maps will have many rooms and many links, but no path between **start** and **end**. <br>
Some maps will have rooms that link to themselves, sending your path-search spinning in circles. <br>
Some maps will have too many/too few ants, no start or end, duplicate rooms, links to unknown rooms, <br>
rooms with invalid coordinates, and a variety of other invalid or poorly-formatted input. <br>
<br>
* `Instructions: as many files as you want`
* [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf) `maximum 5 functions per file, maximum 25 lines per function`
* `Additional personal goal: only 2 files + all the bonuses`


## Algorithm

I tried to copy the behavior of quantum computers.<br>
I explore the paths and when they split I duplicate my data and keep exploring.<br>
Depending on the number of ants, after a certain number of steps discovering new paths does not shorten the migration anymore, so the search stops.<br>
Finally I print the migration of the ants.<br>

## Understanding the maps
```
10          // ants number
1 250 150   // Room name (1) ants it's X-Y coordonates
2 550 150
3 550 450
##start     // Next room will be start room
4 250 450
##end       // Next room will be end room
5 850 450
6 850 150
1-2         // Relations between rooms. Room 1 and 2 are linked
1-3
1-4
2-4
2-6
2-5
3-4
3-5
3-6
5-6
```

## Understanding the output

L[ant]-[room]
```
L1-2 L2-3                // Turn 1 : ant number 1 go to room 2. Ant number 2 go to room 3
L1-5 L3-2 L2-5 L4-3
L3-5 L5-2 L4-5 L6-3
L5-5 L7-2 L6-5 L8-3
L7-5 L9-2 L8-5 L10-3
L9-5 L10-5
```

## Installation

* `git clone https://github.com/aumanuel/42_lem-in.git`

## Usage
Run ```make```.
```
$>./lem-in < maps/3.unicode.map
```

