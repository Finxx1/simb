MDL files are Simb's model format. They contain vertex data
Format:

You can get the number of verticies by dividing the filesize by 20 (sizeof 5 floats)
4 bytes - float X
4 bytes - float Y
4 bytes - float Z
4 bytes - float U
4 bytes - float V

Source file format:
folder: (name)_src
    obj.obj
    albedo.jpg/exr
    normal.jpg/exr