# auto input script for A1-MS1

import os
import sys
import time

import pyautogui

if len(sys.argv) < 2:
    print("Usage: python autogui.py input_file.txt")
    sys.exit(-1)

time.sleep(3)
line_number = 0
with open(sys.argv[1], 'r', encoding='utf-8') as f:
    for line in f:
        line = line.replace('\n', '')
        line_number += 1
        print(f'Processing input line {line_number}:', end=' ')
        if line:
            print(f'{line}', end=' ')
            pyautogui.typewrite(line)
            time.sleep(0.2)
        print(f'ENTER')
        pyautogui.press("enter")