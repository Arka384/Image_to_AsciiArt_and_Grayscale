#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

std::string fileName, source;
int choice = 0;
void input(void);
void image_to_Ascii(sf::Image);
void image_to_gray(sf::Image);

int main()
{
	input();
	sf::Image image;
	image.loadFromFile(source);

	if (choice == 1)
		image_to_Ascii(image);
	if (choice == 2)
		image_to_gray(image);

	return 0;
}

void input()
{
	std::cout << "\n1 -> Convert image to ASCII Art:\n2 -> Convert image to Grayscale image:";
	std::cout << "\nYour choice: ";
	std::cin >> choice;

	std::cout << "\nThe file must be inside Images folder and low resolution";
	std::cout << "\nEnter the file name: ";
	std::cin >> fileName;
	source = "Images/";
	source.append(fileName);
}

void image_to_Ascii(sf::Image image)
{
	sf::Vector2u imageSize = image.getSize();
	sf::Color pixel;
	int grayscaleIntensity = 0;
	char map[10] = ".,:;ox%#@";
	std::ofstream output("Output/output.txt");
	int r, g, b;

	for (int i = 0; i < imageSize.y; i++) {
		for (int j = 0; j < imageSize.x; j++) {
			pixel = image.getPixel(j, i);
			r = pixel.r;
			g = pixel.g;
			b = pixel.b;
			grayscaleIntensity = ((0.2126*r) + (0.7125*g) + (0.0722*b));
			output << map[(255 - grayscaleIntensity) * 10 / 256];
			output << " ";
		}
		output << "\n";
	}
	std::cout << "\nSuccessfully Converted..";
	output.close();
	sf::sleep(sf::Time(sf::seconds(2)));
}

void image_to_gray(sf::Image image)
{
	sf::Vector2u imageSize = image.getSize();
	sf::Color pixel;
	int grayscaleIntensity = 0;
	double newIntensity = 0.0, new_color = 0.0;
	int r, g, b;

	for (int i = 0; i < imageSize.y; i++) {
		for (int j = 0; j < imageSize.x; j++) {
			pixel = image.getPixel(j, i);
			r = pixel.r;
			g = pixel.g;
			b = pixel.b;
			grayscaleIntensity = ((0.2126*r) + (0.7125*g) + (0.0722*b));
			newIntensity = (double)grayscaleIntensity / 255;

			if (newIntensity <= 0.0031308)
				new_color = newIntensity * 12.92;
			else
				new_color = (pow(newIntensity, (1 / 2.4)) * 1.055) - 0.055;

			image.setPixel(j, i, sf::Color(200, 200, 200, new_color * 255));
		}
	}
	std::string des = "Output/";
	des.append(fileName);
	image.saveToFile(des);
	std::cout << "\nSuccessfully Converted..";
	sf::sleep(sf::Time(sf::seconds(2)));
}