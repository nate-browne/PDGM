#!/usr/bin/env python3
"""
Cooperate unless defected against twice in a row. Must be in a row.
"""

import re
import sys
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
    defect_count = 0
    while True:
        cmd = sys.stdin.readline().rstrip()

        if cmd == 'quit':
            break

        if 'Round' in cmd:
            round_num = extract_num_val(cmd)
            if round_num == 1:
                print(f'{ParticipantCommands.COOPERATE.value}')
            continue

        if 'Opponent' in cmd:
            opp_prev_move = extract_num_val(cmd)
            if opp_prev_move == ParticipantCommands.DEFECT.value:
                defect_count += 1
            else:
                defect_count = 0

        if defect_count >= 2:
            print(f'{ParticipantCommands.DEFECT.value}')
        else:
            print(f'{ParticipantCommands.COOPERATE.value}')
