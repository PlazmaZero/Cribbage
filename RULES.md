# The Rules
Cribbage is a game with multiple parts and scoring options. It has many rules. The rules are not shared across all cultures that play this game, so I have included the rules used in my implementation down below.

## The Goal
The winner is the person who gets 121 points first. When there are four players, there are teams of two that compete to get to 121 points first. If a player crosses the finish line before another player hits 90 points, the behind player is considered "Skunked". If the player did not even hit 60 points, the player is "double skunked". Until a player hits 121 points, the game goes in several rounds of two parts.

## Terminology
"Hand" : Four cards of the standard 52 card deck. The hand is used in play and show rounds.
"Crib" : An extra hand assigned to the dealer. Each player puts one card into the crib. 
"Turn-up": After the crib is allocated, an extra card is taken from the deck. All players use this card in scoring, but no one may use it in play.
"Knobs" : When the turn-up is a Jack, the player with the crib gets an extra point. When a player has a Jack in their hand the same suite as the turn-up, that player gets a point.
"Flush" : A full hand with the same suite. In the crib, the turn-up card must also match. In the hand, the turn-up card is not required to match. A flush is worth however many cards made up the flush.
"Run" : A set of 3 or more cards in a sequence. ex: Ace, 2, 3 or 10, J, Q, K. The King does not wrap around to the Ace. The run is scored with as many points as there are cards in the run.
"Pair": Two of a kind, worth two points.
"Fifteen": Any number of cards that add up to the number 15. Ace is a 1. Jack, Queen, and King are all scored at 10. All fifteens are worth two points.
"Play": The portion of the round where players place their cards around the table to get points.
"Show": The portion of the round where players score their hands.

## The Set Up
Each round is reset. The player with the "crib" deals cards to each of the other players. In traditional two-player cribbage, each player gets 6 cards. Four cards go to the hand and two cards from each player go to the crib. When there are three or four players, each player gets 5 cards and extra cards from the deck are added as needed to get the crib to four cards. In ten-hand cribbage, which is an alteration designed to make the game more challenging, each player gets 10 cards. They make two hands of four cards and then send two cards to the crib. With more than one player, ten-hand really becomes 9-hand, as each player gets nine cards. After players have selected the cards to keep, the turn-up is flipped over. If the turn-up is a Jack, the player who dealt gets a point.

## The Play
The person to the right of the dealer starts. Points are accumulated through the round, and players are required to make their most recent card visible. If at any point, a player or team crosses 121 points, the game has been won. Points can be accumulated in play as follows:
- Score a 15: Two points
- Score a pair: Two points
- Three of a kind: Six points
- Four of a kind: Twelve points
- Score a 31: Two points
- Be the last player to go: One point
- A run: as many points as cards in a run. Note that a run's cards do not need to be in sequence during play. A <3, 2, 4> counts as a run of three. However, duplicate numbers do stop a run. <3, 2, 2, 4> is not a run.

A round can get to a maximum of 31 points. If a player cannot put down a card within that limit, they are skipped. A player must place a card if they have a card that works. The next round starts to the right of the last player to place a card. This portion of the game stops when every player runs out of cards. A player can play off their own card, if every other player must be skipped.

## The Show
After the play, each player is given the opportunity to show their cards. Each hand is scored for flushes, runs, pairs, knobs, and fifteens. The scoring goes from the player to the right of the dealer to the dealer. Once the dealer scores their playing hand, they score their crib. If at any point, the score of a player or team passes 121, the game has been won. During ten hand cribbage, where each player has at least one crib, every player's playing hand is counted before counting any of the crib hands.

### The Show - Stealing The Show
In some variations of cribbage, players can earn more points in the show. If a player says their point total aloud, but is short what their hand actually gives, then the player who catches it can steal the points. This is not included in my version, since a computer will always count for its points by default. It is also rare for elite cribbage players to miss points, so training with it was irrelevant.

## Reset
If the "Show" ends with no winner, another round is dealt. The crib moves one to the right, following the motion of play. 

