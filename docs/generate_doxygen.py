import os, sys, getopt

def main(argv):

    doxy_path = "release/doxygen/genesis"
    if not os.path.exists(doxy_path):
        os.makedirs(doxy_path)

    opts, args = getopt.getopt(argv, "hr:v:",["rtf=", "version="])
    
    rtf = bool(0)

    for opt, arg in opts:
        if opt == '-h':
            print ('\nThe following arguments are possible:\n')
            print ('-r <yes/no>             Specify to generate RTF documentation.')
            print ('-v <version>            Input the library version.')
            print (' ')
            print ('--rtf=<yes/no>          Specify to generate RTF documentation.')
            print ('--version=<version>     Input the library version.')
            
            sys.exit()        
        elif opt in ("-r", "--rtf"):
            rtf = (arg in ("YES", "yes", "Yes"))
        elif opt in ("-v", "--version"):
            version = arg
    
    if (len(argv) == 0):
        rtf = bool(0)
        version = "unknow"

    with open("./sources/doxygen/Doxyfile", "rt") as doxygenConfigFile:
        with open("./sources/doxygen/Doxyfile.new", "wt") as newFile:
            for line in doxygenConfigFile:
                if(rtf):
                    newFile.write(line.replace('GENERATE_RTF           = NO', 'GENERATE_RTF           = YES'))
                else:
                    newFile.write(line.replace('GENERATE_RTF           = YES', 'GENERATE_RTF           = NO'))
                if(version):
                    newFile.write(line.replace('__ENV_VERSION__', version))

    doxygenConfigFile.close()
    newFile.close()

    os.system("doxygen sources/doxygen/Doxyfile.new")
    os.remove("./sources/doxygen/Doxyfile.new")
    

if __name__ == "__main__":
   main(sys.argv[1:])