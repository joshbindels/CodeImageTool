import PIL
from PIL import Image
from PIL import ImageDraw

class ImageHandler:

    def __init__(self, file_name):
        self.file_name = file_name
        self.img = None
        self.drawing = None
        self.width = 600
        self.line_height = 17
        self.letter_width = 6

    def create_image(self, lines, bg_color):
        self.img = Image.new(
            "RGBA", (self.width,  lines*self.line_height), bg_color
            )
        self.drawing = ImageDraw.Draw(self.img)

    def save_image(self):
        self.img.save(self.file_name)

    def add_text(self, x, y, content, color):
        self.drawing.text((x*self.letter_width, y*self.line_height), content, color)
        self.drawing = ImageDraw.Draw(self.img)
