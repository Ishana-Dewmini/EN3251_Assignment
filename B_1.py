import pandas as pd
import json
# Provide the path to your Excel file
excel_file = 'PartB.xlsx'

# Read the Excel file into a DataFrame
dictionary = {}

df = pd.read_excel(excel_file)
json_str = df.to_json(orient='records')
json_obj = json.loads(json_str)

for i in range(len(json_obj)):
    dictionary[str(i)] = json_obj[i]

data_out=json.dumps(dictionary) #encode object to JSON
print (data_out)


