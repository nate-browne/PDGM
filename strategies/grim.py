#!/usr/bin/env python3
"""
This strategy is also pretty simple: cooperate until your opponent has defected
at least once. Then, always defect. It's a very vengeful strategy.
"""

import sys
import re
from enum import Enum

class ParticipantCommands(Enum):
    COOPERATE = 0
    DEFECT = 1
    NOOP = 2

def extract_num_val(s: str) -> int:
    """
    Uses regex to extract a number from a string.
    Used to parse a command.
    """
    return int(re.findall(r'\d+', s)[0])

if __name__ == '__main__':
    opp_defected = False
    while True:
        cmd = sys.stdin.readline().rstrip()

        if cmd == 'quit':
            break

        if 'Round:' in cmd:
            continue

        if 'Opponent' in cmd:
            opp_prev_move = extract_num_val(cmd)
            if opp_prev_move == ParticipantCommands.DEFECT.value:
                opp_defected = True

        if opp_defected:
            print(f'{ParticipantCommands.DEFECT.value}')
        else:
            print(f'{ParticipantCommands.COOPERATE.value}')