from bs4 import BeautifulSoup
from requests import get
import pandas as pd
import numpy as py
import matplotlib.pyplot as plt
import math as math
import re


# while True:

link = "https://www.biznesradar.pl/wycena/ORLEN"
respons = get(link)
print(link)
soup = BeautifulSoup(respons.text, 'html.parser')
print(soup)

    # try:
    #     products = soup.find_all(class_='name')
    # except:
    #     print("No i chuj zjebało się!")
    #     continue
    # print('*'*50)
    # print(soup)
    # print('*'*50)
    # try:
    #     price_div = soup.find('span', class_='change goesdown').find('div')
    # except AttributeError:
    #    print("Przepraszamy. Nieznaleziono wyników")
    #    continue
    
    # price = price_div.text.strip()
    # print("Obecna wycena akcji: ", price)
    # respons = get(link)


    # soup = BeautifulSoup(respons.text,'html.parser')
    # print(soup)
    # kwartały = soup.find_all(class_='factPeriod')
    # quarters = [quarter.b.text for quarter in kwartały]
    # lista = []
    # licznik = -1
    # klasa = soup.find_all(class_='cctabdtdn')
    # for element in klasa:
    #     tbody_elements = element.find_all('tbody')

    #     for tbody in tbody_elements:
    #         rows = tbody.find_all('tr')
    #         for row in rows:
    #             liczby = row.find_all(string=re.compile(r'\d+'))
    #             for liczba in liczby:
    #                 licznik += 1
    #                 lista.append(liczba)
    #                 if(licznik == (len(quarters) - 1)): 
    #                     break
    #             if(licznik == (len(quarters) - 1)): 
    #                     break
    #         if(licznik == (len(quarters) - 1)): 
    #                     break
                
    # wartosci = [float(w.replace(',', '.')) for w in lista]

    # lata_kwartaly = [kw.split() for kw in quarters]
    # lata = [int(kw[1]) for kw in lata_kwartaly]
    # kwartaly = [f"{kw[0]} {kw[1]}" for kw in lata_kwartaly]

    # plt.figure(figsize=(10, 6))
    # plt.plot(wartosci, marker='o', linestyle='-', color='b')
    # plt.xticks(range(len(kwartaly)), kwartaly, rotation='vertical')
    # plt.xlabel('Kwartały')
    # plt.ylabel('Wartości')
    # plt.title('Wykres wartości dla poszczególnych kwartałów')
    # plt.tight_layout()
    # # plt.show()

    # endprog = input("zakończyć program (y/n)?: ")
    # if endprog == 'y': break
    # #głupie czyszenie terminala ;)
    # print("\n"*30)