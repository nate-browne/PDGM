# PDGM - a Prisoner's Dilemma Tournament Game Manager

This project is a simple C project that implements a tournament manager for a [Prisoner's Dilemma](https://en.wikipedia.org/wiki/Prisoner%27s_dilemma) simluator. If you've never heard of the Prisoner's Dilemma, follow the previous link.

While this problem is quite famous in game theory and often used as justification for capitalism, it's actually not
a great model of actual human behavior by any means. That said, it's still fun to have it play out.

The way this program works is that you feed it two strategy programs to run (see the [strategy README](./strategies/README.md) for more on those programs), and it starts them up and communicates with them to simulate the problem. It runs x number of games somewhere around 200 rounds per game, where x is a number that is at least 3 and can be larger depending on your desired amount of games.
