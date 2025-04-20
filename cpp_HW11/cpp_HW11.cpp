
#include <glfwbgi.h>
#include <iostream>
#include <conio.h>

using namespace Graph;
using namespace std;

struct MinValue
{
    int index;
    int value;
};

struct Sun 
{
    int index = 0;
    short centerX,
        centerY,
        radiusX,
        radiusY,
        numOfRays;
    unsigned long color = Color::Orange;
};

void DrawForest();

void Task1();
void Task2_3();
void Task4();

/////////////////////////////////////////////////
void DrawTheSun(Sun&sun);
void DrawLand(short, short, short);
void DrawLake(short, short, short, short);
void DrawCloud(short, short, short, short);
void DrawMushroom(short, short, short, short);
int GenerateRandomNumber(int min = -100, int max = 100);
void PrintNumbersCollection(int*, int);
int GetMaxValueFromCollection(int*, int arrSize, int endIndex, int startIndex = 0);
MinValue GetMinValue(int*, int, int endIndex, int startIndex = 0);
void SwapArrayValues(int* arr, int, int, int); 
void SwapSuns(Sun* arr, int);
int GetIndexOfTheLeftSun(Sun* arr, int);
int GetIndexOfTheLowestSun(Sun* arr, int);
int GetIndexOfTheHighestSun(Sun* arr, int);
void IncraeseSizeOfTheSun(Sun&, short);
void DrawPlanets(short, short, short, short, short);

int main()
{
    //DrawForest();

    /*Task1();
    system("cls");*/
    //Task2_3();
    
    Task4();
    
}

void DrawForest()
{
    short resWidth = 1152,
        resHeight = 768;

    short landHeight = 320;

    Sun sun;
    sun.centerX = 150;
    sun.centerY = 150;
    sun.index = 0;
    sun.radiusX = 100;
    sun.radiusY = 100;
    sun.color = Color::Orange;
    sun.numOfRays = 30;

    if (!InitGraph(resWidth, resHeight, "Forest"))
    {
        cout << "There are some errors" << endl;
    }
    ClearDevice(Color::Blue);
    DrawTheSun(sun);
    DrawLand(resHeight - landHeight, resWidth, resHeight);
    DrawLake(resHeight - 100, resWidth - 400, 400, 200);
    DrawCloud(400, 150, resWidth - 600, 200);
    DrawMushroom(100, 550, 50, 80);
    DrawMushroom(160, 600, 40, 60);
    Graph::SwapBuffers();
    Graph::ReadKey();
}

void Task1()
{
    const int arrSize = 15;
    int numArr[arrSize] = {};
    int startIndex = 10;

    srand(time(0));

    for (int i = 0; i < arrSize; i++)
    {
        numArr[i] = GenerateRandomNumber();
    }

    PrintNumbersCollection(numArr, arrSize);

    MinValue min = GetMinValue(numArr, arrSize, arrSize - 1, startIndex);

    cout << "Min value: [" << min.index << "] - " << min.value << endl;
    _getch();

    //swap
    SwapArrayValues(numArr, arrSize, startIndex, min.index);
    PrintNumbersCollection(numArr,arrSize);
    system("cls");

    for (int i = 0; i < arrSize - 1; i++)
    {
        min = GetMinValue(numArr, arrSize, arrSize - 1, i);
        cout << "Min value: [" << min.index << "] - " << min.value << endl;
        _getch();
        SwapArrayValues(numArr, arrSize, i, min.index);
        PrintNumbersCollection(numArr, arrSize);
        system("cls");
    }
}

void Task2_3() 
{
    short resWidth = 1152,
        resHeight = 768;

    const int numberOfSuns = 8;

    if (!InitGraph(resWidth, resHeight, "Task2"))
    {
        cout << "There are some errors" << endl;
    }
    ClearDevice(Color::Blue);

    Sun suns[numberOfSuns] = {};

    short sunCenterX = 100,
        sunCenterY = 100,
        xStep = 150;

    for (int i = 0; i < numberOfSuns; i++)
    {
        suns[i].centerX = sunCenterX;
        suns[i].centerY = sunCenterY;
        suns[i].index = i;
        suns[i].radiusX = 50;
        suns[i].radiusY = 50;
        suns[i].numOfRays = 11+i;

        cout << "Sun " << i << " created!" << endl;
        DrawTheSun(suns[i]);
        sunCenterX += xStep;
    }

    //paint in green 3_1
    int leftSunIndex = GetIndexOfTheLeftSun(suns, numberOfSuns);

    suns[leftSunIndex].color = Color::Green;

    DrawTheSun(suns[leftSunIndex]);
    Graph::SwapBuffers();
    Graph::ReadKey();
    ClearDevice(Color::Blue);

    //resize all 3_2
    short pixels = 30;

    for (int i = 0; i < numberOfSuns; i++)
    {
        IncraeseSizeOfTheSun(suns[i],pixels);
        DrawTheSun(suns[i]);
    }
    Graph::SwapBuffers();
    Graph::ReadKey();
    ClearDevice(Color::Blue);
   
    //3_3 switch suns
    srand(time(0));
    for (int i = 0; i < numberOfSuns; i++)
    {
        suns[i].centerY += GenerateRandomNumber(-40, 250);
        DrawTheSun(suns[i]);
    }
    Graph::SwapBuffers();
    Graph::ReadKey();
    ClearDevice(Color::Blue);

    SwapSuns(suns, numberOfSuns);

    for (int i = 0; i < numberOfSuns; i++)
    {
        DrawTheSun(suns[i]);
    }

    Graph::SwapBuffers();
    Graph::ReadKey();
}

void Task4() 
{
    short resWidth = 1152,
        resHeight = 768;

    if (!InitGraph(resWidth, resHeight, "Forest"))
    {
        cout << "There are some errors" << endl;
    }
    ClearDevice(Color::Black);
    DrawPlanets(20, 400, 40, resWidth, resHeight);
    Graph::SwapBuffers();
    Graph::ReadKey();
}

////////////////////////////////////////////

void DrawTheSun(Sun & sun)
{
    FillEllipseSector(sun.centerX, sun.centerY, sun.radiusX, sun.radiusY, 0, 360, sun.color);
    SetLineWidth(5);
    float step = (float)360 / sun.numOfRays;

    float sector = 0;

    for (int i = 1; i <= sun.numOfRays; i++, sector+=step)
    {
        short x = sun.centerX + sun.radiusX*2 * cos(sector);
        short y = sun.centerY + sun.radiusY*2 * sin(sector);

        DrawLine(sun.centerX, sun.centerY, x, y, sun.color);
    }
}

void DrawLand(short landHeight, short landWidth, short zeroY)
{
    FillRectangle(0, landHeight, landWidth, zeroY, Color::Green);
}

void DrawLake(short centerX, short centerY, short radiusX, short radiusY)
{
    FillEllipseSector(centerX, centerY, radiusX, radiusY, 0, 360, Color::DarkBlue);
}

void DrawCloud(short length, short height, short centerX, short centerY)
{
    short smallRadiusX = floor(length / 6);
    short mediumRadiusX = floor(length / 4);
    short larrgeRadiusX = floor(length / 3);

    short smallRadiusY = floor(height / 4);
    short mediumRadiusY = floor(height / 3);
    short larrgeRadiusY = floor(height / 2);

    FillEllipseSector(centerX, centerY, larrgeRadiusX, larrgeRadiusY, 0, 360, Color::WhiteSmoke);
    FillEllipseSector(centerX-smallRadiusX*2, centerY, smallRadiusX, smallRadiusY, 0, 360, Color::WhiteSmoke);
    FillEllipseSector(centerX+mediumRadiusX, centerY, mediumRadiusX, mediumRadiusY, 0, 360, Color::WhiteSmoke);
}

void DrawMushroom(short baseX, short baseY, short widthHead, short height)
{
    short legWidth = floor(widthHead / 3) * 2;
    short headHeight = floor(legWidth / 2);
    short legHeight = height - headHeight;
    
    FillRectangle(baseX, baseY, baseX + legWidth, baseY + legHeight,Color::Wheat);
    FillEllipseSector(baseX+floor(legWidth/2) ,baseY, 
        headHeight*3, headHeight*2, 0, 180, Color::DarkBrown);
}

int GenerateRandomNumber(int minValue, int maxValue)
{
    return rand() % (maxValue - minValue + 1) + minValue;
}

void PrintNumbersCollection(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << endl;
    }
    _getch();
}

int GetMaxValueFromCollection(int* arr, int arrSize, int endIndex, int startIndex)
{
    int max = arr[startIndex];

    for (int i = startIndex+1; i < arrSize; ++i)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    return max;
}

MinValue GetMinValue(int* arr, int arrSize, int endIndex, int startIndex)
{
    MinValue min;
    min.value = arr[startIndex];
    min.index = startIndex;

    for (int i = startIndex + 1; i < arrSize; ++i)
    {
        if (min.value > arr[i])
        {
            min.value = arr[i];
            min.index = i;
        }
    }

    return min;
}

void SwapArrayValues(int * arr, int size, int firstIndex, int secondIndex)
{
    int buffer = arr[firstIndex];
    arr[firstIndex] = arr[secondIndex];
    arr[secondIndex] = buffer;
}

void SwapSuns(Sun* arr, int size)
{
    int firstIndex = GetIndexOfTheLowestSun(arr, size);
    int secondIndex = GetIndexOfTheHighestSun(arr, size);

    short buffer = arr[firstIndex].centerY;
    arr[firstIndex].centerY = arr[secondIndex].centerY;
    arr[secondIndex].centerY = buffer;
}

int GetIndexOfTheLeftSun(Sun* arr, int size)
{
    int smallestXindex = 0;

    for(int i = 1; i < size; i++)
    { 
        if (arr[i].centerX < arr[smallestXindex].centerX)
        {
            smallestXindex = i;
        }
    }
    return smallestXindex;
}

int GetIndexOfTheLowestSun(Sun* arr, int size)
{
    int biggestYindex = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i].centerY > arr[biggestYindex].centerY)
        {
            biggestYindex = i;
        }
    }
    return biggestYindex;
}
int GetIndexOfTheHighestSun(Sun* arr, int size)
{
    int smallestYindex = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i].centerY < arr[smallestYindex].centerY)
        {
            smallestYindex = i;
        }
    }
    return smallestYindex;
}

void IncraeseSizeOfTheSun(Sun&sun,short pixels)
{
    sun.radiusX += pixels;
    sun.radiusY += pixels;
}

void DrawPlanets(short numOfPlanets, short maxR, short minR, short scrWidth, short scrHeight)
{
    const int numOfCollors = 15;

    unsigned long colors[numOfCollors] = { Color::Red, Color::Blue, Color::Yellow, Color::Orange,
    Color::LightSeaGreen, Color::White, Color::Gray, Color::Brown, Color::Purple, Color::Aquamarine, 
    Color:: GreenYellow, Color:: GrayTeaGreen, Color:: Saffron, Color:: SchoolBusYellow, Color:: LightCoral};

    short step = (maxR - minR) / numOfPlanets;

    srand(time(0));

    for (short i = 0; i < numOfPlanets; i++)
    {
        int colorIndex = GenerateRandomNumber(0, 15);
        FillEllipseSector(scrWidth / 2, scrHeight / 2, maxR, maxR, 0, 360, colors[colorIndex]);

        if (maxR >= minR)
            maxR -= step;  
    }
}