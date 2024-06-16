from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
import sys
import time
import os
import csv
from datetime import datetime

# Ścieżka do chromedriver.exe
path_to_chromedriver = 'D:\GitHub\Projekt_MS_Programowanie2\Wszystkie_kody\chromedriver.exe'

if len(sys.argv) < 2:
    print("Nie podano nazwy spółki")
    sys.exit(1)

spolka = sys.argv[1]

file_name = f"pliki_csv\\KURS_{spolka}.csv"

def scrap():
    start = time.time()

    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--disable-gpu")
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")

    service = Service(executable_path=path_to_chromedriver)
    driver = webdriver.Chrome(service=service, options=chrome_options)

    try:
        driver.get(f'https://www.stockwatch.pl/gpw/{spolka},notowania,wskazniki.aspx')
    except Exception as e:
        print(f"Nie udało się otworzyć strony dla spółki {spolka}. Błąd: {e}")
        driver.quit()
        sys.exit(1)
    
    driver.implicitly_wait(10)
    time.sleep(1)  # krótka pauza na załadowanie strony

    # Szukanie tickera i kursu
    try:
        fl = driver.find_elements(By.CSS_SELECTOR, 'strong')
        kurs = driver.find_elements(By.CSS_SELECTOR, 'span.change.goesup')
        if len(kurs) == 0:
            kurs = driver.find_elements(By.CSS_SELECTOR, 'span.change.goesdown')
    except Exception as e:
        print(f"Błąd podczas szukania danych na stronie: {e}")
        driver.quit()
        return  # Wyjście z funkcji jeśli nie udało się znaleźć danych

    symbol = fl[1].text if len(fl) > 1 else 'Brak symbolu'
    kurs_text = kurs[0].text if len(kurs) > 0 else 'Brak kursu'

    driver.quit()

    # Sprawdzenie i utworzenie katalogu, jeśli nie istnieje
    if not os.path.exists(os.path.dirname(file_name)):
        os.makedirs(os.path.dirname(file_name))


    # Zapis do pliku CSV
    mode = 'a' if os.path.exists(file_name) else 'w'
    with open(file_name, mode=mode, encoding='utf-8', newline='') as file:
        writer = csv.writer(file)
        if mode == 'w':
            writer.writerow(['Symbol', 'Kurs', 'Data'])  # Nagłówek jeśli tworzymy nowy plik
        writer.writerow([symbol, kurs_text, datetime.now().strftime("%Y-%m-%d %H:%M:%S")])

    print(f"Kurs dla spółki {spolka} został zapisany do pliku {file_name}.")

scrap()
