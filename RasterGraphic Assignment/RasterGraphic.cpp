/******* File Header : Cover **********************************************************************************************************
* Student name										: John Dobie
* Student number									: 040 659 609
* Assignment number (and name if any)				: Assignment 3, RasterGraphic in C++ using Polymorphism
* Course name and number							: CST 8219 – F18 – C++ Programming
* Lab section number								: 304
* Professor’s name									: Andrew Tyler
* Due date of assignment							: Saturday, December 1st, 2018
* Submission date of assignment						: Wednesday, December 1st, 2018
* List of source and header files in the project	: ass3.cpp, GraphicElement.cpp, RasterGraphic.cpp, Image.cpp, GraphicElement.h, RasterGraphic.h, 
*													| Image.h, GPUMemoryImage.h, SystemMemoryImage.h
***************************************************************************************************************************************/
/******* File Header ******************************************************************************************************************
* Filename											: RasterGraphic.cpp
* Version											: 1.0
* Purpose											: To handle methods for modifying our vector of images,
*													: (insert, delete from head, chained output.
**************************************************************************************************************************************/

#include <iostream>
#include <forward_list>
#include <string>
#include <vector>
using namespace std;
#include "Image.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"
#include "GraphicElement.h"
#include "RasterGraphic.h"

/******* Function Header **************************************************************************************************************
* Function name										: InsertRasterGraphic()
* Purpose											: To take input for a filename and details for an image and insert it at a specified location
*													: in the vector list.
* Function In parameters							: none
* Function Out parameters							: none
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
void RasterGraphic::InsertGraphicElement()
{
	int x = 0, y = 0, duration = 0, count = 0, index = -1, imgType = 0;
	string name = "", imgName = "", shaderName = "";
	vector<Image*> Images;

	cout << "Insert a GraphicElement in the RasterGraphic" << endl;

	cout << "Please enter the GraphicElement filename: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name);

	cout << "Entering the GraphicElement Images (the sets of dimensions and durations)" << endl;
	cout << "Please enter the number of Images: ";
	cin >> count;

	for (int i = 0; i < count; ++i)
	{
		cout << "Please enter the pixel x for Image #" << i << " pixel_x:";
		cin >> x;
		cout << "Please enter the pixel y for Image #" << i << " pixel_y:";
		cin >> y;
		cout << "Please enter the duration sec for this Image: ";
		cin >> duration;
		cout << "Please enter the name for this Image: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, imgName);
		imgType = 0;
		do
		{
			cout << "Please enter the type for this Image (1 = SystemMemoryImage, 2 = GPUMemoryImage): ";
			cin >> imgType;
		} while (imgType < 1 || imgType > 2);

		if (imgType == 2)
		{
			cout << "Please enter the file name of the associated GPU Shader: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, shaderName);
		}

		switch (imgType)
		{
		case 1: Images.push_back(new SystemMemoryImage(x, y, duration, const_cast<char*>(imgName.c_str())));
			break;
		case 2: 
			Images.push_back(new GPUMemoryImage(x, y, duration, const_cast<char*>(imgName.c_str()), shaderName));
			break;
		}
		cout << endl;
	}

	if (GraphicElements.empty())
	{
		cout << "\nThis is the first element in the list." << endl;
		GraphicElements.emplace_front(name, Images);
	}
	else
	{
		count = distance(GraphicElements.begin(), GraphicElements.end());
		index = count - 1;
		if (count > 1)
		{
			cout << "There are " << count << " GraphicElement(s) in the list." << endl << "Please specify the position, between 0 and " << (count - 1) << " to insert after: ";
			while (!(cin >> index) || index < 0 || index >(count - 1))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input, please specify a number between 0 and " << (count - 1) << endl;
			}
		}
		forward_list<GraphicElement>::iterator i = GraphicElements.begin();
		advance(i, index);
		GraphicElements.emplace_after(i, name, Images);
	}
	cout << endl;
}

/******* Function Header **************************************************************************************************************
* Function name										: DeleteRasterGraphic()
* Purpose											: To remove the 'head' node of our forward list if able.
* Function In parameters							: none
* Function Out parameters							: none
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
void RasterGraphic::DeleteGraphicElement()
{
	cout << "Delete the first GraphicElement from the RasterGraphic" << endl;
	if (!GraphicElements.empty())
	{
		GraphicElements.pop_front();
		cout << "GraphicElement deleted" << endl;
	}
	else
		cout << "No GraphicElement to delete" << endl;
	cout << endl;
}

/******* Function Header **************************************************************************************************************
* Function name										: operator<<()
* Purpose											: An overload of the << operator
*													| To handle output functinality of Image class objects through the output stream
* Function In parameters							: ostream& - the output stream
*													| RasterGraphic& - the RasterGraphic to output
* Function Out parameters							: ostream& - a reference to the ostream
* Version											: 1.0
* Author											: John Dobie
**************************************************************************************************************************************/
ostream & operator<<(ostream & os, RasterGraphic & RG)
{
	forward_list<GraphicElement>::iterator i;
	int count = 0;
	os << "RasterGraphic A" << endl << "Run the RasterGraphic" << endl;
	for (i = RG.GraphicElements.begin(); i != RG.GraphicElements.end(); ++i)
	{
		os << "GraphicElement #" << count << ": ";
		os << *i;
		count++;
	}
	os << endl << "Output finished" << endl;
	return os;
}
