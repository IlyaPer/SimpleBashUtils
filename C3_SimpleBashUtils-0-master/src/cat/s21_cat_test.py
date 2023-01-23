from os import system
import random
import subprocess

class bcolors:
    OKGREEN = '\033[92m'
    ENDC = '\033[0m'

flags = {
    '-b',
    '-e',
    '-n',
    '-s',
    # '-v',
    '-t'}

files = {
    '../samples/hello.txt',
    '../samples/hello1.txt',
    'test_1_cat.txt',
    # 'test_2_cat.txt',
    # 'test_3_cat.txt',
    # 'test_4_cat.txt',
    'test_5_cat.txt'}

    # 'boba.txt'}

my_cat = "./s21_cat"
cat = "cat"


for file in files:
    for flag in flags:
        # a = open(file_cat, "w")
        # b = open(file_s21cat, "w")

        str2 = cat + " " + flag + " " + file
        output = subprocess.check_output(str2, shell=True)
        # a.write(output)
        a = output

        str1 = my_cat + " " + flag + " " + file
        output = subprocess.check_output(str1, shell=True)
        # b.write(output)
        b = output
        # a, b = file_1.read(), file_2.read()
        if a != b:
            print("-----------------ERROR-----------------")
            print("cat command: " + str2)
            print("s21_cat command: " + str1)
            count = 0
            # print(a)
            print("-----------------ORIGINAL CAT-----------------")
            print(a)
            print("-----------------MY CAT-----------------")
            print(b)
            for i in range(len(a)):
                if a[i] != b[i]:
                    print("-----------------correct symbol is-----------------")
                    print("%s%s%s" % (a[i], " index: ", i))
                    print("-----------------my symbol is-----------------")
                    print("%s%s%s" % (b[i], " index: ", i))
                    exit()
            exit()
print(bcolors.OKGREEN + "ALL TESTS PASSED" + bcolors.ENDC)
                