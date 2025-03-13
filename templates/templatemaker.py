import json
import os

target = os.path.expanduser("~/.config/Code/User/snippets/global.code-snippets")  # Linux/macOS
os.makedirs(os.path.dirname(target), exist_ok=True)

tmplt = "string/a.cpp"

if not os.path.exists(tmplt):
    print(f"Error: {tmplt} not found!")
    exit(1)

with open(tmplt, "r", encoding="utf-8") as f:
    lines = f.readlines()

new_snip = [line.rstrip("\n") for line in lines]
name = os.path.splitext(os.path.basename(tmplt))[0]

snip = {
    f"{name} Template": {
        "prefix": name,
        "body": new_snip,
        "description": f"Snippet for {name}.cpp"
    }
}

if os.path.exists(target):
    with open(target, "r", encoding="utf-8") as f:
        try:
            ex_snip = json.load(f)
        except json.JSONDecodeError:
            ex_snip = {}
else:
    ex_snip = {}

ex_snip.update(snip)

with open(target, "w", encoding="utf-8") as f:
    json.dump(ex_snip, f, indent=4)

print(f"Snippet added! Type `{name}` in VS Code and press Enter to use it.")
