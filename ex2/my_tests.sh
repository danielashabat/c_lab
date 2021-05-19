#! /usr/bin/env tcsh



grep -E -i "(cady|mr\.)" mean_girls.txt  > out
./my_grep  -E -i "(cady|mr\.)" mean_girls.txt  | diff out -
rm out


grep -E -b -v -i "(cady|mr\.)" mean_girls.txt  > out
./my_grep  -E -b -v -i  "(cady|mr\.)" mean_girls.txt  | diff out -
rm out

grep -E -b -v -i "(1|)[0-9]" mean_girls.txt  > out
./my_grep  -E -b -v -i  "(1|)[0-9]" mean_girls.txt  | diff out -
rm out


echo "[9]\n[19]\n[12]" | grep -E -b '\[(1|)[0-9]\]' > out
echo "[9]\n[19]\n[12]" |./my_grep   -E -b '\[(1|)[0-9]\]'   | diff out -
rm out

echo "[9]\n[19]\n[12]" | grep -E -b -n  '\[(1|)[0-9]\]' > out
echo "[9]\n[19]\n[12]" |./my_grep   -E -b -n  '\[(1|)[0-9]\]'   | diff out -
rm out

