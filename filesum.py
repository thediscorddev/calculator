import os
import re
import subprocess
rootdir = "scr"
hppFile = 0
hppLine = 0
cppfile = 0
cppLine = 0
OtherFiles = 0
ImageFiles = 0
def isFileType(filename, type_):
    return filename.endswith(type_)

def Walk(root_dir,root_dir_2, image_dỉr):
    global hppFile, hppLine, cppfile, cppLine, OtherFiles, ImageFiles
    for folder, _, files in os.walk(root_dir):
        for file in files:
            if isFileType(file, ".hpp"):
                hppFile=hppFile+1
                path = os.path.join(folder, file)
                with open(path, "r", encoding="utf-8") as f:
                    hppLine = hppLine + len(f.readlines())
            elif isFileType(file, ".cpp"):
                cppfile=cppfile+1
                path = os.path.join(folder, file)
                with open(path, "r", encoding="utf-8") as f:
                    cppLine = cppLine + len(f.readlines())
            else:
                OtherFiles = OtherFiles + 1

    for folder, _, files in os.walk(root_dir_2):
        for file in files:
            if isFileType(file, ".hpp"):
                hppFile=hppFile+1
                path = os.path.join(folder, file)
                with open(path, "r", encoding="utf-8") as f:
                    hppLine = hppLine + len(f.readlines())
            elif isFileType(file, ".cpp"):
                cppfile=cppfile+1
                path = os.path.join(folder, file)
                with open(path, "r", encoding="utf-8") as f:
                    cppLine = cppLine + len(f.readlines())
            else:
                OtherFiles = OtherFiles + 1

    for folder, _, files in os.walk(image_dỉr):
        for file in files:
            if isFileType(file, ".png"):
                ImageFiles=ImageFiles+1

Walk(rootdir,"src","compile")
print("Total: ")
print(hppFile," hpp files")
print(hppLine, " lines written in cpp (header file)")
print(cppfile," cpp files")
print(cppLine, " lines in cpp (source file)")
print(OtherFiles," other files")
print(ImageFiles," image files")
print(hppLine+cppLine," code in C++ (mixed with small html and js too)")
print(OtherFiles + hppFile + cppfile + ImageFiles, " files total")