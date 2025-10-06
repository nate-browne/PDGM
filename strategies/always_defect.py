#!/usr/bin/env python3
"""
This strategy is simple: always choose to defect no matter what.
"""

import sys
from enum import Enum

class ParticipantCommands(Enum):
    COOPERATE = 0
    DEFECT = 1
    NOOP = 2

if __name__ == '__main__':
    while True:
        line = sys.stdin.readline().rstrip()
        if line == 'quit':
            break

        print(f'{ParticipantCommands.DEFECT.value}', flush=True)
