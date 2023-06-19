import os
from tqdm import tqdm

#31_883_264 byte per file for KNACKSAT 2

loop = True
while loop:
    print("=" * 75)
    print("                            Generate Text File                             ")
    print("=" * 75)
    start_number = int(input("Starting file name (in number)       : "))
    last_number  = int(input("Last file name (in number)           : "))
    byte_data    =     input("Hexadecimal that write into the file : ")
    file_size    = int(input("The size of the file (in bytes)      : "))
    path         =     input("Path where the files will be created : ")
    print("=" * 75)
    print("Please wait...")

    byte_data = bytes.fromhex(byte_data)
    for number in tqdm(range(start_number, last_number + 1), desc = "Writing Progress : ", unit = "file", ncols = 100):
        filename = str(number) + ".txt"
        filepath = os.path.join(path, filename)
        try:
            with open(filepath, "wb") as file:
                file.write(byte_data * file_size)
        except IOError:
            print(f"Error occurred while creating file '{filename}'.")
    print("=" * 75)
    print("Completed!")
    print("=" * 75)

    while True:
        Continue = input("Continue (y/n) : ")
        if Continue == "y" or Continue == "Y":
            os.system("cls")
            break
        elif Continue == "n" or Continue == "N":
            loop = False
            break
        else :
            continue



