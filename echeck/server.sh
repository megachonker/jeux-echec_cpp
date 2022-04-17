rm -f  GRAPH GRAPH2 ; mkfifo GRAPH GRAPH2 && 
./echecs < <(nc -l -p 6900 < GRAPH & nc -l -p 6969 < GRAPH2)|tee GRAPH |tee GRAPH2
# ./echecs < <(nc -l -p 6900 < GRAPH & nc -l -p 6969 < GRAPH2)|tee GRAPH > & && echo serveur lancer: