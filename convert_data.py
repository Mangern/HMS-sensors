# Må installeres med "pip install xlsxwriter"
# Bibliotek for å skrive til Excel-filer
import xlsxwriter

# Åpne filen som inneholder målingene
file = open("DATA.txt")

# Skal lagre alle datapunktene
tuples = []

# Gå gjennom fil, linje for linje
for line in file:
    # Konverter linje til datapunkt i Python
    tup = eval(line)
    
    # Legg til i listen over datapunkter
    tuples.append(tup)


# Åpne/lag Excel-fil
workbook = xlsxwriter.Workbook('Målinger.xlsx')
# Legg til et worksheet (nødvendig)
worksheet = workbook.add_worksheet()

# Lagrer hvilken kolonne vi skriver til
col = 0

# Hvor ofte vi registrerte en måling (i sekunder)
measurement_interval = 20

# Lag en kolonne med alle tidspunktene vi registrerte på
for row in range(0, len(tuples)):
    worksheet.write(row, col, measurement_interval * row)

# Lagrer hvilken kolonne og rad vi skriver til
col = 1
row = 0

# Skriv datapunktene i Excel. Luftfuktighet i kolonne 1, Temperatur i kolonne 2
for tup in tuples:
    worksheet.write(row, col, tup[0])
    worksheet.write(row, col+1, tup[1])

    row += 1

# Lagre endringer
workbook.close()
