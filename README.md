# Cribbage
[Cribbage](https://en.wikipedia.org/wiki/Cribbage) is a two to four player English card game from the 17th century.
It is complicated game. There are two parts to each round (play and show) and eight different scoring options. It is played with the standard deck of cards, and the player only knows the five to ten cards in their own hand. This makes it an optimal game for a computer to play. 

## Play the Game
The game can be played [here](https://onlinegdb.com/NT7I4K1ST). Hit the "start" button at the top. You can select from playing a real game or just drilling card selections. The game rules are fairly long, so I included another markdown file in the Github, called [RULES.md](https://github.com/PlazmaZero/Cribbage/blob/main/RULES.md).

## The Inspiration

### Why Cribbage?
One of my roommates used to play in cribbage tournaments. . In addition to being able to play full games, the app can drill specifically the choice of card allocation, the most influential part of the game. Being able to practice my weaknesses with rapid feedback helped me grow as a player. 

### Why C++?
Using the low-level language C++ lets the program calculate the expected value of hundreds of combinations very quickly. Python would have been noticably slower. The goal was a no-frills application to learn quickly. C++ in terminal was the right choice. I have programmed recently in C, for my hardware engineering course, but it has been some time since I used C++. This program allowed me to practice clean coding styles specific to C++, like separating a class into .h and .cpp files.

## Technical Challenges and Notes

### Technical Challenges
- Scoring the hands was more complicated than expected. Humans can identify multiple runs fairly quickly, but the computer differentiating between two runs of three and three runs of three was harder to code than anticipated. I worked through real examples to determine how to calculate a run based on frequency counts of card numbers.
- Determining when the "ten-hand" and normal cribbage versions should separate in the code and when they should align was difficult. Though I have played both versions, I had to notice when parts of play were more similar than they were different.
- The algorithm needed to be as fast as possible, so organizing the code to meet this requirement was necessary. Items are passed by reference where possible, to avoid the cost of copying. The scoring functions that rely on the same frequency counts do not repeat the work. 

### Clean Code
- Separated Class header and content files
- Use of OOP, one class for a "card" and one class for a "player"
- Use of class variables for the game version, number of players, and turn-up card - all of which are shared by all the players
- Use of macros for hard-coded numbers to make them more understandable
- Naming conventions were kept standard, get, set, score, etc
- Unit Testing Suite, to make sure scoring functions were working as anticipated
- Use of private and public variables to make sure only intended functions can alter the object variables







