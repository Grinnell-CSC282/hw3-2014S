#This script should find all files ending in .jpg in the current directory and below and move them to a directory called 
# images. It seems to do this successfuly, but also gives me errors I don't understand. 

#!/bin/bash

#create the image directory, unless it already exists
mkdir -p ./images
#set writing priveleges
chmod u+w images
#find appropriate files and move them
find . -name "*.jpg" -type f -exec mv {} images \;

# Notes: 
# find locates files (in this case, using the regular expression *.jpg)
# . tells it to look in the working directory and below
# -type f tells it only to look at standard files
# -exec tells it to execute the following command, using its results as input
# mv moves files
# {} indicates where the output of find should go (in this case, the file to be moved)
# images is the target directory
# \; ends the command (with \ escaping the ;)
