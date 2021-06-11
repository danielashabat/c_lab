#! /usr/bin/env tcsh

grep -E -i "(cady|mr\.)" mean_girls.txt  > out1
./my_grep  -E -i "(cady|mr\.)" mean_girls.txt  | diff out1 -


grep -E -b -v -i "(cady|mr\.)" mean_girls.txt  > out2
./my_grep  -E -i "(cady|mr\.)" mean_girls.txt  | diff out1 -


echo "running tests finished!"
