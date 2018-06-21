from constants import *
from ImageHandler import ImageHandler

x_pos = 0
y_pos = 0
file_content = None


def read_file_contents(file_name):
    global file_content
    with open(file_name, "r") as f:
        file_content = f.read()
    file_content = file_content.split("\n")

if __name__ == "__main__":
    ih = ImageHandler("test.png")
    read_file_contents("example_file.c")
    ih.create_image(len(file_content), WHITE)

    for line in file_content:
        words = line.split(" ")
        for word in words:
            if word == "":
                ih.add_text(x_pos, y_pos, " ", BLACK)
                x_pos += 1
            else:
                found = False
                for kw in KEYWORDS:
                    index = word.find(kw)
                    if index > -1:
                        found = True
                        ih.add_text(x_pos, y_pos, word[:index], BLACK)
                        x_pos += index
                        ih.add_text(
                            x_pos, y_pos,
                            word[index:index+len(kw)], PURPLE
                            )
                        x_pos += len(kw)
                        ih.add_text(
                            x_pos, y_pos,
                            word[index+len(kw):], BLACK
                            )
                        x_pos += 1
                        break
                if not found:
                    ih.add_text(x_pos, y_pos, word, BLACK)
                    x_pos += len(word)
                x_pos += 1

        y_pos += 1
        x_pos = 0

    ih.save_image()
