# import pyautogui as gui
# import time

# # pause 3 seconds while you set focus to the terminal/console window:
# print('Click on the terminal/console window where the automated keyboard data needs to be entered...')
# print('NOTE: You have 5 seconds to do this!')
# time.sleep(3)

# # auto type test data from text file:
# with open('a2ms2_4-long-inputs.txt', 'r') as tst:
#     time.sleep(1)
#     tst = tst.readlines()
#     for i in range(0, len(tst), 1):
#         print(tst[i])
#         gui.typewrite(tst[i])
#         time.sleep(0.3)
# print('Auto data input completed.')

import os
import sys
import time

import pyautogui

time.sleep(3)
line_number = 0
with open('a2ms2_4-long-inputs.txt', 'r', encoding='utf-8') as f:
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
