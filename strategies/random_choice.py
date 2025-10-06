#!/usr/bin/env python3
"""
This strategy is that the choice to cooperate or defect is a coin flip.
Not much really goes into this other than randomly deciding what to do and reporting
back, so this is one of the simplest strategies (other than perma doing one thing).
"""

import sys
import random
from enum import Enum

class ParticipantCommands(Enum):
    COOPERATE = 0
    DEFECT = 1
    NOOP = 2

if __name__ == '__main__':
    random.seed()

    while True:
        line = sys.stdin.readline().rstrip()
        if line == 'quit':
            break

        if random.randrange(300) % 2 == 0:
            print(f"{ParticipantCommands.COOPERATE.value}", flush=True)
        else:
            print(f'{ParticipantCommands.DEFECT.value}', flush=True)
