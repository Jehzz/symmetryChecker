#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
    float x;
    float y;
};

int main() {
    int x, y;
    float xOrigin, yOrigin;
    float maxX, maxY, minX, minY;

    vector<Point> array;
    Point inPoint;
    ifstream input;
    string inputFileName = "input.txt";
    input.open(inputFileName);

    cout
            << "This program reads ordered pairs arranged one-per-line from the file input.txt, and determines if the set is symmetrical"
            << endl;

    if (!input)
    {
        cerr << "Could not open input file " << "\n";
        return 1;
    }

    //Read the input stream line by line, assigning values to a Point and storing it
    while (input >> x >> y) {
        printf("%d %d \n", x, y);
        inPoint.x = x;
        inPoint.y = y;
        array.push_back(inPoint);
    }
    input.close();

    //Find the extremes of the pattern
    maxX = array[0].x;
    minX = array[0].x;
    maxY = array[0].y;
    minY = array[0].y;
    for (int i = 0; i < array.size(); i++) {
        if (array[i].x > maxX) maxX = array[i].x;
        if (array[i].x < minX) minX = array[i].x;
        if (array[i].y > maxY) maxY = array[i].y;
        if (array[i].y < minY) minY = array[i].y;
    }

    //Calculate geometric mean
    xOrigin = (minX + maxX) / 2.0f;
    yOrigin = (minY + maxY) / 2.0f;
    printf("Origin is (%f, %f) \n ", xOrigin, yOrigin);

    //Iterate through array and test points. I believe I can speed this up significantly with the use of hashmaps and directly checking for pairs, rather than iterating through and testing.
    for (int i = 0; i < array.size(); i++) {    //for each point
        //printf("===ITERATING=== \n");
        bool vertsymmetry = false;              //reset checks
        bool hrzntlsymmetry = false;

        //printf("Current point is : (%f %f)\n", array[i].x, array[i].y);
        if (array[i].x == xOrigin) {
            //printf("Point is on horizontal symmetry line \n");
            hrzntlsymmetry = true;
        }
        if (array[i].y == yOrigin) {
            //printf("Point is on vertical symmetry line \n");
            vertsymmetry = true;
        }

        //Calculate where a symmetric pair would be if it exists. A potential pair across the vertical axis has the same X value, but Y value reflected across axis of symmetry ((yOrigin - (array[i].y - yOrigin))
        Point vertTarget = {array[i].x, (yOrigin - (array[i].y - yOrigin))};
        Point horizontalTarget = {(xOrigin - (array[i].x - xOrigin)), array[i].y};

        //Locate the points of symmetry. Can be improved with a Hashmap. Algorithm performance is o(n^2) because of this loop
        for (int j = 0; j < array.size(); j++) {
            //printf("checking point %f %f \n", array[j].x, array[j].y);
            if (array[j].x == vertTarget.x && array[j].y == vertTarget.y) {
                //printf("vertically symmetric point found \n");
                vertsymmetry = true;
            }
            if (array[j].x == horizontalTarget.x && array[j].y == horizontalTarget.y) {
                hrzntlsymmetry = true;
                //printf("horizontally symmetric point found \n \n");
            }
            if (hrzntlsymmetry && vertsymmetry) {
                //printf("point is symmetric \n \n");   //no need to continue scanning, so break
                break;
            }
        }

        //Check if point is asymmetric to the rest of the pattern
        if (!(hrzntlsymmetry && vertsymmetry)) {
            printf("asymmetric point found. pattern is asymmetric");
            return 0;
        }

    }

    //if code reaches here, all points are symmetric, so pattern must be symmetric
    printf("Set of points is symmetric");
    return 0;
}