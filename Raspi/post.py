data = {
    "pressure1": 0,
    "pressure2": 0,
    "pressure3": 0,

    "motor_rpm": 0,
    "gen_rpm": 0,

    "dc_cur": 0
}

for topic in data.items():
    data[topic] = 1
    print(data)