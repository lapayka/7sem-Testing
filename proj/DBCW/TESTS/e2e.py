import requests

url = "http://localhost:8000/api/v1"

login_url = url + "/singin?type=0"


resp = requests.post(login_url, headers={
        "login": "abc1@mail.ru",
        "password": "1234"
    })

assert resp.status_code == requests.codes.ok


resp = requests.get(url + "/muscomps?selfName=vgm111", headers={"X-token": resp.text})

assert resp.status_code == requests.codes.ok

assert resp.text == '[{"albumName":"vga11","artistName":"vgg","duration":"3:40","id":1,"name":"vgm111","path":""}]\n'
