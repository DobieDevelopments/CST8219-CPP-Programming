/******* File Header ******************************************************************************************************************
* Filename											: GraphicElement.cpp
* Version											: 1.0
* Purpose											: To handle operator methods for our GraphicElement objects
*													: output operator overloading.
**************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Image.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"
#include "GraphicElement.h"

/******* Function Header **************************************************************************************************************
* Function name										: GraphicElement()	//Copy Constructor
* Purpose											: To initialize our GraphicElement class object using the details of another passed in
* Function In parameters							: const GraphicElement& - the GraphicElement to copy from
* Function Out parameters							: GraphicElement - the instance of this class object
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
GraphicElement::GraphicElement(const GraphicElement & graphicElement)
{
	this->fileName = graphicElement.fileName;
	for (unsigned int i = 0; i < graphicElement.Images.size(); ++i)
	{
		this->Images.emplace_back(graphicElement.Images[i]);
	}
}

/******* Function Header **************************************************************************************************************
* Function name										: operator<<()
* Purpose											: An overload of the << operator used to output our list of images
*													| inside the GraphicElement.
* Function In parameters							: ostream& - our output stream
*													| GraphicElement& - our object that contains our Image list that we will iterate through
* Function Out parameters							: ostream& - a reference to our output stream
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
ostream & operator<<(ostream & os, GraphicElement & graphicVector)
{
	vector<Image*>::iterator i;
	int count = 0;

	os << "\tfileName = " << graphicVector.fileName << endl;
	for (i = graphicVector.Images.begin(); i != graphicVector.Images.end(); ++i)
	{
		os << "\tImage #" << count << ": ";
		if (dynamic_cast<SystemMemoryImage*>(*i) != nullptr)
		{
			os << "System Memory Image" << endl;
			os << "\t" << *(*i) << endl << "\tMemory requirements = " << (*i)->BufferSize() << " bytes\n" << endl;
		}
		else
		{
			os << "GPU Memory Image. Shader = " << dynamic_cast<GPUMemoryImage*>(*i)->GetShader() << endl;
			os << "\t" << *(*i) << endl << "\tMemory requirements = " << (*i)->BufferSize() << " bytes\n" << endl;
		}
		count++;
	}
	return os;
}
