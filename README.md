# Mock Estação A2P2

Mock que simula as requisições das estações A2P2 com os dados do solo obtido pelos sensores.

## Requisições

### Métodos GET

Retorna todos os objetos: 
```
 /station 
```
Retorna o objeto com o id de uma requisição específica da estação: 
```
 /station/:id
```

### Método POST

Cria um novo objeto contendo informaçõe que a estação A2P2 coletou: 
```
/station 
```
```
    O corpo esperado:
      {
    "id": 4,
    "farmOwner": {
      "username": "string",
      "email": "string",
      "fullName": "string",
      "telegram": "string"
    },
    "requestDetails": {
      "stationIndex": "number",
      "latitude": "number",
      "longitude": "number",
      "dateTime": "string"
    },
    "soil": {
      "pH": "number",
      "soilMoistude": "number"
    },
    "environment": {
      "temperature": "number",
      "airHumidity": "number",
      "atmosphericPressure": "number",
      "windSpeed": "number",
      "pluviometricIndex": "number"
    }
  }
```
