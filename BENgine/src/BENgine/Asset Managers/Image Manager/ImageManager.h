#ifndef _ImageManager
#define _ImageManager

#include "AzulCore.h"
#include <map>

using MapKey = std::string const;
using ImageManagerMap = std::multimap<MapKey, Image*>;

//Manages the creation, loading, retrieval, storage, and deletion of Images.
class ImageManager
{
private:

    friend class ImageManagerAttorney;

    static ImageManager* ptrInstance;

    ImageManager() = default;
    ImageManager(const ImageManager&) = delete;
    ImageManager& operator=(const ImageManager&) = delete;
    ~ImageManager() = default;

    static ImageManager& Instance();

	//Deletes the instance of the ImageManager and all Images stored in the storageMap. Accessed by BENgine through ImageManagerAttorney.
    static void Delete();

    //No need for a default path since images aren't stored as files.
    //const std::string defaultPath;

	//Map that Images are loaded into and retrieved from. The key is the name the user assigns the image, and the value is a pointer to the image.
    ImageManagerMap storageMap;

    
    Image* privGetImage(MapKey key);
    void privLoad(MapKey key, Texture* tex);
    void privLoad(MapKey key, Texture* tex, Rect* rect);
public:

	//Searches the storageMap for key and returns a pointer to the Image associated with that key.
    //Parameters:
	//key - The key associated with the Image to search for in the storageMap.
    static Image* GetImage(MapKey key);

    //Creates an Image using the entirety of the Texture and then loads the Image into the storageMap with the key passed.
    //Parameters:
	//key - The key to associate with the Image in the storageMap. (Must be unique)
	//tex - The Texture to create the Image from. (Can't be nullptr)
    static void Load(MapKey key, Texture* tex);


    //Creates an Image using a portion of the Texture as defined by the Rect and then loads the Image into the storageMap with the key passed.
    //Parameters:
	//key - The key to associate with the Image in the storageMap. (Must be unique)
	//tex - The Texture to create the Image from. (Can't be nullptr)
	//rect - The Rect that defines the portion of the Texture to create the Image from. (Can't be nullptr)
    static void Load(MapKey key, Texture* tex, Rect* rect);

};

#endif _ImageManager