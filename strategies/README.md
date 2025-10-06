# Strategies

This is the folder where you can add your game-playing strategies for use inside of the Prisoner's
Dilemmma tournament client.

You can look at the provided examples for guidance on implementing your own, but the basics are as follows:

1. PDGM will first tell your bot what round number it is. Format will be "Round: %d"
2. PDGM will next (if it's not round 1) tell you what your opponent did on the previous turn.
3. PDGM will then wait for you to print out your move. Print it to the standard output (PDGM will have captured your
process' stdin and stdout). Print '0' if you want to collaborate, and print '1' if you want to defect.
4. When everything is all done, PDGM will tell your bot 'quit'. Exit your loop once this happens.

There could be some more messaging implemented in the future to allow for more complex strategies to be implemented
(such as "Discriminating Altruist") but that's a future thing.

If you're curious about some of the available strategies, check out [this list](https://plato.stanford.edu/entries/prisoner-dilemma/strategy-table.html).

You can implement strategies in whatever programming language you wish provided you can read from `stdin` and print to `stdout` in
some way. This is how PDGM interacts with the bots, so you need to be able to do that.
