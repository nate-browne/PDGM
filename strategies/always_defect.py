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
    while line := sys.stdin.readline().rstrip() != "quit":
        print(f'{ParticipantCommands.DEFECT.value}')

