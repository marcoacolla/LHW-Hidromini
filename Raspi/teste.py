data = {  
    "pressure1": {"value": 1.53, "type": int},
    "pressure2": {"value": 1.53, "type": float},
    "pressure3": {"value": 0, "type": bool},
}

message = "/mcc/pressure2"
for topic, infos in data.items():
        if message == f"/mcc/{topic}":
            infos["value"] = infos["type"](69)

print(data["pressure3"]["type"](data["pressure3"]["value"]))