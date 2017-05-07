#!/usr/bin/python

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def chooseline(self):
        return random.choice(self.lines)

def main():
    version_msg = "%prog 2.0"
    usage_msg = "usage: %prog [options] arg1 arg2"


    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-1", action="store_true", dest="suppress1", default=False,\
     help="Suppress printing of column 1.")
    parser.add_option("-2", action="store_true", dest="suppress2", default=False,\
     help="Suppress printing of column 2.")
    parser.add_option("-3", action="store_true", dest="suppress3", default=False,\
     help="Suppress printing of column 3.")
    parser.add_option("-u", action="store_true", dest="unsort", default=False,\
     help="Unsort ")
    options, args = parser.parse_args(sys.argv[1:])


    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    if len(args) != 2:
        parser.error("wrong number of operands")
    input_file = args[0]


    # Verify the input files are of the correct format #

    file1=args[0]
    file2=args[1]
    fileOpen1=[]
    fileOpen2=[]
    if file1=="-" and file2=="-":
        print("Both files can not be read from Standard Input. Exit with error.")
        exit()
    elif file1=="-" and file2!="-":
        fileOpen1=sys.stdin.readlines()
        fileOpen2=open(file2, 'r')
    elif file1!="-" and file2=="-":
        fileOpen1=open(file1, 'r')
        fileOpen2=sys.stdin.readlines()
    else:
        fileOpen1=open(file1, 'r')
        fileOpen2=open(file2, 'r')
    
    # Set up two initial columns containing the original file content  #
    initialColumn1=fileOpen1.read().split('\n')
    initialColumn2=fileOpen2.read().split('\n')

    # Close the files as their content has already been transferred #
    fileOpen1.close()
    fileOpen2.close()

    column1=[]
    column2=[]
    column3=[]

    # If the files are already sorted (i.e. no -u option) #
    if options.unsort==0:
        # Loop through both lists, find common lines, then place in column3 #
        for i in initialColumn1:
            for j in initialColumn2:
                if i==j:
                    column3.append(i)
        # Also delete the common lines from columns 1 and 2 #
        for i in column3:
            initialColumn1.remove(i)
            initialColumn2.remove(i)

        # The common lines are removed, so now columns 1 and 2 are set  #
        column1=list(initialColumn1)
        column2=list(initialColumn2)

        # Put all three columns into a sorted list to traverse easily through elements #
        mergedSortedColumn=(column1+column2+column3)
        mergedSortedColumn.sort()

        sys.stdout.write("Column 3 list\n")
        for i in column3:
            print i
        sys.stdout.write("\n")

        sys.stdout.write("This is merged sort list\n")
        for i in mergedSortedColumn:
            print i
        sys.stdout.write("\n")

        sys.stdout.write("This is column 1 list\n")    
        for i in column1:
            print i
        sys.stdout.write("\n")
            
        sys.stdout.write("This is column 2 list\n")
        for i in column2:
            print i
        sys.stdout.write("\n")

        sys.stdout.write("Final output")

        # Given the sorted merged list, put each line into its appropriate column  #
        for i in mergedSortedColumn:
            if i in column1 and options.suppress1==False:
                sys.stdout.write(i)
                sys.stdout.write('\n')
            elif i in column2 and options.suppress2==False:
                #stringValue=i
                #printWithTab="\t"
                sys.stdout.write("\t"+i)
                sys.stdout.write('\n')
            elif i in column3 and options.suppress3==False:
                sys.stdout.write("\t"+"\t"+i)
                sys.stdout.write('\n')
    '''
    try:
        generator = randline(input_file)
        for index in range(numlines):
            sys.stdout.write(generator.chooseline())
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

    '''
                     
if __name__ == "__main__":
    main()
