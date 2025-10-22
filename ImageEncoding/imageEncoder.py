#a simple image encoder for images - CONVERTS IMAGES TO GREYSCALE

from PIL import Image

def encodeImage(name, tilesetSize):
    img = Image.open(name).convert('L') #converts to greyscale ('L')
    
    width, height = img.size;
    print(f"width:{width}, height:{height}")

    with open("output.txt",'w') as f:
        for y in range(height):
            for x in range(width):
                brightness = img.getpixel((x,y))
                roundedBrightness = int((tilesetSize-1)*brightness/255) #set to an int between 0 and tilesetSize-1 to become reference to index in tilseset
                f.write(f"{roundedBrightness:03d}"+" ") #write to output.txt
            f.write("\n")

    print("done encoding...")


