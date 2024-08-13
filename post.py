import requests

url = "https://exemplo.com/api"  # Substitua pela URL para onde você quer enviar a requisição
data = {
    "chave1": "valor1",
    "chave2": "valor2"
}

try:
    response = requests.post(url, data=data)
    if response.status_code == 200:
        print("Requisição enviada com sucesso!")
        print("Resposta:", response.text)
    else:
        print(f"Erro na requisição: {response.status_code}")
except requests.exceptions.RequestException as e:
    print(f"Erro ao enviar a requisição: {e}")
