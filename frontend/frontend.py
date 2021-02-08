# %%
import pandas as pd
import requests
import plotly.graph_objects as go
from plotly.subplots import make_subplots

def getdata(device="1DB09B"):
    # %%
    URL = "http://iot.ingeniatic.com/api/iot/" + device
    response = requests.get(URL)
    print(response.status_code)
    json_data = (response.json())
    print(len(json_data))

    df = pd.DataFrame(json_data).drop([
        'Payload',
        'id_Sigfox',
        'Field5',
        'Field6',
        'Field7',
        'Field8',
        'Field9',
        'Field10',
        'deleted_at',
        'created_at'],
                                    axis=1)
    df.set_index('id', inplace=True)
    df.rename(columns = {'Field1':'Temperatura', 'Field2':'Humedad', 
                                'Field3':'Luminosidad(%)', 'Field4': 'Volt.'}, inplace = True) 
    # %%
    df.iloc[:,-1] = pd.to_datetime(df.iloc[:,-1])
    # %%
    list(df.iloc[:,-1])
    fig = make_subplots(rows=2, cols=2,
                        subplot_titles=("Temperatura", "Humedad", "Luminoasidad(%)", "Volt."))
    fig.add_trace(go.Scatter(x=list(df.iloc[:,-1]), y=list(df.iloc[:,0])),row=1, col=1)
    fig.add_trace(go.Scatter(x=list(df.iloc[:,-1]), y=list(df.iloc[:,1])),row=1, col=2)
    fig.add_trace(go.Scatter(x=list(df.iloc[:,-1]), y=list(df.iloc[:,2])),row=2, col=1)
    fig.add_trace(go.Scatter(x=list(df.iloc[:,-1]), y=list(df.iloc[:,3])),row=2, col=2)

    fig.show()

if __name__ == '__main__':
    getdata(device='1DB09B')
