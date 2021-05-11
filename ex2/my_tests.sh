#! /usr/bin/env tcsh

echo "start running my_tests!"


grep -E -i "(cady|mr\.)" mean_girls.txt  > out
./my_grep  -E -i "(cady|mr\.)" mean_girls.txt  | diff out -
rm out


grep -E -b -v -i "(cady|mr\.)" mean_girls.txt  > out
./my_grep  -E -b -v -i  "(cady|mr\.)" mean_girls.txt  | diff out -
rm out

grep -E -b -v -i "(1|)[0-9]" mean_girls.txt  > out
./my_grep  -E -b -v -i  "(1|)[0-9]" mean_girls.txt  | diff out -
rm out


echo "Done running my_tests !"
