from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
import sys
import time
import os
import csv
from datetime import datetime

#tutaj ważne jest aby podać ścieżkę do chromedriver.exe
path_to_chromedriver = 'D:\GitHub\Projekt_MS_Programowanie2\Wszystkie_kody\chromedriver.exe'

if len(sys.argv) < 2:
    print("Nie podano nazwy spółki")
    sys.exit(1)

spolka = sys.argv[1]

file_name = f"pliki_csv\\{spolka}.csv"

# C:\Python_Scripts\Repozytoria_Git\Projekt_MS_Programowanie2\Wszystkie_kody\sunex.csv

def current_quarter():
    now = datetime.now()
    year = now.year
    month = now.month
    if month in [1, 2, 3]:
        quarter = 1
    elif month in [4, 5, 6]:
        quarter = 2
    elif month in [7, 8, 9]:
        quarter = 3
    else:
        quarter = 4
    return year, quarter

def scrap():
    start = time.time()

    # Ustawienie ścieżki do chromedriver i trybu headless
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--disable-gpu")
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")

    service = Service(executable_path=path_to_chromedriver)
    driver = webdriver.Chrome(service=service, options=chrome_options)

    # Otwarcie strony
    try:
        driver.get(f'https://www.stockwatch.pl/gpw/{spolka},notowania,wskazniki.aspx')
    except:
        print(f"Nie udało się otworzyć strony dla spółki {spolka}.")
        driver.quit()
        sys.exit(1)
    driver.implicitly_wait(10)  # Zamiast sleep, używamy implicit wait
    time.sleep(1)
    
    # Bezpośrednie wyszukiwanie elementu zawierającego tekst 'WSKAŹNIKI RYNKOWE'
    elements = driver.find_elements(By.CSS_SELECTOR, 'td')
    fl = driver.find_elements(By.CSS_SELECTOR, 'strong')
    print(fl[1].text)
    sym = fl[1].text

    # Przetwarzanie elementów
    kwartalne = []
    found = False
    for element in elements:
        if 'Kurs ' in element.text:
            found = True
            break 

    if found:
        start_index = elements.index(element) + 1
        for i in range(start_index, len(elements)):
            kwartalne.append(elements[i].text)
            if 'WSKAŹNIKI RYNKOWE' in elements[i].text:
                break
    kwartalne = kwartalne[:-1]

    # Zamykanie przeglądarki
    driver.quit()

    # Połączenie kwartałów z danymi giełdowymi
    year, quarter = current_quarter()
    quarter -= 1
    kwartaly = []
    kwartalne.reverse()
    for i in range(len(kwartalne)-1):
        kwartaly.append([quarter, year])
        print(f'{kwartaly[i]} - {kwartalne[i]}')
        quarter -= 1
        if quarter < 1:
            year -= 1
            quarter = 4
    print('-'*50)
    print(f'Czas wykonania: {time.time()-start}')

    # Zapisanie danych do pliku CSV
    with open(file_name, mode='w', encoding='utf-8', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['SYMBOL','kwartal','rok','cena'])
        for i in range(len(kwartaly)-1):
            writer.writerow([f'{sym}',kwartaly[i][0],kwartaly[i][1],kwartalne[i]])

    print(f"Dane dla spółki {spolka} zostały zapisane do pliku {file_name}.")

# Sprawdzenie, czy plik istnieje
if os.path.exists(file_name):
    print(f"Dane dla spółki {spolka} są już zapisane w pliku {file_name}. Odczytuję dane...")
    with open(file_name, mode='r', encoding='utf-8') as file:
        reader = csv.reader(file)
        nagluwek = next(reader)
        zcsv = next(reader)
    x = str(zcsv[1])
    y = str(current_quarter()[1]-1)
    z = str(zcsv[2])
    t = str(current_quarter()[0])
    if (x == y) and (z == t):
        print(f'Q{current_quarter()[1]-1} {current_quarter()[0]}')
        print("Dane są aktualne.")
        with open(file_name, mode='r', encoding='utf-8') as file:
            reader = csv.reader(file)
            for row in reader:
                print(', '.join(row))
    else:
        os.remove(file_name)
        print(f"Usunięto stary plik: {file_name}")
        print("Pobieram nowe dane...")
        scrap()
else: 
    scrap()