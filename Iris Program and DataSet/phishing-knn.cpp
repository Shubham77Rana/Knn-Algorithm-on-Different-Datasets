#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <climits>
#include <cmath>
#include <string.h>

#define  DATA 150
#define  ATTRIBUTES 5
#define  TRAINING_DATA 120
#define  TESTING_DATA  30
#define  CLASSES 3
#define  START_KNN 1
#define  END_KNN 110

using namespace std;

struct class_distance
{
	float distance;
	float classes;
};

float actual_data[DATA][ATTRIBUTES];
float train_data[TRAINING_DATA][ATTRIBUTES];
float test_data[TESTING_DATA][ATTRIBUTES];
class_distance distance_array[TRAINING_DATA];

void randomize ( int arr[], int n )
{
    srand ( time(NULL) );
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(arr[i], arr[j]);
    }
}

void intialize_random_array(int random_array[])
{
        for(int i=0;i<DATA;i++)
                random_array[i] = i;
        randomize(random_array, DATA);
}

float distance(int index)
{
	for(int i=0;i<TRAINING_DATA;i++)
	{
		float d = 0;
		for(int j=0;j<ATTRIBUTES-1;j++)
		{
			d += pow(train_data[i][j] - test_data[index][j], 2);
		}
		distance_array[i].classes = train_data[i][4];
		distance_array[i].distance = sqrt(d);
	}
}

bool compare(class_distance a, class_distance b)
{
	return a.distance < b.distance;
}

int best_knn_evaluator(int KNN, int random_array[])
{
    float accuracy = 0;
    for(int i=0;i<TESTING_DATA;i++)
    {
	distance(i);
	int count[CLASSES] = {0};
	sort(distance_array, distance_array+TRAINING_DATA, compare);
	for(int j=0;j<KNN;j++)
	{
		for(int x=0;x<CLASSES;x++)
		{
			if(distance_array[j].classes == x)
			{
				count[x]++;
				break;
			}
		}
	}

	int max = INT_MIN, max_index;
	for(int x = 0;x<CLASSES;x++)
	{
		if(max < count[x])
		{
			max = count[x];
			max_index = x;
		}
	}

	if(max_index == test_data[i][4])
		accuracy ++;
     }

     return accuracy;
}

int main()
{
    int random_array[DATA];
    intialize_random_array(random_array);

    FILE *data = fopen("iris.txt","r");
    int index = 0;
    float feature[ATTRIBUTES];
    char str[100];

    while(fscanf(data, "%f,%f,%f,%f,%s", &feature[0],
    &feature[1], &feature[2], &feature[3], str) != EOF && index < DATA)
    {
	actual_data[index][0] = feature[0];
	actual_data[index][1] = feature[1];
	actual_data[index][2] = feature[2];
	actual_data[index][3] = feature[3];

	if(!strcmp(str, "Iris-setosa"))
		actual_data[index][4] = 0;
	else if(!strcmp(str, "Iris-versicolor"))
		actual_data[index][4] = 1;
	else
		actual_data[index][4] = 2;
			

	index++;
    }

    index = 0;
    while(index < TRAINING_DATA)
    {
	train_data[index][0] = actual_data[random_array[index]][0];
	train_data[index][1] = actual_data[random_array[index]][1];
	train_data[index][2] = actual_data[random_array[index]][2];
	train_data[index][3] = actual_data[random_array[index]][3];
	train_data[index][4] = actual_data[random_array[index]][4];

	index++;
    }

    int test_index = 0;
    while(index < DATA)
    {
	test_data[test_index][0] = actual_data[random_array[index]][0];
	test_data[test_index][1] = actual_data[random_array[index]][1];
	test_data[test_index][2] = actual_data[random_array[index]][2];
	test_data[test_index][3] = actual_data[random_array[index]][3];
	test_data[test_index][4] = actual_data[random_array[index]][4];

	test_index++;
	index++;
    }

    float max_knn, max_accuracy;
    for(int i=START_KNN;i<=END_KNN;i++)
    {
        float temp_accuracy = best_knn_evaluator(i, random_array); 
	if(max_accuracy < temp_accuracy)
	{
		max_accuracy = temp_accuracy;
                max_knn = i; 
                cout << "New KNN found at accuracy " << (max_accuracy/TESTING_DATA)*100 << endl;
	}
    }

    cout << "Maximum Accuracy is " << (max_accuracy/TESTING_DATA)*100 << endl;
    cout << "Value of Optimum KNN is "<< max_knn << endl;

    return 0;
}
