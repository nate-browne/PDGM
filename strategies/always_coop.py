"""
This strategy is simple: always choose to cooperate no matter what.
"""
#!/usr/bin/env python3

import sys

if __name__ == '__main__':
    while line := sys.stdin.readline().rstrip() != "quit":
        print("0")

