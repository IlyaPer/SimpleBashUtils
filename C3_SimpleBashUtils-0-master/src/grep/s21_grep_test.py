from os import system
import random
import subprocess

class bcolors:
    OKGREEN = '\033[92m'
    ENDC = '\033[0m'

flags = {
    'e',
    'l',
    'i',
    'n',
    'o',
    'v',
    'h',
    'c',
    's'}

pattern = "tab"

files = {
    '../samples/hello.txt',
    '../samples/hello1.txt'}
    # 'biba.txt' 
    # 'boba.txt'}

my_grep = "./s21_grep"
grep = "grep"

for file in files:
    for flag in flags:
        str2 = grep + " -" + flag + " " + pattern + " " + file
        output = subprocess.check_output(str2, shell=True)
        a = output

        str1 = my_grep + " -" + flag + " " + pattern + " " + file
        output = subprocess.check_output(str1, shell=True)
        b = output
        if a != b:
            print("-----------------ERROR-----------------")
            print("gre command: " + str2)
            print("s21_grep command: " + str1)
            
            print("-----------------ORIGINAL GREP-----------------")
            print(a)
            print("-----------------MY GREP-----------------")
            print(b)
            for i in range(len(a)):
                if len(a) == 0:
                    print("-----------------first symbol mistake-----------------")
                if a[i] != b[i]:
                    print("-----------------correct symbol is-----------------")
                    print("%s%s%s" % (a[i], " index: ", i))
                    print("-----------------my symbol is-----------------")
                    print("%s%s%s" % (b[i], " index: ", i))
                    exit()
            exit()
print(bcolors.OKGREEN + "ALL TESTS WITH ONE FLAG PASSED" + bcolors.ENDC)
print("----------------SEVERAL FLAGS-----------------")

for file in files:
    for flag in flags:
        for flag2 in flags:
            #  lc flag combination was not checked!
            if flag == flag2 or flag == 'e' or flag2 == 'e' or (flag == 'l' and flag2 == 'c') or (flag == 'c' and flag2 == 'l'):
                continue
            str2 = grep + " " + pattern + " -" + flag + flag2 + " " + file
            print(str2)
            output = subprocess.check_output(str2, shell=True)
            a = output

            str1 = my_grep + " " + pattern + " -" + flag + flag2 + " " + file
            output = subprocess.check_output(str1, shell=True)
            b = output
            if a != b:
                print("-----------------ERROR-----------------")
                print("grep command: " + str2)
                print("s21_grep command: " + str1)
                count = 0
                print("-----------------ORIGINAL GREP-----------------")
                print(a)
                print("-----------------MY GREP-----------------")
                print(b)
                for i in range(len(a)):
                    if a[i] != b[i]:
                        print("-----------------correct symbol is-----------------")
                        print("%s%s%s" % (a[i], " index: ", i))
                        print("-----------------my symbol is-----------------")
                        print("%s%s%s" % (b[i], " index: ", i))
                        exit()
                exit()
print(bcolors.OKGREEN + "ALL TESTS WITH SEVERAL FLAGS PASSED" + bcolors.ENDC)