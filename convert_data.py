import xlsxwriter

file = open("DATA.txt")

tuples = []

for line in file:
    tup = eval(line)
    tuples.append(tup)



workbook = xlsxwriter.Workbook('Målinger.xlsx')
worksheet = workbook.add_worksheet()

col = 0

for row in range(0, len(tuples)):
    worksheet.write(row, col, 20*row)

col = 1
row = 0

for tup in tuples:
    worksheet.write(row, col, tup[0])
    worksheet.write(row, col+1, tup[1])

    row += 1

workbook.close()
