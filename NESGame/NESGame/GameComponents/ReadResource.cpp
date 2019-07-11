#include "ReadResource.h"

ReadResource*			ReadResource::__instance = NULL;

ReadResource::ReadResource()
{
}


ReadResource * ReadResource::Instance()
{
	if (!__instance)
		__instance = new ReadResource();
	return __instance;
}

ReadResource::~ReadResource()
{
	__instance = NULL;
	delete __instance;
}
std::vector<Rect> ReadResource::LoadXML(tinyxml2::XMLDocument *xmlDocument, const char* animationName)
{
	_listRectSprites.clear();
	tinyxml2::XMLNode *rootNode = xmlDocument->FirstChildElement("Animations");
	tinyxml2::XMLNode *animationNode = rootNode->FirstChild();
	while (animationNode)
	{
		tinyxml2::XMLElement* animationElement = animationNode->ToElement();

		std::string nameAnimation = animationElement->Attribute("name");
		if (nameAnimation.compare(animationName) == 0)//find animation
		{
			//count frames
			tinyxml2::XMLElement *elem = animationElement->FirstChildElement();
			while (elem)
			{
				//create rect from xml
				Rect rect;
				rect.left = elem->IntAttribute("x");
				rect.right = rect.left + elem->IntAttribute("w");
				rect.top = elem->IntAttribute("y");
				rect.bottom = rect.top + elem->IntAttribute("h");
				int cX = elem->IntAttribute("cX"), cY = elem->IntAttribute("cY");
				if (cX != 0 && cY != 0)
				{
					rect.SetCenter(cX, cY);
				}
				else if (cX != 0)
				{
					rect.SetCenter(cX);
				}

				//store rect
				_listRectSprites.push_back(rect);

				//next
				elem = elem->NextSiblingElement();
			}
			break;
		}

		animationNode = animationNode->NextSibling();
	}
	return _listRectSprites;
}