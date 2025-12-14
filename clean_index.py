with open('index.html') as html:
    for line in html:
        print(f'"{line.replace('"', '\\"').rstrip()}\\n"', end='\n')
