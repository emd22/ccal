import os, sys

compiler = "gcc"

options = "-g"

src_dir = "./src"
bin_dir = "./bin"

if not os.path.exists(bin_dir):
    os.makedirs(bin_dir)

command = "{} {} -o {}/outfile -Iinclude/".format(compiler, options, bin_dir)

for dirpath, dirnames, filenames in os.walk(src_dir):
    for file in [f for f in filenames]:
        if file.endswith(".c"):
            print("{}/{}...".format(dirpath, file))
            command = "{} {}/{} ".format(command, dirpath, file)

if os.system("{}".format(command)):
    #failed build
    print("BUILD: Cannot Run - Build errors")
else:
    #success!
    print("BUILD: Running...")
    args = sys.argv
    args.pop(0)
    newargs = ''.join(args)
    os.system("./bin/outfile {}".format(newargs))

print("BUILD: Build complete")
