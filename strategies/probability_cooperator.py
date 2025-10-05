#!/usr/bin/env python3
"""
This strategy is also pretty simple: cooperate with fixed probability p where
 0 <= p <= 1
"""

import sys
import random
from enum import Enum

COLLABORATION_PROBABILITY = 45  # 45% chance to collaborate

class ParticipantCommands(Enum):
    COOPERATE = 0
    DEFECT = 1
    NOOP = 2

if __name__ == '__main__':
    random.seed()

    while cmd := sys.stdin.readline().rstrip() != 'quit':
        if random.randrange(100) <= COLLABORATION_PROBABILITY:
            print(f'{ParticipantCommands.COOPERATE.value}')
        else:
            print(f'{ParticipantCommands.DEFECT.value}')
