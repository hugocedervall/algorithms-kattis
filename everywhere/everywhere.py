number = int(input())


for i in range(number):
    amounts = int(input())
    citys = []
    for i in range(amounts):
        city = input()
        if not (city in citys):
            citys.append(city)
    print(len(citys))
