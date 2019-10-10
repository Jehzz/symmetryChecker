#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
    float x;
    float y;
};


int main()
{
    int x, y;
    float xOrigin, yOrigin;
    vector<Point> array;
    Point inPoint;
    ifstream input;
    string inputFileName;
    Point minPoint;
    Point maxPoint;

    //Input text location
    inputFileName = "input.txt";

    //Init and open the Input stream
    input.open(inputFileName);

    //Read out line by line
    while (input >> x >> y)
    {
        printf ("%d %d \n", x, y);
        inPoint.x = x;
        inPoint.y = y;
        array.push_back(inPoint);

    }
    input.close();


    float maxX, maxY, minX, minY;
    maxX = array[0].x;
    minX = array[0].x;
    maxY = array[0].y;
    minY = array[0].y;

    //Find corners
    for(int i = 0; i < array.size(); i++){
        if (array[i].x > maxX) maxX = array[i].x;
        if (array[i].x < minX) minX = array[i].x;
        if (array[i].y > maxY) maxY = array[i].y;
        if (array[i].y < minY) minY = array[i].y;
    }


    //Calculate geometric mean
    xOrigin = (minX+maxX) / 2.0f;
    yOrigin = (minY+maxY) / 2.0f;
    printf("Origin is (%f, %f) \n ", xOrigin, yOrigin);


    //Iterate through array and test points. I believe I can speed this up significantly with the use of hashmaps and directly checking for pairs, rather than iterating through and testing.
    for (int i = 0; i < array.size(); i++){

        printf("===ITERATING=== \n");
        bool vertsymmetry = false;
        bool hrzntlsymmetry = false;

        printf("Current point is : (%f %f)\n", array[i].x, array[i].y);
        if (array[i].x == xOrigin){
            printf("on horizontal symmetry line. check hrznt \n");
            hrzntlsymmetry = true;
        }
        if (array[i].y == yOrigin){
            printf("on vertical symmetry line. check hrzt \n");
            vertsymmetry = true;
        }
        //if not on origin of symmetry, test if symmetric point exists on both axes
        Point vertTarget = {array[i].x, (yOrigin - (array[i].y- yOrigin))};
        Point horizontalTarget = {(xOrigin - (array[i].x- xOrigin)), array[i].y};

        printf("Vertical target is (%f %f)\n",vertTarget.x, vertTarget.y);
        printf("Horizontal target is (%f %f)\n", horizontalTarget.x, horizontalTarget.y);



        //iterate and check each point.
        for (int j = 0; j < array.size(); j++) {
            printf("checking point %f %f \n", array[j].x, array[j].y);
            if (array[j].x == vertTarget.x && array[j].y == vertTarget.y ) {
                printf("vertical pair found \n");
                vertsymmetry = true;
            }
            if (array[j].x == horizontalTarget.x && array[j].y == horizontalTarget.y ){
                hrzntlsymmetry = true;
                printf("horizontal pair found \n \n");
            }
            if(hrzntlsymmetry&&vertsymmetry){
                printf("point is symmetric \n \n");
                break;
            }
        }


        if(!(hrzntlsymmetry&&vertsymmetry)){
            printf("asymetric point found. pattern is asymmetric");
            return 0;
        }


    }

    /*CODE TO TEST THAT ARRAY VALUES ARE CORRECT
    for (int i = 0; i < array.size(); i++){
        printf("%d", array[i].y );
    }
    */

    //if code reaches here, pattern is symmetric
    printf("Set of points is symmetric");
    return 0;
}