import os

def listFiles(root):
    allFiles = list()
    for filename in os.listdir(root):
        filepath = os.path.join(root, filename)

        if os.path.isdir(filepath):
            allFiles = allFiles + listFiles(filepath)
        else:
            allFiles.append(filepath)
    return allFiles

def shouldRemove(filename):
    return filename.endswith('.bak') or filename.endswith('.sym')

allFiles = listFiles(os.getcwd())

print('Removing files...')
for filename in allFiles:
    if shouldRemove(filename):
        print(filename)
        os.remove(filename)
print('Done!')
