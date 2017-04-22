# expand -t 1 hightemp.txt

print(open('./hightemp.txt').read().replace('\t', ' '), end='')
