#include "RessourceManager.h"
#include "GameObject.h"

void loadTexture(GameObj* obj, Texture* tex,const std::string& RessourceName) {
	obj->Assets.Textures.insert(std::make_pair(RessourceName, tex));
}

Texture* getTexture(GameObj* obj, const std::string& ResourceName) {
	return obj->Assets.Textures[ResourceName];
}