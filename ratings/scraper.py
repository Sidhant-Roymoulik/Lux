import requests
import pandas as pd
from bs4 import BeautifulSoup

# CCRL
engine = "Lux"
pages = [["CCRL 40/15", 4040], ["CCRL Blitz", 404]]

for [title, page_id] in pages:
    print(title)

    url = requests.get(
        f"https://computerchess.org.uk/ccrl/{page_id}/cgi/compare_engines.cgi?family={engine}&print=Rating+list",
        headers={"User-Agent": "..."},
    )
    table = (
        BeautifulSoup(url.text, "html.parser")
        .find("table", attrs={"class": "rating_table"})
        .find_all("tr")
    )

    df = pd.DataFrame(columns=["Version", "Rating"])
    for tablepart in table:
        columns = tablepart.find_all("td")

        try:
            version = columns[1].find("a").text
            version = version[:-7]
        except:
            version = None

        try:
            rating = columns[2].text
        except:
            rating = None

        engine_version = [version, rating]
        if not None in engine_version:
            df.loc[len(df)] = engine_version

    print(df)
    print()


# MCERL
# print("MCERL")

# url = requests.get(f"https://www.chessengeria.eu/mcerl", headers={"User-Agent": "..."})
# table = (
#     BeautifulSoup(url.text, "html.parser")
#     .find("tbody", attrs={"class": "wixui-table__body"})
#     .find_all("tr")
# )


# df = pd.DataFrame(columns=["Version", "Rating"])
# for tablepart in table:
#     columns = tablepart.find_all("td")

#     try:
#         version = columns[1].text.strip()
#     except:
#         version = None

#     try:
#         rating = columns[2].text
#     except:
#         rating = None

#     engine_version = [version, rating]
#     # print(engine_version)
#     if not None in engine_version:
#         df.loc[len(df)] = engine_version

# print(df)
# print()
