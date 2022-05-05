import pdfkit
from pymongo import MongoClient
import pymongo

DATABASE_NAME = 'RFID'
TABLE_NAME = 'tabela'

def get_table():
    client = MongoClient('mongodb://localhost:27017')
    db = client[DATABASE_NAME]
    return db[TABLE_NAME]

def main():
    table = get_table()
    doc = table.find()
    #pdfkit.from_string('Ola Mundo', './out.pdf')
    for it in doc:
        print(it)
        #print('Nome = ' + it['Nome'])

if __name__ == "__main__":
    main()
