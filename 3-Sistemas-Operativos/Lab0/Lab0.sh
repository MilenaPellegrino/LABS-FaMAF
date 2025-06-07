cat /proc/cpuinfo | grep 'model name'
cat /proc/cpuinfo | grep 'model name' | wc -l
curl -s https://raw.githubusercontent.com/dariomalchiodi/superhero-datascience/master/content/data/heroes.csv | cut -d ";" -f 2 | tr '[:upper:]' '[:lower:]' | sed 's/ //g' | grep -v '^$'
dia=$(sort -k5,5nr weather_cordoba.in | head -n 1); echo "Fecha con temperatura maxima: "; echo "$dia" | awk '{print $1"/"$2"/"$3}'; dia=$(sort -k5,5n weather_cordoba.in | head -n 1); echo "Fecha con temperatura maxima: "; echo "$dia" | awk '{print $1"/"$2"/"$3}' 
sort -k3,3 -n atpplayers.in
awk '{print $0, $7 - $8}' superliga.in | sort -k2,2nr -k9,9nr | awk '{print $1, $2, $3, $4, $5, $6, $7, $8}' > superliga_temp.in
ip link show | grep -i -o -m 1 'ether [0-9a-f:]\{17\}' | awk '{print $2}'
for i in {01..10}; do touch "fma_S01E${i}_es.srt"; done; for file in *_es.srt; do mv "$file" "${file/_es.srt/.srt}"; done