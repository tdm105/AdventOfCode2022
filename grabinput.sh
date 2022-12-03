session=53616c7465645f5fb19548606508d3df91430d104f13294fa2a25eda8ad78b91655786bdd2e57528bf59d29a5a60e2064e79008cee36fb75fb09270b5ea74c19
curl --output $2 --cookie session=$session https://adventofcode.com/2022/day/$1/input
chmod +x grabinput.sh