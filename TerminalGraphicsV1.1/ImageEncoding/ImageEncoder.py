from PIL import Image

def encodeImage(name, tilesetSize):
    img = Image.open(name).convert('L') #converts to greyscale ('L')
    
    width, height = img.size;
    print(f"width:{width}, height:{height}")

    maxBrightness = 0

    for y in range(height):
        for x in range(width):
            if(img.getpixel((x,y))>maxBrightness):
                maxBrightness=img.getpixel((x,y))


    #----------TEMP---------
    #maxBrightness=0
    #-----------------------

    with open("output.txt",'w') as f:
        for y in range(height):
            for x in range(width):
                brightness = img.getpixel((x,y))
                roundedBrightness = round((tilesetSize-1)*brightness/(255)) #set to an int between 0 and tilesetSize-1 to become reference to index in tilseset
                f.write(f"{roundedBrightness:03d}"+" ") #write to output.txt
            f.write("\n")

    print("done encoding...")

encodeImage('imgs/CGOLtestimage.jpg',2)
