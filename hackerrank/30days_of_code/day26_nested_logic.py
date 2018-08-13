da, ma, ya = list(map(int, input().split()))
de, me, ye = list(map(int, input().split()))

if ya > ye:
    fine = 10000
elif ma > me and ya == ye:
    fine = 500 * (ma - me)
elif da > de and ma == me and ya == ye:
    fine = 15 * (da - de)
else:
    fine = 0

print(fine)
