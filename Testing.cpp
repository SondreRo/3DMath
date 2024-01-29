
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <vector>

std::ofstream dataFile("Oppgave3.txt");
class Vertex
{
public:
	// Position Data
	float x;
	float y;
	float z;

	// Color Data
	float r;
	float g;
	float b;
};


 //f(x) = 4x^4 + 8x^2 + x + 2
float func(float x)
{
	return 4 * x * x * x * x + 8 * x * x + x + 2;
}

float funcDer(float x)
{
	return 16 * x * x * x + 16 * x + 1;
}

float funcOther(float x)
{
	return sin(x);
}

float planeFunc(float x, float y)
{
	return cos(x) + sin(y) + x + y;
}


std::vector<std::shared_ptr<Vertex>> GetDataPoints(float start, float end, float step)
{
	std::vector<std::shared_ptr<Vertex>> tempVector;
	double it = start;
	int AmountOfLines = 0;
	float x0{0}, x1{0}, y0{0}, y1{0};

	while (it < end + step)
	{
		std::shared_ptr<Vertex> tempVertex = std::make_shared<Vertex>();
		x0 = it;
		y0 = func(it);
		float Diff = funcDer(it);
		tempVertex->x = x0;
		tempVertex->y = y0;
		tempVertex->z = 1;
		if (Diff > 0)
		{
			tempVertex->r = 0;
			tempVertex->g = 1;
			tempVertex->b = 0;
		}
		else
		{
			tempVertex->r = 1;
			tempVertex->g = 0;
			tempVertex->b = 0;
		}
		tempVector.push_back(tempVertex);
		x1 = x0;
		y1 = y0;
		it += step;
		AmountOfLines++;
	}
	return tempVector;
}

std::vector<std::shared_ptr<Vertex>> GetDataPoints3D(float start, float end, float step)
{
	std::vector<std::shared_ptr<Vertex>> tempVector;
	double it = start;
	int AmountOfLines = 0;

	while (it < end + step)
	{
		std::shared_ptr<Vertex> tempVertex = std::make_shared<Vertex>();

		float x = cos(it) * it / 5;
		float z = sin(it) * it / 5;
		float y = it / 3;


		
		tempVertex->x = x;
		tempVertex->y = y;
		tempVertex->z = z;
		
		tempVertex->r = 0;
		tempVertex->g = z/40+0.5;
		tempVertex->b = 0;
		
	
		tempVector.push_back(tempVertex);
		it += step;
		AmountOfLines++;
	}
	return tempVector;
}

std::vector<std::shared_ptr<Vertex>> GetDataPoints3DPlane(float xStart, float xEnd, float yStart, float yEnd, float step)
{
	std::vector<std::shared_ptr<Vertex>> tempVector;
	int AmountOfLines = 0;

	float x = xStart;
	float y = yStart;
	float z = 0;
	
	

	while (x < xEnd + step)
	{
		while (y < yEnd + step)
		{
			std::shared_ptr<Vertex> tempVertex = std::make_shared<Vertex>();
			z = planeFunc(x, y);
			tempVertex->x = x;
			tempVertex->y = y;	
			tempVertex->z = z;
			tempVertex->r = 0;
			tempVertex->g = z / 40 + 0.5;
			tempVertex->b = 0;
			tempVector.push_back(tempVertex);

			x += step;
			z = planeFunc(x, y);
			tempVertex->x = x;
			tempVertex->y = y;
			tempVertex->z = z;
			tempVertex->r = 0;
			tempVertex->g = z / 40 + 0.5;
			tempVertex->b = 0;
			tempVector.push_back(tempVertex);
			x -= step;
			y += step;
			AmountOfLines += 2;
		}
		y = yStart;
		x += step * 2;
	}


	return tempVector;
}


int main()
{
	std::cout << std::fixed << std::setprecision(3);
	dataFile << std::fixed << std::setprecision(3);
	if (dataFile)
	{

		std::vector<std::shared_ptr<Vertex>> MyVertexVector;
		//MyVertexVector = GetDataPoints(-6, 6, 0.5);
		//MyVertexVector = GetDataPoints3D(0, 100, 0.05);
		MyVertexVector = GetDataPoints3DPlane(0,10,0,10,.5);
		dataFile << MyVertexVector.size() << std::endl;
		for (int i{}; i < MyVertexVector.size(); i++)
		{
			dataFile << 
				MyVertexVector[i]->x << ", " << 
				MyVertexVector[i]->y << ", " << 
				MyVertexVector[i]->z << ", " << 
				MyVertexVector[i]->r << ", " << 
				MyVertexVector[i]->g << ", " << 
				MyVertexVector[i]->b << std::endl;
			
		}
		dataFile.close();
	}

}
