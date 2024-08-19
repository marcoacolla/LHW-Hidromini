measures = {  
    "pressure1": {"value": 0.0, "type": float, "id": "00"},
    "pressure2": {"value": 0.0, "type": float, "id": "01"},
    "pressure3": {"value": 0.0, "type": float, "id": "02"},
    "motor_rpm": {"value": 0.0, "type": float, "id": "03"},
    "gen_rpm": {"value": 0.0, "type": float, "id": "04"},
    "dc_cur": {"value": 0.0, "type": float, "id": "05"},
    "dc_volt": {"value": 0.0, "type": float, "id": "06"},
    "valve1": {"value": False, "type": bool, "id": "07"},
    "valve2": {"value": False, "type": bool, "id": "08"}
}

# Prepara os dados para envio, ignorando 'id' e 'type'
def preparar_dados_para_envio(measures):
    dados_para_envio = {}
    for key, sub_dict in measures.items():
        dados_para_envio[key] = {"value": sub_dict["value"]}
    return dados_para_envio

# Prepara os dados para envio
dados_para_envio = preparar_dados_para_envio(measures)

print(dados_para_envio)
