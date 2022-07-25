f = open("temp.txt", "r")
t = f.read().split("\n")
res = []
for w in t:
    res.append(w.split("-")[0].strip())




print(";".join(res))
