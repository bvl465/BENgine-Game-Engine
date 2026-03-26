#include "ImageManager.h"
#include "Image.h"
#include "../Texture Manager/TextureManager.h"

ImageManager* ImageManager::ptrInstance = nullptr;


ImageManager& ImageManager::Instance()
{
    if (ptrInstance == nullptr) {
        ptrInstance = new ImageManager();
    }
    return *ptrInstance;
}

void ImageManager::Delete()
{
    if (ptrInstance != nullptr) {
        for (ImageManagerMap::iterator it = ptrInstance->storageMap.begin(); it != ptrInstance->storageMap.end(); ++it)
        {
            delete it->second;
            it->second = nullptr;
        }
        delete ptrInstance;
        ptrInstance = nullptr;
    }

}


Image* ImageManager::privGetImage(MapKey key)
{
    ImageManagerMap::iterator it = storageMap.find(key);
    if (it == storageMap.end()) {
        //Key not in the storageMap
        throw std::invalid_argument("Key " + key + " could not be found.");
    }
    else {
        return it->second; 
    }
}

void ImageManager::privLoad(MapKey key, Texture* tex)
{
	ImageManagerMap::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a Model.");
	}
	else {
        if (tex != nullptr) {
            Rect* rect = new Rect(0.0f, 0.0f, float(tex->getWidth()), float(tex->getHeight()));
            this->storageMap.insert({ key, new Image(tex, rect) });
        }
        else {
            throw std::invalid_argument("Texture passed is nullptr");
        }
	}
}

void ImageManager::privLoad(MapKey key, Texture* tex, Rect* rect)
{
    ImageManagerMap::iterator it = storageMap.find(key);
    if (it != storageMap.end()) {
        //Using the same key multiple times throw an error
        throw std::invalid_argument("Key " + key + " is already used to define a Model.");
    }
    else {
        if (tex != nullptr && rect != nullptr) {
            this->storageMap.insert({ key, new Image(tex, rect) });
        }
        else {
            if (tex == nullptr && rect == nullptr) {
                throw std::invalid_argument("Texture passed is nullptr and rect passed is nullptr");
            }
            else if (tex == nullptr) {
                throw std::invalid_argument("Texture passed is nullptr");
            }
            else {
                throw std::invalid_argument("Rect passed is nullptr");
            }
        }
    }
}

Image* ImageManager::GetImage(MapKey key)
{
	return Instance().privGetImage(key);
}

void ImageManager::Load(MapKey key, Texture* tex)
{
    Instance().privLoad(key, tex);
}

void ImageManager::Load(MapKey key, Texture* tex, Rect* rect)
{
    Instance().privLoad(key, tex, rect);
}