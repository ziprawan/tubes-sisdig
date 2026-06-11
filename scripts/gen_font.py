import math
from urllib.request import urlopen, HTTPError, Request

req = Request(
  "https://sisdig.ajos.my.id/api/fonts/tubes",
  headers={
    "User-Agent": "curl/8.5.0"
  }
)

try:
  with urlopen(req) as response:
      data = response.read()
  with open("font", "wb") as f:
    f.write(data)
except HTTPError as e:
  print("Status:", e.code)

  body = e.read()
  raise ValueError(body)


MAGIC = b'DSD!'
HEIGHT = 6
OUT_NAME = "gen.cpp"

font_file = open("font", "rb")
magic = font_file.read(4)
if magic != MAGIC:
  raise ValueError("Invalid font header")

name_len = int.from_bytes(font_file.read(1))
char_count = int.from_bytes(font_file.read(1))
name = font_file.read(name_len).decode()
print(f"Font \"{name}\" has {char_count} letters, exporting into C code")

writer = open(OUT_NAME, "w+")
writer.write("unsigned char font_data[] = {")
datas = []
for i in range(char_count):
  letter_data = int.from_bytes(font_file.read(1))
  has_data = (letter_data >> 7) == 1
  letter = letter_data & 0x7F
  char = chr(letter)
  datas.append(str(letter))

  if has_data:
    width = int.from_bytes(font_file.read(1))
    byte_total = math.ceil(HEIGHT * width / 8)
    datas.append(str(width))
    
    for _ in range(byte_total):
      datas.append(str(int.from_bytes(font_file.read(1))))
  else:
    datas.append(str(0))

writer.write(', '.join(datas))
writer.write('};')
writer.close()
font_file.close()
