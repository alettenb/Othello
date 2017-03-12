To make my AI tournament worty, I primarily created an alpha-beta pruning algorithm that
was fast enough to go to a good depth on my computer. No idea what that means on the
lab computers. Now, I actually made two alpha-beta pruning methods.
The first was the absolute one. This was just based off of their side minus
your side. The other one was position-based. Each square on the board was given
an integer value, and based on where the pieces were, a side would get a certain
value based on its positions on the board. The move function would use the 
position-based alpha-beta pruning in the beginning and middle sections of the
game, and at the end, it would use the absolute one to rack up as many points as possible.
I think that this will work because of that switch, along with the position-based algorithm.
my algorithm will be a step above everyone else's, for I am assuming that many of
them did just the absolute algorithm. I tried to do a mobility-based algorithm, but
that just segfaulted, and it would be easier to just make the position one.