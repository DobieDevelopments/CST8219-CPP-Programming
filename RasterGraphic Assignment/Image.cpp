/******* File Header ******************************************************************************************************************
* Filename											: Image.cpp
* Version											: 1.0
* Purpose											: To handle methods for modifying our linked list,
*													: (insert, delete from head, print/iterate through list.
**************************************************************************************************************************************/
#include <iostream>
using namespace std;
#include "Image.h"

/******* Function Header **************************************************************************************************************
* Function name										: Image()	//Default Constructor
* Purpose											: To initialize our Image class object
* Function In parameters							: int - x coordinate of the image
* 													| int - y coordinate of the image
* 													| int - how long to display the image
* 													| char* - the image filename
* Function Out parameters							: Image - the instance of this class object
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
Image::Image(int x, int y, int duration, char * name)
{
	this->pixel_x = x;
	this->pixel_y = y;
	this->duration = duration;
	this->name = new char[strlen(name) * sizeof(char) + 1];
	strcpy_s(this->name, strlen(name) * sizeof(char) + 1, name);
}

/******* Function Header **************************************************************************************************************
* Function name										: Image()	//Copy Constructor
* Purpose											: To initialize our image class object using the details of another passed in
* Function In parameters							: const Image& - the image to copy from
* Function Out parameters							: Image - the instance of this class object
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
Image::Image(const Image & I)
{
	this->pixel_x = I.pixel_x;
	this->pixel_y = I.pixel_y;
	this->duration = I.duration;
	this->name = new char[strlen(I.name) * sizeof(char) + 1];
	strcpy_s(this->name, strlen(I.name) * sizeof(char) + 1, I.name);
}

/******* Function Header **************************************************************************************************************
* Function name										: operator<<()
* Purpose											: An overload of the << operator
*													| To handle output functinality of Image class objects through the output stream
* Function In parameters							: ostream& - the output stream
*													| Image& - the image to output
* Function Out parameters							: ostream& - a reference to the ostream
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
ostream & operator<<(ostream & os, Image & image)
{
	os << "Image name = " << image.name
		<< "; pixel_x = " << image.pixel_x
		<< "; pixel_y = " << image.pixel_y
		<< "; duration = " << image.duration << endl
		<< "\tCounting the seconds for this Image: ";
	for (int i = 0; i < image.duration; ++i)
	{
		if (i != (image.duration - 1))
			os << (i + 1) << ", ";
		else
			os << (i + 1) << ".";
	}
	return os;
}
