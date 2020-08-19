
amount_students = int(input())

ids = []
for i in range(amount_students):
    ids.append(int(input()))

module = len(ids)

while(True):
    temp_ids = []
    for i in range(len(ids)):
        temp = ids[i] % module
        if (temp in temp_ids):
            module += 1
            break
        else:
            temp_ids.append(temp)
    if(len(ids) == len(temp_ids)):
        break

print(module)
