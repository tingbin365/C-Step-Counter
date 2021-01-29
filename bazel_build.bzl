def include_folders(folders,package):    
    result= []
    for folder in folders:
        line = "/I" +package + "/" + folder
        result.append(line)    
    return result


def export_include_folder(folders,package):    
    result= []
    for folder in folders:
        line = package + "/" + folder
        result.append(line)    
    return result


def include_folder_hdrs(folders):    
    result= []
    for folder in folders:
        line = folder + "/*.h" 
        result.append(line)    
    return result
