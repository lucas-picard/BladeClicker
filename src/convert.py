from PIL import Image

def remove_bg(img, tolerance=30):
    img = img.convert("RGBA")
    data = img.getdata()
    bg_color = data[0][:3]  # couleur du coin superieur gauche = fond
    new_data = []
    for pixel in data:
        r, g, b, a = pixel
        if abs(r - bg_color[0]) < tolerance and abs(g - bg_color[1]) < tolerance and abs(b - bg_color[2]) < tolerance:
            new_data.append((0, 0, 0, 0))  # transparent
        else:
            new_data.append(pixel)
    img.putdata(new_data)
    return img

def convert(input_file, var_name, width, height, fichier):
    img = Image.open(input_file)
    img = remove_bg(img)
    img = img.resize((width, height))
    img = img.convert("RGBA")

    fichier.write(f"const uint16_t {var_name}[] = {{\n")
    for y in range(img.height):
        for x in range(img.width):
            r, g, b, a = img.getpixel((x, y))
            if a < 128:
                fichier.write(f"0xFFFF, ")  # marqueur transparent
            else:
                rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
                fichier.write(f"0x{rgb565:04X}, ")
        fichier.write("\n")
    fichier.write("};\n")
    fichier.write(f"const int {var_name}_width  = {width};\n")
    fichier.write(f"const int {var_name}_height = {height};\n\n")

with open("images.h", "w") as f:
    f.write("#pragma once\n#include <stdint.h>\n\n")
    convert("img/epee.png",     "epee",     16, 16, f)
    convert("img/bouclier.png", "bouclier", 16, 16, f)
    convert("img/couronne.png", "couronne", 16, 16, f)

print("images.h genere avec succes !")