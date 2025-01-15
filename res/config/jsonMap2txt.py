import sys, json

file_name = input("name of json_file(with suffix): ")

try:
  # 打开并读取JSON文件
  with open(file_name, "r", encoding="utf-8") as file:
      data = json.load(file)
except Exception:
  print("file not exists")
  sys.exit(1)

# 打印map
for row in data["map"]:
  for item in row:
    print(item, end=" ")
  print()