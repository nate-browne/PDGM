"""
This strategy is that the choice to cooperate or defect is a coin flip.
Not much really goes into this other than randomly deciding what to do and reporting
back, so this is one of the simplest strategies (other than perma doing one thing).
"""
#!/usr/bin/env python3

import sys
import random

if __name__ == '__main__':
    random.seed()

    while line := sys.stdin.readline().rstrip() != "quit":
        if random.randrange(300) % 2 == 0:
            print("0")
        else:
            print("1")
