#!/usr/bin/env python3
"""
Cooperate on the first round, then imitate opponent's previous move thereafter.
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
    while True:
        opp_defected = False
        cmd = sys.stdin.readline().rstrip()

        if cmd == 'quit':
            break

        if 'Round' in cmd:
            round_num = extract_num_val(cmd)
            if round_num == 1:
                print(f'{ParticipantCommands.COOPERATE.value}', flush=True)
            continue

        if 'Opponent' in cmd:
            opp_prev_move = extract_num_val(cmd)
            if opp_prev_move == ParticipantCommands.DEFECT.value:
                opp_defected = True

        if opp_defected:
            print(f'{ParticipantCommands.DEFECT.value}', flush=True)
        else:
            print(f'{ParticipantCommands.COOPERATE.value}', flush=True)
