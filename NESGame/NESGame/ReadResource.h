#pragma once
#ifndef __READRESOURCE_H__
#define __READRESOURCE_H__
#include "../MapReader/tinyxml2.h"
#include<vector>
#include"../GameComponents/Rect.h"
#include<string>
#include<iostream>
using namespace std;
//Read file xml and return a list of rectangle's 

class ReadResource
{
private:
	static ReadResource*			__instance;
	ReadResource();
	std::vector<Rect> _listRectSprites;
public:
	static ReadResource*			Instance();
	/*std::vector<Rect>				LoadXML(char* fileName, string key);*/
	~ReadResource();
	std::vector<Rect> LoadXML(tinyxml2::XMLDocument *xmlDocument, char* animationName);
};

#endif __READRESOURCE_H__
